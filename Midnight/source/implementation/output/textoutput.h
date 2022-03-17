#ifndef TEXTOUTPUT_H
#define TEXTOUTPUT_H

#include <QPlainTextEdit>

namespace Night
{
    class TextOutput : public QPlainTextEdit
    {
        Q_OBJECT
    public:
        TextOutput(QWidget *parent = nullptr);

        QString Initialize();

        QString SetPosition(int x, int y, QString symbol);

        QString Move(int dir_x, int dir_y, int current_x, int current_y, QString symbol);

    private:

        QString ReconstructOutput();

        QString scene[80][20];
    };
}

#endif // TEXTOUTPUT_H
