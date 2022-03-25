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

    void Go();

private slots:
    void MainGameLoop();

private:
    Ui::RhanaWindow *ui;
    Night::VulkanWidget *m_VkWidget;
    QWidget *m_VulkanWidget;
    QTimer m_Timer;
};

#endif // RHANAWINDOW_H
