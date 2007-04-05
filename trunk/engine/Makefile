CC = g++
LINKER = g++ -shared

SOURCES = engine.cpp 
SRC_SYSTEM = linuxwindow.cpp linuxsystem.cpp linuxinput.cpp linuxtimer.cpp
SRC_WORLD= entity.cpp camera.cpp object.cpp light.cpp
SRC_GRAPHICS = md2.cpp pcx.cpp texture.cpp tga.cpp bmp.cpp linuxfont.cpp drawing3d.cpp
SRC_UI = menu.cpp

OBJS=$(SOURCES:%.cpp=$(OBJS_DIR)/%.o)
OBJS_SYSTEM=$(SRC_SYSTEM:%.cpp=$(OBJS_DIR)/system/%.o)
OBJS_WORLD=$(SRC_WORLD:%.cpp=$(OBJS_DIR)/world/%.o)
OBJS_GRAPHICS=$(SRC_GRAPHICS:%.cpp=$(OBJS_DIR)/graphics/%.o)
OBJS_UI=$(SRC_UI:%.cpp=$(OBJS_DIR)/ui/%.o)

OBJS_DIR = ../bin/engine



all: $(OBJS) $(OBJS_SYSTEM) $(OBJS_WORLD) $(OBJS_GRAPHICS) $(OBJS_UI) $(OBJS_DIR)/libengine.so

clean:
	rm $(OBJS)
	rm $(OBJS_DIR)/libengine.so
	rm $(OBJS_SYSTEM)
	rm $(OBJS_WORLD)
	rm $(OBJS_GRAPHICS)
	rm $(OBJS_UI)


$(OBJS_DIR)/libengine.so: $(OBJS) $(OBJS_SYSTEM) $(OBJS_WORLD) $(OBJS_GRAPHICS)
	$(LINKER) -o $(OBJS_DIR)/libengine.so $(OBJS_SYSTEM) $(OBJS) $(OBJS_WORLD) $(OBJS_GRAPHICS) $(OBJS_UI)

$(OBJS): $(OBJS_DIR)/%.o : %.cpp
	$(CC) -c $< -o $@
	
$(OBJS_SYSTEM) : $(OBJS_DIR)/system/%.o : system/%.cpp
	$(CC) -c $< -o $@

$(OBJS_WORLD): $(OBJS_DIR)/world/%.o : world/%.cpp
	$(CC) -c $< -o $@
	
$(OBJS_GRAPHICS): $(OBJS_DIR)/graphics/%.o: graphics/%.cpp
	$(CC) -c $< -o $@
	
$(OBJS_UI): $(OBJS_DIR)/ui/%.o: ui/%.cpp
	$(CC) -c $< -o $@

$(OBJS_DIR)/engine.o: engine.cpp engine.h system/linuxsystem.h system/isystem.h \
  system/iwindow.h system/iinput.h system/linuxwindow.h \
  system/linuxinput.h system/linuxinput.h world/entity.h world/camera.h \
  world/entity.h
$(OBJS_DIR)/system/linuxwindow.o: system/linuxwindow.cpp system/linuxwindow.h \
  system/iwindow.h
$(OBJS_DIR)/system/linuxsystem.o: system/linuxsystem.cpp system/linuxsystem.h \
  system/isystem.h system/iwindow.h system/iinput.h system/linuxwindow.h \
  system/linuxinput.h
$(OBJS_DIR)/system/linuxinput.o: system/linuxinput.cpp system/linuxinput.h system/iinput.h
$(OBJS_DIR)/world/camera.o: world/camera.cpp world/camera.h world/entity.h
$(OBJS_DIR)/world/entity.o: world/entity.cpp world/entity.h
$(OBJS_DIR)/graphics/md2.o: graphics/md2.cpp graphics/md2.h graphics/texture.h \
  graphics/anorms.h graphics/anormtab.h
$(OBJS_DIR)/graphics/texture.o: graphics/texture.cpp graphics/texture.h graphics/bmp.h \
  graphics/tga.h graphics/pcx.h
$(OBJS_DIR)/graphics/pcx.o: graphics/pcx.cpp graphics/pcx.h
$(OBJS_DIR)/graphics/bmp.o: graphics/bmp.cpp graphics/bmp.h
$(OBJS_DIR)/graphics/tga.o: graphics/tga.cpp graphics/tga.h
$(OBJS_DIR)/world/object.o: world/object.cpp
$(OBJS_DIR)/ui/menu.o: ui/menu.cpp ui/menu.h
