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

struct Auth {
  std::string type;
  std::string token;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Auth, type, token)

struct AuthResp {
  std::string type;
  int code;
  std::string msg;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AuthResp, type, code, msg);

struct TextData {
  std::string type;
  std::string text;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TextData, type, text);
struct MsgData {
  std::string uuid;
  int sender;
  int room;
  TextData data;
  std::string sent;
  bool modified;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(MsgData, uuid, sender, room, data, sent, modified);
struct ReceiveMsg {
  std::string type;
  MsgData data;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ReceiveMsg, type, data);

} // end namespace chatoy
