/*  Copyright (C) 2014-2019 FastoGT. All right reserved.

    This file is part of FastoTV.

    FastoTV is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    FastoTV is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FastoTV. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <string>

#include <common/types.h>  // for time64_t

namespace fastotv {

typedef std::string stream_id_t;  // must be unique
static const stream_id_t invalid_stream_id = stream_id_t();

typedef std::string login_t;           // unique, user email now
typedef std::string device_id_t;       // unique, mongodb id, registered by user
typedef std::string user_id_t;         // mongodb/redis id in json
typedef size_t bandwidth_t;            // bytes/s
typedef common::time64_t timestamp_t;  // millisecond

static const device_id_t invalid_device_id = device_id_t();

enum StreamType : int {
  PROXY = 0,
  RELAY = 1,
  ENCODE = 2,
  TIMESHIFT_PLAYER = 3,
  TIMESHIFT_RECORDER = 4,
  CATCHUP = 5,
  TEST_LIFE = 6,
  VOD_RELAY = 7,
  VOD_ENCODE = 8,
  COD_RELAY = 9,
  COD_ENCODE = 10,
  SCREEN  // for inner use
};

}  // namespace fastotv
