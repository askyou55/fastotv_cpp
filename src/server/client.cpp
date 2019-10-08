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

#include <fastotv/server/client.h>

#include <string>

#include <fastotv/server/commands_factory.h>

namespace fastotv {
namespace server {

Client::Client(common::libev::IoLoop* server, const common::net::socket_info& info) : base_class(server, info) {}

common::ErrnoError Client::Ping() {
  commands_info::ClientPingInfo client_ping_info;
  return Ping(client_ping_info);
}

common::ErrnoError Client::Ping(const commands_info::ClientPingInfo& ping) {
  protocol::request_t ping_request;
  common::Error err_ser = PingRequest(NextRequestID(), ping, &ping_request);
  if (err_ser) {
    return common::make_errno_error(err_ser->GetDescription(), EAGAIN);
  }

  return WriteRequest(ping_request);
}

common::ErrnoError Client::CheckLoginFail(protocol::sequance_id_t id, common::Error err) {
  const std::string error_str = err->GetDescription();
  protocol::response_t resp;
  common::Error err_ser = LoginResponseFail(id, error_str, &resp);
  if (err_ser) {
    return common::make_errno_error(err_ser->GetDescription(), EAGAIN);
  }

  return WriteResponse(resp);
}

common::ErrnoError Client::ActivateDeviceFail(protocol::sequance_id_t id, common::Error err) {
  const std::string error_str = err->GetDescription();
  protocol::response_t resp;
  common::Error err_ser = ActivateDeviceResponseFail(id, error_str, &resp);
  if (err_ser) {
    return common::make_errno_error(err_ser->GetDescription(), EAGAIN);
  }

  return WriteResponse(resp);
}

common::ErrnoError Client::ActivateDeviceSuccess(protocol::sequance_id_t id,
                                                 const commands_info::DevicesInfo& devices) {
  protocol::response_t resp;
  common::Error err_ser = ActivateDeviceResponseSuccess(id, devices, &resp);
  if (err_ser) {
    return common::make_errno_error(err_ser->GetDescription(), EAGAIN);
  }

  return WriteResponse(resp);
}

common::ErrnoError Client::LoginFail(protocol::sequance_id_t id, common::Error err) {
  const std::string error_str = err->GetDescription();
  protocol::response_t resp;
  common::Error err_ser = LoginResponseFail(id, error_str, &resp);
  if (err_ser) {
    return common::make_errno_error(err_ser->GetDescription(), EAGAIN);
  }

  return WriteResponse(resp);
}

common::ErrnoError Client::LoginSuccess(protocol::sequance_id_t id) {
  protocol::response_t resp;
  common::Error err_ser = LoginResponseSuccess(id, &resp);
  if (err_ser) {
    return common::make_errno_error(err_ser->GetDescription(), EAGAIN);
  }

  return WriteResponse(resp);
}

common::ErrnoError Client::Pong(protocol::sequance_id_t id) {
  commands_info::ServerPingInfo server_ping_info;
  return Pong(id, server_ping_info);
}

common::ErrnoError Client::Pong(protocol::sequance_id_t id, const commands_info::ServerPingInfo& pong) {
  protocol::response_t resp;
  common::Error err_ser = PingResponseSuccess(id, pong, &resp);
  if (err_ser) {
    const std::string err_str = err_ser->GetDescription();
    return common::make_errno_error(err_str, EAGAIN);
  }

  return WriteResponse(resp);
}

common::ErrnoError Client::GetServerInfoFail(protocol::sequance_id_t id, common::Error err) {
  const std::string error_str = err->GetDescription();
  protocol::response_t resp;
  common::Error err_ser = GetServerInfoResponseFail(id, error_str, &resp);
  if (err_ser) {
    return common::make_errno_error(err_ser->GetDescription(), EAGAIN);
  }

  return WriteResponse(resp);
}

common::ErrnoError Client::GetServerInfoSuccess(protocol::sequance_id_t id,
                                                const common::net::HostAndPort& bandwidth_host) {
  commands_info::ServerInfo serv(bandwidth_host);
  protocol::response_t resp;
  common::Error err_ser = GetServerInfoResponseSuccess(id, serv, &resp);
  if (err_ser) {
    const std::string err_str = err_ser->GetDescription();
    return common::make_errno_error(err_str, EAGAIN);
  }

  return WriteResponse(resp);
}

common::ErrnoError Client::GetChannelsFail(protocol::sequance_id_t id, common::Error err) {
  const std::string error_str = err->GetDescription();
  protocol::response_t resp;
  common::Error err_ser = GetChannelsResponseFail(id, error_str, &resp);
  if (err_ser) {
    return common::make_errno_error(err_ser->GetDescription(), EAGAIN);
  }

  return WriteResponse(resp);
}

common::ErrnoError Client::GetChannelsSuccess(protocol::sequance_id_t id, const commands_info::ChannelsInfo& channels) {
  protocol::response_t resp;
  common::Error err_ser = GetChannelsResponseSuccess(id, channels, &resp);
  if (err_ser) {
    const std::string err_str = err_ser->GetDescription();
    return common::make_errno_error(err_str, EAGAIN);
  }

  return WriteResponse(resp);
}

common::ErrnoError Client::GetRuntimeChannelInfoSuccess(protocol::sequance_id_t id, stream_id_t sid, size_t watchers) {
  commands_info::RuntimeChannelInfo channel(sid, watchers);
  return GetRuntimeChannelInfoSuccess(id, channel);
}

common::ErrnoError Client::GetRuntimeChannelInfoSuccess(protocol::sequance_id_t id,
                                                        const commands_info::RuntimeChannelInfo& channel) {
  protocol::response_t resp;
  common::Error err_ser = GetRuntimeChannelInfoResponseSuccess(id, channel, &resp);
  if (err_ser) {
    const std::string err_str = err_ser->GetDescription();
    return common::make_errno_error(err_str, EAGAIN);
  }

  return WriteResponse(resp);
}

}  // namespace server
}  // namespace fastotv
