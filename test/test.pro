QT -= core gui

CONFIG += c++11

TARGET = testconsole
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../libtscalc/include

SOURCES += main.cpp

HEADERS += 

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libtscalc/release/ -llibtscalc
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libtscalc/debug/ -llibtscalc
else:unix: LIBS += -L$$OUT_PWD/../libtscalc/ -llibtscalc

INCLUDEPATH += $$PWD/../libtscalc
DEPENDPATH += $$PWD/../libtscalc

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libtscalc/release/liblibtscalc.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libtscalc/debug/liblibtscalc.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libtscalc/release/libtscalc.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libtscalc/debug/libtscalc.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../libtscalc/liblibtscalc.a
