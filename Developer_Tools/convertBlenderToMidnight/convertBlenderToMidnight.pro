QT += core gui widgets

CONFIG += c17 c++17 console
#CONFIG -= app_bundle

LIBS += -lassimp

SOURCES += \
        main.cpp \
        source/gfx/modelloader.cpp \
        source/gfx/vulkanrendering.cpp \
        source/gfx/vulkanwidget.cpp \
        source/rhanawindow.cpp

HEADERS += \
    source/gfx/buffers.h \
    source/gfx/modelloader.h \
    source/gfx/vulkanrendering.h \
    source/gfx/vulkanwidget.h \
    source/rhanawindow.h

FORMS += \
    source/rhanawindow.ui


DISTFILES += \
    source/resource/shaders/color_frag.spv \
    source/resource/shaders/color_vert.spv


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
