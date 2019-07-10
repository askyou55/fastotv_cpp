/*  Copyright (C) 2014-2019 FastoGT. All right reserved.
    This file is part of iptv_cloud.
    iptv_cloud is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    iptv_cloud is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with iptv_cloud.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <common/net/types.h>

#include <fastotv/client.h>
#include <fastotv/commands_info/channels_info.h>
#include <fastotv/commands_info/ping_info.h>
#include <fastotv/commands_info/runtime_channel_info.h>
#include <fastotv/protocol/types.h>

namespace fastotv {
namespace server {

class Client : public ProtocoledClient {
 public:
  typedef ProtocoledClient base_class;
  Client(common::libev::IoLoop* server, const common::net::socket_info& info);

  // requests
  common::ErrnoError Ping() WARN_UNUSED_RESULT;
  common::ErrnoError Ping(const commands_info::ClientPingInfo& ping) WARN_UNUSED_RESULT;

  // responses
  common::ErrnoError CheckActivateFail(protocol::sequance_id_t id, common::Error err) WARN_UNUSED_RESULT;

  common::ErrnoError ActivateFail(protocol::sequance_id_t id, common::Error err) WARN_UNUSED_RESULT;
  common::ErrnoError ActivateSuccess(protocol::sequance_id_t id) WARN_UNUSED_RESULT;

  common::ErrnoError Pong(protocol::sequance_id_t id) WARN_UNUSED_RESULT;
  common::ErrnoError Pong(protocol::sequance_id_t id, const commands_info::ServerPingInfo& pong) WARN_UNUSED_RESULT;

  common::ErrnoError GetServerInfoFail(protocol::sequance_id_t id, common::Error err) WARN_UNUSED_RESULT;
  common::ErrnoError GetServerInfoSuccess(protocol::sequance_id_t id,
                                          const common::net::HostAndPort& bandwidth_host) WARN_UNUSED_RESULT;

  common::ErrnoError GetChannelsFail(protocol::sequance_id_t id, common::Error err) WARN_UNUSED_RESULT;
  common::ErrnoError GetChannelsSuccess(protocol::sequance_id_t id,
                                        const commands_info::ChannelsInfo& channels) WARN_UNUSED_RESULT;

  common::ErrnoError GetRuntimeChannelInfoSuccess(protocol::sequance_id_t id,
                                                  stream_id sid,
                                                  size_t watchers) WARN_UNUSED_RESULT;
  common::ErrnoError GetRuntimeChannelInfoSuccess(protocol::sequance_id_t id,
                                                  const commands_info::RuntimeChannelInfo& channel) WARN_UNUSED_RESULT;
};

}  // namespace server
}  // namespace fastotv
