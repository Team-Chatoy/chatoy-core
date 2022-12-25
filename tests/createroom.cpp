#include <catch2/catch_test_macros.hpp>

#include <chatoy/login.hpp>
#include <chatoy/room.hpp>

TEST_CASE("createroom test", "[creatroom]") {
  const auto login_res = chatoy::login("116.62.242.193", "4000", "ZhangSan", "114514");
  const std::string token = login_res.msg;
	const auto create_res = chatoy::create_room("116.62.242.193", "4000", token ,"testroom");

	REQUIRE(create_res.id > 0);
}
