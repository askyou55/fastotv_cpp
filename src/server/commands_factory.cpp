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

#include <fastotv/server/commands_factory.h>

#include <fastotv/commands/commands.h>

#define CHANNELS_FIELD "channels"
#define VODS_FIELD "vods"

namespace fastotv {
namespace server {

common::Error PingRequest(protocol::sequance_id_t id,
                          const commands_info::ClientPingInfo& params,
                          protocol::request_t* req) {
  if (!req) {
    return common::make_error_inval();
  }

  std::string ping_client_json;
  common::Error err_ser = params.SerializeToString(&ping_client_json);
  if (err_ser) {
    return err_ser;
  }

  protocol::request_t lreq;
  lreq.id = id;
  lreq.method = SERVER_PING;
  lreq.params = ping_client_json;
  *req = lreq;
  return common::Error();
}

common::Error GetClientInfoRequest(protocol::sequance_id_t id, protocol::request_t* req) {
  if (!req) {
    return common::make_error_inval();
  }

  protocol::request_t lreq;
  lreq.id = id;
  lreq.method = SERVER_GET_CLIENT_INFO;
  *req = lreq;
  return common::Error();
}

common::Error ActivateDeviceResponseSuccess(protocol::sequance_id_t id,
                                            const commands_info::DevicesInfo& params,
                                            protocol::response_t* resp) {
  if (!resp) {
    return common::make_error_inval();
  }

  json_object* obj = nullptr;
  common::Error err_ser = params.Serialize(&obj);
  if (err_ser) {
    return err_ser;
  }

  json_object* parent = json_object_new_object();
  json_object_object_add(parent, "devices", obj);
  const std::string devices_json = json_object_get_string(parent);
  json_object_put(parent);

  *resp = protocol::response_t::MakeMessage(
      id, common::protocols::json_rpc::JsonRPCMessage::MakeSuccessMessage(devices_json));
  return common::Error();
}

common::Error ActivateDeviceResponseFail(protocol::sequance_id_t id,
                                         const std::string& error_text,
                                         protocol::response_t* resp) {
  if (!resp) {
    return common::make_error_inval();
  }

  *resp = protocol::response_t::MakeError(
      id, common::protocols::json_rpc::JsonRPCError::MakeInternalErrorFromText(error_text));
  return common::Error();
}

common::Error LoginResponseSuccess(protocol::sequance_id_t id, protocol::response_t* resp) {
  if (!resp) {
    return common::make_error_inval();
  }

  *resp = protocol::response_t::MakeMessage(id, common::protocols::json_rpc::JsonRPCMessage::MakeSuccessMessage());
  return common::Error();
}

common::Error LoginResponseFail(protocol::sequance_id_t id, const std::string& error_text, protocol::response_t* resp) {
  if (!resp) {
    return common::make_error_inval();
  }

  *resp = protocol::response_t::MakeError(
      id, common::protocols::json_rpc::JsonRPCError::MakeInternalErrorFromText(error_text));
  return common::Error();
}

common::Error PingResponseSuccess(protocol::sequance_id_t id,
                                  const commands_info::ServerPingInfo& params,
                                  protocol::response_t* resp) {
  if (!resp) {
    return common::make_error_inval();
  }

  std::string ping_str;
  common::Error err_ser = params.SerializeToString(&ping_str);
  if (err_ser) {
    return err_ser;
  }

  *resp =
      protocol::response_t::MakeMessage(id, common::protocols::json_rpc::JsonRPCMessage::MakeSuccessMessage(ping_str));
  return common::Error();
}

common::Error GetServerInfoResponseSuccess(protocol::sequance_id_t id,
                                           const commands_info::ServerInfo& params,
                                           protocol::response_t* resp) {
  if (!resp) {
    return common::make_error_inval();
  }

  std::string server_json;
  common::Error err_ser = params.SerializeToString(&server_json);
  if (err_ser) {
    return err_ser;
  }

  *resp = protocol::response_t::MakeMessage(
      id, common::protocols::json_rpc::JsonRPCMessage::MakeSuccessMessage(server_json));
  return common::Error();
}

common::Error GetServerInfoResponseFail(protocol::sequance_id_t id,
                                        const std::string& error_text,
                                        protocol::response_t* resp) {
  if (!resp) {
    return common::make_error_inval();
  }

  *resp = protocol::response_t::MakeError(
      id, common::protocols::json_rpc::JsonRPCError::MakeInternalErrorFromText(error_text));
  return common::Error();
}

common::Error GetChannelsResponseSuccess(protocol::sequance_id_t id,
                                         const commands_info::ChannelsInfo& channels,
                                         const commands_info::VodsInfo& vods,
                                         protocol::response_t* resp) {
  if (!resp) {
    return common::make_error_inval();
  }

  json_object* cobj = nullptr;
  common::Error err_ser = channels.Serialize(&cobj);
  if (err_ser) {
    return err_ser;
  }

  json_object* vobj = nullptr;
  err_ser = vods.Serialize(&vobj);
  if (err_ser) {
    return err_ser;
  }

  json_object* parent = json_object_new_object();
  json_object_object_add(parent, VODS_FIELD, vobj);
  json_object_object_add(parent, CHANNELS_FIELD, cobj);
  const std::string chan_json = json_object_get_string(parent);
  json_object_put(parent);

  *resp =
      protocol::response_t::MakeMessage(id, common::protocols::json_rpc::JsonRPCMessage::MakeSuccessMessage(chan_json));
  return common::Error();
}

common::Error GetChannelsResponseFail(protocol::sequance_id_t id,
                                      const std::string& error_text,
                                      protocol::response_t* resp) {
  if (!resp) {
    return common::make_error_inval();
  }

  *resp = protocol::response_t::MakeError(
      id, common::protocols::json_rpc::JsonRPCError::MakeInternalErrorFromText(error_text));
  return common::Error();
}

common::Error GetRuntimeChannelInfoResponseSuccess(protocol::sequance_id_t id,
                                                   const commands_info::RuntimeChannelInfo& params,
                                                   protocol::response_t* resp) {
  if (!resp) {
    return common::make_error_inval();
  }

  std::string run_json;
  common::Error err_ser = params.SerializeToString(&run_json);
  if (err_ser) {
    return err_ser;
  }

  *resp =
      protocol::response_t::MakeMessage(id, common::protocols::json_rpc::JsonRPCMessage::MakeSuccessMessage(run_json));
  return common::Error();
}

}  // namespace server
}  // namespace fastotv
