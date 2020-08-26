
QT+=widgets
QT+=opengl
QT += gui
QT+=core


SOURCES += \
        body.cpp \
        gl_cube.cpp \
        gl_game.cpp \
        main.cpp \
        qmainwindows_.cpp \
        world.cpp

HEADERS += \
    body.h \
    gl_cube.h \
    gl_game.h \
    qmainwindows_.h \
    world.h

RESOURCES += \
    Shaders.qrc \

DISTFILES +=
