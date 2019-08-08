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

namespace fastotv {
namespace commands_info {

class OperationSystemInfo : public common::serializer::JsonSerializer<OperationSystemInfo> {
 public:
  OperationSystemInfo();
  OperationSystemInfo(const std::string& name,
                      const std::string& version,
                      const std::string& arch,
                      int64_t ram_total,
                      int64_t ram_free);

  bool IsValid() const;

  std::string GetName() const;
  std::string GetVersion() const;
  std::string GetArch() const;
  int64_t GetRamTotal() const;
  int64_t GetRamFree() const;

  static OperationSystemInfo MakeOSSnapshot();

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  std::string name_;
  std::string version_;
  std::string arch_;

  int64_t ram_total_;
  int64_t ram_free_;
};

}  // namespace commands_info
}  // namespace fastotv
