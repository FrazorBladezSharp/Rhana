#include "vulkanrendering.h"


namespace Night
{
    static float vertexData[] = { // Y up, front = CCW
         0.0f,   0.5f,   1.0f, 0.0f, 0.0f,
        -0.5f,  -0.5f,   0.0f, 1.0f, 0.0f,
         0.5f,  -0.5f,   0.0f, 0.0f, 1.0f
    };

    //static const int UNIFORM_DATA_SIZE = 16 * sizeof(float);

    static inline VkDeviceSize aligned(VkDeviceSize v, VkDeviceSize byteAlign)
    {
        return (v + byteAlign - 1) & ~(byteAlign - 1);
    }



    VulkanRendering::VulkanRendering(QVulkanWindow *window)
        : m_vulkanWindow(window)
        , m_deviceFunctions(nullptr)
    {
        m_curretTimer.start(1000);

    }



    void VulkanRendering::initResources()
    {
        qInfo()
                << "[VulkanRendering] initResources active.";

        VkDevice gpuDevice = m_vulkanWindow->device();
        m_deviceFunctions = m_vulkanWindow->vulkanInstance()->deviceFunctions(gpuDevice);

        const int concurrentFrameCount = m_vulkanWindow->concurrentFrameCount();
        const VkPhysicalDeviceLimits *pdevLimits = &m_vulkanWindow->physicalDeviceProperties()->limits;
        const VkDeviceSize uniAlign = pdevLimits->minUniformBufferOffsetAlignment;

        qInfo()
                << "uniform buffer offset alignment is %u"
                << (uint)uniAlign;



        VkBufferCreateInfo bufInfo;
        memset(&bufInfo, 0, sizeof(bufInfo));
        bufInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;

        // Our internal layout is vertex(, uniform, uniform), ... with each uniform buffer start offset aligned to uniAlign.
        const VkDeviceSize vertexAllocSize = aligned(sizeof(vertexData), uniAlign);
        //const VkDeviceSize uniformAllocSize = aligned(UNIFORM_DATA_SIZE, uniAlign);

        bufInfo.size = vertexAllocSize + concurrentFrameCount * 1; //uniformAllocSize;
        bufInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;// | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;



        VkResult err = m_deviceFunctions->vkCreateBuffer(gpuDevice, &bufInfo, nullptr, &m_buf);
        if (err != VK_SUCCESS )
            qFatal("Failed to create buffer: %d", err);

        VkMemoryRequirements memReq;
        m_deviceFunctions->vkGetBufferMemoryRequirements(gpuDevice, m_buf, &memReq);

        /*
        VkMemoryAllocateInfo memAllocInfo = {
            VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
            nullptr,
            memReq.size,
            m_vulkanWindow->hostVisibleMemoryIndex()
        };*/
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
        m_fpsCounter++;
        if (m_curretTimer.remainingTime() <= 1)
            fpsUpdate();

        VkClearColorValue clearColor = {{ 0.0f, 0.0f, 0.05f, 1.0f }};
        VkClearDepthStencilValue clearDS = { 1.0f, 0 };
        VkClearValue clearValues[2];
        memset(clearValues, 0, sizeof(clearValues));
        clearValues[0].color = clearColor;
        clearValues[1].depthStencil = clearDS;

        VkRenderPassBeginInfo rpBeginInfo;
        memset(&rpBeginInfo, 0, sizeof(rpBeginInfo));
        rpBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        rpBeginInfo.renderPass = m_vulkanWindow->defaultRenderPass();
        rpBeginInfo.framebuffer = m_vulkanWindow->currentFramebuffer();
        const QSize sz = m_vulkanWindow->swapChainImageSize();
        rpBeginInfo.renderArea.extent.width = sz.width();
        rpBeginInfo.renderArea.extent.height = sz.height();
        rpBeginInfo.clearValueCount = 2;
        rpBeginInfo.pClearValues = clearValues;
        VkCommandBuffer cmdBuf = m_vulkanWindow->currentCommandBuffer();
        m_deviceFunctions->vkCmdBeginRenderPass(cmdBuf, &rpBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

        // Do nothing else. We will just clear screen, changing the component on
        // every invocation. This also helps verifying the rate to which the thread
        // is throttled to. (The elapsed time between startNextFrame calls should
        // typically be around 16 ms. Note that rendering is 2 frames ahead of what
        // is displayed.)

        m_deviceFunctions->vkCmdEndRenderPass(cmdBuf);

        m_vulkanWindow->frameReady();

    }

    void VulkanRendering::fpsUpdate()
    {
        m_curretTimer.stop();

        m_fps = m_fpsCounter;
        m_fpsCounter = 0;

        qDebug()
                << "Is this a security breach allowing access via the gpu"
                << (VK_FALSE == VK_SUCCESS);

        m_curretTimer.start(1000);
    }

}
