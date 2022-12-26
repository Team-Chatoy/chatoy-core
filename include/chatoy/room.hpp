#pragma once

#include <nlohmann/json.hpp>

#include <string>
#include <vector>

#include <chatoy/types.hpp>

namespace chatoy {

auto create_room(
  const std::string& host,
  const std::string& token,
  const std::string& name
) -> IdResp;

auto join_room(
  const std::string& host,
  const std::string& token,
  const int id
) -> Resp;

struct RoomInfo {
  int id;
  std::string name;
  std::string description;
  std::string created;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
  RoomInfo,
  id,
  name,
  description,
  created
)

auto get_room(
  const std::string& host,
  const int id
) -> RoomInfo;

auto my_rooms(
  const std::string& host,
  const std::string& token
) -> std::vector<RoomInfo>;

} // end namespace chatoy
