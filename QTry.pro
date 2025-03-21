QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AbilityScorePage.cpp \
    ClassesDialog.cpp \
    RaceDialog.cpp \
    SheetPage.cpp \
    TreePage.cpp \
    UserCharacter.cpp \
    extrasPage.cpp \
    jsonmanipulation.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    AbilityScorePage.h \
    ClassesDialog.h \
    RaceDialog.h \
    SheetPage.h \
    SmallClasses.h \
    TreePage.h \
    UserCharacter.h \
    extrasPage.h \
    jsonmanipulation.h \
    mainwindow.h

FORMS += \
    AbilityScorePage.ui \
    ClassesDialog.ui \
    RaceDialog.ui \
    SheetPage.ui \
    TreePage.ui \
    extrasPage.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
