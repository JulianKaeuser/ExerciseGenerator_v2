#-------------------------------------------------
#
# Project created by QtCreator 2017-10-08T16:26:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ExerciseGenerator_v2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    exercisemainwindow.cpp \
    animationdisplaywindow.cpp \
    timeslotdata.cpp \
    toolutilities.cpp \
    exerciseitem.cpp \
    paintlabel.cpp

HEADERS += \
        exercisemainwindow.h \
    animationdisplaywindow.h \
    timeslotdata.h \
    globaldata.h \
    toolutilities.h \
    exerciseitem.h \
    paintlabel.h \
    qtgifimage/src/gifimage/qgifglobal.h \
    qtgifimage/src/gifimage/qgifimage.h \
    qtgifimage/src/gifimage/qgifimage_p.h

FORMS += \
        exercisemainwindow.ui

RESOURCES += \
    exercisegenerator_v2_resources.qrc

include(/home/juliankaeuser/build-ExerciseGenerator-Desktop-Debug/qtgifimage/src/gifimage/qtgifimage.pri)
