QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    selectseat.cpp \
    targetplaceselect.cpp \
    ticketlist.cpp \
    ticketpay.cpp

HEADERS += \
    loginwindow.h \
    mainwindow.h \
    selectseat.h \
    targetplaceselect.h \
    ticketlist.h \
    ticketpay.h

FORMS += \
    loginwindow.ui \
    mainwindow.ui \
    selectseat.ui \
    targetplaceselect.ui \
    ticketlist.ui \
    ticketpay.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image/images.qrc

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
