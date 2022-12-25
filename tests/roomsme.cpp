#include <catch2/catch_test_macros.hpp>

#include <chatoy/login.hpp>
#include <chatoy/room.hpp>

TEST_CASE("roomsme test", "[roomsme]") {
  const auto login_res = chatoy::login("116.62.242.193", "4000", "LiSi", "1919810");
  const std::string token = login_res.msg;
  const auto roomsme_res = chatoy::my_rooms("116.62.242.193", "4000", token);

  REQUIRE(roomsme_res.size() == 2);
	REQUIRE(roomsme_res[0].id == 2);
  REQUIRE(roomsme_res[0].name == "room1");
}