add_library(chatoy_core core.cpp)

target_include_directories(chatoy_core PUBLIC ../include)
target_link_libraries(chatoy_core PRIVATE Boost::boost)
target_compile_features(chatoy_core PUBLIC cxx_std_20)
