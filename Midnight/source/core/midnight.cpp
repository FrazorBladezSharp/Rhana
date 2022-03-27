#include "midnight.h"


namespace Night
{
    Midnight::Midnight(QObject *parent)
        : QObject(parent)
        , m_movementSystem(CreateRef<BasicMovement>())
        , m_renderingSystem(CreateRef<BasicRendering>())
        , m_scene(CreateRef<Scene>())
        , m_output(CreateRef<TextOutput>(nullptr))
        , m_camera(CreateRef<Camera>(m_scene->addEntity(), m_scene))
        , m_player(CreateRef<Player>(m_scene->addEntity(), m_scene))
    {
        m_scene->initialize();
    }

    void Midnight::onUpdate()
    {
        m_renderingSystem->textRendering(m_output, m_textView);
    }

    bool Midnight::registerOutput(TextOutput *output)
    {
        bool result = true;

        m_output.reset(output);
        m_textView = m_output->initialize();

        result = !(m_output == nullptr);

        return result;
    }

    void Midnight::setPlayerPosition(int x, int y)
    {
        PositionComponent* playerPosition =
                m_player->getPosition();

        playerPosition->x = x;
        playerPosition->y = y;

        m_textView = m_output->setPosition(x, y, "@");
    }

    void Midnight::movePlayer(QKeyEvent *event)
    {
        m_movementSystem->movePlayer(
                    m_player,
                    m_textView,
                    m_output,
                    event);
    }

}
