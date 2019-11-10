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
#include <fastotv/types.h>

namespace fastotv {
namespace commands_info {

class MovieInfo : public common::serializer::JsonSerializer<MovieInfo> {
 public:
  typedef std::vector<common::uri::Url> urls_t;
  enum Type { VODS, SERIES };

  MovieInfo();
  MovieInfo(const std::string& name,
            const urls_t& urls,
            const std::string& description,
            const common::uri::Url& preview_icon,
            const common::uri::Url& trailer_url,
            double user_score,
            timestamp_t prime_date,
            const std::string& country,
            timestamp_t duration,
            Type type);

  bool IsValid() const;

  void SetUrls(const urls_t& urls);
  urls_t GetUrls() const;

  void SetDisplayName(const std::string& name);
  std::string GetDisplayName() const;

  void SetDescription(const std::string& descr);
  std::string GetDescription() const;

  void SetPreviewIcon(const common::uri::Url& url);
  common::uri::Url GetPreviewIcon() const;

  common::uri::Url GetTrailerUrl() const;
  double GetUserScore() const;
  timestamp_t GetPrimeDate() const;
  const std::string& GetCountry() const;
  timestamp_t GetDuration() const;

  Type GetType() const;
  void SetType(Type type);

  bool Equals(const MovieInfo& os) const;

  static const common::uri::Url& GetUnknownIconUrl();
  static bool IsUnknownIconUrl(const common::uri::Url& url);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* deserialized) const override;

 private:
  std::string display_name_;
  urls_t urls_;
  std::string description_;
  common::uri::Url preview_icon_;
  common::uri::Url trailer_url_;
  double user_score_;
  timestamp_t prime_date_;
  std::string country_;
  timestamp_t duration_;
  Type type_;
};

inline bool operator==(const MovieInfo& left, const MovieInfo& right) {
  return left.Equals(right);
}

inline bool operator!=(const MovieInfo& x, const MovieInfo& y) {
  return !(x == y);
}

}  // namespace commands_info
}  // namespace fastotv
