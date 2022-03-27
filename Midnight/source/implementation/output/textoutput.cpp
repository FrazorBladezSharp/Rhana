#include "textoutput.h"


namespace Night
{
    TextOutput::TextOutput(QWidget *parent)
        : QPlainTextEdit(parent)
    {
        // Empty
    }

    QString TextOutput::initialize()
    {
        // initialize text output
        for (int y = 0; y < 20; y++)
        {
            for (int x = 0; x < 79; x++)
                scene[x][y] = ".";

            scene[79][y] += "\n";
        }

        return reconstructOutput();
    }   

    QString TextOutput::setPosition(int x, int y, QString symbol)
    {
        scene[x][y] = symbol;

        return reconstructOutput();
    }

    QString TextOutput::move(int dirX, int dirY, int currentX, int currentY, QString symbol)
    {
        scene[currentX - dirX][currentY - dirY] = ".";
        scene[currentX][currentY] = symbol;

        return reconstructOutput();
    }

    QString TextOutput::reconstructOutput()
    {
        QString result;

        for (int y = 0; y < 20; y++)
        {
            for (int x = 0; x < 79; x++)
                result += scene[x][y];

            result += "\n";
        }

        return result;
    }
}
