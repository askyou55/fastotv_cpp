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

#define AUTH_INFO_LOGIN_FIELD "login"
#define AUTH_INFO_PASSWORD_FIELD "password"
#define AUTH_INFO_DEVICE_ID_FIELD "device_id"

namespace fastotv {
namespace commands_info {

AuthInfo::AuthInfo() : login_(), password_() {}

AuthInfo::AuthInfo(const login_t& login, const std::string& password, device_id_t dev)
    : login_(login), password_(password), device_id_(dev) {}

bool AuthInfo::IsValid() const {
  return !login_.empty() && !password_.empty() && !device_id_.empty();
}

common::Error AuthInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  json_object_object_add(deserialized, AUTH_INFO_LOGIN_FIELD, json_object_new_string(login_.c_str()));
  json_object_object_add(deserialized, AUTH_INFO_PASSWORD_FIELD, json_object_new_string(password_.c_str()));
  json_object_object_add(deserialized, AUTH_INFO_DEVICE_ID_FIELD, json_object_new_string(device_id_.c_str()));
  return common::Error();
}

common::Error AuthInfo::DoDeSerialize(json_object* serialized) {
  json_object* jlogin = nullptr;
  json_bool jlogin_exists = json_object_object_get_ex(serialized, AUTH_INFO_LOGIN_FIELD, &jlogin);
  if (!jlogin_exists) {
    return common::make_error_inval();
  }

  json_object* jpass = nullptr;
  json_bool jpass_exists = json_object_object_get_ex(serialized, AUTH_INFO_PASSWORD_FIELD, &jpass);
  if (!jpass_exists) {
    return common::make_error_inval();
  }

  json_object* jdevid = nullptr;
  json_bool jdevid_exists = json_object_object_get_ex(serialized, AUTH_INFO_DEVICE_ID_FIELD, &jdevid);
  if (!jdevid_exists) {
    return common::make_error_inval();
  }

  AuthInfo ainf(json_object_get_string(jlogin), json_object_get_string(jpass), json_object_get_string(jdevid));
  *this = ainf;
  return common::Error();
}

device_id_t AuthInfo::GetDeviceID() const {
  return device_id_;
}

void AuthInfo::SetDeviceID(device_id_t dev) {
  device_id_ = dev;
}

login_t AuthInfo::GetLogin() const {
  return login_;
}

void AuthInfo::SetLogin(const login_t& login) {
  login_ = login;
}

std::string AuthInfo::GetPassword() const {
  return password_;
}

void AuthInfo::SetPassword(const std::string& password) {
  password_ = password;
}

bool AuthInfo::Equals(const AuthInfo& auth) const {
  return login_ == auth.login_ && password_ == auth.password_;
}

}  // namespace commands_info
}  // namespace fastotv
