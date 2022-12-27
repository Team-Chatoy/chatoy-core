#include <catch2/catch_test_macros.hpp>

#include <chatoy/types.hpp>
#include <chatoy/user.hpp>
#include <chatoy/room.hpp>

TEST_CASE("create_room") {
  auto [_code, token] = chatoy::login("116.62.242.193:4000", "ZhangSan", "114514");
  auto [id] = chatoy::create_room("116.62.242.193:4000", token , "Test Room");

  REQUIRE(id > 0);
}

TEST_CASE("join_room") {
  auto [_code, token] = chatoy::login("116.62.242.193:4000", "ZhangSan", "114514");
  auto [code, msg] = chatoy::join_room("116.62.242.193:4000", token, 1);

  REQUIRE(code == 4);
  REQUIRE(msg == "Failed to join the room `1`!");
}

TEST_CASE("get_room") {
  chatoy::RoomInfo res = chatoy::get_room("116.62.242.193:4000", 1);
  
  REQUIRE(res.id == 1);
  REQUIRE(res.name == "room1");
  REQUIRE(res.created == "2022-12-24T19:30:50.507134731+08:00");
}

TEST_CASE("my_rooms") {
  auto [_code, token] = chatoy::login("116.62.242.193:4000", "LiSi", "1919810");
  auto rooms = chatoy::my_rooms("116.62.242.193:4000", token);

  REQUIRE(rooms.size() == 2);
}
