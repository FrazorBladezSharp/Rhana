#ifndef MIDNIGHT_H
#define MIDNIGHT_H

#include "source/night_common.h"

#include <QObject>
#include "source/systems/Movement/basicmovement.h"
#include "source/systems/Rendering/basicrendering.h"

#include "source/ECS/scene.h"
#include "source/implementation/mobile/mobiles.h"
#include "source/implementation/output/textoutput.h"



namespace Night
{
    class Midnight : public QObject
    {
        Q_OBJECT

    public:
        Midnight(QObject *parent);

        void OnUpdate();

        bool RegisterOutput(TextOutput* output);

        void SetPlayerPosition(int x, int y);

        void MovePlayer(QKeyEvent *event);


    private:
        Ref<BasicMovement> m_MovementSystem;
        Ref<BasicRendering> m_RenderingSystem;

        Ref<Scene> m_Scene;
        Ref<TextOutput> m_Output;
        Ref<Camera> m_Camera;
        Ref<Player> m_Player;
        QString m_TextView;

    };
}

#endif // MIDNIGHT_H
