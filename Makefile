
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lpthread
CLIENT_SOURCE = ./src/client/*.cpp
SERVER_SOURCE = ./src/server.cpp
CLIENT_BIN_PATH = ./bin/client
SERVER_BIN_PATH = ./bin/server
RESOURCES_H = ./src/client/Resources.h

client:
	mkdir -p bin
	g++ -std=c++17 -o $(CLIENT_BIN_PATH) -O3 $(FLAGS) $(CLIENT_SOURCE) -I/src/client/ -I/usr/include/SFML $(SFML_LIBS) 

resources:
	rm -f $(RESOURCES_H)
	@echo '#pragma once' >> $(RESOURCES_H) 

	@for file in $(shell find ./res -type f) ;\
	do \
		xxd -i $${file} | sed 's/unsigned/const\ unsigned/g' >> $(RESOURCES_H) && \
		echo "$${file} >> $(RESOURCES_H)" ;\
	done

server:
	g++ -o $(SERVER_BIN_PATH) $(SERVER_SOURCE)

all: resources client server