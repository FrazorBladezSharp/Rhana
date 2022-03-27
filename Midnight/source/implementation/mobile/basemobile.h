#ifndef BASEMOBILE_H
#define BASEMOBILE_H

#include "source/night_common.h"
#include "source/ECS/scene.h"
namespace Night
{
    // this class has to be inherited
    class BaseMobile
    {

    public:
        virtual PositionComponent* getPosition() = 0;

    protected:
        explicit BaseMobile(int id, Ref<Scene> &scene);

        int m_id =0;
        Ref<Scene> m_scene;

    };
}

#endif // BASEMOBILE_H
