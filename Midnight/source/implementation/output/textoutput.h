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

        QString initialize();

        QString setPosition(int x, int y, QString symbol);

        QString move(int dirX, int dirY, int currentX, int currentY, QString symbol);

    private:

        QString reconstructOutput();

        QString scene[80][20];
    };
}

#endif // TEXTOUTPUT_H
