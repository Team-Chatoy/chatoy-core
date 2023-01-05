#include <boost/beast/http.hpp>

#include <nlohmann/json.hpp>

#include <string>
#include <vector>

#include <chatoy/types.hpp>
#include <chatoy/core.hpp>
#include <chatoy/room.hpp>

namespace chatoy {

auto create_room(
  const std::string& host,
  const std::string& token,
  const std::string& name
) -> IdResp {
  return post<IdResp>(
    host,
    "/rooms",
    {
      {"token", token},
      {"name", name}
    }
  );
}

auto join_room(
  const std::string& host,
  const std::string& token,
  const int id
) -> Resp {
  return post<Resp>(
    host,
    "/rooms/" + std::to_string(id) + "/join",
    {
      {"token", token}
    }
  );
}

auto get_room(
  const std::string& host,
  const int id
) -> RoomInfo {
  return get<RoomInfo>(host, "/rooms/" + std::to_string(id));
}

auto my_rooms(
  const std::string& host,
  const std::string& token
) -> std::vector<RoomInfo> {
  return get<std::vector<RoomInfo>>(
    host,
    "/rooms/me",
    {
      {boost::beast::http::field::authorization, "Bearer " + token}
    }
  );
}

} // end namespace chatoy
