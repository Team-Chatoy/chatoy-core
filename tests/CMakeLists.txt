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
