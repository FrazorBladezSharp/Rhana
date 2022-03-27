#include "basicmovement.h"


namespace Night
{
    BasicMovement::BasicMovement()
    {

    }

    void BasicMovement::movePlayer(
            Ref<Player> &player,
            QString &textView,
            Ref<TextOutput> &output,
            QKeyEvent *event)
    {
        PositionComponent* playerPosition =
                player->getPosition();

        int x = 0;
        int y = 0;

        int posX = playerPosition->x;
        int posY = playerPosition->y;

        x += ((event->key() == Qt::Key::Key_D) * 1);
        x -= ((event->key() == Qt::Key::Key_A) * 1);
        y += ((event->key() == Qt::Key::Key_S) * 1);
        y -= ((event->key() == Qt::Key::Key_W) * 1);

        x = (x * ((posX + x >= 0) && (posX + x < 79)));
        y = (y * ((posY + y >= 0) && (posY + y < 20)));
        posX += x;
        posY += y;

        textView = output->move(x, y, posX, posY, "P");

        playerPosition->x = posX;
        playerPosition->y = posY;
    }

}
