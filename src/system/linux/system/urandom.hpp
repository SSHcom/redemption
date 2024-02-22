/*
SPDX-FileCopyrightText: 2023 Wallix Proxies Team

SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "core/error.hpp"
#include "utils/log.hpp"
#include "utils/random.hpp"

#include <limits>

#ifndef COMPAT_CENTOS7
#include <sys/random.h>


class URandom final : public Random
{
public:
    void random(writable_bytes_view buf) override
    {
        uint8_t* data = buf.data();
        size_t len = buf.size();
        while (len) {
#if defined(__sun) && defined(__SVR4)
            /* On Solaris, getrandom() is limited to returning up to 1024 bytes. */
            size_t len_max = 1024;
#else
            size_t len_max = std::numeric_limits<ssize_t>::max();
#endif
            // TODO This is basically a blocking read, we should provide timeout management and behaviour
            ssize_t n = getrandom(data, len < len_max ? len : len_max, 0);
            if (REDEMPTION_UNLIKELY(n < 0)) {
                if (errno == EINTR) {
                    continue;
                }
                // ignore errno == EAGAIN because GRND_NONBLOCK flag is not used
                LOG(LOG_ERR, "random source failed to provide random data [%s]", strerror(errno));
                throw Error(ERR_RANDOM_SOURCE_FAILED);
            }
            data += n;
            len -= n;
        }
    }
};
#else // COMPAT_CENTOS7
#include <cstdio>

const size_t RAND_BUF_SIZE = 1024;

class URandom final : public Random
{
public:
    URandom() {
        std::FILE* f = std::fopen("/dev/urandom", "r");
        if (!f) {
            LOG(LOG_ERR, "failed to open /dev/urandom");
            throw Error(ERR_RANDOM_SOURCE_FAILED);
        }
        LOG(LOG_INFO, "opened /dev/urandom");
        _devRandom = f;
        _bufSize = 0;
    }

    ~URandom() {
        LOG(LOG_INFO, "closed /dev/urandom");
        std::fclose(_devRandom);
    }

    void random(writable_bytes_view buf) override {
        uint8_t* data = buf.data();
        size_t len = buf.size();
        size_t written = 0;

        while (written < len) {
            if (_bufSize == 0) {
                size_t n = fread(_buf, sizeof(uint8_t), RAND_BUF_SIZE, _devRandom);
                if (n != RAND_BUF_SIZE) {
                    LOG(LOG_ERR, "random source failed to provide random data [%s]", strerror(errno));
                    throw Error(ERR_RANDOM_SOURCE_FAILED);
                }
                LOG(LOG_INFO, "read from /dev/urandom");
                _bufSize = RAND_BUF_SIZE;
            }
            size_t n = len - written;
            if (len > _bufSize) {
                n = _bufSize;
            }
            memcpy(data + written, _buf + (RAND_BUF_SIZE - _bufSize), n);
            _bufSize -= n;
            written += n;
        }
        LOG(LOG_INFO, "returned %d bytes of random data", len);
        // size_t n = fread(data, sizeof(uint8_t), len, _devRandom);
        // if (n != len) {
        //     LOG(LOG_ERR, "random source failed to provide random data [%s]", strerror(errno));
        //     throw Error(ERR_RANDOM_SOURCE_FAILED);
        // }
    }

protected:
    std::FILE* _devRandom;
    uint8_t _buf[RAND_BUF_SIZE];
    size_t _bufSize;
};
#endif // COMPAT_CENTOS7
