#include "gameEngine.h"



    GameEngine::GameEngine(QObject *parent)
        : QObject(parent)
        , m_movementSystem(Night::CreateRef<Night::BasicMovement>())
//        , m_renderingSystem(CreateRef<BasicRendering>())
        , m_scene(Night::CreateRef<Night::Scene>())
        , m_output(Night::CreateRef<MazeOutput>(nullptr))
//        , m_camera(CreateRef<Camera>(m_scene->addEntity(), m_scene))
        , m_player(Night::CreateRef<Night::Player>(m_scene->addEntity(), m_scene))
    {
        m_scene->initialize();
    }

    void GameEngine::onUpdate()
    {
//        m_renderingSystem->textRendering(m_output, m_textView);
    }

    bool GameEngine::registerOutput(MazeOutput *output)
    {
        bool result = true;

        m_output.reset(output);
        m_textView = m_output->initialize();

        result = !(m_output == nullptr);

        return result;
    }

    void GameEngine::setPlayerPosition(int x, int y)
    {
        Night::PositionComponent* playerPosition =
                m_player->getPosition();

        playerPosition->x = x;
        playerPosition->y = y;

        m_textView = m_output->setPosition(x, y, "@");
    }

    void GameEngine::movePlayer(QKeyEvent *event)
    {
//        m_movementSystem->movePlayer(
//                    m_player,
//                    m_textView,
//                    m_output,
//                    event);
    }


