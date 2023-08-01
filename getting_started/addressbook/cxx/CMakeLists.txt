# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name and language
project(addressbook LANGUAGES CXX)

# Find required protobuf package
#find_package(protobuf CONFIG REQUIRED)
find_package(Protobuf REQUIRED)

include_directories(cxx_proto)

add_executable(list_people list_people.cc cxx_proto/addressbook.pb.cc)
target_link_libraries(list_people protobuf::libprotobuf)

add_executable(add_person add_person.cc cxx_proto/addressbook.pb.cc)
target_link_libraries(add_person protobuf::libprotobuf)

add_executable(create_addressbook create_addressbook.cc cxx_proto/addressbook.pb.cc)
target_link_libraries(create_addressbook protobuf::libprotobuf)

add_executable(print_to_string print_to_string.cc cxx_proto/addressbook.pb.cc)
target_link_libraries(print_to_string protobuf::libprotobuf)
