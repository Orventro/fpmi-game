
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
CLIENT_FILES = ./src/client/*.cpp
CLIENT_BIN_PATH = ./bin/client
RESOURCES_H = ./src/client/Resources.h

client:
	mkdir -p bin
	g++ -o $(CLIENT_BIN_PATH) $(FLAGS) $(CLIENT_FILES) -I/src/client/ -I/usr/include/SFML   $(SFML_LIBS) 

resources:
	rm -f $(RESOURCES_H)
	xxd -i ./res/fonts/Freshman.ttf | sed 's/unsigned/const\ unsigned/g' >> $(RESOURCES_H) 

all: resources client