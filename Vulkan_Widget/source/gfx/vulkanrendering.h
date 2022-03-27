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
            return m_fps;
        }


        void fpsUpdate();

    private:
        QVulkanWindow *m_vulkanWindow;
        QVulkanDeviceFunctions *m_deviceFunctions;

        QTimer m_curretTimer;
        int m_fps = 0;
        int m_fpsCounter = 0;
    };
}

#endif // VULKANRENDERING_H
