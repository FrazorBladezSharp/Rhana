#include "vulkanrendering.h"


namespace Night
{
    VulkanRendering::VulkanRendering(QVulkanWindow *window)
        : m_VulkanWindow(window)
        , m_DeviceFunctions(nullptr)
    {
        m_CurretTimer.start(1000);

    }

    void VulkanRendering::initResources()
    {
        qInfo()
                << "[VulkanRendering] initResources active.";

        m_DeviceFunctions = m_VulkanWindow->vulkanInstance()->deviceFunctions(m_VulkanWindow->device());
    }

    void VulkanRendering::initSwapChainResources()
    {
        qInfo()
                << "[VulkanRendering] initSwapChainResources active.";
    }

    void VulkanRendering::releaseSwapChainResources()
    {
        qInfo()
                << "[VulkanRendering] releaseSwapChainResources active.";
    }

    void VulkanRendering::releaseResources()
    {
        qInfo()
                << "[VulkanRendering] releaseResources active.";
    }

    void VulkanRendering::startNextFrame()
    {
        m_FPScounter++;
        if (m_CurretTimer.remainingTime() <= 1)
            FPSUpdate();

        VkClearColorValue clearColor = {{ 0.0f, 0.0f, 0.05f, 1.0f }};
        VkClearDepthStencilValue clearDS = { 1.0f, 0 };
        VkClearValue clearValues[2];
        memset(clearValues, 0, sizeof(clearValues));
        clearValues[0].color = clearColor;
        clearValues[1].depthStencil = clearDS;

        VkRenderPassBeginInfo rpBeginInfo;
        memset(&rpBeginInfo, 0, sizeof(rpBeginInfo));
        rpBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        rpBeginInfo.renderPass = m_VulkanWindow->defaultRenderPass();
        rpBeginInfo.framebuffer = m_VulkanWindow->currentFramebuffer();
        const QSize sz = m_VulkanWindow->swapChainImageSize();
        rpBeginInfo.renderArea.extent.width = sz.width();
        rpBeginInfo.renderArea.extent.height = sz.height();
        rpBeginInfo.clearValueCount = 2;
        rpBeginInfo.pClearValues = clearValues;
        VkCommandBuffer cmdBuf = m_VulkanWindow->currentCommandBuffer();
        m_DeviceFunctions->vkCmdBeginRenderPass(cmdBuf, &rpBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

        // Do nothing else. We will just clear screen, changing the component on
        // every invocation. This also helps verifying the rate to which the thread
        // is throttled to. (The elapsed time between startNextFrame calls should
        // typically be around 16 ms. Note that rendering is 2 frames ahead of what
        // is displayed.)

        m_DeviceFunctions->vkCmdEndRenderPass(cmdBuf);

        m_VulkanWindow->frameReady();

    }

    void VulkanRendering::FPSUpdate()
    {
        m_CurretTimer.stop();

        m_FPS = m_FPScounter;
        m_FPScounter = 0;

        m_CurretTimer.start(1000);
    }

}
