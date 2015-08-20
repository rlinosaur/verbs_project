#-------------------------------------------------
#
# Project created by QtCreator 2015-08-06T09:52:36
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = verbs_project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    verbs_database.cpp \
    verbeditor.cpp \
    defines.cpp \
    settingsdialog.cpp \
    lineeditforverbs.cpp

HEADERS  += mainwindow.h \
    verbs_database.h \
    verbeditor.h \
    defines.h \
    settingsdialog.h \
    lineeditforverbs.h

FORMS    += mainwindow.ui \
    verbeditor.ui \
    settingsdialog.ui

OTHER_FILES += \
    todo.txt

RESOURCES += \
    resources.qrc
