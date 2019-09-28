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

#include <fastotv/commands_info/auth_info.h>

#include <string>  // for string

#include <common/convert2string.h>
#include <common/sprintf.h>

#define AUTH_INFO_DEVICE_ID_FIELD "device_id"

namespace fastotv {
namespace commands_info {

AuthInfo::AuthInfo() : base_class() {}

AuthInfo::AuthInfo(const LoginInfo& login, device_id_t dev) : base_class(login), device_id_(dev) {}

bool AuthInfo::IsValid() const {
  return base_class::IsValid() && !device_id_.empty();
}

common::Error AuthInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  json_object_object_add(deserialized, AUTH_INFO_DEVICE_ID_FIELD, json_object_new_string(device_id_.c_str()));
  return base_class::SerializeFields(deserialized);
}

common::Error AuthInfo::DoDeSerialize(json_object* serialized) {
  base_class login;
  common::Error err = login.DeSerialize(serialized);
  if (err) {
    return err;
  }

  json_object* jdevid = nullptr;
  json_bool jdevid_exists = json_object_object_get_ex(serialized, AUTH_INFO_DEVICE_ID_FIELD, &jdevid);
  if (!jdevid_exists) {
    return common::make_error_inval();
  }

  AuthInfo ainf(login, json_object_get_string(jdevid));
  *this = ainf;
  return common::Error();
}

device_id_t AuthInfo::GetDeviceID() const {
  return device_id_;
}

void AuthInfo::SetDeviceID(device_id_t dev) {
  device_id_ = dev;
}

bool AuthInfo::Equals(const AuthInfo& auth) const {
  return base_class::Equals(auth) && device_id_ == auth.device_id_;
}

}  // namespace commands_info
}  // namespace fastotv
