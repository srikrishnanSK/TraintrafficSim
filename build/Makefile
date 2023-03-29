
PROG = traintrafficsimulation
ROOT_DIR = ../
CXX = g++
CXXFLAGS += -g -O0 -std=c++11

CPPFLAGS += \
	-I. \
	-I$(ROOT_DIR)include/

LDLIBS = \
		 -lpthread

LDFLAGS += -L/usr/local/lib $(LDLIBS)

all: $(PROG)
	@echo $(PROG) compilation success!

SRCS = \
	$(ROOT_DIR)src/Tracks.cpp \
	$(ROOT_DIR)src/ConnecTracks.cpp \
	$(ROOT_DIR)src/Junction.cpp \
	$(ROOT_DIR)src/SignalSystem.cpp \
	$(ROOT_DIR)src/Trains.cpp \
	$(ROOT_DIR)src/RoutePlanner.cpp \
	$(ROOT_DIR)src/Simulator.cpp \
	$(ROOT_DIR)src/main.cpp
OBJS=$(subst .cc,.o, $(subst .cpp,.o, $(SRCS)))

$(PROG): $(OBJS)
	$(CXX) $^ $(LDFLAGS) -o $@

clean:
	rm -f $(OBJS) $(PROG) ./.depend

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MM $^ >  ./.depend;

