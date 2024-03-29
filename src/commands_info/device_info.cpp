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

#include <fastotv/commands_info/device_info.h>

#define DEVICE_INFO_ID_FIELD "id"
#define DEVICE_INFO_NAME_FIELD "name"

namespace fastotv {
namespace commands_info {

DeviceInfo::DeviceInfo() : DeviceInfo(invalid_device_id, std::string()) {}

DeviceInfo::DeviceInfo(device_id_t did, const std::string& name) : did_(did), name_(name) {}

bool DeviceInfo::IsValid() const {
  return did_ != invalid_device_id && !name_.empty();
}

void DeviceInfo::SetDeviceID(device_id_t did) {
  did_ = did;
}

device_id_t DeviceInfo::GetDeviceID() const {
  return did_;
}

void DeviceInfo::SetName(const std::string& name) {
  name_ = name;
}

std::string DeviceInfo::GetName() const {
  return name_;
}

common::Error DeviceInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  json_object_object_add(deserialized, DEVICE_INFO_ID_FIELD, json_object_new_string(did_.c_str()));
  json_object_object_add(deserialized, DEVICE_INFO_NAME_FIELD, json_object_new_string(name_.c_str()));
  return common::Error();
}

common::Error DeviceInfo::DoDeSerialize(json_object* serialized) {
  device_id_t did;
  json_object* jdid = nullptr;
  json_bool jdid_exists = json_object_object_get_ex(serialized, DEVICE_INFO_ID_FIELD, &jdid);
  if (!jdid_exists) {
    return common::make_error_inval();
  }
  did = json_object_get_string(jdid);

  std::string name;
  json_object* jname = nullptr;
  json_bool jname_exists = json_object_object_get_ex(serialized, DEVICE_INFO_NAME_FIELD, &jname);
  if (!jname_exists) {
    return common::make_error_inval();
  }
  name = json_object_get_string(jdid);

  DeviceInfo dev(did, name);
  if (!dev.IsValid()) {
    return common::make_error_inval();
  }

  *this = dev;
  return common::Error();
}

bool DeviceInfo::Equals(const DeviceInfo& url) const {
  return did_ == url.did_ && name_ == url.name_;
}

}  // namespace commands_info
}  // namespace fastotv
