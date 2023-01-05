#pragma once

#include <nlohmann/json.hpp>

#include <string>

#include <chatoy/types.hpp>

namespace chatoy {

auto regist(
  const std::string& host,
  const std::string& username,
  const std::string& password
) -> Resp;

auto login(
  const std::string& host,
  const std::string& username,
  const std::string& password
) -> Resp;

struct UserInfo {
  int id;
  std::string username;
  std::string nickname;
  std::string slogan;
  int status;
  std::string registered;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
  UserInfo,
  id,
  username,
  nickname,
  slogan,
  status,
  registered
)

auto get_user(
  const std::string& host,
  const int id
) -> UserInfo;

} // end namespace chatoy
