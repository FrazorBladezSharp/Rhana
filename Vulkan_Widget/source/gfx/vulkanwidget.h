#ifndef VULKANWIDGET_H
#define VULKANWIDGET_H

#include <QVulkanWindow>
#include <QWidget>

#include "vulkanrendering.h"


namespace Night
{
    class VulkanWidget : public QVulkanWindow
    {
        Q_OBJECT

    public:
        VulkanWidget();

        QVulkanWindowRenderer *createRenderer() override;

        QWidget* GetVulkanWidget(){
            return m_WindowContainer;
        }

    signals:
        void vulkanInfoReceived(const QString &text); // delete
        void frameQueued(int colorValue); // delete

    private:
        QWidget *m_WindowContainer;
    };
}

#endif // VULKANWIDGET_H
