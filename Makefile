
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
CLIENT_FILES = ./src/client/*.cpp
CLIENT_BIN_PATH = ./bin/client
RESOURCES_H = ./src/client/Resources.h

client:
	mkdir -p bin
	g++ -std=c++17 -o $(CLIENT_BIN_PATH) -O3 $(FLAGS) $(CLIENT_FILES) -I/src/client/ -I/usr/include/SFML $(SFML_LIBS) 

resources:
	rm -f $(RESOURCES_H)
	@echo '#pragma once' >> $(RESOURCES_H) 

	@for file in $(shell find ./res -type f) ;\
	do \
		xxd -i $${file} | sed 's/unsigned/const\ unsigned/g' >> $(RESOURCES_H) && \
		echo "$${file} >> $(RESOURCES_H)" ;\
	done

all: resources client