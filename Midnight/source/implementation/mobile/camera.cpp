#include "camera.h"


namespace Night
{
    Camera::Camera(int id, Ref<Scene> &scene)
        : BaseMobile(id, scene)
    {
        // Empty
    }

    Position_Component *Camera::getPosition()
    {
        Position_Component* camera_position = nullptr;

        auto registry = m_Scene->ViewRegistry();

        Scene::Object* object = registry[m_ID];

        camera_position = static_cast<Position_Component*>(object->components[(int)Component::COMP_POSITION]);

        return camera_position;
    }

}
