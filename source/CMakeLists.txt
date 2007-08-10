PROJECT (Small)
INCLUDE(FindOpenGL)
INCLUDE(FindJPEG)

SET(WORLD_SRCS world/camera.cpp world/entity.cpp world/light.cpp world/object.cpp)
SET(UI_SRCS ui/menu.cpp)
SET(SYSTEM_SRCS system/linuxinput.cpp system/linuxtimer.cpp system/linuxwindow.cpp)
SET(GRAPHICS_SRCS graphics/bitset.cpp graphics/drawing3d.cpp graphics/frustum.cpp graphics/image.cpp 
	graphics/linuxfont.cpp graphics/md2.cpp graphics/pcx.cpp graphics/q3bsp.cpp graphics/texture.cpp)
SET(SOUND_SRCS sound/sound.cpp)
SET(MATH_SRCS math/color.cpp math/matrix4x4.cpp math/plane.cpp math/vector2d.cpp math/vector3d.cpp math/vector4d.cpp)

ADD_EXECUTABLE (Small engine.cpp game.cpp linuxmain.cpp waymap.cpp 
	${WORLD_SRCS} ${UI_SRCS} ${SYSTEM_SRCS} ${GRAPHICS_SRCS} ${SOUND_SRCS}
	${MATH_SRCS})

TARGET_LINK_LIBRARIES(Small ${OPENGL_LIBRARIES} ${JPEG_LIBRARIES})
