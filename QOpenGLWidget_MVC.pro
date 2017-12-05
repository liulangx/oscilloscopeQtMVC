QT += opengl widgets core

qtConfig(opengles.|angle|dynamicgl): error("This example requires Qt to be configured with -opengl desktop")

HEADERS += \
           scene.h \
    roundedbox.h \
    gltrianglemesh.h \
    crender.h
SOURCES += \
           main.cpp \
           scene.cpp \
    roundedbox.cpp \
    gltrianglemesh.cpp \
    crender.cpp
#LIBS += -L/usr/lib/x86_64-linux-gnu/ -lGL -lglut

DISTFILES += \
    basic.Frag \
    basic.vert
