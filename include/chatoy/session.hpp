#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>

#include <memory>
#include <functional>

namespace chatoy {

class Session : public std::enable_shared_from_this<Session> {
  using error_code = boost::beast::error_code;

private:
  boost::asio::ip::tcp::resolver resolver_;
  boost::beast::ssl_stream<boost::beast::tcp_stream> stream_;
  boost::beast::flat_buffer buffer_; // Must persist between reads
  boost::beast::http::request<boost::beast::http::empty_body> req_;
  boost::beast::http::response<boost::beast::http::string_body> res_;

  std::function<void(error_code)> on_err_;
  std::function<void(const boost::beast::string_view&)> on_ok_;

  void request(
    boost::beast::http::verb,
    char const *host,
    char const *port,
    char const *target
  );

  void on_resolve(
    error_code,
    boost::asio::ip::tcp::resolver::results_type
  );
  void on_connect(
    error_code,
    boost::asio::ip::tcp::resolver::results_type::endpoint_type
  );
  void on_handshake(error_code);
  void on_write(error_code, std::size_t);
  void on_read(error_code, std::size_t);
  void on_shutdown(error_code);

public:
  explicit Session(
    boost::asio::any_io_executor,
    boost::asio::ssl::context&,
    std::function<void(error_code)>&& on_err,
    std::function<void(const boost::beast::string_view&)>&& on_ok
  );

  void get(char const *host, char const *port, char const *target);
  void post(char const *host, char const *port, char const *target);
};

} // end namespace chatoy
