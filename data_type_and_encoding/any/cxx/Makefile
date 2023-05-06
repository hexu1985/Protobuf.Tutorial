CXX = g++
CXXFLAGS = -g3 -Wall -Wextra
INCLUDES = -Icxx_proto
LDFLAGS = 
LDLIBS = -lprotobuf
VPATH = cxx_proto

PROGS =	test

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cc
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDES)

test: test.o test.pb.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDLIBS)

