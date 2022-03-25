#ifndef VULKANRENDERING_H
#define VULKANRENDERING_H

#include <QVulkanWindowRenderer>
#include <QVulkanWindow>
#include <QVulkanDeviceFunctions>

#include <QTimer>

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

        int getFPS(){
            return m_FPS;
        }


        void FPSUpdate();

    private:
        QVulkanWindow *m_VulkanWindow;
        QVulkanDeviceFunctions *m_DeviceFunctions;

        QTimer m_CurretTimer;
        int m_FPS = 0;
        int m_FPScounter = 0;
    };
}

#endif // VULKANRENDERING_H
