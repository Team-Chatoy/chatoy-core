#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include <chatoy/core.hpp>

namespace chatoy {

// a WebSocket connection
class Wsconnection {
private:
  boost::asio::io_context ioc;
  boost::beast::websocket::stream<boost::asio::ip::tcp::socket> ws{ioc};
public:
  AuthResp auth_resp; // for test
  Wsconnection(
    const std::string& raw_host,
    const std::string& token
  );
  auto send_msg (
    const int roomid,
    const std::string& text_type,
    const std::string& text 
  ) -> ReceiveMsg;
  ~Wsconnection();
};

} // end namespace chatoy
