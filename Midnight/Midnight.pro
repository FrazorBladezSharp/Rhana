QT -= gui

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    midnight.cpp \
    source/ECS/scene.cpp \
    source/core/midnight.cpp \
    source/implementation/mobile/asset.cpp \
    source/implementation/mobile/basemobile.cpp \
    source/implementation/mobile/camera.cpp \
    source/implementation/mobile/player.cpp \
    source/implementation/output/intropicture.cpp \
    source/implementation/output/textoutput.cpp \
    source/systems/Movement/basicmovement.cpp \
    source/systems/Rendering/basicrendering.cpp

HEADERS += \
    midnight.h \
    source/ECS/components.h \
    source/ECS/scene.h \
    source/core/midnight.h \
    source/implementation/mobile/asset.h \
    source/implementation/mobile/basemobile.h \
    source/implementation/mobile/camera.h \
    source/implementation/mobile/mobiles.h \
    source/implementation/mobile/player.h \
    source/implementation/output/intropicture.h \
    source/implementation/output/textoutput.h \
    source/night_common.h \
    source/systems/Movement/basicmovement.h \
    source/systems/Rendering/basicrendering.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    source/assets/items/item_data.txt \
    source/assets/pictures/midnight.jpg
