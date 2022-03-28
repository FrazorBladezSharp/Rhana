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

        const QVector <Scene::Object*>& viewHandTool(){
            return *m_handTool;
        }


    private:
        void loadItemFile(QString file, QVector <Scene::Object*> *shelf);

        Ref<Scene> m_world;
        int m_items;
        Scene::Object *m_baseItemObject = nullptr;

        QVector <Scene::Object*> *m_handTool;



    };
}

#endif // ITEMWAREHOUSE_H
