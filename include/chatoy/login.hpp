#pragma once

#include <string>

namespace chatoy {
    std::string login(
        const std::string& url,
        const std::string& port,
        const std::string& username,
        const std::string& password
    );
}