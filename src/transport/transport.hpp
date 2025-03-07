/*
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   Product name: redemption, a FLOSS RDP proxy
   Copyright (C) Wallix 2012
   Author(s): Christophe Grosjean

   Transport layer abstraction
*/


#pragma once

#include <sys/time.h>
#include <cstdint>
#include <cstddef>

#include "cxx/cxx.hpp"
#include "core/error.hpp"
#include "utils/invalid_socket.hpp"
#include "utils/log.hpp"
#include "utils/sugar/noncopyable.hpp"
#include "utils/sugar/std_stream_proto.hpp"
#include "utils/sugar/bytes_view.hpp"

#include "configs/autogen/enums.hpp"


using std::size_t; /*NOLINT*/

class ServerNotifier;

struct TLSClientParams
{
    uint32_t tls_min_level = 0;
    uint32_t tls_max_level = 0;
    bool show_common_cipher_list = false;
    std::string cipher_string;
};


class Transport : noncopyable
{
protected:
    uint32_t seqno = 0;

public:
    explicit Transport() = default;

    Transport(const Transport &) = delete;
    Transport& operator=(const Transport &) = delete;

    virtual ~Transport() = default;

    [[nodiscard]] uint32_t get_seqno() const
    { return this->seqno; }

    enum class [[nodiscard]] TlsResult : uint8_t { Ok, Fail, Want, WaitExternalEvent, };
    virtual TlsResult enable_client_tls(
        ServerNotifier & server_notifier, const TLSClientParams & /*tls_client_params*/)
    {
        // default enable_tls do nothing
        (void)server_notifier;
        return TlsResult::Fail;
    }

    virtual void enable_server_tls(const char * certificate_password,
        const char * ssl_cipher_list, uint32_t tls_min_level, uint32_t tls_max_level, bool show_common_cipher_list)
    {
        // default enable_tls do nothing
        (void)certificate_password;
        (void)ssl_cipher_list;
        (void)tls_min_level;
        (void)tls_max_level;
        (void)show_common_cipher_list;
    }

    [[nodiscard]] virtual array_view_const_u8 get_public_key() const
    {
        return {};
    }

    enum class [[nodiscard]] Read : bool { Eof, Ok };

    /// recv_boom read len bytes into buffer or throw an Error
    /// if EOF is encountered at that point it's also an error and
    /// it throws Error(ERR_TRANSPORT_NO_MORE_DATA)
    writable_bytes_view recv_boom(writable_byte_ptr buffer, size_t len)
    {
        if (Read::Eof == this->atomic_read(buffer, len)) {
            LOG(LOG_ERR, "Transport::recv_boom (1): Failed to read transport!");
            throw Error(ERR_TRANSPORT_NO_MORE_DATA);
        }
        return {buffer, len};
    }

    writable_bytes_view recv_boom(writable_bytes_view buffer)
    {
        if (Read::Eof == this->atomic_read(buffer.as_u8p(), buffer.size())) {
            LOG(LOG_ERR, "Transport::recv_boom (2): Failed to read transport!");
            throw Error(ERR_TRANSPORT_NO_MORE_DATA);
        }
        return buffer;
    }

    /// atomic_read either read len bytes into buffer or throw an Error
    /// returned value is either true is read was successful
    /// or false if nothing was read (End of File reached at block frontier)
    /// if an exception is thrown buffer is dirty and may have been modified.
    REDEMPTION_CXX_NODISCARD
    Read atomic_read(writable_byte_ptr buffer, size_t len)
    {
        return this->do_atomic_read(buffer.as_u8p(), len);
    }

    REDEMPTION_CXX_NODISCARD
    Read atomic_read(writable_bytes_view buffer)
    {
        return this->do_atomic_read(buffer.as_u8p(), buffer.size());
    }

    // TODO returns writable_bytes_view
    REDEMPTION_CXX_NODISCARD
    size_t partial_read(writable_byte_ptr buffer, size_t len)
    {
        return this->do_partial_read(buffer.as_u8p(), len);
    }

    // TODO returns writable_bytes_view
    REDEMPTION_CXX_NODISCARD
    size_t partial_read(writable_bytes_view buffer)
    {
        return this->do_partial_read(buffer.as_u8p(), buffer.size());
    }

    void send(byte_ptr buffer, size_t len)
    {
        this->do_send(buffer.as_u8p(), len);
    }

    void send(bytes_view buffer)
    {
        this->do_send(buffer.as_u8p(), buffer.size());
    }

    virtual void flush()
    {}

    virtual void seek(int64_t offset, int whence)
    {
        (void)offset;
        (void)whence;
        throw Error(ERR_TRANSPORT_SEEK_NOT_AVAILABLE);
    }

private:
    // note: `func(buf, len)` derived function shadows `f(array)` function base.
    // do_*() function resolves this problem

