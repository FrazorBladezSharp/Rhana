#ifndef SCENE_H
#define SCENE_H

#include "source/night_common.h"

#include "components.h"
#include <QVector>
#include <QUuid>


namespace Night
{

    class Scene
    {

        struct Entity
        {

            int entities[NIGHT_MAX_ENTITIES];

        };

    public:

        typedef struct
        {

            int entityID;
            QUuid uuid;
            void* components[(unsigned)Night::Component::COMP_TOTAL];

        } Object;


        Scene();
        ~Scene();

        void initialize();

        int addEntity();

        const QVector <Object*>& viewRegistry();

        Object* getObject(int baseEntity) {
            return *m_registry[baseEntity].data();
        }

    private:
        void baseComponents(int entity_id);

        Ref<Entity> m_entity = CreateRef<Entity>();
        // needs to be kept in sync with Entity.
        QVector <Object*> *m_registry;

    };

}
#endif // SCENE_H
