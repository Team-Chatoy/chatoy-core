#pragma once

#include <string>

namespace chatoy {

struct LoginResp {
  int code;
  std::string msg;
};

LoginResp login(
  const std::string& url,
  const std::string& port,
  const std::string& username,
  const std::string& password
);

} // end namespace chatoy
