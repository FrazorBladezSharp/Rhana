#ifndef RHANAWINDOW_H
#define RHANAWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QTimer>

#include "source/gfx/vulkanwidget.h"


QT_BEGIN_NAMESPACE
    namespace Ui { class RhanaWindow; }
QT_END_NAMESPACE


class RhanaWindow : public QMainWindow
{
    Q_OBJECT

public:
    RhanaWindow(Night::VulkanWidget *vkWidget = nullptr);
    ~RhanaWindow();

    void go();

private slots:
    void mainGameLoop();

private:
    Ui::RhanaWindow *m_ui;
    Night::VulkanWidget *m_vkWidget;
    QWidget *m_vulkanWidget;
    QTimer m_timer;
};

#endif // RHANAWINDOW_H
