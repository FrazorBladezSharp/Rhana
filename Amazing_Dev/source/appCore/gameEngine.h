#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "source/night_common.h"

#include <QObject>
#include <QKeyEvent>
#include <source/systems/Movement/basicmovement.h>
//#include "source/systems/Rendering/basicrendering.h"

#include <source/ECS/scene.h>
#include <source/implementation/mobile/mobiles.h>

#include "source/appImplementation/appOutput/mazeoutput.h"




    class GameEngine : public QObject
    {
        Q_OBJECT

    public:
        GameEngine(QObject *parent);

        void onUpdate();

        bool registerOutput(MazeOutput* output, int sceneWidth, int sceneHeight);

        void setPlayerPosition(int x, int y);

        void movePlayer(QKeyEvent *event);


    private:
        Night::Ref<Night::BasicMovement> m_movementSystem;
//        Ref<BasicRendering> m_renderingSystem;

        Night::Ref<Night::Scene> m_scene;
        Night::Ref<MazeOutput> m_output;
//        Ref<Camera> m_camera;
        Night::Ref<Night::Player> m_player;
        QString m_textView;

    };


#endif // GAMEENGINE_H
