QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addvertexdialog.cpp \
    deletevertexdialog.cpp \
    editvertexdialog.cpp \
    graphpresenter.cpp \
    graphprocessor.cpp \
    intermediary.cpp \
    main.cpp \
    mainwindow.cpp \
    myopenglwidget.cpp \
    travellingsalemanproblemsolver.cpp

HEADERS += \
    addvertexdialog.h \
    deletevertexdialog.h \
    editvertexdialog.h \
    graphpresenter.h \
    graphprocessor.h \
    intermediary.h \
    mainwindow.h \
    myopenglwidget.h \
    travellingsalemanproblemsolver.h

FORMS += \
    addvertexdialog.ui \
    deletevertexdialog.ui \
    editvertexdialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
