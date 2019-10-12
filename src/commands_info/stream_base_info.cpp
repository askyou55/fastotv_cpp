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

#include <fastotv/commands_info/stream_base_info.h>

#define CHANNEL_INFO_ID_FIELD "id"
#define CHANNEL_INFO_TYPE_FIELD "type"
#define CHANNEL_INFO_GROUP_FIELD "group"
#define CHANNEL_INFO_VIDEO_ENABLE_FIELD "video"
#define CHANNEL_INFO_AUDIO_ENABLE_FIELD "audio"

namespace fastotv {
namespace commands_info {

StreamBaseInfo::StreamBaseInfo()
    : stream_id_(invalid_stream_id), type_(PUBLIC), group_(), enable_audio_(true), enable_video_(true) {}

StreamBaseInfo::StreamBaseInfo(stream_id_t sid,
                               Type type,
                               const std::string& group,
                               bool enable_audio,
                               bool enable_video)
    : stream_id_(sid), type_(type), group_(group), enable_audio_(enable_audio), enable_video_(enable_video) {}

bool StreamBaseInfo::IsValid() const {
  return stream_id_ != invalid_stream_id;
}

stream_id_t StreamBaseInfo::GetStreamID() const {
  return stream_id_;
}

void StreamBaseInfo::SetStreamID(const stream_id_t sid) {
  stream_id_ = sid;
}

StreamBaseInfo::Type StreamBaseInfo::GetType() const {
  return type_;
}

void StreamBaseInfo::SetType(Type type) {
  type_ = type;
}

std::string StreamBaseInfo::GetGroup() const {
  return group_;
}

void StreamBaseInfo::SetGroup(const std::string& group) {
  group_ = group;
}

bool StreamBaseInfo::IsEnableAudio() const {
  return enable_audio_;
}

bool StreamBaseInfo::IsEnableVideo() const {
  return enable_video_;
}

common::Error StreamBaseInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  json_object_object_add(deserialized, CHANNEL_INFO_ID_FIELD, json_object_new_string(stream_id_.c_str()));
  json_object_object_add(deserialized, CHANNEL_INFO_TYPE_FIELD, json_object_new_int(type_));
  json_object_object_add(deserialized, CHANNEL_INFO_GROUP_FIELD, json_object_new_string(group_.c_str()));
  json_object_object_add(deserialized, CHANNEL_INFO_AUDIO_ENABLE_FIELD, json_object_new_boolean(enable_audio_));
  json_object_object_add(deserialized, CHANNEL_INFO_VIDEO_ENABLE_FIELD, json_object_new_boolean(enable_video_));
  return common::Error();
}

common::Error StreamBaseInfo::DoDeSerialize(json_object* serialized) {
  stream_id_t sid;
  json_object* jsid = nullptr;
  json_bool jsid_exists = json_object_object_get_ex(serialized, CHANNEL_INFO_ID_FIELD, &jsid);
  if (!jsid_exists) {
    return common::make_error_inval();
  }
  sid = json_object_get_string(jsid);

  Type type = PUBLIC;
  json_object* jtype = nullptr;
  json_bool jtype_exists = json_object_object_get_ex(serialized, CHANNEL_INFO_TYPE_FIELD, &jtype);
  if (jtype_exists) {
    type = static_cast<Type>(json_object_get_int(jtype));
  }

  std::string group;
  json_object* jgroup = nullptr;
  json_bool jgroup_exists = json_object_object_get_ex(serialized, CHANNEL_INFO_GROUP_FIELD, &jgroup);
  if (jgroup_exists) {
    group = json_object_get_string(jgroup);
  }

  bool enable_audio = true;
  json_object* jenable_audio = nullptr;
  json_bool jenable_audio_exists =
      json_object_object_get_ex(serialized, CHANNEL_INFO_AUDIO_ENABLE_FIELD, &jenable_audio);
  if (jenable_audio_exists) {
    enable_audio = json_object_get_boolean(jenable_audio);
  }

  bool enable_video = true;
  json_object* jdisable_video = nullptr;
  json_bool jdisable_video_exists =
      json_object_object_get_ex(serialized, CHANNEL_INFO_VIDEO_ENABLE_FIELD, &jdisable_video);
  if (jdisable_video_exists) {
    enable_video = json_object_get_boolean(jdisable_video);
  }

  StreamBaseInfo url(sid, type, group, enable_audio, enable_video);
  if (!url.IsValid()) {
    return common::make_error_inval();
  }

  *this = url;
  return common::Error();
}

bool StreamBaseInfo::Equals(const StreamBaseInfo& url) const {
  return stream_id_ == url.stream_id_ && enable_audio_ == url.enable_audio_ && enable_video_ == url.enable_video_;
}

}  // namespace commands_info
}  // namespace fastotv
