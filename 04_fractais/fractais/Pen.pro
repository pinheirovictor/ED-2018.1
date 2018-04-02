TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    lib/pen.cpp \
    lib/cpen.cpp \
    aluno/frac_exemplos_cpp.cpp \
    aluno/frac_exemplos_c.cpp

HEADERS += \
    lib/cpen.h \
    lib/sfLine.h \
    lib/pen.h


CONFIG += c++11
LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
