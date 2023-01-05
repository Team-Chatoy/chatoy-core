#pragma once

#include <boost/beast/http.hpp>

#include <nlohmann/json.hpp>

#include <string>

namespace chatoy {

struct HttpHeader {
  boost::beast::http::field key;
  std::string value;
};

struct Resp {
  int code;
  std::string msg;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Resp, code, msg)

struct IdResp {
  int id;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(IdResp, id)

} // end namespace chatoy
