QT       -= core gui

TARGET = lib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += 

HEADERS += \ 
    tsdev/calculations/anglefunction.h \
    tsdev/calculations/binaryoperator.h \
    tsdev/calculations/brackets.h \
    tsdev/calculations/divide.h \
    tsdev/calculations/double.h \
    tsdev/calculations/element.h \
    tsdev/calculations/elementptr.h \
    tsdev/calculations/exporter.h \
    tsdev/calculations/formatter.h \
    tsdev/calculations/function.h \
    tsdev/calculations/integrate.h \
    tsdev/calculations/latex.h \
    tsdev/calculations/minus.h \
    tsdev/calculations/multiplicate.h \
    tsdev/calculations/operator.h \
    tsdev/calculations/physicalvalue.h \
    tsdev/calculations/plus.h \
    tsdev/calculations/pow.h \
    tsdev/calculations/reference.h \
    tsdev/calculations/replacer.h \
    tsdev/calculations/sin.h \
    tsdev/calculations/stack.h \
    tsdev/calculations/unaryoperator.h \
    tsdev/calculations/unit.h \
    tsdev/calculations/unittable.h \
    tsdev/calculations/util.h \
    tsdev/calculations/value.h \
    tsdev/calculations/variable.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
