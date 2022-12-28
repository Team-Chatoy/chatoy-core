#include <catch2/catch_test_macros.hpp>

#include <chatoy/wsconnection.hpp>
#include <chatoy/user.hpp>
#include <chatoy/types.hpp>

TEST_CASE("ws connect") {
  chatoy::Resp res = chatoy::login("116.62.242.193:4000", "LiSi", "1919810");  
  chatoy::Wsconnection wsc("116.62.242.193:4000", res.msg);

  REQUIRE(wsc.auth_resp.msg == "");
  REQUIRE(wsc.auth_resp.code == 0);
  REQUIRE(wsc.auth_resp.type == "Auth");
}

TEST_CASE("ws sendmsg") {
  chatoy::Resp res = chatoy::login("116.62.242.193:4000", "LiSi", "1919810");  
  chatoy::Wsconnection wsc("116.62.242.193:4000", res.msg);

  chatoy::ReceiveMsg receive_msg = wsc.send_msg(1, "Text", "hello");
  chatoy::ReceiveMsg receive_msg2 = wsc.send_msg(1, "Text", "chatoy");

  REQUIRE(receive_msg.data.modified == false);
  REQUIRE(receive_msg.type == "Recv");
  REQUIRE(receive_msg.data.room == 1);
  REQUIRE(receive_msg.data.sender == 2);
  REQUIRE(receive_msg.data.data.text == "hello");

  REQUIRE(receive_msg2.data.data.text == "chatoy");
}
