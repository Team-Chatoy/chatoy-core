#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/asio/strand.hpp>
#include <chatoy/core.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>

namespace chatoy {

// a WebSocket connection
class Wsconnection : public std::enable_shared_from_this<session>{
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

  auto receive_msg() -> ReceiveMsg;
};



} // end namespace chatoy
