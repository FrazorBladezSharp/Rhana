#include "vulkanwidget.h"


namespace Night
{
    VulkanWidget::VulkanWidget()
        : m_renderer(new VulkanRendering(this))
    {

        m_windowContainer = QWidget::createWindowContainer(this);
        m_windowContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    }

    QVulkanWindowRenderer *VulkanWidget::createRenderer()
    {
        return m_renderer;
    }

}
