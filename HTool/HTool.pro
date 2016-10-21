#-------------------------------------------------
#
# Project created by QtCreator 2016-10-14T13:14:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HTool
TEMPLATE = app

INCLUDEPATH += \
	common\


SOURCES += \
	main.cpp\
    common/function/helpfunc.cpp \
    common/widget/customtable.cpp \
    wndbatchrename.cpp \
    wndfiledecode.cpp \
    common/widget/resizeablewidget.cpp

HEADERS  += \
    common/function/helpfunc.h \
    common/widget/customtable.h \
    common/common.h \
    wndbatchrename.h \
    wndfiledecode.h \
    common/widget/resizeablewidget.h
