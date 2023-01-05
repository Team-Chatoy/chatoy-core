#pragma once

#include <boost/beast/http.hpp>

#include <nlohmann/json.hpp>

#include <string>
#include <utility>
#include <vector>
#include <optional>

#include <chatoy/types.hpp>

namespace chatoy {

auto split(
  const std::string&,
  const char
) -> std::pair<std::string, std::string>;

auto http_req(
  const boost::beast::http::verb method,
  const std::string& raw_host,
  const std::string& path,
  const std::vector<HttpHeader>& headers,
  const std::optional<nlohmann::json>& payload
) -> std::string;

template<typename T>
auto get(
  const std::string& raw_host,
  const std::string& path,
  const std::vector<HttpHeader>& headers = { }
) -> T {
  std::string result = http_req(
    boost::beast::http::verb::get,
    raw_host,
    path,
    headers,
    std::nullopt
  );

  return nlohmann::json::parse(result);
}

template<typename T>
auto post(
  const std::string& raw_host,
  const std::string& path,
  const nlohmann::json& payload
) -> T {
  std::string result = http_req(
    boost::beast::http::verb::post,
    raw_host,
    path,
    { },
    payload
  );

  return nlohmann::json::parse(result);
}

} // end namespace chatoy
