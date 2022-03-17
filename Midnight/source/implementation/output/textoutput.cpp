#include "textoutput.h"


namespace Night
{
    TextOutput::TextOutput(QWidget *parent)
        : QPlainTextEdit(parent)
    {
        // Empty
    }

    QString TextOutput::Initialize()
    {
        // initialize text output
        for (int y = 0; y < 20; y++)
        {
            for (int x = 0; x < 79; x++)
                scene[x][y] = ".";

            scene[79][y] += "\n";
        }

        return ReconstructOutput();
    }   

    QString TextOutput::SetPosition(int x, int y, QString symbol)
    {
        scene[x][y] = symbol;

        return ReconstructOutput();
    }

    QString TextOutput::Move(int dir_x, int dir_y, int current_x, int current_y, QString symbol)
    {
        scene[current_x - dir_x][current_y - dir_y] = ".";
        scene[current_x][current_y] = symbol;

        return ReconstructOutput();
    }

    QString TextOutput::ReconstructOutput()
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
