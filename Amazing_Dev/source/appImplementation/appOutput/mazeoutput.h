#ifndef MAZEOUTPUT_H
#define MAZEOUTPUT_H

#include <QPlainTextEdit>



    class MazeOutput : public QPlainTextEdit
    {
        Q_OBJECT
    public:
        MazeOutput(QWidget *parent = nullptr);

        QString initialize(int sceneWidth, int sceneHeight);

        QString setPosition(int x, int y, QString symbol);

        QString move(int dirX, int dirY, int currentX, int currentY, QString symbol);

    private:

        QString reconstructOutput();

        QString m_scene;

        int m_sceneWidth;

        int m_sceneHeight;
    };


#endif // MAZEOUTPUT_H
