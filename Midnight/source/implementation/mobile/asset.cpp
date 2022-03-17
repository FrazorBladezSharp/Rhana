#include "asset.h"

namespace Night
{
    Asset::Asset(int id, Ref<Scene> &scene)
        : BaseMobile(id, scene)
    {
        // Empty
    }

    Position_Component *Asset::getPosition()
    {
        Position_Component* asset_position = nullptr;

        auto registry = m_Scene->ViewRegistry();

        Scene::Object* object = registry[m_ID];

        asset_position = static_cast<Position_Component*>(object->components[(int)Component::COMP_POSITION]);

        return asset_position;
    }

}
