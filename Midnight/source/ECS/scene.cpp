#include "scene.h"


namespace Night
{

    Scene::Scene()
    {
        m_registry = new QVector<Object*>();
    }

    Scene::~Scene()
    {
        m_registry->clear();
        delete m_registry;
    }

    void Scene::initialize()
    {
        for (int index = 0; index < NIGHT_MAX_ENTITIES; index++)
            m_entity->entities[index] = NIGHT_UNUSED;
    }

    int Scene::addEntity()
    {
        static int entityID = NIGHT_UNUSED;
        entityID++;

        m_entity->entities[entityID] = entityID;

        baseComponents(entityID);

        return entityID;
    }

    const QVector<Scene::Object *> &Scene::viewRegistry()
    {
        return *m_registry;
    }

    void Scene::baseComponents(int entityID)
    {
        PositionComponent *position = new PositionComponent();

        Object *object = new Object();

        for (int index = 0; index < (int)Night::Component::COMP_TOTAL; index++)
            object->components[index] = nullptr;

        object->entityID = entityID;
        object->uuid = QUuid::createUuid();
        object->components[(unsigned)Night::Component::COMP_POSITION] = position;

        m_registry->push_back(object);
    }
}
