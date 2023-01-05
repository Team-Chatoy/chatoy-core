#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

#include <nlohmann/json.hpp>

#include <string>
#include <utility>
#include <vector>
#include <optional>

#include <chatoy/types.hpp>
#include <chatoy/core.hpp>

namespace chatoy {

auto split(
  const std::string& str,
  const char delimiter
) -> std::pair<std::string, std::string> {
  int len = str.length();

  for (int i = 0; i < len; ++ i) {
    if (str[i] == delimiter) {
      return std::make_pair(
        str.substr(0, i),
        str.substr(i + 1)
      );
    }
  }

  return std::make_pair(str, "");
}

auto http_req(
  const boost::beast::http::verb method,
  const std::string& raw_host,
  const std::string& path,
  const std::vector<HttpHeader>& headers,
  const std::optional<nlohmann::json>& payload
) -> std::string {
  namespace beast = boost::beast;
  namespace http = beast::http;
  namespace net = boost::asio;
  using tcp = net::ip::tcp;

  auto [host, port] = split(raw_host, ':');

  if (port == "") {
    port = "80";
  }

  net::io_context ioc;

  tcp::resolver resolver(ioc);
  beast::tcp_stream stream(ioc);

  // http://${host}:${port}
  auto const results = resolver.resolve(host, port);

  stream.connect(results);

  // ${method} ${path} HTTP/1.1
  http::request<http::string_body> req{method, path, 11};
  req.set(http::field::host, raw_host);
  req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
  if (method == http::verb::post && payload.has_value()) {
    req.set(http::field::content_type, "application/json");
    req.body() = payload.value().dump();
    req.prepare_payload();
  }

  for (const auto& header : headers) {
    req.set(header.key, header.value);
  }

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
