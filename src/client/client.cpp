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

#include <fastotv/client/client.h>

#include <common/system_info/cpu_info.h>     // for CurrentCpuInfo
#include <common/system_info/system_info.h>  // for AmountOfAvailable...

#include <fastotv/client/commands_factory.h>

namespace fastotv {
namespace client {

Client::Client(common::libev::IoLoop* server, const common::net::socket_info& info) : base_class(server, info) {}

common::ErrnoError Client::Ping() {
  commands_info::ServerPingInfo serv_ping;
  return Ping(serv_ping);
}

common::ErrnoError Client::Ping(const commands_info::ServerPingInfo& ping) {
  protocol::request_t ping_request;
  common::Error err_ser = PingRequest(NextRequestID(), ping, &ping_request);
  if (err_ser) {
    return common::make_errno_error(err_ser->GetDescription(), EINVAL);
  }

  return WriteRequest(ping_request);
}

common::ErrnoError Client::Pong(protocol::sequance_id_t id) {
  commands_info::ClientPingInfo client_pong;
  return Pong(id, client_pong);
}

common::ErrnoError Client::Pong(protocol::sequance_id_t id, const commands_info::ClientPingInfo& pong) {
  protocol::response_t resp;
  common::Error err_ser = PingResponseSuccess(id, pong, &resp);
  if (err_ser) {
    const std::string err_str = err_ser->GetDescription();
    return common::make_errno_error(err_str, EINVAL);
  }

  return WriteResponse(resp);
}

common::ErrnoError Client::SystemInfo(protocol::sequance_id_t id,
                                      const fastotv::login_t& login,
                                      bandwidth_t bandwidth) {
  const common::system_info::CpuInfo& c1 = common::system_info::CurrentCpuInfo();
  std::string brand = c1.GetBrandName();

  int64_t ram_total = common::system_info::AmountOfPhysicalMemory();
  int64_t ram_free = common::system_info::AmountOfAvailablePhysicalMemory();

  std::string os_name = common::system_info::OperatingSystemName();
  std::string os_version = common::system_info::OperatingSystemVersion();
  std::string os_arch = common::system_info::OperatingSystemArchitecture();

  std::string os = common::MemSPrintf("%s %s(%s)", os_name, os_version, os_arch);

  commands_info::ClientInfo info(login, os, brand, ram_total, ram_free, bandwidth);
  return SystemInfo(id, info);
}

common::ErrnoError Client::SystemInfo(protocol::sequance_id_t id, const commands_info::ClientInfo& info) {
  protocol::response_t resp;
  common::Error err_ser = SystemInfoResponseSuccess(id, info, &resp);
  if (err_ser) {
    return common::make_errno_error(err_ser->GetDescription(), EINVAL);
  }

  return WriteResponse(resp);
}

common::ErrnoError Client::Activate(const login_t& login, const std::string& password, device_id_t dev) {
  commands_info::AuthInfo auth_info(login, password, dev);
  return Activate(auth_info);
}

common::ErrnoError Client::Activate(const fastotv::commands_info::AuthInfo& auth) {
  protocol::request_t auth_request;
  common::Error err_ser = ActiveRequest(NextRequestID(), auth, &auth_request);
  if (err_ser) {
    return common::make_errno_error(err_ser->GetDescription(), EINVAL);
  }

  return WriteRequest(auth_request);
}

common::ErrnoError Client::GetServerInfo() {
  protocol::request_t server_info_request;
  common::Error err_ser = GetServerInfoRequest(NextRequestID(), &server_info_request);
  if (err_ser) {
    return common::make_errno_error(err_ser->GetDescription(), EINVAL);
  }

  return WriteRequest(server_info_request);
}

common::ErrnoError Client::GetChannels() {
  protocol::request_t server_info_request;
  common::Error err_ser = GetChannelsRequest(NextRequestID(), &server_info_request);
  if (err_ser) {
    return common::make_errno_error(err_ser->GetDescription(), EINVAL);
  }

  return WriteRequest(server_info_request);
}

common::ErrnoError Client::GetRuntimeChannelInfo(stream_id sid) {
  protocol::request_t run_channels_request;
  commands_info::RuntimeChannelLiteInfo run(sid);
  common::Error err_ser = GetRuntimeChannelInfoRequest(NextRequestID(), run, &run_channels_request);
  if (err_ser) {
    return common::make_errno_error(err_ser->GetDescription(), EINVAL);
  }

  return WriteRequest(run_channels_request);
}

}  // namespace client
}  // namespace fastotv
