#include <catch2/catch_test_macros.hpp>

#include <chatoy/login.hpp>
#include <chatoy/room.hpp>

TEST_CASE("joinroom test", "[joinroom]") {
  const auto login_res = chatoy::login("116.62.242.193", "4000", "ZhangSan", "114514");
  const std::string token = login_res.msg;
  const auto join_res = chatoy::join_room("116.62.242.193", "4000", token, 1);

	REQUIRE(join_res.code == 4);
	REQUIRE(join_res.msg == "Failed to join the new room!");
}