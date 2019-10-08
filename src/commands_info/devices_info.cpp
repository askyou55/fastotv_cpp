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

#include <fastotv/commands_info/devices_info.h>

#include <common/sprintf.h>

namespace fastotv {
namespace commands_info {

DevicesInfo::DevicesInfo() : devices_() {}

void DevicesInfo::AddDevice(const DeviceInfo& dev) {
  devices_.push_back(dev);
}

DevicesInfo::devices_t DevicesInfo::GetDevices() const {
  return devices_;
}

size_t DevicesInfo::GetSize() const {
  return devices_.size();
}

bool DevicesInfo::IsEmpty() const {
  return devices_.empty();
}

bool DevicesInfo::Equals(const DevicesInfo& chan) const {
  return devices_ == chan.devices_;
}

common::Error DevicesInfo::SerializeArray(json_object* deserialized_array) const {
  for (DeviceInfo url : devices_) {
    json_object* jurl = nullptr;
    common::Error err = url.Serialize(&jurl);
    if (err) {
      continue;
    }
    json_object_array_add(deserialized_array, jurl);
  }

  return common::Error();
}

common::Error DevicesInfo::DoDeSerialize(json_object* serialized) {
  devices_t devices;
  size_t len = json_object_array_length(serialized);
  for (size_t i = 0; i < len; ++i) {
    json_object* jurl = json_object_array_get_idx(serialized, i);
    DeviceInfo url;
    common::Error err = url.DeSerialize(jurl);
    if (err) {
      continue;
    }
    devices.push_back(url);
  }

  (*this).devices_ = devices;
  return common::Error();
}

}  // namespace commands_info
}  // namespace fastotv
