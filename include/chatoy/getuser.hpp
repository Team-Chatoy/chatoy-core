#pragma once

#include <string>

namespace chatoy {

struct UserInfo {
	int id;
	std::string username;
	std::string nickname;
	std::string slogan;
	int status;
	std::string registered;
};

UserInfo get_user(
	const std::string& url,
	const std::string& port,
	const int userid
);

} // end namespace chatoy