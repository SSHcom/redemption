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
   Copyright (C) Wallix 2018
   Author(s): David Fort
*/

#pragma once

#include <chrono>
#include <memory>
#include <vector>
#include <string>

#include "transport/recorder_transport.hpp"
#include "transport/file_transport.hpp"
#include "utils/sugar/unique_fd.hpp"


/**
 *    @brief a transport that will replay a full capture
 */
class ReplayTransport : public Transport
{
public:
    enum class FdType : bool { Timer, AlwaysReady };
    enum class UncheckedPacket : uint8_t { None, Send };
    enum class FirstPacket : bool { DisableTimer, EnableTimer };

    ReplayTransport(
        const char* fname, const char *ip_address, int port,
        TimeObj& timeobj, FdType fd_type = FdType::Timer,
        FirstPacket first_packet = FirstPacket::DisableTimer,
        UncheckedPacket unchecked_packet = UncheckedPacket::None);

    ~ReplayTransport();

    [[nodiscard]] array_view_const_u8 get_public_key() const override;

    TlsResult enable_client_tls(ServerNotifier & server_notifier, const TLSClientParams & tls_client_params) override;

    void enable_server_tls(const char * certificate_password,
        const char * ssl_cipher_list, uint32_t tls_min_level, uint32_t tls_max_level, bool show_common_cipher_list) override;

    bool disconnect() override;
    bool connect() override;

    [[nodiscard]] int get_fd() const override { return this->fd.fd(); }

    [[nodiscard]] std::vector<std::string> const& get_infos() const noexcept { return this->infos; }

private:
    using PacketType = RecorderFile::PacketType;

    void reschedule_timer();

    size_t do_partial_read(uint8_t * buffer, size_t len) override;

    Read do_atomic_read(uint8_t * buffer, size_t len) override;

    void do_send(const uint8_t * const buffer, size_t len) override;

    void read_timer();

    void cleanup_data(std::size_t len, PacketType type);

    std::chrono::milliseconds prefetchForTimer();

    /** @brief a chunk of capture file */
    struct Data
    {
        std::unique_ptr<uint8_t[]> data;
        size_t size;
        PacketType type;
        std::chrono::milliseconds time;

        [[nodiscard]] array_view_const_u8 av() const noexcept;
    };

    Data *read_single_chunk();
    size_t searchAndPrefetchFor(PacketType kind);

private:
    long long count_packet = 0;

    TimeObj& timeobj;
    std::chrono::milliseconds start_time;

    InFileTransport in_file;
    const unique_fd fd;
    const FdType fd_type;
    FdType fd_current_type;
    const UncheckedPacket unchecked_packet;

    std::vector<Data> mPrefetchQueue;
    size_t data_in_pos;
    size_t data_out_pos;

    struct Key
    {
        std::unique_ptr<uint8_t[]> data;
        size_t size = 0;
    };
    Key public_key;

    std::vector<std::string> infos;
};
