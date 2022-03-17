#ifndef BASICMOVEMENT_H
#define BASICMOVEMENT_H

#include "source/night_common.h"

#include <QKeyEvent>

#include "source/ECS/scene.h"
#include "source/implementation/mobile/mobiles.h"
#include "source/implementation/output/textoutput.h"

namespace Night
{
    class BasicMovement
    {
    public:
        BasicMovement();

        void MovePlayer(
                Ref<Player>& player,
                QString& textView,
                Ref<TextOutput>& output,
                QKeyEvent *event);
    };
}

#endif // BASICMOVEMENT_H
