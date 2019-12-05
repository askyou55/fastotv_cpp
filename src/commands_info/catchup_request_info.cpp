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

#include <fastotv/commands_info/catchup_request_info.h>

#define CATCHUP_REQUEST_INFO_ID_FIELD "id"
#define CATCHUP_REQUEST_INFO_START_FIELD "start"
#define CATCHUP_REQUEST_INFO_STOP_FIELD "stop"

namespace fastotv {
namespace commands_info {

CatchupRequestInfo::CatchupRequestInfo() : sid_(invalid_stream_id), start_time_(0), stop_time_(0) {}

CatchupRequestInfo::CatchupRequestInfo(stream_id_t sid, timestamp_t start_time, timestamp_t stop_time)
    : sid_(sid), start_time_(start_time), stop_time_(stop_time) {}

CatchupRequestInfo::~CatchupRequestInfo() {}

bool CatchupRequestInfo::IsValid() const {
  return sid_ != invalid_stream_id;
}

void CatchupRequestInfo::SetStreamID(stream_id_t sid) {
  sid_ = sid;
}

stream_id_t CatchupRequestInfo::GetStreamID() const {
  return sid_;
}

void CatchupRequestInfo::SetStart(timestamp_t start) {
  start_time_ = start;
}

timestamp_t CatchupRequestInfo::GetStart() const {
  return start_time_;
}

void CatchupRequestInfo::SetStop(timestamp_t stop) {
  stop_time_ = stop;
}

timestamp_t CatchupRequestInfo::GetStop() const {
  return stop_time_;
}

bool CatchupRequestInfo::Equals(const CatchupRequestInfo& inf) const {
  return sid_ == inf.sid_;
}

common::Error CatchupRequestInfo::DoDeSerialize(json_object* serialized) {
  CatchupRequestInfo inf;
  json_object* jcid = nullptr;
  json_bool jcid_exists = json_object_object_get_ex(serialized, CATCHUP_REQUEST_INFO_ID_FIELD, &jcid);
  if (!jcid_exists) {
    return common::make_error_inval();
  }

  stream_id_t cid = json_object_get_string(jcid);
  if (cid == invalid_stream_id) {
    return common::make_error_inval();
  }
  inf.sid_ = cid;

  json_object* jstart = nullptr;
  json_bool jstart_exists = json_object_object_get_ex(serialized, CATCHUP_REQUEST_INFO_START_FIELD, &jstart);
  if (!jstart_exists) {
    return common::make_error_inval();
  }

  json_object* jstop = nullptr;
  json_bool jstop_exists = json_object_object_get_ex(serialized, CATCHUP_REQUEST_INFO_STOP_FIELD, &jstop);
  if (!jstop_exists) {
    return common::make_error_inval();
  }

  *this = inf;
  return common::Error();
}

common::Error CatchupRequestInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  json_object_object_add(deserialized, CATCHUP_REQUEST_INFO_ID_FIELD, json_object_new_string(sid_.c_str()));
  json_object_object_add(deserialized, CATCHUP_REQUEST_INFO_START_FIELD, json_object_new_int64(start_time_));
  json_object_object_add(deserialized, CATCHUP_REQUEST_INFO_STOP_FIELD, json_object_new_int64(stop_time_));
  return common::Error();
}

}  // namespace commands_info
}  // namespace fastotv
