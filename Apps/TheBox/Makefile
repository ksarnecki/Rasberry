CPP		 = g++
LK_LIBS = ../../Common/AnsiString.cpp ../../Common/Exception.cpp ../../Common/StringBuffer.cpp ../../Common/StringUtil.cpp
LIBS     = -I./data/ -I../Common/ -I../../Common -g
CFLAGS	 = -c -w -Wall -I./  -lpq -g
BIN 	 = TheBox

TheBox : TheBox.cpp Logger.o MainUtils.o ConfigReader.o
	$(CPP) -o $(BIN) TheBox.cpp Logger.o MainUtils.o ConfigReader.o $(LIBS) $(LK_LIBS)

Logger.o: ../Common/Logger.cpp
	$(CPP) $(CFLAGS) ../Common/Logger.cpp $(LIBS)
  
MainUtils.o: ../Common/MainUtils.cpp
	$(CPP) $(CFLAGS) ../Common/MainUtils.cpp $(LIBS)

ConfigReader.o: ../Common/ConfigReader.cpp
	$(CPP) $(CFLAGS) ../Common/ConfigReader.cpp $(LIBS) 
