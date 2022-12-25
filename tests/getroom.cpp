#include <catch2/catch_test_macros.hpp>

#include <chatoy/room.hpp>

TEST_CASE("getroom test", "[getroom]") {
  const auto get_res = chatoy::get_room("116.62.242.193", "4000", 1);
  
  REQUIRE(get_res.id == 1);
}