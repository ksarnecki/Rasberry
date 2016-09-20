LFLAGS=-Wall -o2 -w
LIBS= -I../../Common  -I../../Common protocol.cpp common.cpp data/AppData.cpp net.cpp ../../Common/AnsiString.cpp ../../Common/Exception.cpp   ../../Common/SimpleData.cpp  ../../Common/Binary.cpp -w
CXX := g++

all: TheBoxTunnel

TheBoxTunnel: $(OBJS)
	$(CXX) $(LFLAGS) rpi_main.cpp -o TheBoxTunnel  $(LIBS) 

local: $(OBJS)
	$(CXX) $(LFLAGS) local.cpp -o local  $(LIBS) 	

clean:
	rm -f *.o *.exe *.obj *.tds
