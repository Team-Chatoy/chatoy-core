#pragma once

#include <string>

namespace chatoy {

class User {
private:
  std::string id;         // The id of this account.
  std::string password;   // The password of this account.
  std::string username;   // The username of this account.
  std::string nickname;   // The nickname of this account.
  std::string slogan;     // Introduction or motto, or something else.
  std::string ststus;     // The status of this account.
  std::string registed;   // The time when this account was registered.

public:
  User();
  User(const std::string& id, const std::string& password);
  User(
    const std::string& id,
    const std::string& password,
    const std::string& username,
    const std::string& nickname,
    const std::string& slogan,
    const std::string& status,
    const std::string& registed
  );
};

} // end namespace chatoy
