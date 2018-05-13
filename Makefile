# CONFIG #######################################################################

bin = main
src = src/

#####################################################
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic -std=c++17 \
-I/usr/include/`pkg-config --cflags --libs gtk+-3.0` \
-I/usr/include/goocanvas-2.0 \
-Isrc/ \
-Ilib
LDFLAGS = `pkg-config --libs gtk+-3.0` `pkg-config --libs goocanvas-2.0`

debug : CXXFLAGS += -g

fls = $(shell find $(src) -type f -name "*.cc")
bas = $(basename $(fls))
obj = $(addsuffix .o, $(bas))

all: $(obj)
	$(CXX) $(CXXFLAGS) $^ -o $(bin) $(LDFLAGS)

debug:
	$(CXX) $(CXXFLAGS) $(fls) -o $(bin) $(LDFLAGS)

clean:
	$(RM) $(obj) $(bin)
