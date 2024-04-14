QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ClassesDialog.cpp \
    TreePage.cpp \
    UserCharacter.cpp \
    dialogTraits.cpp \
    jsonmanipulation.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ClassesDialog.h \
    TreePage.h \
    UserCharacter.h \
    dialogTraits.h \
    jsonmanipulation.h \
    mainwindow.h

FORMS += \
    ClassesDialog.ui \
    TreePage.ui \
    dialogTraits.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
