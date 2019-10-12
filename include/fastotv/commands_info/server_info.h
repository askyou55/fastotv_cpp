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

#include <common/net/types.h>  // for HostAndPort

#include <common/serializer/json_serializer.h>

namespace fastotv {
namespace commands_info {

class ServerInfo : public common::serializer::JsonSerializer<ServerInfo> {
 public:
  ServerInfo();
  explicit ServerInfo(const common::net::HostAndPort& bandwidth_host);

  common::net::HostAndPort GetBandwidthHost() const;
  void SetBandwidthHost(const common::net::HostAndPort& host);

  bool Equals(const ServerInfo& serv) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  common::net::HostAndPort bandwidth_host_;
};

inline bool operator==(const ServerInfo& lhs, const ServerInfo& rhs) {
  return lhs.Equals(rhs);
}

inline bool operator!=(const ServerInfo& x, const ServerInfo& y) {
  return !(x == y);
}

}  // namespace commands_info
}  // namespace fastotv
