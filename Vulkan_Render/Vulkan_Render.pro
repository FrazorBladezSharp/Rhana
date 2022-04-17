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

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    source/resource/shaders/Scratchpad.txt \
    source/resource/shaders/color.frag \
    source/resource/shaders/color.vert \
    source/resource/shaders/color_frag.spv \
    source/resource/shaders/color_vert.spv \
    source/resource/shaders/reference_vert.spv

FORMS += \
    source/rhanawindow.ui

HEADERS += \
    source/gfx/buffers.h \
    source/gfx/modelloader.h \
    source/gfx/vulkanrendering.h \
    source/gfx/vulkanwidget.h \
    source/rhanawindow.h
