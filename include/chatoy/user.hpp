#pragma once
#include <string>

namespace chatoy 
{
   class User
   {    
        private:
            std::string id;         //The id of this account.
            std::string password;   //The password of this account.
            std::string username;   //The username of this account.
            std::string nickname;   //The nickname of this account.
            std::string slogan;     //Introduction or motto, or something else.
            std::string ststus;     //The status of this account.
            std::string registed;   //The time when this account was registered.
        public:
            User();
            User(std::string id, std::string password);
            User(std::string id, std::string password, std::string username, std::string nickname, std::string slogan, std::string status, std::string registed);     
   };
} 