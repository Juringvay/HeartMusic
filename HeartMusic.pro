#-------------------------------------------------
#
# Project created by QtCreator 2016-07-07T14:46:33
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HeartMusic
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    logindialog.cpp

HEADERS  += mainwidget.h \
    logindialog.h

FORMS    += mainwidget.ui \
    logindialog.ui


MOC_DIR       = temp/moc
RCC_DIR       = temp/rcc
UI_DIR        = temp/ui
OBJECTS_DIR   = temp/obj
DESTDIR       = bin

RC_FILE = main.rc

RESOURCES += \
    image.qrc
