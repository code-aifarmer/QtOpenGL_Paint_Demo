QT       += core gui
QT       += opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    board.cpp \
    main.cpp \
    base.cpp \
    openglwidget.cpp

HEADERS += \
    base.h \
    board.h \
    openglwidget.h

FORMS += \
    base.ui \
    board.ui \
    openglwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pic.qrc
win32:LIBS += -lOpengl32\
-lglu32
unix:LIBS += -lglut -lGLU
