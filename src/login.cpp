#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

#include "chatoy/login.hpp"

auto login(const std::string &url,
           const std::string &port,
           const std::string &username,
           const std::string &password)
    -> std::string
{
    namespace beast = boost::beast;
    namespace http = beast::http;
    namespace net = boost::asio;
    using tcp = net::ip::tcp;

    // The io_context is required for all I/O
    net::io_context ioc;

    // These objects perform our I/O
    tcp::resolver resolver(ioc);
    beast::tcp_stream stream(ioc);

    // Look up the domain name
    auto const results = resolver.resolve(url, port);

    // Make the connection on the IP address we get from a lookup
    stream.connect(results);

    // Set up an HTTP POST request message
    http::request<http::string_body> req{http::verb::post, "/login", 11};
    req.set(http::field::host, url);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    req.set(http::field::content_type, "application/json");
    req.body() = R"({"username":")" + username + R"(","password":")" + password + R"("})"; // TODO: maybe use json library
    req.prepare_payload();

    // Send the HTTP request to the remote host
    http::write(stream, req);

    // This buffer is used for reading and must be persisted
    beast::flat_buffer buffer;

    // Declare a container to hold the response
    http::response<http::basic_string_body<char>> res;

    // Receive the HTTP response
    http::read(stream, buffer, res);

    // Save the response as std::string
    std::string result = res.body();

    // Gracefully close the socket
    beast::error_code ec;
    stream.socket().shutdown(tcp::socket::shutdown_both, ec);

    if (ec && ec != beast::errc::not_connected)
        throw beast::system_error{ec};

    // If we get here then the connection is closed gracefully

    return result;
}