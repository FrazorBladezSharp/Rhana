#include "asset.h"

namespace Night
{
    Asset::Asset(int id, Ref<Scene> &scene)
        : BaseMobile(id, scene)
    {
        // Empty
    }

    PositionComponent *Asset::getPosition()
    {
        PositionComponent* assetPosition = nullptr;

        auto registry = m_scene->viewRegistry();

        Scene::Object* object = registry[m_id];

        assetPosition = static_cast<PositionComponent*>(object->components[(int)Component::COMP_POSITION]);

        return assetPosition;
    }

}
