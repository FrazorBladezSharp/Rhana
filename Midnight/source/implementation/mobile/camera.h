#ifndef CAMERA_H
#define CAMERA_H

#include "source/night_common.h"
#include "basemobile.h"

namespace Night
{
    class Camera : public BaseMobile
    {

    public:
        Camera(int id, Ref<Scene> &scene);

        virtual Position_Component* getPosition() override;
    };

}

#endif // CAMERA_H
