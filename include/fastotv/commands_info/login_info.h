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

#include <string>

#include <common/serializer/json_serializer.h>

#include <fastotv/types.h>

namespace fastotv {
namespace commands_info {

class LoginInfo : public common::serializer::JsonSerializer<LoginInfo> {
 public:
  LoginInfo();
  LoginInfo(const login_t& login, const std::string& password);

  bool IsValid() const;

  login_t GetLogin() const;
  void SetLogin(const login_t& login);

  std::string GetPassword() const;
  void SetPassword(const std::string& password);

  bool Equals(const LoginInfo& auth) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  login_t login_;  // unique
  std::string password_;
};

inline bool operator==(const LoginInfo& lhs, const LoginInfo& rhs) {
  return lhs.Equals(rhs);
}

inline bool operator!=(const LoginInfo& x, const LoginInfo& y) {
  return !(x == y);
}

}  // namespace commands_info
}  // namespace fastotv
