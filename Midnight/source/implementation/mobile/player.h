#ifndef PLAYER_H
#define PLAYER_H

#include "source/night_common.h"
#include "basemobile.h"

namespace Night
{
    class Player : public BaseMobile
    {

    public:
        Player(int id, Ref<Scene> &scene);

        virtual PositionComponent* getPosition() override;
    };

}

#endif // PLAYER_H
