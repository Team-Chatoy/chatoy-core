add_library(
  chatoy_core
  core.cpp
  session.cpp
  register.cpp
  login.cpp
  room.cpp
  getuser.cpp
)

target_include_directories(chatoy_core PUBLIC ../include)
target_link_libraries(
  chatoy_core
  PRIVATE
  Boost::boost
  OpenSSL::SSL
  nlohmann_json::nlohmann_json
)
target_compile_features(chatoy_core PUBLIC cxx_std_20)
