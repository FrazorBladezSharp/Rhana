#ifndef RHANAWINDOW_H
#define RHANAWINDOW_H

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#include <QMainWindow>
#include <QWidget>
#include <QSizePolicy>

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

private:
    Ui::RhanaWindow *ui;
    QWidget *m_VulkanWidget;
};

#endif // RHANAWINDOW_H
