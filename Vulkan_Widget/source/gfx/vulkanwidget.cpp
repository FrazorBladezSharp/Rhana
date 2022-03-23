#include "vulkanwidget.h"


namespace Night
{
    VulkanWidget::VulkanWidget()
    {

        m_WindowContainer = QWidget::createWindowContainer(this);
        m_WindowContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    }

    QVulkanWindowRenderer *VulkanWidget::createRenderer()
    {
        return new VulkanRendering(this);
    }

}
