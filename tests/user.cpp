#include <catch2/catch_test_macros.hpp>

#include <chatoy/types.hpp>
#include <chatoy/user.hpp>

TEST_CASE("register") {
  chatoy::Resp res = chatoy::regist("116.62.242.193:4000", "ZhangSan", "114514");

  REQUIRE(res.code == 2);
  REQUIRE(res.msg == "This username has been used!");
}

TEST_CASE("login") {
  chatoy::Resp res = chatoy::login("116.62.242.193:4000", "ZhangSan", "1919810");

  REQUIRE(res.code == 4);
  REQUIRE(res.msg == "Password error!");
}

TEST_CASE("get_user") {
  chatoy::UserInfo res = chatoy::get_user("116.62.242.193:4000", 1);

  REQUIRE(res.id == 1);
  REQUIRE(res.username == "ZhangSan");
  REQUIRE(res.status == 0);
}
