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
#include <vector>

#include <common/serializer/json_serializer.h>
#include <common/uri/url.h>  // for Uri

namespace fastotv {
namespace commands_info {

class MovieInfo : public common::serializer::JsonSerializer<MovieInfo> {
 public:
  typedef std::vector<common::uri::Url> urls_t;

  MovieInfo();
  MovieInfo(const urls_t& urls, const std::string& description, const common::uri::Url& preview_icon);

  bool IsValid() const;

  bool Equals(const MovieInfo& os) const;

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  urls_t urls_;
  std::string description_;
  common::uri::Url preview_icon_;
};

inline bool operator==(const MovieInfo& left, const MovieInfo& right) {
  return left.Equals(right);
}

inline bool operator!=(const MovieInfo& x, const MovieInfo& y) {
  return !(x == y);
}

}  // namespace commands_info
}  // namespace fastotv