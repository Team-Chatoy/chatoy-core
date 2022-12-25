#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

#include <nlohmann/json.hpp>

#include <chatoy/getuser.hpp>

namespace chatoy {

void from_json(const nlohmann::json& j, UserInfo& resp) {
  j.at("id").get_to(resp.id);
  j.at("username").get_to(resp.username);
	j.at("nickname").get_to(resp.nickname);
	j.at("password").get_to(resp.password);
	j.at("slogan").get_to(resp.slogan);
	j.at("status").get_to(resp.status);
	j.at("registered").get_to(resp.registered);
}

auto get_user(
	const std::string& url,
  const std::string& port,
	const int userid
) -> UserInfo {
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

  // GET /users/:id HTTP/1.1
  http::request<http::string_body> req{http::verb::get, "/users/" + std::to_string(userid), 11};
  req.set(http::field::host, url);
  req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
  req.set(http::field::content_type, "application/json");

	http::write(stream, req);

  beast::flat_buffer buffer;

  http::response<http::basic_string_body<char>> res;
  http::read(stream, buffer, res);

  UserInfo result = json::parse(res.body());

	// Close the socket
  beast::error_code ec;
  stream.socket().shutdown(tcp::socket::shutdown_both, ec);

  if (ec && ec != beast::errc::not_connected)
    throw beast::system_error{ec};

  return result;
}

} // end namespace chatoy