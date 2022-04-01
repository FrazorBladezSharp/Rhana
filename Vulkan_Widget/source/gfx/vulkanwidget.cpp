#include "vulkanwidget.h"


namespace Night
{
    VulkanWidget::VulkanWidget(QVulkanInstance* ourInstance)
    {
        this->setVulkanInstance(ourInstance);

        qInfo()
                << "\nVulkanWidget Created\n";

        m_renderer = new VulkanRendering(this, false);

        m_windowContainer = QWidget::createWindowContainer(this);
        m_windowContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    }

    QVulkanWindowRenderer *VulkanWidget::createRenderer()
    {
        return m_renderer;
    }

}
