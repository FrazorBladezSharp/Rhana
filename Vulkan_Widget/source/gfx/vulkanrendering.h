#ifndef VULKANRENDERING_H
#define VULKANRENDERING_H

#include <QVulkanWindowRenderer>
#include <QVulkanWindow>
#include <QVulkanDeviceFunctions>


namespace Night
{
    class VulkanRendering : public QVulkanWindowRenderer
    {
    public:
        VulkanRendering(QVulkanWindow *window = nullptr);

        void initResources() override;
        void initSwapChainResources() override;
        void releaseSwapChainResources() override;
        void releaseResources() override;

        void startNextFrame() override;


    private:
        QVulkanWindow *m_VulkanWindow;
        QVulkanDeviceFunctions *m_DeviceFunctions;
    };
}

#endif // VULKANRENDERING_H
