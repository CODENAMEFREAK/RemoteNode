CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		RemoteNode.o

LIBS =		-lvirt

TARGET =	RemoteNode

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
