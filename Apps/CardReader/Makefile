CFLAGS=-c -Wall -I../../Common -I../Util -I../Admin -I./postgresql/include/ -fpermissive -w
LFLAGS=-Wall -O2
LIBS=-L./postgresql/lib/ -lpq -liconv
CC=g++
OBJS=Utils.o AppData.o AnsiString.o Exception.o SimpleData.o Binary.o StringUtil.o PGLibraryLoader.o Database.o DBIntf.o StringBuffer.o Utf8Util.o

all: Main.exe

Main.exe: $(OBJS) Main.o
	$(CC) $(LFLAGS) -o Main.exe $(OBJS) Main.o $(LIBS)

Main.o: Main.cpp
	$(CC) $(CFLAGS) Main.cpp
  
Utils.o: Utils.cpp
	$(CC) $(CFLAGS) Utils.cpp

AppData.o: data/AppData.cpp
	$(CC) $(CFLAGS) data/AppData.cpp

AnsiString.o: ../../Common/AnsiString.cpp
	$(CC) $(CFLAGS) ../../Common/AnsiString.cpp

Exception.o: ../../Common/Exception.cpp
	$(CC) $(CFLAGS) ../../Common/Exception.cpp

Utf8Util.o: ../../Common/Utf8Util.cpp
	$(CC) $(CFLAGS) ../../Common/Utf8Util.cpp
  
SimpleData.o: ../../Common/SimpleData.cpp
	$(CC) $(CFLAGS) ../../Common/SimpleData.cpp

Binary.o: ../../Common/Binary.cpp
	$(CC) $(CFLAGS) ../../Common/Binary.cpp

StringUtil.o: ../../Common/StringUtil.cpp
	$(CC) $(CFLAGS) ../../Common/StringUtil.cpp

StringBuffer.o: ../../Common/StringBuffer.cpp
	$(CC) $(CFLAGS) ../../Common/StringBuffer.cpp

PGLibraryLoader.o: ../../Common/PGLibraryLoader.cpp
	$(CC) $(CFLAGS) ../../Common/PGLibraryLoader.cpp

Database.o: ../../Common/Database.cpp
	$(CC) $(CFLAGS) ../../Common/Database.cpp

DBIntf.o: ../../Common/DBIntf.cpp
	$(CC) $(CFLAGS) ../../Common/DBIntf.cpp

clean:
	rm -f *.o ParamGen *.exe *.obj *.tds
