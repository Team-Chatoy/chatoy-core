#include <catch2/catch_test_macros.hpp>

#include <chatoy/core.hpp>
#include <chatoy/register.hpp>

TEST_CASE("basic test", "[basic]") {
  std::string expected =
    "<html>"                                            "\r\n"
    "<head><title>301 Moved Permanently</title></head>" "\r\n"
    "<body>"                                            "\r\n"
    "<center><h1>301 Moved Permanently</h1></center>"   "\r\n"
    "<hr><center>nginx/1.20.2</center>"                 "\r\n"
    "</body>"                                           "\r\n"
    "</html>"                                           "\r\n";
  std::string expected2 =
    "{\"code\":0,\"msg\":\"success\",\"data\":{\"username\":\"Aux\",\"password\":\"114514\"}}";
  std::string res = chatoy::get("yurzhang.com");
  std::string res2 = chatoy::regist("yurzhang.com", "Aux", "114514");
  REQUIRE(res == expected);
  REQUIRE(res2 == expected2);
}
