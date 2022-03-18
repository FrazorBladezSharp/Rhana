#ifndef ITEMWAREHOUSE_H
#define ITEMWAREHOUSE_H

#include <source/night_common.h>
#include <source/ECS/scene.h>
#include "source/core/utils/utilities.h"

#include <QStringList>


namespace Night
{
    class ItemWarehouse
    {

    public:
        ItemWarehouse(Ref<Scene>& world);
        ~ItemWarehouse();

        void Initialize();

        const QVector <Scene::Object*>& ViewWeapons(){
            return *m_Weapons;
        }


    private:
        Ref<Scene> m_World;
        QVector <Scene::Object*> *m_Weapons;

    };
}

#endif // ITEMWAREHOUSE_H
