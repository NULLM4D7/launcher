QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    exitBtn.cpp \
    helpbtn.cpp \
    main.cpp \
    minimizebtn.cpp \
    newstabwidget.cpp \
    newswidget.cpp \
    setbtn.cpp \
    setwidget.cpp \
    startbtn.cpp \
    tipbtn.cpp \
    toolbarbtn.cpp \
    widget.cpp

HEADERS += \
    exitBtn.h \
    helpbtn.h \
    minimizebtn.h \
    newstabwidget.h \
    newswidget.h \
    setbtn.h \
    setwidget.h \
    startbtn.h \
    tipbtn.h \
    toolbarbtn.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
