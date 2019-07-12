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

#include <gtest/gtest.h>

#include <fastotv/commands_info/auth_info.h>
#include <fastotv/commands_info/channel_info.h>
#include <fastotv/commands_info/channels_info.h>
#include <fastotv/commands_info/client_info.h>
#include <fastotv/commands_info/epg_info.h>
#include <fastotv/commands_info/ping_info.h>
#include <fastotv/commands_info/programme_info.h>
#include <fastotv/commands_info/runtime_channel_info.h>
#include <fastotv/commands_info/server_info.h>

typedef fastotv::commands_info::AuthInfo::serialize_type serialize_t;

TEST(ChannelInfo, serialize_deserialize) {
  const std::string name = "alex";
  const fastotv::stream_id stream_id = "123";
  const common::uri::Url url("http://localhost:8080/hls/69_avformat_test_alex_2/play.m3u8");
  const bool enable_video = false;
  const bool enable_audio = true;

  fastotv::commands_info::EpgInfo epg_info(stream_id, url, name);
  ASSERT_EQ(epg_info.GetDisplayName(), name);
  ASSERT_EQ(epg_info.GetTvgID(), stream_id);
  ASSERT_EQ(epg_info.GetUrl(), url);

  serialize_t user;
  common::Error err = epg_info.Serialize(&user);
  ASSERT_TRUE(!err);
  fastotv::commands_info::EpgInfo depg;
  err = depg.DeSerialize(user);
  ASSERT_TRUE(!err);

  ASSERT_EQ(epg_info, depg);

  fastotv::commands_info::ChannelInfo http_uri(stream_id, epg_info, enable_audio, enable_video);
  ASSERT_EQ(http_uri.GetName(), name);
  ASSERT_EQ(http_uri.GetStreamID(), stream_id);
  ASSERT_EQ(http_uri.GetUrl(), url);
  ASSERT_EQ(http_uri.IsEnableAudio(), enable_audio);
  ASSERT_EQ(http_uri.IsEnableVideo(), enable_video);

  serialize_t ser;
  err = http_uri.Serialize(&ser);
  ASSERT_TRUE(!err);
  fastotv::commands_info::ChannelInfo dhttp_uri;
  err = dhttp_uri.DeSerialize(ser);
  ASSERT_TRUE(!err);

  ASSERT_EQ(http_uri, dhttp_uri);

  const std::string channel_inf_json =
      R""({"audio": true, "video": true, "id": "5d0db38335c23f2dd95e803d", "epg": {"icon": "https://upload.wikimedia.org/wikipedia/commons/thumb/0/0c/Channel_NewsAsia_logo_%28shape_only%29.svg/220px-Channel_NewsAsia_logo_%28shape_only%29.svg.png", "url": "https://drsh196ivjwe8.cloudfront.net/hls/cnai/03.m3u8?fluxustv.m3u8", "display_name": "Channel NewsAsia (Opt-1)", "id": "", "programs": []}})"";
  fastotv::commands_info::ChannelInfo chan;
  err = chan.DeSerializeFromString(channel_inf_json);
  ASSERT_TRUE(!err);
}

TEST(ServerInfo, serialize_deserialize) {
  const common::net::HostAndPort hs = common::net::HostAndPort::CreateLocalHost(3554);

  fastotv::commands_info::ServerInfo serv_info(hs);
  ASSERT_EQ(serv_info.GetBandwidthHost(), hs);

  serialize_t ser;
  common::Error err = serv_info.Serialize(&ser);
  ASSERT_TRUE(!err);
  fastotv::commands_info::ServerInfo dser;
  err = dser.DeSerialize(ser);
  ASSERT_TRUE(!err);

  ASSERT_EQ(serv_info.GetBandwidthHost(), dser.GetBandwidthHost());
}

TEST(EpgInfo, serialize_deserialize) {
  const fastotv::commands_info::EpgInfo::tvg_id_t id = "tid";
  const common::uri::Url uri("http://fasotgt.com:8080/master.m3u8");
  const std::string name = "test";

  fastotv::commands_info::EpgInfo epg(id, uri, name);
  ASSERT_TRUE(epg.IsValid());
  serialize_t ser;
  common::Error err = epg.Serialize(&ser);
  ASSERT_TRUE(!err);

  fastotv::commands_info::EpgInfo dser;
  ASSERT_TRUE(!dser.IsValid());
  err = dser.DeSerialize(ser);
  ASSERT_TRUE(!err);
  ASSERT_TRUE(dser.IsValid());

  ASSERT_EQ(epg.GetTvgID(), dser.GetTvgID());
  ASSERT_EQ(epg.GetUrl(), dser.GetUrl());
  ASSERT_EQ(epg.GetDisplayName(), dser.GetDisplayName());
  ASSERT_EQ(epg, dser);
}

TEST(ServerPingInfo, serialize_deserialize) {
  fastotv::commands_info::ServerPingInfo ping_info;
  serialize_t ser;
  common::Error err = ping_info.Serialize(&ser);
  ASSERT_TRUE(!err);
  fastotv::commands_info::ServerPingInfo dser;
  err = dser.DeSerialize(ser);
  ASSERT_TRUE(!err);

  ASSERT_EQ(ping_info.GetTimeStamp(), dser.GetTimeStamp());
}

TEST(ClientPingInfo, serialize_deserialize) {
  fastotv::commands_info::ClientPingInfo ping_info;
  serialize_t ser;
  common::Error err = ping_info.Serialize(&ser);
  ASSERT_TRUE(!err);
  fastotv::commands_info::ClientPingInfo dser;
  err = dser.DeSerialize(ser);
  ASSERT_TRUE(!err);

  ASSERT_EQ(ping_info.GetTimeStamp(), dser.GetTimeStamp());
}

