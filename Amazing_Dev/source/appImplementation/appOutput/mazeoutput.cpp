#include "mazeoutput.h"


  MazeOutput::MazeOutput(QWidget *parent)
        : QPlainTextEdit(parent)
    {
        // Empty
    }

    QString MazeOutput::initialize(int sceneWidth, int sceneHeight)
    {
        // initialize text output
        m_sceneWidth = sceneWidth;
        m_sceneHeight = sceneHeight;

        for (int y = 0; y < sceneHeight; y++)
        {
            for (int x = 0; x < sceneWidth - 1; x++)
                m_scene += ".";

            m_scene += "\n";
        }

        return reconstructOutput();
    }   

    QString MazeOutput::setPosition(int x, int y, QString symbol)
    {
        m_scene.replace(1, x + y * x, symbol);

        return reconstructOutput();
    }

    QString MazeOutput::move(int dirX, int dirY, int currentX, int currentY, QString symbol)
    {
        m_scene.replace(1, (currentX - dirX) + (currentY - dirY) * (currentX - dirX), ".");
        m_scene.replace(1, currentX + currentY * currentX, symbol);

        return reconstructOutput();
    }

    QString MazeOutput::reconstructOutput()
    {
        QString result;

        for (int y = 0; y < m_sceneHeight; y++)
        {
            for (int x = 0; x < m_sceneWidth - 1; x++)
                result += m_scene[x + y * x];

            result += "\n";
        }

        return result;
    }

