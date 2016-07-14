QT       -= core gui

TARGET = lib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += 

HEADERS += 

unix {
    target.path = /usr/lib
    INSTALLS += target
}
