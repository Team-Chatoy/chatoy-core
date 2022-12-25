#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

#include <nlohmann/json.hpp>

#include <chatoy/room.hpp>

namespace chatoy {
	
void from_json(const nlohmann::json& j, CreateResp& resp) {
  j.at("id").get_to(resp.id);
}

void from_json(const nlohmann::json& j, JoinResp& resp) {
  j.at("code").get_to(resp.code);
  j.at("msg").get_to(resp.msg);
}

void from_json(const nlohmann::json& j, RoomInfo& resp) {
  j.at("id").get_to(resp.id);
  j.at("name").get_to(resp.name);
	j.at("description").get_to(resp.description);
	j.at("created").get_to(resp.created);
}

auto create_room(
	const std::string& url,
  const std::string& port,
	const std::string& token,
	const std::string& roomname
) -> CreateResp {
	namespace beast = boost::beast;
  namespace http = beast::http;
  namespace net = boost::asio;
  using tcp = net::ip::tcp;

  using json = nlohmann::json;
	
	net::io_context ioc;

	tcp::resolver resolver(ioc);
  beast::tcp_stream stream(ioc);

	// http://${url}:${port}
	auto const results = resolver.resolve(url, port);

  stream.connect(results);

	// POST /rooms HTTP/1.1
	http::request<http::string_body> req{http::verb::post, "/rooms", 11};
  req.set(http::field::host, url);
  req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
  req.set(http::field::content_type, "application/json");
  json payload = {
    {"token", token},
    {"name", roomname}
  };
  req.body() = payload.dump();
  req.prepare_payload();

	http::write(stream, req);

  beast::flat_buffer buffer;

  http::response<http::basic_string_body<char>> res;
  http::read(stream, buffer, res);

	CreateResp result = json::parse(res.body());

	// Close the socket
  beast::error_code ec;
  stream.socket().shutdown(tcp::socket::shutdown_both, ec);

  if (ec && ec != beast::errc::not_connected)
    throw beast::system_error{ec};

  return result;
}

auto join_room(
	const std::string& url,
  const std::string& port,
	const std::string& token,
	const int roomid
) -> JoinResp {
	namespace beast = boost::beast;
  namespace http = beast::http;
  namespace net = boost::asio;
  using tcp = net::ip::tcp;

  using json = nlohmann::json;
	
	net::io_context ioc;

	tcp::resolver resolver(ioc);
  beast::tcp_stream stream(ioc);

	// http://${url}:${port}
	auto const results = resolver.resolve(url, port);

  stream.connect(results);

	// POST /rooms/:id/join HTTP/1.1
	std::string target = "/rooms/" + std::to_string(roomid) + "/join";
	http::request<http::string_body> req{http::verb::post, target, 11};
  req.set(http::field::host, url);
  req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
  req.set(http::field::content_type, "application/json");
  json payload = {
    {"token", token},
  };
  req.body() = payload.dump();
  req.prepare_payload();

	http::write(stream, req);

  beast::flat_buffer buffer;

  http::response<http::basic_string_body<char>> res;
  http::read(stream, buffer, res);

  JoinResp result = json::parse(res.body());

	// Close the socket
  beast::error_code ec;
  stream.socket().shutdown(tcp::socket::shutdown_both, ec);

  if (ec && ec != beast::errc::not_connected)
    throw beast::system_error{ec};

  return result;
}

auto get_room(
	const std::string& url,
  const std::string& port,
	const int roomid
) -> RoomInfo {
	namespace beast = boost::beast;
  namespace http = beast::http;
  namespace net = boost::asio;
  using tcp = net::ip::tcp;

  using json = nlohmann::json;
	
	net::io_context ioc;

	tcp::resolver resolver(ioc);
  beast::tcp_stream stream(ioc);

	// http://${url}:${port}
	auto const results = resolver.resolve(url, port);

	stream.connect(results);

  // GET /rooms/:id HTTP/1.1
	std::string target = "/rooms/" + std::to_string(roomid);
	http::request<http::string_body> req{http::verb::get, target, 11};
  req.set(http::field::host, url);
  req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

	http::write(stream, req);

	beast::flat_buffer buffer;

	http::response<http::basic_string_body<char>> res;
  http::read(stream, buffer, res);

	RoomInfo result = json::parse(res.body());	

	// Close the socket
  beast::error_code ec;
  stream.socket().shutdown(tcp::socket::shutdown_both, ec);

  if (ec && ec != beast::errc::not_connected)
    throw beast::system_error{ec};

  return result;
}

auto my_rooms (
	const std::string& url,
  const std::string& port,
	const std::string& token
) -> std::vector<RoomInfo> {
	namespace beast = boost::beast;
  namespace http = beast::http;
  namespace net = boost::asio;
  using tcp = net::ip::tcp;

  using json = nlohmann::json;
	
	net::io_context ioc;

	tcp::resolver resolver(ioc);
  beast::tcp_stream stream(ioc);

	// http://${url}:${port}
	auto const results = resolver.resolve(url, port);

	stream.connect(results);

  // GET /room/me HTTP/1.1
	http::request<http::string_body> req{http::verb::get, "/rooms/me", 11};
  req.set(http::field::host, url);
  req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
  req.set(http::field::authorization, "Bearer " + token);

	http::write(stream, req);

	beast::flat_buffer buffer;

	http::response<http::basic_string_body<char>> res;
  http::read(stream, buffer, res);

	std::string resp = res.body();

	std::vector<std::string> rooms;
	int start(0);
	for(int i = 0; i < resp.size(); ++i) {
		if(resp[i] == '{')
			start = i;
		else if(resp[i] == '}')
			rooms.push_back(resp.substr(start, i - start + 1));
	}

	std::vector<RoomInfo> result;
	for(std::string room : rooms) {
		result.push_back(json::parse(room));
	}

	// Close the socket
  beast::error_code ec;
  stream.socket().shutdown(tcp::socket::shutdown_both, ec);

  if (ec && ec != beast::errc::not_connected)
    throw beast::system_error{ec};

  return result;
}

} // end namespace chatoy