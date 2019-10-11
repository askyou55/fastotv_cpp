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

class StreamBaseInfo : public common::serializer::JsonSerializer<StreamBaseInfo> {
 public:
  enum Type { PUBLIC, PRIVATE };

  StreamBaseInfo();
  StreamBaseInfo(stream_id_t sid, Type type, const std::string& group, bool enable_audio, bool enable_video);

  bool IsValid() const;
  stream_id_t GetStreamID() const;
  Type GetType() const;
  std::string GetGroup() const;

  bool IsEnableAudio() const;
  bool IsEnableVideo() const;

  bool Equals(const StreamBaseInfo& url) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  stream_id_t stream_id_;
  Type type_;
  std::string group_;

  bool enable_audio_;
  bool enable_video_;
};

inline bool operator==(const StreamBaseInfo& left, const StreamBaseInfo& right) {
  return left.Equals(right);
}

inline bool operator!=(const StreamBaseInfo& x, const StreamBaseInfo& y) {
  return !(x == y);
}

}  // namespace commands_info
}  // namespace fastotv