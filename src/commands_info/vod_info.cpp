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

#include <fastotv/commands_info/vod_info.h>

#define CHANNEL_INFO_MOVIE_FIELD "vod"

namespace fastotv {
namespace commands_info {

VodInfo::VodInfo() : base_class(), movie_() {}

VodInfo::VodInfo(stream_id_t sid,
                 const std::string& group,
                 const MovieInfo& movie,
                 bool enable_audio,
                 bool enable_video)
    : base_class(sid, group, enable_audio, enable_video), movie_(movie) {}

bool VodInfo::IsValid() const {
  return base_class::IsValid() && movie_.IsValid();
}

MovieInfo VodInfo::GetMovieInfo() const {
  return movie_;
}

void VodInfo::SetMovieInfo(const MovieInfo& movie) {
  movie_ = movie;
}

common::Error VodInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  common::Error err = base_class::SerializeFields(deserialized);
  if (err) {
    return err;
  }

  json_object* jmovie = nullptr;
  err = movie_.Serialize(&jmovie);
  if (err) {
    return err;
  }

  json_object_object_add(deserialized, CHANNEL_INFO_MOVIE_FIELD, jmovie);
  return common::Error();
}

common::Error VodInfo::DoDeSerialize(json_object* serialized) {
  VodInfo inf;
  common::Error err = inf.base_class::DoDeSerialize(serialized);
  if (err) {
    return err;
  }

  json_object* jepg = nullptr;
  json_bool jepg_exists = json_object_object_get_ex(serialized, CHANNEL_INFO_MOVIE_FIELD, &jepg);
  if (!jepg_exists) {
    return common::make_error_inval();
  }

  MovieInfo epg;
  err = epg.DeSerialize(jepg);
  if (err) {
    return err;
  }

  inf.movie_ = epg;
  *this = inf;
  return common::Error();
}

bool VodInfo::Equals(const VodInfo& url) const {
  return base_class::Equals(url) && movie_ == url.movie_;
}

}  // namespace commands_info
}  // namespace fastotv
