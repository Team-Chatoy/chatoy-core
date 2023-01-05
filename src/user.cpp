#include <nlohmann/json.hpp>

#include <string>

#include <chatoy/types.hpp>
#include <chatoy/core.hpp>
#include <chatoy/user.hpp>

namespace chatoy {

auto regist(
  const std::string& host,
  const std::string& username,
  const std::string& password
) -> Resp {
  return post<Resp>(
    host,
    "/users",
    {
      {"username", username},
      {"password", password}
    }
  );
}

auto login(
  const std::string& host,
  const std::string& username,
  const std::string& password
) -> Resp {
  return post<Resp>(
    host,
    "/login",
    {
      {"username", username},
      {"password", password}
    }
  );
}

auto get_user(
  const std::string& host,
  const int id
) -> UserInfo {
  return get<UserInfo>(host, "/users/" + std::to_string(id));
}

} // end namespace chatoy
