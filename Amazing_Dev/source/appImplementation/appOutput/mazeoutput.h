#ifndef MAZEOUTPUT_H
#define MAZEOUTPUT_H

#include <QPlainTextEdit>

#define SCENE_WIDTH 10
#define SCENE_HEIGHT 10


    class MazeOutput : public QPlainTextEdit
    {
        Q_OBJECT
    public:
        MazeOutput(QWidget *parent = nullptr);

        QString initialize();

        QString setPosition(int x, int y, QString symbol);

        QString move(int dirX, int dirY, int currentX, int currentY, QString symbol);

    private:

        QString reconstructOutput();

        QString scene[SCENE_WIDTH][SCENE_HEIGHT];
    };


#endif // MAZEOUTPUT_H
