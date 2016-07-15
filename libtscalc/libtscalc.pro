QT       -= core gui

TARGET = libtscalc
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \ 
    source/cos.cpp \
    source/sin.cpp \
    source/unit.cpp

HEADERS += \ 
    include/tsdev/calculations/anglefunction.h \
    include/tsdev/calculations/binaryoperator.h \
    include/tsdev/calculations/brackets.h \
    include/tsdev/calculations/divide.h \
    include/tsdev/calculations/double.h \
    include/tsdev/calculations/element.h \
    include/tsdev/calculations/elementptr.h \
    include/tsdev/calculations/exporter.h \
    include/tsdev/calculations/formatter.h \
    include/tsdev/calculations/function.h \
    include/tsdev/calculations/integrate.h \
    include/tsdev/calculations/latex.h \
    include/tsdev/calculations/minus.h \
    include/tsdev/calculations/multiplicate.h \
    include/tsdev/calculations/operator.h \
    include/tsdev/calculations/physicalvalue.h \
    include/tsdev/calculations/plus.h \
    include/tsdev/calculations/pow.h \
    include/tsdev/calculations/reference.h \
    include/tsdev/calculations/replacer.h \
    include/tsdev/calculations/sin.h \
    include/tsdev/calculations/stack.h \
    include/tsdev/calculations/unaryoperator.h \
    include/tsdev/calculations/unit.h \
    include/tsdev/calculations/unittable.h \
    include/tsdev/calculations/util.h \
    include/tsdev/calculations/value.h \
    include/tsdev/calculations/variable.h \
    include/tsdev/calculations/exportstreamer.h \
    include/tsdev/calculations/calculations.h \
    include/tsdev/calculations/cos.h \
    include/sdev/calculations/error.h \
    include/tsdev/calculations/trapz.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
