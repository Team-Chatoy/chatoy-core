#pragma once

#include <string>

namespace chatoy {

struct RegisterResp {
  int code;
  std::string msg;
};

RegisterResp regist(
  const std::string& url,
  const std::string& port,
  const std::string& username,
  const std::string& password
);

} // end namespace chatoy
