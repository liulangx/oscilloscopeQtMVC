QT += opengl widgets core
DEFINES += DEBUG
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
    InsertQtWin/CGraphicsWidget.h \
    AxisAndGrid/CAxis.h \
    DataManage/CVaoVboManager.h \
    AxisAndGrid/CLines.h \
    AxisAndGrid/CLineManager.h \
    AxisAndGrid/CSceneManager.h \
    AxisAndGrid/CAxisManager.h \
    AxisAndGrid/CGrid.h \
    AxisAndGrid/CGridManager.h \
    AxisAndGrid/textureindex.h \
    InsertQtWin/CInsQtWinManager.h
SOURCES += \
           main.cpp \
    LLComboWidget.cpp \
    Shaders/CRender.cpp \
    MVC/CScene.cpp \
    MVC/CMVCWidget.cpp \
    MVC/CGraphicsView.cpp \
    InsertQtWin/ItemDialog.cpp \
    InsertQtWin/CTwoSidedGraphicsWidget.cpp \
    InsertQtWin/CGraphicsWidget.cpp \
    AxisAndGrid/CAxis.cpp \
    DataManage/CVaoVboManager.cpp \
    AxisAndGrid/CLines.cpp \
    AxisAndGrid/CLineManager.cpp \
    AxisAndGrid/CSceneManager.cpp \
    AxisAndGrid/CAxisManager.cpp \
    AxisAndGrid/CGrid.cpp \
    AxisAndGrid/CGridManager.cpp \
    InsertQtWin/CInsQtWinManager.cpp
#LIBS += -L/usr/lib/x86_64-linux-gnu/ -lGL -lglut

DISTFILES += \
    Shaders/basic.Frag \
    Shaders/basic.vert \
    Shaders/lines.geo \
    Shaders/lines.Frag \
    Shaders/coord.frag \
    Shaders/lines.vert \
    Shaders/coord.vert
