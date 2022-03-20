#include "vulkanwidget.h"


namespace Night
{
    VulkanWidget::VulkanWidget()
    {

        m_WindowContainer = QWidget::createWindowContainer(this);

    }

    QVulkanWindowRenderer *VulkanWidget::createRenderer()
    {
        return new VulkanRendering(this);
    }

}
