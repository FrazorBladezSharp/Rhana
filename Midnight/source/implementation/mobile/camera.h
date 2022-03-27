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

        virtual PositionComponent* getPosition() override;
    };

}

#endif // CAMERA_H
