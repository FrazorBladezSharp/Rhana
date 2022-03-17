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
        virtual Position_Component* getPosition() = 0;

    protected:
        explicit BaseMobile(int id, Ref<Scene> &scene);

        int m_ID =0;
        Ref<Scene> m_Scene;

    };
}

#endif // BASEMOBILE_H
