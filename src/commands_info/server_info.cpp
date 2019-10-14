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

#include <fastotv/commands_info/server_info.h>

#define BANDWIDTH_HOST_FIELD "bandwidth_host"
#define EPG_URL_FIELD "epg_url"

namespace fastotv {
namespace commands_info {

ServerInfo::ServerInfo() : bandwidth_host_(), epg_url_() {}

ServerInfo::ServerInfo(const common::net::HostAndPort& bandwidth_host, const common::uri::Url& epg_url)
    : bandwidth_host_(bandwidth_host), epg_url_(epg_url) {}

common::Error ServerInfo::SerializeFields(json_object* deserialized) const {
  const std::string host_str = common::ConvertToString(bandwidth_host_);
  json_object_object_add(deserialized, BANDWIDTH_HOST_FIELD, json_object_new_string(host_str.c_str()));

  const std::string epg_url_str = epg_url_.GetUrl();
  json_object_object_add(deserialized, EPG_URL_FIELD, json_object_new_string(epg_url_str.c_str()));
  return common::Error();
}

common::Error ServerInfo::DoDeSerialize(json_object* serialized) {
  json_object* jband = nullptr;
  json_bool jband_exists = json_object_object_get_ex(serialized, BANDWIDTH_HOST_FIELD, &jband);
  ServerInfo inf;
  if (jband_exists) {
    const std::string host_str = json_object_get_string(jband);
    common::net::HostAndPort hs;
    if (common::ConvertFromString(host_str, &hs)) {
      inf.bandwidth_host_ = hs;
    }
  }

  json_object* jepg_url = nullptr;
  json_bool jepg_url_exists = json_object_object_get_ex(serialized, EPG_URL_FIELD, &jepg_url);
  if (jepg_url_exists) {
    const std::string epg_url_str = json_object_get_string(jepg_url);
    common::uri::Url hs;
    if (common::ConvertFromString(epg_url_str, &hs)) {
      inf.epg_url_ = hs;
    }
  }

  *this = inf;
  return common::Error();
}

common::net::HostAndPort ServerInfo::GetBandwidthHost() const {
  return bandwidth_host_;
}

void ServerInfo::SetBandwidthHost(const common::net::HostAndPort& host) {
  bandwidth_host_ = host;
}

common::uri::Url ServerInfo::GetEpgUrl() const {
  return epg_url_;
}

void ServerInfo::SetEpgUrl(const common::uri::Url& url) {
  epg_url_ = url;
}

bool ServerInfo::Equals(const ServerInfo& serv) const {
  return serv.bandwidth_host_ == bandwidth_host_;
}

}  // namespace commands_info
}  // namespace fastotv
