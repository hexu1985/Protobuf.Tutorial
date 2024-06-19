# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name and language
project(addressbook LANGUAGES CXX)

# Find required protobuf package
#find_package(protobuf CONFIG REQUIRED)
find_package(Protobuf REQUIRED)

include_directories(generated)

add_executable(list_people list_people.cc generated/addressbook.pb.cc)
target_link_libraries(list_people protobuf::libprotobuf)

add_executable(add_person add_person.cc generated/addressbook.pb.cc)
target_link_libraries(add_person protobuf::libprotobuf)

add_executable(create_addressbook create_addressbook.cc generated/addressbook.pb.cc)
target_link_libraries(create_addressbook protobuf::libprotobuf)

add_executable(print_to_string print_to_string.cc generated/addressbook.pb.cc)
target_link_libraries(print_to_string protobuf::libprotobuf)

add_executable(message_to_json_string message_to_json_string.cc generated/addressbook.pb.cc)
target_link_libraries(message_to_json_string protobuf::libprotobuf)

add_executable(write_to_text_file write_to_text_file.cc generated/addressbook.pb.cc)
target_link_libraries(write_to_text_file protobuf::libprotobuf)
