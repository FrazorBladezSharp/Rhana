#include "vulkanwidget.h"


namespace Night
{
    VulkanWidget::VulkanWidget()
        : m_Renderer(new VulkanRendering(this))
    {

        m_WindowContainer = QWidget::createWindowContainer(this);
        m_WindowContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    }

    QVulkanWindowRenderer *VulkanWidget::createRenderer()
    {
        return m_Renderer;
    }

}
