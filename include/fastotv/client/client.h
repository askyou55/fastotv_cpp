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

#include <fastotv/client.h>
#include <fastotv/commands_info/auth_info.h>
#include <fastotv/commands_info/client_info.h>
#include <fastotv/commands_info/ping_info.h>
#include <fastotv/protocol/types.h>

namespace fastotv {
namespace client {

class Client : public ProtocoledClient {
 public:
  typedef ProtocoledClient base_class;
  Client(common::libev::IoLoop* server, const common::net::socket_info& info);

  // requests
  common::ErrnoError ActivateDevice(const commands_info::LoginInfo& login) WARN_UNUSED_RESULT;
  common::ErrnoError Login(const commands_info::AuthInfo& auth) WARN_UNUSED_RESULT;

  common::ErrnoError Ping() WARN_UNUSED_RESULT;
  common::ErrnoError Ping(const commands_info::ServerPingInfo& ping) WARN_UNUSED_RESULT;

  common::ErrnoError GetServerInfo() WARN_UNUSED_RESULT;
  common::ErrnoError GetChannels() WARN_UNUSED_RESULT;
  common::ErrnoError GetRuntimeChannelInfo(stream_id sid) WARN_UNUSED_RESULT;

  // responses
  common::ErrnoError NotificationTextOK(protocol::sequance_id_t id) WARN_UNUSED_RESULT;
  common::ErrnoError Pong(protocol::sequance_id_t id) WARN_UNUSED_RESULT;
  common::ErrnoError Pong(protocol::sequance_id_t id, const commands_info::ClientPingInfo& pong) WARN_UNUSED_RESULT;

  common::ErrnoError SystemInfo(protocol::sequance_id_t id,
                                const login_t& login,
                                bandwidth_t bandwidth) WARN_UNUSED_RESULT;
  common::ErrnoError SystemInfo(protocol::sequance_id_t id, const commands_info::ClientInfo& info) WARN_UNUSED_RESULT;
};

}  // namespace client
}  // namespace fastotv
