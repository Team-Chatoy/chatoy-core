#include <chatoy/wsconnect.hpp>
#include <chatoy/types.hpp>

namespace chatoy {

Wsconnection::Wsconnection(
  const std::string& raw_host,
  const std::string& path,
  const std::string& token
) {
  namespace beast = boost::beast;
  namespace http = beast::http;
  namespace websocket = beast::websocket;
  namespace net = boost::asio;
  using tcp = boost::asio::ip::tcp;

  tcp::resolver resolver{ioc};
  auto [host, port] = split(raw_host, ':');

  auto const results = resolver.resolve(host, port);
  auto ep = net::connect(ws.next_layer(), results);

  host += ':' + std::to_string(ep.port());
  
  ws.set_option(websocket::stream_base::decorator(
    [](websocket::request_type& req) {
      req.set(http::field::user_agent,
      std::string(BOOST_BEAST_VERSION_STRING) +
        " websocket-client-coro");
  }));

  ws.handshake(host, "/ws");

  nlohmann::json j;
  j["type"] = "Auth";
  j["token"] = token;

  ws.write(net::buffer(j.dump()));

  beast::flat_buffer buffer;

  ws.read(buffer);
  
  std::string ret = beast::buffers_to_string(buffer.data());

  this->auth_resp = nlohmann::json::parse(ret);
}

Wsconnection::~Wsconnection() {
  ws.close(boost::beast::websocket::close_code::normal);
}

auto Wsconnection::send_msg(
  const int roomid,
  const std::string& text_type,
  const std::string& text 
) -> ReceiveMsg {

  boost::uuids::uuid a_uuid = boost::uuids::random_generator()(); 
  std::string uuid = boost::uuids::to_string(a_uuid);

  TextData text_data;
  text_data.type = text_type;
  text_data.text = text;

  nlohmann::json j;
  j["type"] = "Msg";
  j["uuid"] = uuid;
  j["room"] = roomid;
  j["data"] = text_data;

  ws.write(boost::asio::buffer(j.dump()));

  boost::beast::flat_buffer buffer;

  ws.read(buffer);

  std::string result = boost::beast::buffers_to_string(buffer.data());

  return nlohmann::json::parse(result);
}

} // end namespace chatoy
