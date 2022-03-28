QT += core gui widgets

CONFIG += c17 c++17 console
#CONFIG -= app_bundle


SOURCES += \
        main.cpp \
        source/gfx/vulkanrendering.cpp \
        source/gfx/vulkanwidget.cpp \
        source/rhanawindow.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    source/rhanawindow.ui

HEADERS += \
    source/gfx/buffers.h \
    source/gfx/vulkanrendering.h \
    source/gfx/vulkanwidget.h \
    source/rhanawindow.h
