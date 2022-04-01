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
        VulkanWidget(QVulkanInstance *ourInstance = nullptr);

        QVulkanWindowRenderer *createRenderer() override;

        QWidget* getVulkanWidget(){
            return m_windowContainer;
        }
        VulkanRendering *getRenderer(){
            return m_renderer;
        }

    private:
        QWidget *m_windowContainer;
        VulkanRendering *m_renderer;
    };
}

#endif // VULKANWIDGET_H
