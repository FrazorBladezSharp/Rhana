#include "camera.h"


namespace Night
{
    Camera::Camera(int id, Ref<Scene> &scene)
        : BaseMobile(id, scene)
    {
        // Empty
    }

    PositionComponent *Camera::getPosition()
    {
        PositionComponent* cameraPosition = nullptr;

        auto registry = m_scene->viewRegistry();

        Scene::Object* object = registry[m_id];

        cameraPosition = static_cast<PositionComponent*>(object->components[(int)Component::COMP_POSITION]);

        return cameraPosition;
    }

}
