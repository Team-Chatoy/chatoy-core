#include <catch2/catch_test_macros.hpp>

#include <chatoy/register.hpp>

TEST_CASE("register test", "[register]") {
  chatoy::RegisterResp res = chatoy::regist("116.62.242.193", "4000", "ZhangSan", "114514");

  REQUIRE(res.code == 2);
  REQUIRE(res.msg == "This username has been used!");
}
