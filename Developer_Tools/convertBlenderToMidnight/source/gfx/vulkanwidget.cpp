#include "vulkanwidget.h"


namespace Night
{
    VulkanWidget::VulkanWidget(Night::GameModel *model, QVulkanInstance *ourInstance)

    {
        this->setVulkanInstance(ourInstance);

        qDebug()
                << "\n[VulkanWidget] : Constructed";

        m_renderer= new VulkanRendering(this, false, model);
        m_windowContainer = QWidget::createWindowContainer(this);
        m_windowContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    }

    QVulkanWindowRenderer *VulkanWidget::createRenderer()
    {
        return m_renderer;
    }

}
