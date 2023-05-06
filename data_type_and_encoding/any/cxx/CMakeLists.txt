# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name and language
project(addressbook LANGUAGES CXX)

# Find required protobuf package
#find_package(protobuf CONFIG REQUIRED)
find_package(Protobuf REQUIRED)

include_directories(cxx_proto)

add_executable(test test.cc cxx_proto/test.pb.cc)
target_link_libraries(test protobuf::libprotobuf)
