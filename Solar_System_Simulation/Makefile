CC = g++
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
INCLUDE = -Iinclude

SRC = main.cpp src/*.cpp
TARGET = build/app

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $^ $(INCLUDE) -o $@ $(LIBS)

clean:
	rm -f $(TARGET)
