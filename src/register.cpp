#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

#include <chatoy/register.hpp>

namespace chatoy {

// register new user
auto regist(
  const std::string& url,
  const std::string& port,
  const std::string& username,
  const std::string& password
) -> std::string {
  namespace beast = boost::beast;
  namespace http = beast::http;
  namespace net = boost::asio;
  using tcp = net::ip::tcp;

  net::io_context ioc;

  tcp::resolver resolver(ioc);
  beast::tcp_stream stream(ioc);

  // http://${url}:${port}
  auto const results = resolver.resolve(url, port);

  stream.connect(results);

  // POST /users HTTP/1.1
  http::request<http::string_body> req{http::verb::post, "/users", 11};
  req.set(http::field::host, url);
  req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
  req.set(http::field::content_type, "application/json");
  req.body() = R"({"username":")" + username + R"(","password":")" + password + R"("})";
  req.prepare_payload();

  http::write(stream, req);

  beast::flat_buffer buffer;

  http::response<http::basic_string_body<char>> res;
  http::read(stream, buffer, res);

  std::string result = res.body();

  // Close the socket
  beast::error_code ec;
  stream.socket().shutdown(tcp::socket::shutdown_both, ec);

  if (ec && ec != beast::errc::not_connected)
    throw beast::system_error{ec};

  return result;
}

} // end namespace chatoy
