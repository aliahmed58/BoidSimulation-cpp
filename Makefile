CC = g++

OBJS = src/*.cpp

CXXFLAGS=-g -std=gnu++0x -Wall -pedantic

INCLUDE_PATHS = -I C:/libs/SDL2-2.26.3/i686-w64-mingw32/include/SDL2/ -I C:/libs/SDL2_ttf-2.20.2/i686-w64-mingw32/include/SDL2 -I C:/libs/SDL2_image-2.6.3/i686-w64-mingw32/include/SDL2/ -Iinclude/

LIB_PATHS = -L C:/libs/SDL2-2.26.3/i686-w64-mingw32/lib/ -L C:/libs/SDL2_ttf-2.20.2/i686-w64-mingw32/lib/ -L C:/libs/SDL2_image-2.6.3/i686-w64-mingw32/lib/

LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

windows:
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIB_PATHS)  $(LINKER_FLAGS) -o ./bin/main && start ./bin/main

linux:
	mkdir -p bin && $(CC) $(CXXFLAGS) $(OBJS) -I include/ $(LINKER_FLAGS) -o ./bin/main && start ./bin/main
