# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# Project
project(protobuf-examples)

# Find required protobuf package
find_package(protobuf CONFIG REQUIRED)

add_executable(list_people list_people.cc addressbook.pb.cc)
target_link_libraries(list_people protobuf::libprotobuf)

add_executable(add_person add_person.cc addressbook.pb.cc)
target_link_libraries(add_person protobuf::libprotobuf)

