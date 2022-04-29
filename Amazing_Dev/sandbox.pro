QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c17 c++17

# a hack so QT can find the .ui file
INCLUDEPATH += ./source/appCore

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    source/appCore/applicationwindow.cpp \
    source/appCore/gameEngine.cpp \
    source/appImplementation/appOutput/mazeoutput.cpp


HEADERS += \
    source/appCore/applicationwindow.h \
    source/appCore/gameEngine.h \
    source/appImplementation/appOutput/mazeoutput.h



FORMS += \
    source/appCore/applicationwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-Midnight-Desktop_Qt_6_2_3_GCC_64bit-Debug/release/ -lMidnight
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-Midnight-Desktop_Qt_6_2_3_GCC_64bit-Debug/debug/ -lMidnight
else:unix:!macx: LIBS += -L$$PWD/../build-Midnight-Desktop_Qt_6_2_3_GCC_64bit-Debug/ -lMidnight

INCLUDEPATH += $$PWD/../Midnight
DEPENDPATH += $$PWD/../Midnight

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-Midnight-Desktop_Qt_6_2_3_GCC_64bit-Debug/release/libMidnight.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-Midnight-Desktop_Qt_6_2_3_GCC_64bit-Debug/debug/libMidnight.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-Midnight-Desktop_Qt_6_2_3_GCC_64bit-Debug/release/Midnight.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-Midnight-Desktop_Qt_6_2_3_GCC_64bit-Debug/debug/Midnight.lib
else:unix:!macx: PRE_TARGETDEPS += $$PWD/../build-Midnight-Desktop_Qt_6_2_3_GCC_64bit-Debug/libMidnight.a

DISTFILES += \
    README.md
