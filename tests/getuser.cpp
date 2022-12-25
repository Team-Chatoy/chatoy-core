#include <catch2/catch_test_macros.hpp>

#include <chatoy/getuser.hpp>

TEST_CASE("getuser test", "[getuser]") {
  const auto get_res = chatoy::get_user("116.62.242.193", "4000", 1);

  REQUIRE(get_res.id == 1);
  REQUIRE(get_res.username == "ZhangSan");
  REQUIRE(get_res.status == 0);
}