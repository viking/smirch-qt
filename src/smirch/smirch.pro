include(../ui/ui.pri)

TARGET = smirch
TEMPLATE = app
DESTDIR = ../../bin

CONFIG += communi debug

OBJECTS_DIR = .obj
MOC_DIR = .moc
RCC_DIR = .rcc
UI_DIR = .ui

SOURCES += connectdialog.cpp main.cpp mainwindow.cpp smirch.cpp tab.cpp
HEADERS += connectdialog.h mainwindow.h smirch.h tab.h
