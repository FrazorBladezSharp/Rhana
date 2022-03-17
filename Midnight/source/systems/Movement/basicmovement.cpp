#include "basicmovement.h"


namespace Night
{
    BasicMovement::BasicMovement()
    {

    }

    void BasicMovement::MovePlayer(
            Ref<Player> &player,
            QString &textView,
            Ref<TextOutput> &output,
            QKeyEvent *event)
    {
        Position_Component* player_position =
                player->getPosition();

        int x = 0;
        int y = 0;

        int posX = player_position->x;
        int posY = player_position->y;

        x += ((event->key() == Qt::Key::Key_D) * 1);
        x -= ((event->key() == Qt::Key::Key_A) * 1);
        y += ((event->key() == Qt::Key::Key_S) * 1);
        y -= ((event->key() == Qt::Key::Key_W) * 1);

        x = (x * ((posX + x >= 0) && (posX + x < 79)));
        y = (y * ((posY + y >= 0) && (posY + y < 20)));
        posX += x;
        posY += y;

        textView = output->Move(x, y, posX, posY, "P");

        player_position->x = posX;
        player_position->y = posY;
    }

}
