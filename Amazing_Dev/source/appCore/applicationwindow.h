#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include <source/night_common.h>
#include <source/core/midnight.h>

#include "source/appImplementation/appOutput/mazeoutput.h"


QT_BEGIN_NAMESPACE
namespace Ui { class ApplicationWindow; }
QT_END_NAMESPACE


class ApplicationWindow : public QMainWindow
{
    Q_OBJECT

public:
    ApplicationWindow(QWidget *parent = nullptr);
    ~ApplicationWindow();

    void Run();
    void OnUpdate();

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;

private slots:


private:
    void InitializeEngine();

    Ui::ApplicationWindow *ui;
    QTimer *m_Timer;

    Night::Midnight *m_Midnight;


    Night::Ref<MazeOutput> m_mazeOutput;
};
#endif // APPLICATIONWINDOW_H