    /// Atomic read read exactly the amount of data requested or return an error
    /// @see atomic_read
    virtual Read do_atomic_read(uint8_t * buffer, size_t len)
    {
        (void)buffer;
        (void)len;
        throw Error(ERR_TRANSPORT_INPUT_ONLY_USED_FOR_RECV);
    }

    virtual size_t do_partial_read(uint8_t * buffer, size_t len)
    {
        (void)buffer;
        (void)len;
        throw Error(ERR_TRANSPORT_INPUT_ONLY_USED_FOR_RECV);
    }

    virtual void do_send(const uint8_t * buffer, size_t len)
    {
        (void)buffer;
        (void)len;
        throw Error(ERR_TRANSPORT_OUTPUT_ONLY_USED_FOR_SEND);
    }

public:
    virtual void set_trace_send(bool /*send_trace*/) {}

    virtual void set_trace_receive(bool /*receive_trace*/) {}

    virtual bool disconnect()
    {
        return true;
    }

    virtual bool connect()
    {
        return true;
    }

    virtual void timestamp(timeval now)
    { (void)now; }

    /* Some transports are splitted between sequential discrete units
     * (it may be block, chunk, numbered files, directory entries, whatever).
     * Calling next means flushing the current unit and start the next one.
     * seqno countains the current sequence number, starting from 0. */
    virtual bool next()
    {
        this->seqno++;
        return true;
    }

    [[nodiscard]] virtual int get_fd() const { return INVALID_SOCKET; }
};


REDEMPTION_OSTREAM(out, Transport::Read status)
{
    return out << (status == Transport::Read::Ok ? "Read::Ok" : "Read::Eof");
}

struct InTransport
{
    InTransport(Transport & t)
      : t(t)
    {}

    void recv_boom(writable_byte_ptr buffer, size_t len) { this->t.recv_boom(buffer, len); }
    void recv_boom(writable_bytes_view buffer) { this->t.recv_boom(buffer); }

    REDEMPTION_CXX_NODISCARD
    Transport::Read atomic_read(writable_byte_ptr buffer, size_t len) { return this->t.atomic_read(buffer, len); }

    REDEMPTION_CXX_NODISCARD
    size_t partial_read(writable_byte_ptr buffer, size_t len) { return this->t.partial_read(buffer, len); }

    [[nodiscard]] uint32_t get_seqno() const { return this->t.get_seqno(); }

    Transport::TlsResult enable_client_tls(ServerNotifier & server_notifier, const TLSClientParams & tls_client_params)
    {
        return this->t.enable_client_tls(server_notifier, tls_client_params);
    }

    void enable_server_tls(const char * certificate_password, const char * ssl_cipher_list, uint32_t tls_min_level, uint32_t tls_max_level, bool show_common_cipher_list)
    { this->t.enable_server_tls(certificate_password, ssl_cipher_list, tls_min_level, tls_max_level, show_common_cipher_list); }

    [[nodiscard]] array_view_const_u8 get_public_key() const { return this->t.get_public_key(); }

    void seek(int64_t offset, int whence) { this->t.seek(offset, whence); }
    bool disconnect() { return this->t.disconnect(); }
    bool connect() { return this->t.connect(); }
    void timestamp(timeval now) { this->t.timestamp(now); }
    bool next() { return this->t.next(); }
    [[nodiscard]] int get_fd() const { return this->t.get_fd(); }

    REDEMPTION_ATTRIBUTE_DEPRECATED
    [[nodiscard]] Transport & get_transport() const { return this->t; }

private:
    Transport & t;
};

struct OutTransport
{
    OutTransport(Transport & t)
      : t(t)
    {}

    void send(byte_ptr buffer, size_t len) { this->t.send(buffer, len); }
    void send(bytes_view buffer) { this->t.send(buffer); }

    [[nodiscard]] uint32_t get_seqno() const { return this->t.get_seqno(); }

    Transport::TlsResult enable_client_tls(ServerNotifier & server_notifier, const TLSClientParams & tls_client_params)
    {
        return this->t.enable_client_tls(server_notifier, tls_client_params);
    }

    void enable_server_tls(const char * certificate_password, const char * ssl_cipher_list, uint32_t tls_min_level, uint32_t tls_max_level, bool show_common_cipher_list)
    { this->t.enable_server_tls(certificate_password, ssl_cipher_list, tls_min_level, tls_max_level, show_common_cipher_list); }

    [[nodiscard]] array_view_const_u8 get_public_key() const { return this->t.get_public_key(); }

    void seek(int64_t offset, int whence) { this->t.seek(offset, whence); }
    bool disconnect() { return this->t.disconnect(); }
    bool connect() { return this->t.connect(); }
    void timestamp(timeval now) { this->t.timestamp(now); }
    bool next() { return this->t.next(); }
    [[nodiscard]] int get_fd() const { return this->t.get_fd(); }

    // TODO REDEMPTION_ATTRIBUTE_DEPRECATED
    [[nodiscard]] Transport & get_transport() const { return this->t; }

private:
    Transport & t;
};
