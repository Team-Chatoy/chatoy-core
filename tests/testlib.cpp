#include <catch2/catch_test_macros.hpp>

#include <chatoy/core.hpp>
#include <chatoy/register.hpp>
#include <chatoy/login.hpp>

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

TEST_CASE("register test", "[register]") {
  std::string expected = R"({"code":2,"msg":"This username has been used!"})";
  std::string res = chatoy::regist("116.62.242.193", "4000", "ZhangSan", "114514");

  REQUIRE(res == expected);
}

TEST_CASE("login test", "[login]") {
  std::string expected = R"({"code":0,"msg":""})";
  std::string res = chatoy::login("116.62.242.193", "4000", "ZhangSan", "114514");

  REQUIRE(res == expected);
}
