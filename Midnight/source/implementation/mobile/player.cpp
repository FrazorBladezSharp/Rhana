#include "player.h"


namespace Night
{
    Player::Player(int id, Ref<Scene> &scene)
        : BaseMobile(id, scene)
    {
        // Empty
    }

    PositionComponent *Player::getPosition()
    {
        PositionComponent* playerPosition = nullptr;

        auto registry = m_scene->viewRegistry();

        Scene::Object* object = registry[m_id];

        playerPosition = static_cast<PositionComponent*>(object->components[(int)Component::COMP_POSITION]);

        return playerPosition;
    }

}
