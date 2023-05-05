CXX = g++
CXXFLAGS = -g3 -Wall -Wextra
INCLUDES = -Icxx_proto
LDFLAGS = 
LDLIBS = -lprotobuf
VPATH = cxx_proto

PROGS =	list_people add_person create_addressbook print_addressbook

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

print_addressbook: print_addressbook.o addressbook.pb.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDLIBS)

