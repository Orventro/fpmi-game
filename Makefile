
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
CLIENT_FILES = ./src/client/*.cpp
CLIENT_BIN_PATH = ./bin/client
RESOURCES_H = ./src/client/Resources.h
RESOURCES_Point_none = ./src/client/Point_none.h
RESOURCES_Point_red = ./src/client/Point_red.h
RESOURCES_Point_blue = ./src/client/Point_blue.h

client:
	mkdir -p bin
	g++ -o $(CLIENT_BIN_PATH) $(FLAGS) $(CLIENT_FILES) -I/src/client/ -I/usr/include/SFML   $(SFML_LIBS) 

resources:
	rm -f $(RESOURCES_H)
	xxd -i ./res/fonts/Freshman.ttf | sed 's/unsigned/const\ unsigned/g' >> $(RESOURCES_H) 
	
	rm -f $(RESOURCES_Point_none)
	xxd -i ./res/points/none.png | sed  's/unsigned/const\ unsigned/g' >>  $(RESOURCES_Point_none)
	
	rm -f $(RESOURCES_Point_red)
	xxd -i ./res/points/red.png | sed  's/unsigned/const\ unsigned/g' >>  $(RESOURCES_Point_red)
	
	rm -f $(RESOURCES_Point_blue)
	xxd -i ./res/points/blue.png | sed  's/unsigned/const\ unsigned/g' >>  $(RESOURCES_Point_blue)

all: resources client