PROJECT (Small)
INCLUDE(FindOpenGL)
INCLUDE(FindJPEG)

SET(WORLD_SRCS world/camera.cpp world/entity.cpp world/light.cpp world/object.cpp world/player.cpp)
SET(SYSTEM_SRCS system/linuxinput.cpp system/linuxtimer.cpp system/linuxwindow.cpp)
SET(GRAPHICS_SRCS graphics/bitset.cpp graphics/drawing3d.cpp graphics/frustum.cpp graphics/image.cpp 
	graphics/linuxfont.cpp graphics/md2.cpp graphics/pcx.cpp graphics/q3bsp.cpp graphics/texture.cpp)
SET(SOUND_SRCS sound/sound.cpp)
SET(MATH_SRCS math/color.cpp math/matrix4x4.cpp math/plane.cpp math/vector2d.cpp math/vector3d.cpp math/vector4d.cpp)
SET(SCRIPT_SRCS script/script.cpp script/bindings.cpp)

SET(XF86VM_SEARCH_PATH
/usr/lib
/usr/X11R6/lib
)

SET(STD_SEARCH_PATH
/usr/lib
)

SET(LOCAL_SEARCH_PATH
/usr/local/lib
)

FIND_LIBRARY(XF86VM_LIB Xxf86vm ${XF86VM_SEARCH_PATH})
FIND_LIBRARY(LUA_LIB lua5.1 ${LOCAL_SEARCH_PATH} NO_DEFAULT_PATH)
FIND_LIBRARY(FMOD_LIB fmod-3.75 ${LOCAL_SEARCH_PATH})
FIND_LIBRARY(XMLPARSER_LIB xmlParser ${LOCAL_SEARCH_PATH})
#FIND_LIBRARY(TOLUA_LIB tolua ${LOCAL_SEARCH_PATH})

ADD_EXECUTABLE (Small engine.cpp stategame.cpp statemenu.cpp linuxmain.cpp waymap.cpp log.cpp
	${WORLD_SRCS}  ${SYSTEM_SRCS} ${GRAPHICS_SRCS} ${SOUND_SRCS}
	${SCRIPT_SRCS} ${MATH_SRCS})

TARGET_LINK_LIBRARIES(Small ${OPENGL_LIBRARIES} ${JPEG_LIBRARIES} 
	${XF86VM_LIB} ${LUA_LIB} ${FMOD_LIB} ${XMLPARSER_LIB}
	libtolua.a)
#	${TOLUA_LIB})
