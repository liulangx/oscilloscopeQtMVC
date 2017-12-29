QT += opengl widgets core

qtConfig(opengles.|angle|dynamicgl): error("This example requires Qt to be configured with -opengl desktop")

HEADERS += \  
    Database.h \
    LLComboWidget.h \
    Shaders/CRender.h \
    MVC/CScene.h \
    MVC/CMVCWidget.h \
    MVC/CGraphicsView.h \
    InsertQtWin/ItemDialog.h \
    InsertQtWin/CTwoSidedGraphicsWidget.h \
    InsertQtWin/CGraphicsWidget.h
SOURCES += \
           main.cpp \
    LLComboWidget.cpp \
    Shaders/CRender.cpp \
    MVC/CScene.cpp \
    MVC/CMVCWidget.cpp \
    MVC/CGraphicsView.cpp \
    InsertQtWin/ItemDialog.cpp \
    InsertQtWin/CTwoSidedGraphicsWidget.cpp \
    InsertQtWin/CGraphicsWidget.cpp
#LIBS += -L/usr/lib/x86_64-linux-gnu/ -lGL -lglut

DISTFILES += \
    Shaders/basic.Frag \
    Shaders/basic.vert
