add_library(
  chatoy_core
  core.cpp
  user.cpp
  room.cpp
  wsconnection.cpp
)

target_include_directories(chatoy_core PUBLIC ../include)
target_link_libraries(
  chatoy_core
  PUBLIC
  Boost::boost
  # OpenSSL::SSL
  nlohmann_json::nlohmann_json
)
target_compile_features(chatoy_core PUBLIC cxx_std_20)


add_library(
  chatoy_jni
  jni.cpp
)

target_include_directories(chatoy_jni PUBLIC ../include)
target_link_libraries(
  chatoy_jni
  PUBLIC
  chatoy_core
  JNI::JNI
)
target_compile_features(chatoy_jni PUBLIC cxx_std_20)
