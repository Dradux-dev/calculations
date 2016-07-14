QT       -= core gui

TARGET = lib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += 

HEADERS += \ 
    anglefunction.h \
    binaryoperator.h \
    brackets.h \
    divide.h \
    double.h \
    element.h \
    elementptr.h \
    exporter.h \
    formatter.h \
    function.h \
    integrate.h \
    latex.h \
    minus.h \
    multiplicate.h \
    operator.h \
    physicalvalue.h \
    plus.h \
    pow.h \
    reference.h \
    replacer.h \
    sin.h \
    stack.h \
    unaryoperator.h \
    unit.h \
    unittable.h \
    util.h \
    value.h \
    variable.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
