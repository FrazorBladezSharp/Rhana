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
        VulkanRendering *GetRenderer(){
            return m_Renderer;
        }

    private:
        QWidget *m_WindowContainer;
        VulkanRendering *m_Renderer;
    };
}

#endif // VULKANWIDGET_H
