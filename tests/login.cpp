#include <catch2/catch_test_macros.hpp>

#include <chatoy/login.hpp>

TEST_CASE("login test", "[login]") {
  chatoy::LoginResp res = chatoy::login("116.62.242.193", "4000", "ZhangSan", "1919810");

  REQUIRE(res.code == 4);
  REQUIRE(res.msg == "Password error!");
}
