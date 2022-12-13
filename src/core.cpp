#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

#include <chatoy/core.hpp>

namespace chatoy {

std::string get(const std::string& url) {
  namespace beast = boost::beast;
  namespace http = beast::http;
  namespace net = boost::asio;
  using tcp = net::ip::tcp;

  net::io_context ioc;

  tcp::resolver resolver(ioc);
  beast::tcp_stream stream(ioc);

  // http://${url}:80
  auto const results = resolver.resolve(url, "80");

  stream.connect(results);

  // GET / HTTP/1.1
  http::request<http::string_body> req{http::verb::get, "/", 11};
  req.set(http::field::host, url);
  req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

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