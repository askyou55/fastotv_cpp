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

#define CHANNEL_INFO_ID_FIELD "id"
#define CHANNEL_INFO_TYPE_FIELD "type"
#define CHANNEL_INFO_STEAM_TYPE_FIELD "stream_type"
#define CHANNEL_INFO_GROUP_FIELD "group"
#define CHANNEL_INFO_EPG_FIELD "epg"
#define CHANNEL_INFO_VIDEO_ENABLE_FIELD "video"
#define CHANNEL_INFO_AUDIO_ENABLE_FIELD "audio"

namespace fastotv {
namespace commands_info {

ChannelInfo::ChannelInfo()
    : stream_id_(invalid_stream_id),
      type_(PUBLIC),
      stream_type_(PROXY),
      group_(),
      epg_(),
      enable_audio_(true),
      enable_video_(true) {}

ChannelInfo::ChannelInfo(stream_id sid,
                         Type type,
                         StreamType stype,
                         const std::string& group,
                         const EpgInfo& epg,
                         bool enable_audio,
                         bool enable_video)
    : stream_id_(sid),
      type_(type),
      stream_type_(stype),
      group_(group),
      epg_(epg),
      enable_audio_(enable_audio),
      enable_video_(enable_video) {}

bool ChannelInfo::IsValid() const {
  return stream_id_ != invalid_stream_id && epg_.IsValid();
}

common::uri::Url ChannelInfo::GetUrl() const {
  return epg_.GetUrl();
}

std::string ChannelInfo::GetName() const {
  return epg_.GetDisplayName();
}

stream_id ChannelInfo::GetStreamID() const {
  return stream_id_;
}

ChannelInfo::Type ChannelInfo::GetType() const {
  return type_;
}

StreamType ChannelInfo::GetStreamType() const {
  return stream_type_;
}

EpgInfo ChannelInfo::GetEpg() const {
  return epg_;
}

std::string ChannelInfo::GetGroup() const {
  return group_;
}

bool ChannelInfo::IsEnableAudio() const {
  return enable_audio_;
}

bool ChannelInfo::IsEnableVideo() const {
  return enable_video_;
}

common::Error ChannelInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  json_object* jepg = nullptr;
  common::Error err = epg_.Serialize(&jepg);
  if (err) {
    return err;
  }

  json_object_object_add(deserialized, CHANNEL_INFO_ID_FIELD, json_object_new_string(stream_id_.c_str()));
  json_object_object_add(deserialized, CHANNEL_INFO_TYPE_FIELD, json_object_new_int(type_));
  json_object_object_add(deserialized, CHANNEL_INFO_STEAM_TYPE_FIELD, json_object_new_int(stream_type_));
  json_object_object_add(deserialized, CHANNEL_INFO_GROUP_FIELD, json_object_new_string(group_.c_str()));
  json_object_object_add(deserialized, CHANNEL_INFO_EPG_FIELD, jepg);
  json_object_object_add(deserialized, CHANNEL_INFO_AUDIO_ENABLE_FIELD, json_object_new_boolean(enable_audio_));
  json_object_object_add(deserialized, CHANNEL_INFO_VIDEO_ENABLE_FIELD, json_object_new_boolean(enable_video_));
  return common::Error();
}

common::Error ChannelInfo::DoDeSerialize(json_object* serialized) {
  json_object* jepg = nullptr;
  json_bool jepg_exists = json_object_object_get_ex(serialized, CHANNEL_INFO_EPG_FIELD, &jepg);
  if (!jepg_exists) {
    return common::make_error_inval();
  }

  EpgInfo epg;
  common::Error err = epg.DeSerialize(jepg);
  if (err) {
    return err;
  }

  stream_id sid;
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

  StreamType ui_type = PROXY;
  json_object* jui_type = nullptr;
  json_bool jui_type_exists = json_object_object_get_ex(serialized, CHANNEL_INFO_STEAM_TYPE_FIELD, &jui_type);
  if (jui_type_exists) {
    ui_type = static_cast<StreamType>(json_object_get_int(jui_type));
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

  ChannelInfo url(sid, type, ui_type, group, epg, enable_audio, enable_video);
  if (!url.IsValid()) {
    return common::make_error_inval();
  }

  *this = url;
  return common::Error();
}

bool ChannelInfo::Equals(const ChannelInfo& url) const {
  return stream_id_ == url.stream_id_ && epg_ == url.epg_ && enable_audio_ == url.enable_audio_ &&
         enable_video_ == url.enable_video_;
}

}  // namespace commands_info
}  // namespace fastotv
