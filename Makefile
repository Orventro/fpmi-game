
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

CLIENT_FILES = ./src/client/*.cpp

CLIENT_BIN_PATH = ./bin/client

client:
	mkdir -p bin
	g++ -o $(CLIENT_BIN_PATH) $(FLAGS) $(CLIENT_FILES) -I/src/client/ -I/usr/include/SFML   $(SFML_LIBS)  