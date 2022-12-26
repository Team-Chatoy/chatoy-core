FetchContent_Declare(
  catch
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.2.1
)
FetchContent_MakeAvailable(catch)

# Basic tests (http_req)
add_executable(basic_test basic.cpp)

target_compile_features(basic_test PRIVATE cxx_std_20)
target_link_libraries(basic_test PRIVATE chatoy_core Catch2::Catch2WithMain)

add_test(
  NAME basic
  COMMAND basic_test
)

# User tests (register, login, get_user)
add_executable(user_test user.cpp)

target_compile_features(user_test PRIVATE cxx_std_20)
target_link_libraries(user_test PRIVATE chatoy_core Catch2::Catch2WithMain)

add_test(
  NAME user
  COMMAND user_test
)

# Room tests (create, join, get, my_rooms)
add_executable(room_test room.cpp)

target_compile_features(room_test PRIVATE cxx_std_20)
target_link_libraries(room_test PRIVATE chatoy_core Catch2::Catch2WithMain)

add_test(
  NAME room
  COMMAND room_test
)
