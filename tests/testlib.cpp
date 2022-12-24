#include <catch2/catch_test_macros.hpp>

#include <chatoy/core.hpp>

TEST_CASE("basic test", "[basic]") {
  std::string expected =
    "<html>"                                            "\r\n"
    "<head><title>301 Moved Permanently</title></head>" "\r\n"
    "<body>"                                            "\r\n"
    "<center><h1>301 Moved Permanently</h1></center>"   "\r\n"
    "<hr><center>nginx/1.22.1</center>"                 "\r\n"
    "</body>"                                           "\r\n"
    "</html>"                                           "\r\n";
  std::string res = chatoy::get("yurzhang.com");

  REQUIRE(res == expected);
}
