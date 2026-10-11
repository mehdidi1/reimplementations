add_library(dsu INTERFACE)
add_library(reimpl::dsu ALIAS dsu)
target_include_directories(dsu INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(dsu INTERFACE cxx_std_17)

