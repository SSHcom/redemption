/*
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   Product name: redemption, a FLOSS RDP proxy
   Copyright (C) Wallix 2013
   Author(s): Christophe Grosjean

   Network related utility functions

*/

#pragma once

#include "utils/sugar/unique_fd.hpp"
#include "utils/sugar/bytes_view.hpp"

#include <chrono>

#include <cstdint>
#include <cstdio>

class in_addr;

bool try_again(int errnum);

/// std::expected
/// \return nullptr if ok, view string if error
char const* resolve_ipv4_address(const char* ip, in_addr & s4_sin_addr);

unique_fd ip_connect(const char* ip, int port,
                     std::chrono::milliseconds connection_establishment_timeout,
                     int connection_retry_count, char const** error_result = nullptr);

unique_fd local_connect(const char* sck_name, bool no_log);

unique_fd addr_connect(const char* addr, bool no_log_for_unix_socket);

int parse_ip_conntrack(int fd, const char * source, const char * dest, int sport, int dport,
                       writable_bytes_view transparent_dest, uint32_t verbose);

FILE* popen_conntrack(const char* source_ip, int source_port, int target_port);
