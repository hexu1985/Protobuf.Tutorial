PROTOBUF_ROOT_DIR=$(HOME)/local/protobuf

CXX = g++
CXXFLAGS = -g3 -Wall -Wextra
INCLUDES = -I$(PROTOBUF_ROOT_DIR)/include
LDFLAGS = -lprotobuf 
LDPATH = -Wl,-rpath,$(PROTOBUF_ROOT_DIR)/lib -Wl,--enable-new-dtags -L$(PROTOBUF_ROOT_DIR)/lib
VPATH =

PROGS =	list_people add_person

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cc
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDES)

list_people: list_people.o addressbook.pb.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

add_person: add_person.o addressbook.pb.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

