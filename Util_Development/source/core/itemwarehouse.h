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
        ItemWarehouse(Ref<Scene>& world, int items);
        ~ItemWarehouse();

        void initialize();

        const QVector <Scene::Object*>& viewWeapons(){
            return *m_Weapons;
        }


    private:
        void loadItemFile(QString file, QVector <Scene::Object*> *shelf);

        Ref<Scene> m_World;
        int m_Items;
        Scene::Object *m_BaseItemObject = nullptr;

        QVector <Scene::Object*> *m_Weapons;



    };
}

#endif // ITEMWAREHOUSE_H
