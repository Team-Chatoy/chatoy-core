#pragma once

#include <string>
#include <vector>
namespace chatoy {

struct CreateResp {
	int id;
};

struct JoinResp {
	int code;
	std::string msg;
};

struct RoomInfo {
	int id;
	std::string name;
	std::string description;
	std::string created;
};

CreateResp create_room(
	const std::string& url,
  const std::string& port,
	const std::string& token,
	const std::string& roomname
);

JoinResp join_room(
	const std::string& url,
  const std::string& port,
	const std::string& token,
	const int roomid
);

RoomInfo get_room(
	const std::string& url,
  const std::string& port,
	const int roomid
);


std::vector<RoomInfo> my_rooms(
	const std::string& url,
  const std::string& port,
	const std::string& token
);

} // end namespace chatoy