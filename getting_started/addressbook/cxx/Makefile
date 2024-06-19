CXX = g++
CXXFLAGS = -g3 -Wall -Wextra
INCLUDES = -Igenerated
LDFLAGS = 
LDLIBS = -lprotobuf
VPATH = generated

PROGS =	list_people add_person create_addressbook print_to_string message_to_json_string \
		write_to_text_file read_from_text_file write_to_binary_file

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cc
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDES)

list_people: list_people.o addressbook.pb.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDLIBS)

add_person: add_person.o addressbook.pb.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDLIBS)

create_addressbook: create_addressbook.o addressbook.pb.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDLIBS)

print_to_string: print_to_string.o addressbook.pb.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDLIBS)

message_to_json_string: message_to_json_string.o addressbook.pb.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDLIBS)

write_to_text_file: write_to_text_file.o addressbook.pb.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDLIBS)

read_from_text_file: read_from_text_file.o addressbook.pb.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDLIBS)

write_to_binary_file: write_to_binary_file.o addressbook.pb.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDLIBS)

