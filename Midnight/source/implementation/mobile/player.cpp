#include "player.h"


namespace Night
{
    Player::Player(int id, Ref<Scene> &scene)
        : BaseMobile(id, scene)
    {
        // Empty
    }

    Position_Component *Player::getPosition()
    {
        Position_Component* player_position = nullptr;

        auto registry = m_Scene->ViewRegistry();

        Scene::Object* object = registry[m_ID];

        player_position = static_cast<Position_Component*>(object->components[(int)Component::COMP_POSITION]);

        return player_position;
    }

}
