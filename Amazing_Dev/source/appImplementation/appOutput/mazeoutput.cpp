#include "mazeoutput.h"


  MazeOutput::MazeOutput(QWidget *parent)
        : QPlainTextEdit(parent)
    {
        // Empty
    }

    QString MazeOutput::initialize()
    {
        // initialize text output

        // TODO: (Bladez)
        // need a new container to store our scene QList ??

        for (int y = 0; y < SCENE_HEIGHT; y++)
        {
            for (int x = 0; x < SCENE_WIDTH - 1; x++)
                scene[x][y] = ".";

            scene[SCENE_WIDTH - 1][y] += "\n";
        }

        return reconstructOutput();
    }   

    QString MazeOutput::setPosition(int x, int y, QString symbol)
    {
        scene[x][y] = symbol;

        return reconstructOutput();
    }

    QString MazeOutput::move(int dirX, int dirY, int currentX, int currentY, QString symbol)
    {
        scene[currentX - dirX][currentY - dirY] = ".";
        scene[currentX][currentY] = symbol;

        return reconstructOutput();
    }

    QString MazeOutput::reconstructOutput()
    {
        QString result;

        for (int y = 0; y < SCENE_HEIGHT; y++)
        {
            for (int x = 0; x < SCENE_WIDTH - 1; x++)
                result += scene[x][y];

            result += "\n";
        }

        return result;
    }

