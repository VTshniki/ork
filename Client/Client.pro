QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 qaxcontainer

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    assistantclasss.cpp \
    authorization.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    serializationclass.cpp \
    sortedwidgetinanalisyswindow.cpp \
    tableanalisyswindow.cpp \
    tableuploadwindow.cpp

HEADERS += \
    assistantclasss.h \
    authorization.h \
    mainwindow.h \
    menu.h \
    serializationclass.h \
    sortedwidgetinanalisyswindow.h \
    tableanalisyswindow.h \
    tableuploadwindow.h

FORMS += \
    authorization.ui \
    mainwindow.ui \
    menu.ui \
    sortedwidgetinanalisyswindow.ui \
    tableanalisyswindow.ui \
    tableuploadwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
