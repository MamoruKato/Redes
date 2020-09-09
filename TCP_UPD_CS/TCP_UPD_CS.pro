QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TCP_UPD_CS
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/cliente.cpp \
    src/servidor.cpp \
    src/mthread.cpp \
    src/servidorudp.cpp \
    src/dialog.cpp

HEADERS  += includes/mainwindow.h \
    includes/cliente.h \
    includes/servidor.h \
    includes/mthread.h \
    includes/servidorudp.h \
    includes/dialog.h

FORMS    += ui/mainwindow.ui \
    ui/dialog.ui

INCLUDEPATH += $$PWD/includes
INCLUDEPATH += $$PWD/ui


DISTFILES +=

RESOURCES += \
    images.qrc

