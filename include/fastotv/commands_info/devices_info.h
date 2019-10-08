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

#include <vector>

#include <fastotv/commands_info/device_info.h>

namespace fastotv {
namespace commands_info {

class DevicesInfo : public common::serializer::JsonSerializerArray<DevicesInfo> {
 public:
  typedef std::vector<DeviceInfo> devices_t;
  DevicesInfo();

  void AddDevice(const DeviceInfo& device);
  devices_t GetDevices() const;

  size_t GetSize() const;
  bool IsEmpty() const;

  bool Equals(const DevicesInfo& chan) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeArray(json_object* deserialized_array) const override;

 private:
  devices_t devices_;
};

inline bool operator==(const DevicesInfo& lhs, const DevicesInfo& rhs) {
  return lhs.Equals(rhs);
}

inline bool operator!=(const DevicesInfo& x, const DevicesInfo& y) {
  return !(x == y);
}

}  // namespace commands_info
}  // namespace fastotv