TEST(ProgrammeInfo, serialize_deserialize) {
  const fastotv::stream_id id = "1234";
  const fastotv::timestamp_t start_time = 1;
  const fastotv::timestamp_t stop_time = 123;
  const std::string title = "tit";

  fastotv::commands_info::ProgrammeInfo prog(id, start_time, stop_time, title);
  ASSERT_TRUE(prog.IsValid());
  ASSERT_EQ(prog.GetChannel(), id);
  ASSERT_EQ(prog.GetStart(), start_time);
  ASSERT_EQ(prog.GetStop(), stop_time);
  ASSERT_EQ(prog.GetTitle(), title);

  serialize_t ser;
  common::Error err = prog.Serialize(&ser);
  ASSERT_TRUE(!err);

  fastotv::commands_info::ProgrammeInfo dser;
  ASSERT_TRUE(!dser.IsValid());
  err = dser.DeSerialize(ser);
  ASSERT_TRUE(!err);

  ASSERT_EQ(prog.GetChannel(), dser.GetChannel());
  ASSERT_EQ(prog.GetStart(), dser.GetStart());
  ASSERT_EQ(prog.GetStop(), dser.GetStop());
  ASSERT_EQ(prog.GetTitle(), dser.GetTitle());
  ASSERT_EQ(prog, dser);
}

TEST(ClientInfo, serialize_deserialize) {
  const fastotv::login_t login = "Alex";
  const std::string os = "Os";
  const std::string cpu_brand = "brand";
  const int64_t ram_total = 1;
  const int64_t ram_free = 2;
  const fastotv::bandwidth_t bandwidth = 5;

  fastotv::commands_info::ClientInfo cinf(login, os, cpu_brand, ram_total, ram_free, bandwidth);
  ASSERT_EQ(cinf.GetLogin(), login);
  ASSERT_EQ(cinf.GetOs(), os);
  ASSERT_EQ(cinf.GetCpuBrand(), cpu_brand);
  ASSERT_EQ(cinf.GetRamTotal(), ram_total);
  ASSERT_EQ(cinf.GetRamFree(), ram_free);
  ASSERT_EQ(cinf.GetBandwidth(), bandwidth);

  serialize_t ser;
  common::Error err = cinf.Serialize(&ser);
  ASSERT_TRUE(!err);
  fastotv::commands_info::ClientInfo dcinf;
  err = dcinf.DeSerialize(ser);
  ASSERT_TRUE(!err);

  ASSERT_EQ(cinf.GetLogin(), dcinf.GetLogin());
  ASSERT_EQ(cinf.GetOs(), dcinf.GetOs());
  ASSERT_EQ(cinf.GetCpuBrand(), dcinf.GetCpuBrand());
  ASSERT_EQ(cinf.GetRamTotal(), dcinf.GetRamTotal());
  ASSERT_EQ(cinf.GetRamFree(), dcinf.GetRamFree());
  ASSERT_EQ(cinf.GetBandwidth(), dcinf.GetBandwidth());
}

TEST(channels_t, serialize_deserialize) {
  const std::string name = "alex";
  const fastotv::stream_id stream_id = "123";
  const common::uri::Url url("http://localhost:8080/hls/69_avformat_test_alex_2/play.m3u8");
  const bool enable_video = false;
  const bool enable_audio = true;

  fastotv::commands_info::ChannelsInfo channels;
  fastotv::commands_info::EpgInfo epg_info(stream_id, url, name);
  channels.AddChannel(fastotv::commands_info::ChannelInfo(stream_id, epg_info, enable_audio, enable_video));
  ASSERT_EQ(channels.GetSize(), 1);

  serialize_t ser;
  common::Error err = channels.Serialize(&ser);
  ASSERT_TRUE(!err);
  fastotv::commands_info::ChannelsInfo dchannels;
  err = dchannels.DeSerialize(ser);
  ASSERT_TRUE(!err);

  ASSERT_EQ(channels, dchannels);
}

TEST(AuthInfo, serialize_deserialize) {
  const std::string login = "palec";
  const std::string password = "ff";
  const std::string device = "dev";
  fastotv::commands_info::AuthInfo auth_info(login, password, device);
  ASSERT_EQ(auth_info.GetLogin(), login);
  ASSERT_EQ(auth_info.GetPassword(), password);
  ASSERT_EQ(auth_info.GetDeviceID(), device);
  serialize_t ser;
  common::Error err = auth_info.Serialize(&ser);
  ASSERT_TRUE(!err);
  fastotv::commands_info::AuthInfo dser;
  err = dser.DeSerialize(ser);
  ASSERT_TRUE(!err);

  ASSERT_EQ(auth_info, dser);
}

TEST(RuntimeChannelInfo, serialize_deserialize) {
  const std::string channel_id = "1234";
  const size_t watchers = 7;
  fastotv::commands_info::RuntimeChannelInfo rinf_info(channel_id, watchers);
  ASSERT_EQ(rinf_info.GetStreamID(), channel_id);
  ASSERT_EQ(rinf_info.GetWatchersCount(), watchers);
  serialize_t ser;
  common::Error err = rinf_info.Serialize(&ser);
  ASSERT_TRUE(!err);
  fastotv::commands_info::RuntimeChannelInfo dser;
  err = dser.DeSerialize(ser);
  ASSERT_TRUE(!err);

  ASSERT_EQ(rinf_info, dser);
}
