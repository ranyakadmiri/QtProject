QT       += core gui
QT+= sql
QT+= printsupport
QT+= core gui sql
QT+= core gui sql charts
QT+= location qml quickwidgets
QT+= core network
QT+= charts serialport
QT+= core gui  serialport
QT       += core gui sql printsupport serialport network multimedia multimediawidgets charts widgets axcontainer
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    client.cpp \
    connection.cpp \
    employe.cpp \
    evenement.cpp \
    exportexelobjet.cpp \
    lieux.cpp \
    main.cpp \
    mainwindow.cpp \
    partenaires.cpp \
    qrcode.cpp \
    smtp.cpp

HEADERS += \
    arduino.h \
    client.h \
    connection.h \
    employe.h \
    evenement.h \
    exportexelobjet.h \
    lieux.h \
    mainwindow.h \
    partenaires.h \
    qrcode.h \
    smtp.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
