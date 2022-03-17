#include "midnight.h"


namespace Night
{
    Midnight::Midnight(QObject *parent)
        : QObject(parent)
        , m_MovementSystem(CreateRef<BasicMovement>())
        , m_RenderingSystem(CreateRef<BasicRendering>())
        , m_Scene(CreateRef<Scene>())
        , m_Output(CreateRef<TextOutput>(nullptr))
        , m_Camera(CreateRef<Camera>(m_Scene->AddEntity(), m_Scene))
        , m_Player(CreateRef<Player>(m_Scene->AddEntity(), m_Scene))
    {
        m_Scene->Initialize();
    }

    void Midnight::OnUpdate()
    {
        m_RenderingSystem->TextRendering(m_Output, m_TextView);
    }

    bool Midnight::RegisterOutput(TextOutput *output)
    {
        bool result = true;

        m_Output.reset(output);
        m_TextView = m_Output->Initialize();

        result = !(m_Output == nullptr);

        return result;
    }

    void Midnight::SetPlayerPosition(int x, int y)
    {
        Position_Component* player_position =
                m_Player->getPosition();

        player_position->x = x;
        player_position->y = y;

        m_TextView = m_Output->SetPosition(x, y, "P");
    }

    void Midnight::MovePlayer(QKeyEvent *event)
    {
        m_MovementSystem->MovePlayer(
                    m_Player,
                    m_TextView,
                    m_Output,
                    event);
    }

}
