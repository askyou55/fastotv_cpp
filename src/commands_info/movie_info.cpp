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

#include <fastotv/commands_info/movie_info.h>

#define MOVIE_INFO_URLS_FIELD "urls"
#define MOVIE_INFO_DESCRIPTION_FIELD "description"
#define MOVIE_INFO_PREVIEW_ICON_FIELD "preview_icon"

namespace fastotv {
namespace commands_info {

MovieInfo::MovieInfo() : urls_(), description_(), preview_icon_() {}

MovieInfo::MovieInfo(const urls_t& urls, const std::string& description, const common::uri::Url& preview_icon)
    : urls_(urls), description_(description), preview_icon_(preview_icon) {}

bool MovieInfo::IsValid() const {
  return !urls_.empty();
}

void MovieInfo::SetUrls(const urls_t& urls) {
  urls_ = urls;
}

MovieInfo::urls_t MovieInfo::GetUrls() const {
  return urls_;
}

void MovieInfo::SetDescription(const std::string& descr) {
  description_ = descr;
}

std::string MovieInfo::GetDescription() const {
  return description_;
}

void MovieInfo::SetPreviewIcon(const common::uri::Url& url) {
  preview_icon_ = url;
}

common::uri::Url MovieInfo::GetPreviewIcon() const {
  return preview_icon_;
}

common::Error MovieInfo::SerializeFields(json_object* deserialized) const {
  if (!IsValid()) {
    return common::make_error_inval();
  }

  json_object_object_add(deserialized, MOVIE_INFO_DESCRIPTION_FIELD, json_object_new_string(description_.c_str()));
  const std::string icon_url_str = preview_icon_.GetUrl();
  json_object_object_add(deserialized, MOVIE_INFO_PREVIEW_ICON_FIELD, json_object_new_string(icon_url_str.c_str()));

  json_object* jurls = json_object_new_array();
  for (const auto url : urls_) {
    std::string url_str = url.GetUrl();
    json_object* jurl = json_object_new_string(url_str.c_str());
    json_object_array_add(jurls, jurl);
  }
  json_object_object_add(deserialized, MOVIE_INFO_URLS_FIELD, jurls);
  return common::Error();
}

common::Error MovieInfo::DoDeSerialize(json_object* serialized) {
  json_object* jurls = nullptr;
  json_bool jurls_exists = json_object_object_get_ex(serialized, MOVIE_INFO_URLS_FIELD, &jurls);
  if (!jurls_exists) {
    return common::make_error_inval();
  }

  urls_t urls;
  size_t len = json_object_array_length(jurls);
  for (size_t i = 0; i < len; ++i) {
    json_object* jurl = json_object_array_get_idx(jurls, i);
    const std::string url_str = json_object_get_string(jurl);
    common::uri::Url url(url_str);
    if (url.IsValid()) {
      urls.push_back(url);
    }
  }

  std::string description;
  json_object* jdescription = nullptr;
  json_bool jdescription_exists = json_object_object_get_ex(serialized, MOVIE_INFO_DESCRIPTION_FIELD, &jdescription);
  if (jdescription_exists) {
    description = json_object_get_string(jdescription);
  }

  common::uri::Url preview_icon;
  json_object* jpreview_icon = nullptr;
  json_bool jpreview_icon_exists = json_object_object_get_ex(serialized, MOVIE_INFO_PREVIEW_ICON_FIELD, &jpreview_icon);
  if (jpreview_icon_exists) {
    preview_icon = common::uri::Url(json_object_get_string(jpreview_icon));
  }

  MovieInfo url(urls, description, preview_icon);
  *this = url;
  return common::Error();
}

bool MovieInfo::Equals(const MovieInfo& url) const {
  return urls_ == url.urls_ && description_ == url.description_ && preview_icon_ == url.preview_icon_;
}

}  // namespace commands_info
}  // namespace fastotv
