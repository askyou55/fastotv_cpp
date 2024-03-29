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

#include <common/uri/url.h>  // for Uri

#include <fastotv/commands_info/epg_info.h>
#include <fastotv/commands_info/stream_base_info.h>

namespace fastotv {
namespace commands_info {

class ChannelInfo : public StreamBaseInfo {
 public:
  typedef StreamBaseInfo base_class;

  ChannelInfo();
  ChannelInfo(stream_id_t sid, const std::string& group, const EpgInfo& epg, bool enable_audio, bool enable_video);

  bool IsValid() const;

  EpgInfo GetEpg() const;

  bool Equals(const ChannelInfo& url) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  EpgInfo epg_;
};

inline bool operator==(const ChannelInfo& left, const ChannelInfo& right) {
  return left.Equals(right);
}

inline bool operator!=(const ChannelInfo& x, const ChannelInfo& y) {
  return !(x == y);
}

}  // namespace commands_info
}  // namespace fastotv
