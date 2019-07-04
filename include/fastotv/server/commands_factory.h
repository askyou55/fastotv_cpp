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

#include <string>  // for string

#include <fastotv/protocol/types.h>

#include <fastotv/commands_info/channels_info.h>
#include <fastotv/commands_info/ping_info.h>
#include <fastotv/commands_info/runtime_channel_info.h>
#include <fastotv/commands_info/server_info.h>

namespace fastotv {
namespace server {

// requests
common::Error PingRequest(protocol::sequance_id_t id,
                          const commands_info::ClientPingInfo& params,
                          protocol::request_t* req);

// responses
common::Error ActivateResponseSuccess(protocol::sequance_id_t id, protocol::response_t* resp);
common::Error ActivateResponseFail(protocol::sequance_id_t id,
                                   const std::string& error_text,
                                   protocol::response_t* resp);

// client ping
common::Error PingResponseSuccess(protocol::sequance_id_t id,
                                  const commands_info::ServerPingInfo& params,
                                  protocol::response_t* resp);

// server info
common::Error GetServerInfoResponseSuccess(protocol::sequance_id_t id,
                                           const commands_info::ServerInfo& params,
                                           protocol::response_t* resp);
common::Error GetServerInfoResponseFail(protocol::sequance_id_t id,
                                        const std::string& error_text,
                                        protocol::response_t* resp);

// channels
common::Error GetChannelsResponseSuccess(protocol::sequance_id_t id,
                                         const commands_info::ChannelsInfo& params,
                                         protocol::response_t* resp);
common::Error GetChannelsResponseFail(protocol::sequance_id_t id,
                                      const std::string& error_text,
                                      protocol::response_t* resp);

// runtimeChannel
common::Error GetRuntimeChannelInfoResponseSuccess(protocol::sequance_id_t id,
                                                   const commands_info::RuntimeChannelInfo& params,
                                                   protocol::response_t* resp);

}  // namespace server
}  // namespace fastotv
