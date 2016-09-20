CPP		 = g++
LK_LIBS = ../../Common/AnsiString.cpp ../../Common/Exception.cpp ../../Common/StringBuffer.cpp ../../Common/StringUtil.cpp
LIBS     = -I./data/ -I../Common/ -I../../Common -I/usr/include/postgresql/ -L/usr/lib/postgresql/lib -lpq -g
CFLAGS	 = -c -w -Wall -I./  -lpq -g
BIN 	 = NetBalancer

NetBalancer : NetBalancer.cpp Logger.o ConfigReader.o NetworkNameUtil.o ShellUtil.o IfconfigUtil.o EthtoolUtil.o DhcpUtil.o AppData.o NBCommon.o RouteUtil.o IptablesUtil.o LteUtil.o
	$(CPP) -o $(BIN) NetBalancer.cpp Logger.o ConfigReader.o ShellUtil.o NetworkNameUtil.o IfconfigUtil.o EthtoolUtil.o DhcpUtil.o AppData.o Common.o RouteUtil.o IptablesUtil.o LteUtil.o $(LIBS) $(LK_LIBS)

Logger.o: ../Common/Logger.cpp
	$(CPP) $(CFLAGS) ../Common/Logger.cpp $(LIBS)
  
NetworkNameUtil.o: ../Common/NetworkNameUtil.cpp
	$(CPP) $(CFLAGS) ../Common/NetworkNameUtil.cpp $(LIBS)
  
ShellUtil.o: ../Common/ShellUtil.cpp
	$(CPP) $(CFLAGS) ../Common/ShellUtil.cpp $(LIBS)
  
IfconfigUtil.o: ../Common/IfconfigUtil.cpp
	$(CPP) $(CFLAGS) ../Common/IfconfigUtil.cpp $(LIBS) 
  
LteUtil.o: ../Common/LteUtil.cpp
	$(CPP) $(CFLAGS) ../Common/LteUtil.cpp $(LIBS) 
  
EthtoolUtil.o: ../Common/EthtoolUtil.cpp
	$(CPP) $(CFLAGS) ../Common/EthtoolUtil.cpp $(LIBS)
  
RouteUtil.o: ../Common/RouteUtil.cpp
	$(CPP) $(CFLAGS) ../Common/RouteUtil.cpp $(LIBS)

ConfigReader.o: ../Common/ConfigReader.cpp
	$(CPP) $(CFLAGS) ../Common/ConfigReader.cpp $(LIBS)
  
IptablesUtil.o: ../Common/IptablesUtil.cpp
	$(CPP) $(CFLAGS) ../Common/IptablesUtil.cpp $(LIBS)
  
NBCommon.o: Common.cpp
	$(CPP) $(CFLAGS) Common.cpp $(LIBS) 
  
DhcpUtil.o: ../Common/DhcpUtil.cpp
	$(CPP) $(CFLAGS) ../Common/DhcpUtil.cpp $(LIBS) 

AppData.o: data/AppData.cpp
	$(CPP) $(CFLAGS) data/AppData.cpp $(LIBS) 