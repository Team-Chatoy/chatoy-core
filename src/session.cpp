#include <boost/beast/version.hpp>

#include <chrono>

#include <chatoy/session.hpp>

namespace chatoy {

Session::Session(
  boost::asio::any_io_executor ex,
  boost::asio::ssl::context& ctx,
  std::function<void(error_code)>&& on_err,
  std::function<void(const boost::beast::string_view&)>&& on_ok
): resolver_(ex), stream_(ex, ctx), on_err_(on_err), on_ok_(on_ok) { }

auto Session::request(
  boost::beast::http::verb method,
  char const *host,
  char const *port,
  char const *target
) -> void {
  if (!SSL_set_tlsext_host_name(stream_.native_handle(), host)) {
    error_code ec{static_cast<int>(::ERR_get_error()), boost::asio::error::get_ssl_category()};
    on_err_(ec);
    return;
  }

  req_.version(11);
  req_.method(method);
  req_.target(target);
  req_.set(boost::beast::http::field::host, host);
  req_.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);

  resolver_.async_resolve(
    host,
    port,
    boost::beast::bind_front_handler(
      &Session::on_resolve,
      shared_from_this()
    )
  );
}

auto Session::on_resolve(
  error_code ec,
  boost::asio::ip::tcp::resolver::results_type results
) -> void {
  if (ec) {
    on_err_(ec);
    return;
  }

  boost::beast::get_lowest_layer(stream_)
    .expires_after(std::chrono::seconds(30));

  boost::beast::get_lowest_layer(stream_)
    .async_connect(
      results,
      boost::beast::bind_front_handler(
        &Session::on_connect,
        shared_from_this()
      )
    );
}

auto Session::on_connect(
  error_code ec,
  boost::asio::ip::tcp::resolver::results_type::endpoint_type
) -> void {
  if (ec) {
    on_err_(ec);
    return;
  }

  stream_.async_handshake(
    boost::asio::ssl::stream_base::client,
    boost::beast::bind_front_handler(
      &Session::on_handshake,
      shared_from_this()
    )
  );
}

auto Session::on_handshake(error_code ec) -> void {
  if (ec) {
    on_err_(ec);
    return;
  }

  boost::beast::get_lowest_layer(stream_)
    .expires_after(std::chrono::seconds(30));

  boost::beast::http::async_write(
    stream_,
    req_,
    boost::beast::bind_front_handler(
      &Session::on_write,
      shared_from_this()
    )
  );
}

auto Session::on_write(
  error_code ec,
  std::size_t bytes_transferred
) -> void {
  boost::ignore_unused(bytes_transferred);

  if (ec) {
    on_err_(ec);
    return;
  }

  boost::beast::http::async_read(
    stream_,
    buffer_,
    res_,
    boost::beast::bind_front_handler(
      &Session::on_read,
      shared_from_this()
    )
  );
}

auto Session::on_read(
  error_code ec,
  std::size_t bytes_transferred
) -> void {
  boost::ignore_unused(bytes_transferred);

  if (ec) {
    on_err_(ec);
    return;
  }

  on_ok_(res_.body());

  boost::beast::get_lowest_layer(stream_)
    .expires_after(std::chrono::seconds(30));

  stream_.async_shutdown(
    boost::beast::bind_front_handler(
      &Session::on_shutdown,
      shared_from_this()
    )
  );
}

auto Session::on_shutdown(error_code ec) -> void {
  if (ec == boost::asio::error::eof) {
    ec = {};
  }

  if (ec) {
    on_err_(ec);
    return;
  }
}

void Session::get(char const *host, char const *port, char const *target) {
  request(boost::beast::http::verb::get, host, port, target);
}

void Session::post(char const *host, char const *port, char const *target) {
  // TODO: add post body
  request(boost::beast::http::verb::post, host, port, target);
}

} // end namespace chatoy
