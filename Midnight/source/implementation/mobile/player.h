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

        virtual Position_Component* getPosition() override;
    };

}

#endif // PLAYER_H
