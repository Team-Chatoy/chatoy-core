FetchContent_Declare(
  catch
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.2.1
)
FetchContent_MakeAvailable(catch)

add_executable(testlib testlib.cpp)

target_compile_features(testlib PRIVATE cxx_std_20)
target_link_libraries(testlib PRIVATE chatoy_core Catch2::Catch2WithMain)

add_test(
  NAME basictest
  COMMAND testlib
)


add_executable(test_session session.cpp)

target_compile_features(test_session PRIVATE cxx_std_20)
target_link_libraries(test_session PRIVATE chatoy_core Catch2::Catch2WithMain)

add_test(
  NAME test_session
  COMMAND test_session
)

add_executable(test_register register.cpp)

target_compile_features(test_register PRIVATE cxx_std_20)
target_link_libraries(test_register PRIVATE chatoy_core Catch2::Catch2WithMain)

add_test(
  NAME test_register
  COMMAND test_register
)

add_executable(test_login login.cpp)

target_compile_features(test_login PRIVATE cxx_std_20)
target_link_libraries(test_login PRIVATE chatoy_core Catch2::Catch2WithMain)

add_test(
  NAME test_login
  COMMAND test_login
)


add_executable(test_createroom createroom.cpp)

target_compile_features(test_createroom PRIVATE cxx_std_20)
target_link_libraries(test_createroom PRIVATE chatoy_core Catch2::Catch2WithMain)

add_test(
  NAME test_createroom
  COMMAND test_createroom
)

add_executable(test_joinroom joinroom.cpp)

target_compile_features(test_joinroom PRIVATE cxx_std_20)
target_link_libraries(test_joinroom PRIVATE chatoy_core Catch2::Catch2WithMain)

add_test(
  NAME test_joinroom
  COMMAND test_joinroom
)

add_executable(test_getroom getroom.cpp)

target_compile_features(test_getroom PRIVATE cxx_std_20)
target_link_libraries(test_getroom PRIVATE chatoy_core Catch2::Catch2WithMain)

add_test(
  NAME test_getroom
  COMMAND test_getroom
)

add_executable(test_roomsme roomsme.cpp)

target_compile_features(test_roomsme PRIVATE cxx_std_20)
target_link_libraries(test_roomsme PRIVATE chatoy_core Catch2::Catch2WithMain)

add_test(
  NAME test_roomsme
  COMMAND test_roomsme
)

add_executable(test_getuser getuser.cpp)

target_compile_features(test_getuser PRIVATE cxx_std_20)
target_link_libraries(test_getuser PRIVATE chatoy_core Catch2::Catch2WithMain)

add_test(
  NAME test_getuser
  COMMAND test_getuser
)