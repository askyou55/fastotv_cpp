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

#include <fastotv/commands_info/channel_info.h>

#define CHANNEL_INFO_EPG_FIELD "epg"

namespace fastotv {
namespace commands_info {

ChannelInfo::ChannelInfo() : base_class(), epg_() {}

ChannelInfo::ChannelInfo(stream_id_t sid,
                         const std::string& group,
                         const EpgInfo& epg,
                         bool enable_audio,
                         bool enable_video)
    : base_class(sid, group, enable_audio, enable_video), epg_(epg) {}

bool ChannelInfo::IsValid() const {
  return base_class::IsValid() && epg_.IsValid();
}

EpgInfo ChannelInfo::GetEpg() const {
  return epg_;
}

common::Error ChannelInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  common::Error err = base_class::SerializeFields(deserialized);
  if (err) {
    return err;
  }

  json_object* jepg = nullptr;
  err = epg_.Serialize(&jepg);
  if (err) {
    return err;
  }

  json_object_object_add(deserialized, CHANNEL_INFO_EPG_FIELD, jepg);
  return common::Error();
}

common::Error ChannelInfo::DoDeSerialize(json_object* serialized) {
  ChannelInfo inf;
  common::Error err = inf.base_class::DoDeSerialize(serialized);
  if (err) {
    return err;
  }

  json_object* jepg = nullptr;
  json_bool jepg_exists = json_object_object_get_ex(serialized, CHANNEL_INFO_EPG_FIELD, &jepg);
  if (!jepg_exists) {
    return common::make_error_inval();
  }

  EpgInfo epg;
  err = epg.DeSerialize(jepg);
  if (err) {
    return err;
  }

  inf.epg_ = epg;
  *this = inf;
  return common::Error();
}

bool ChannelInfo::Equals(const ChannelInfo& url) const {
  return base_class::Equals(url) && epg_ == url.epg_;
}

}  // namespace commands_info
}  // namespace fastotv
