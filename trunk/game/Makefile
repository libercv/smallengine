# Si no existen los directorios hay que crearlos
# Ver includes para que ciertas variables sean para todo el proyecto
CC = g++
LINKER = g++
BIN_PREFIX=../bin
OBJS_DIR = $(BIN_PREFIX)/game
SOURCES = game.cpp linuxmain.cpp
OBJS=$(SOURCES:%.cpp=$(OBJS_DIR)/%.o)
ENGINE_DIR = $(BIN_PREFIX)/engine


all: $(OBJS) $(OBJS_DIR)/small
	cd ../engine && make

$(OBJS_DIR)/small: $(OBJS) $(ENGINE_DIR)/libengine.so
	$(LINKER) $(OBJS) -o $(OBJS_DIR)/small -L/usr/X11R6/lib -lGL -lGLU -lXxf86vm -L$(ENGINE_DIR) -lengine

$(ENGINE_DIR)/libengine.so:
	cd ../engine && make


$(OBJS): $(OBJS_DIR)/%.o : %.cpp
	$(CC) -c $< -o $@

game.cpp: game.h

clean:
	cd ../engine && make clean
	rm $(OBJS_DIR)/*.o
	rm $(OBJS_DIR)/small
	