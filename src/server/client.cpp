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

Client::Client(common::libev::IoLoop* server, const common::net::socket_info& info)
    : base_class(server, info), id_(0) {}

common::ErrnoError Client::Ping() {
  fastotv::commands_info::ClientPingInfo client_ping_info;
  return Ping(client_ping_info);
}

common::ErrnoError Client::Ping(const fastotv::commands_info::ClientPingInfo& ping) {
  fastotv::protocol::request_t ping_request;
  common::Error err_ser = fastotv::server::PingRequest(NextRequestID(), ping, &ping_request);
  if (err_ser) {
    return common::make_errno_error(err_ser->GetDescription(), EAGAIN);
  }

  return WriteRequest(ping_request);
}

common::ErrnoError Client::CheckActivateFail(fastotv::protocol::sequance_id_t id, common::Error err) {
  const std::string error_str = err->GetDescription();
  fastotv::protocol::response_t resp;
  common::Error err_ser = fastotv::server::ActivateResponseFail(id, error_str, &resp);
  if (err_ser) {
    return common::make_errno_error(err_ser->GetDescription(), EAGAIN);
  }

  return WriteResponce(resp);
}

common::ErrnoError Client::ActivateFail(fastotv::protocol::sequance_id_t id, common::Error err) {
  const std::string error_str = err->GetDescription();
  fastotv::protocol::response_t resp;
  common::Error err_ser = fastotv::server::ActivateResponseFail(id, error_str, &resp);
  if (err_ser) {
    return common::make_errno_error(err_ser->GetDescription(), EAGAIN);
  }

  return WriteResponce(resp);
}

common::ErrnoError Client::ActivateSuccess(fastotv::protocol::sequance_id_t id) {
  fastotv::protocol::response_t resp;
  common::Error err_ser = fastotv::server::ActivateResponseSuccess(id, &resp);
  if (err_ser) {
    return common::make_errno_error(err_ser->GetDescription(), EAGAIN);
  }

  return WriteResponce(resp);
}

common::ErrnoError Client::Pong(fastotv::protocol::sequance_id_t id) {
  fastotv::commands_info::ServerPingInfo server_ping_info;
  return Pong(id, server_ping_info);
}

common::ErrnoError Client::Pong(fastotv::protocol::sequance_id_t id,
                                const fastotv::commands_info::ServerPingInfo& pong) {
  fastotv::protocol::response_t resp;
  common::Error err_ser = fastotv::server::PingResponseSuccess(id, pong, &resp);
  if (err_ser) {
    const std::string err_str = err_ser->GetDescription();
    return common::make_errno_error(err_str, EAGAIN);
  }

  return WriteResponce(resp);
}

common::ErrnoError Client::GetServerInfoFail(fastotv::protocol::sequance_id_t id, common::Error err) {
  const std::string error_str = err->GetDescription();
  fastotv::protocol::response_t resp;
  common::Error err_ser = fastotv::server::GetServerInfoResponceFail(id, error_str, &resp);
  if (err_ser) {
    return common::make_errno_error(err_ser->GetDescription(), EAGAIN);
  }

  return WriteResponce(resp);
}

common::ErrnoError Client::GetServerInfoSuccess(fastotv::protocol::sequance_id_t id,
                                                const common::net::HostAndPort& bandwidth_host) {
  fastotv::commands_info::ServerInfo serv(bandwidth_host);
  fastotv::protocol::response_t server_info_responce;
  common::Error err_ser = fastotv::server::GetServerInfoResponceSuccsess(id, serv, &server_info_responce);
  if (err_ser) {
    const std::string err_str = err_ser->GetDescription();
    return common::make_errno_error(err_str, EAGAIN);
  }

  return WriteResponce(server_info_responce);
}

common::ErrnoError Client::GetChannelsFail(fastotv::protocol::sequance_id_t id, common::Error err) {
  const std::string error_str = err->GetDescription();
  fastotv::protocol::response_t resp;
  common::Error err_ser = fastotv::server::GetChannelsResponceFail(id, error_str, &resp);
  if (err_ser) {
    return common::make_errno_error(err_ser->GetDescription(), EAGAIN);
  }

  return WriteResponce(resp);
}

common::ErrnoError Client::GetChannelsSuccess(fastotv::protocol::sequance_id_t id,
                                              const fastotv::commands_info::ChannelsInfo& channels) {
  fastotv::protocol::response_t resp;
  common::Error err_ser = fastotv::server::GetChannelsResponceSuccsess(id, channels, &resp);
  if (err_ser) {
    const std::string err_str = err_ser->GetDescription();
    return common::make_errno_error(err_str, EAGAIN);
  }

  return WriteResponce(resp);
}

common::ErrnoError Client::GetRuntimeChannelInfoSuccess(fastotv::protocol::sequance_id_t id,
                                                        fastotv::stream_id sid,
                                                        size_t watchers) {
  fastotv::commands_info::RuntimeChannelInfo channel(sid, watchers);
  return GetRuntimeChannelInfoSuccess(id, channel);
}

common::ErrnoError Client::GetRuntimeChannelInfoSuccess(fastotv::protocol::sequance_id_t id,
                                                        const fastotv::commands_info::RuntimeChannelInfo& channel) {
  fastotv::protocol::response_t channels_responce;
  common::Error err_ser = fastotv::server::GetRuntimeChannelInfoResponceSuccsess(id, channel, &channels_responce);
  if (err_ser) {
    const std::string err_str = err_ser->GetDescription();
    return common::make_errno_error(err_str, EAGAIN);
  }

  return WriteResponce(channels_responce);
}

fastotv::protocol::sequance_id_t Client::NextRequestID() {
  const fastotv::protocol::seq_id_t next_id = id_++;
  return common::protocols::json_rpc::MakeRequestID(next_id);
}

}  // namespace server
}  // namespace fastotv
