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

        void onUpdate();

        bool registerOutput(TextOutput* output);

        void setPlayerPosition(int x, int y);

        void movePlayer(QKeyEvent *event);


    private:
        Ref<BasicMovement> m_movementSystem;
        Ref<BasicRendering> m_renderingSystem;

        Ref<Scene> m_scene;
        Ref<TextOutput> m_output;
        Ref<Camera> m_camera;
        Ref<Player> m_player;
        QString m_textView;

    };
}

#endif // MIDNIGHT_H
