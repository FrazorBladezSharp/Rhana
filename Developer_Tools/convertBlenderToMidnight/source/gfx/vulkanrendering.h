#ifndef VULKANRENDERING_H
#define VULKANRENDERING_H

#include <QVulkanWindowRenderer>
#include <QVulkanWindow>
#include <QVulkanFunctions>
#include <QVulkanDeviceFunctions>

#include <QTimer>
#include <QFile>

namespace Night
{
    class VulkanRendering : public QVulkanWindowRenderer
    {


    public:
        VulkanRendering(QVulkanWindow *window = nullptr, bool msaa = false);

        VkShaderModule createShader(const QString &name);

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

        VkDeviceMemory m_bufMem = VK_NULL_HANDLE;
        VkBuffer m_buf = VK_NULL_HANDLE;
        VkDescriptorBufferInfo m_uniformBufInfo[QVulkanWindow::MAX_CONCURRENT_FRAME_COUNT];

        VkDescriptorPool m_descPool = VK_NULL_HANDLE;
        VkDescriptorSetLayout m_descSetLayout = VK_NULL_HANDLE;
        VkDescriptorSet m_descSet[QVulkanWindow::MAX_CONCURRENT_FRAME_COUNT];

        VkPipelineCache m_pipelineCache = VK_NULL_HANDLE;
        VkPipelineLayout m_pipelineLayout = VK_NULL_HANDLE;
        VkPipeline m_pipeline = VK_NULL_HANDLE;

        QMatrix4x4 m_proj;
        float m_rotation = 0.0f;
    };
}

#endif // VULKANRENDERING_H