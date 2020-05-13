include_directories(${piyo-piyo_SOURCE_DIR}/lib/glew/include)

add_definitions(-DGLEW_STATIC)
add_library(
    glew STATIC
    src/glew.c
    include/GL/eglew.h
    include/GL/glew.h
    include/GL/glxew.h
    include/GL/wglew.h
)
