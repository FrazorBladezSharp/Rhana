#include "vulkanrendering.h"


namespace Night
{

    static const int UNIFORM_DATA_SIZE = 16 * sizeof(float);

    static inline VkDeviceSize aligned(VkDeviceSize v, VkDeviceSize byteAlign)
    {
        return (v + byteAlign - 1) & ~(byteAlign - 1);
    }



    VulkanRendering::VulkanRendering(QVulkanWindow *window, bool msaa, Night::GameModel *model)
        : m_vulkanWindow(window)
        , m_deviceFunctions(nullptr)
        , m_model(model)
    {
        qDebug()
                << "\n[VulkanRendering] : Constructed";

        if (msaa) {
            const QList<int> counts = m_vulkanWindow->supportedSampleCounts();
            qDebug() << "Supported sample counts:" << counts;
            for (int s = 16; s >= 4; s /= 2) {
                if (counts.contains(s)) {
                    qDebug("Requesting sample count %d", s);
                    m_vulkanWindow->setSampleCount(s);
                    break;
                }
            }
        }

        // instead of passing the model into VulkanRendering
        // we can load the model here

        // PLEASE DELETE FOLLOWING IN PASS2 AS IT DETAILS CODE.
        // - or pass the model into our rendering from any place in our code base
        // - this requires a new function ie: setModelForRendering(Night::GameModel *model){
        // -    m_model = model
        // - {

//        if (m_model== nullptr) qInfo("\n[main] 3D Model did not load\n");
//        else
//            qInfo()
//                    << "\n[VulkanRendering] : 3D model loaded"
//                    << *m_model->vboStorage
//                    << "\n";

        m_projectionMatrix.setToIdentity();
        m_viewMatrix.setToIdentity();
        m_modelMatrix.setToIdentity();
    }

    VulkanRendering::~VulkanRendering()
    {
        qDebug() << "\n[VulkanRendering] : Destroyed";
        //VulkanRendering::releaseSwapChainResources();
        //VulkanRendering::releaseResources();
    }

    VkShaderModule VulkanRendering::createShader(const QString &name)
    {
        QFile file(name);
        if (!file.open(QIODevice::ReadOnly)) {
            qWarning("\nFailed to read shader %s\n", qPrintable(name));
            return VK_NULL_HANDLE;
        }
        QByteArray code = file.readAll();
        file.close();

        VkShaderModuleCreateInfo shaderInfo;

        //memset(&shaderInfo, 0, sizeof(shaderInfo));

        shaderInfo.sType =
            VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;

        shaderInfo.pNext =
            nullptr;

        shaderInfo.flags =
            0;

        shaderInfo.codeSize =
            code.size();

        shaderInfo.pCode =
            reinterpret_cast<const uint32_t *>(
                code.constData()
        );

        VkShaderModule shaderModule;

        VkResult err =
            m_deviceFunctions->vkCreateShaderModule(
                m_vulkanWindow->device(),
                &shaderInfo,
                nullptr,
                &shaderModule
        );

        if (err != VK_SUCCESS)
        {
            qWarning(
                "Failed to create shader module: %d",
                err
            );

            return VK_NULL_HANDLE;
        }

        return shaderModule;
    }

    void VulkanRendering::initResources()
    {
        qInfo() << "[VulkanRendering] initResources active.";

        qInfo() << "Available Physical Devices : "
                << m_vulkanWindow->availablePhysicalDevices().data();

        VkDevice gpuDevice =
            m_vulkanWindow->device();

        m_deviceFunctions =
            m_vulkanWindow->vulkanInstance()->deviceFunctions(
                gpuDevice
        );

        const int concurrentFrameCount =
            m_vulkanWindow->concurrentFrameCount();

        const VkPhysicalDeviceLimits *pdevLimits =
            &m_vulkanWindow->physicalDeviceProperties()->limits;

        const VkDeviceSize uniAlign =
            pdevLimits->minUniformBufferOffsetAlignment;

        qInfo() << "uniform buffer offset alignment is "
                << (uint)uniAlign;



        // this must equate to the data to be used for the 3D model
        VkBufferCreateInfo bufInfo;

        memset(
            &bufInfo,
            0,
            sizeof(bufInfo)
        );

        bufInfo.sType =
            VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;



        // Our internal layout is vertex(, uniform, uniform),
        // ... with each uniform buffer start offset aligned to uniAlign.
        const VkDeviceSize vertexAllocSize =
            aligned(
                static_cast<uint64_t>(
                    sizeof(float) * m_model->vboStorage->size()
                ),
            uniAlign
        );



        const VkDeviceSize uniformAllocSize =
            aligned(
                UNIFORM_DATA_SIZE,
                uniAlign
        );

        bufInfo.size =
            vertexAllocSize +
            concurrentFrameCount *
            uniformAllocSize;

        bufInfo.usage =
            VK_BUFFER_USAGE_VERTEX_BUFFER_BIT |
            VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;



        VkResult err =
            m_deviceFunctions->vkCreateBuffer(
                gpuDevice,
                &bufInfo,
                nullptr,
                &m_buf
        );

        if (err != VK_SUCCESS )
            qFatal(
                "Failed to create buffer: %d",
                err
            );



        // Allocate the memory for the vertex buffer
        VkMemoryRequirements memReq;

        m_deviceFunctions->vkGetBufferMemoryRequirements(
            gpuDevice,
            m_buf,
            &memReq
        );



        VkMemoryAllocateInfo memAllocInfo =
        {

            VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
            nullptr,
            memReq.size,
            m_vulkanWindow->hostVisibleMemoryIndex()

        };

        m_deviceFunctions->vkAllocateMemory(
            gpuDevice,
            &memAllocInfo,
            nullptr,
            &m_bufMem
        );

        m_deviceFunctions->vkBindBufferMemory(
            gpuDevice,
            m_buf,
            m_bufMem,
            0
        );



        /******************** Assign data to the gpu buffers ****************************/
        quint8 *pointerToDataOnGPU;

        m_deviceFunctions->vkMapMemory(
            gpuDevice,
            m_bufMem,
            0,
            memReq.size,
            0,
            reinterpret_cast<void **>(
                &pointerToDataOnGPU
            )
        );

        // data for the 3D Model
        // this should be replaced by a non std lib function
        memcpy(
            pointerToDataOnGPU,
            &m_model->vboStorage[0][0],
            static_cast<uint64_t>(
                sizeof(float) *
                m_model->vboStorage->size()
            )
        );

        // data for the shader Uniform variables
        QMatrix4x4 ident;

        memset(m_uniformBufInfo, 0, sizeof(m_uniformBufInfo));

        for (int i = 0; i < concurrentFrameCount; ++i) {
            const VkDeviceSize offset = vertexAllocSize + i * uniformAllocSize;
            memcpy(pointerToDataOnGPU + offset, ident.constData(), 16 * sizeof(float));
            m_uniformBufInfo[i].buffer = m_buf;
            m_uniformBufInfo[i].offset = offset;
            m_uniformBufInfo[i].range = uniformAllocSize;
        }

        // Unbinds the memory to avoid accidental access
        m_deviceFunctions->vkUnmapMemory(gpuDevice, m_bufMem);

        /********************************************************************************/



        // The following describes to the gpu - how we have arranged our data for usage
        // in the shader programs
        VkVertexInputBindingDescription vertexBindingDesc = {
            0, // binding
            8 * sizeof(float),
            VK_VERTEX_INPUT_RATE_VERTEX
        };



        VkVertexInputAttributeDescription vertexAttrDesc[] = {
            { // position
                0, // location in shader
                0, // binding
                VK_FORMAT_R32G32B32A32_SFLOAT,
                0
            },
            { // color
                1,
                0,
                VK_FORMAT_R32G32B32A32_SFLOAT,
                4 * sizeof(float)
            }
        };



        VkPipelineVertexInputStateCreateInfo vertexInputInfo;
            vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
            vertexInputInfo.pNext = nullptr;
            vertexInputInfo.flags = 0;
            vertexInputInfo.vertexBindingDescriptionCount = 1;
            vertexInputInfo.pVertexBindingDescriptions = &vertexBindingDesc;
            vertexInputInfo.vertexAttributeDescriptionCount = 2;
            vertexInputInfo.pVertexAttributeDescriptions = vertexAttrDesc;



            // Set up descriptor set and its layout.
            VkDescriptorPoolSize descPoolSizes =
            {
                VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                uint32_t(concurrentFrameCount)
            };



            VkDescriptorPoolCreateInfo descPoolInfo = {};

            //memset(&descPoolInfo, 0, sizeof(descPoolInfo));

            descPoolInfo.sType =
                VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;

            descPoolInfo.pNext =
                nullptr;

            descPoolInfo.maxSets =
                concurrentFrameCount;

            descPoolInfo.poolSizeCount =
                1;

            descPoolInfo.pPoolSizes =
                &descPoolSizes;

            err =
                m_deviceFunctions->vkCreateDescriptorPool(
                    gpuDevice,
                    &descPoolInfo,
                    nullptr,
                    &m_descPool
            );

            if (err != VK_SUCCESS)
                qFatal(
                    "Failed to create descriptor pool: %d",
                    err
                );



            VkDescriptorSetLayoutBinding layoutBinding =
            {
                0, // binding
                VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                1,
                VK_SHADER_STAGE_VERTEX_BIT,
                nullptr
            };



            VkDescriptorSetLayoutCreateInfo descLayoutInfo =
            {
                VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
                nullptr,
                0,
                1,
                &layoutBinding
            };

            err =
                m_deviceFunctions->vkCreateDescriptorSetLayout(
                    gpuDevice,
                    &descLayoutInfo,
                    nullptr,
                    &m_descSetLayout
            );

            if (err != VK_SUCCESS)
                qFatal(
                    "Failed to create descriptor set layout: %d",
                    err
                );



            for (int i = 0; i < concurrentFrameCount; ++i)
            {
                VkDescriptorSetAllocateInfo descSetAllocInfo =
                {
                    VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
                    nullptr,
                    m_descPool,
                    1,
                    &m_descSetLayout
                };

                err =
                    m_deviceFunctions->vkAllocateDescriptorSets(
                        gpuDevice,
                        &descSetAllocInfo,
                        &m_descSet[i]
                );

                if (err != VK_SUCCESS)
                    qFatal(
                        "Failed to allocate descriptor set: %d",
                        err
                    );



                VkWriteDescriptorSet descWrite = {};

                //memset(&descWrite, 0, sizeof(descWrite));

                descWrite.sType =
                    VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;

                descWrite.pNext =
                    nullptr;

                descWrite.dstSet =
                    m_descSet[i];

                descWrite.descriptorCount =
                    1;

                descWrite.descriptorType =
                    VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;

                descWrite.pBufferInfo =
                    &m_uniformBufInfo[i];

                descWrite.dstArrayElement =
                    0;

                descWrite.dstBinding =
                    0;

                m_deviceFunctions->vkUpdateDescriptorSets(
                    gpuDevice,
                    1,
                    &descWrite,
                    0,
                    nullptr
                );
            }



            // Pipeline cache
            VkPipelineCacheCreateInfo pipelineCacheInfo;
            memset(&pipelineCacheInfo, 0, sizeof(pipelineCacheInfo));
            pipelineCacheInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
            err = m_deviceFunctions->vkCreatePipelineCache(gpuDevice, &pipelineCacheInfo, nullptr, &m_pipelineCache);
            if (err != VK_SUCCESS)
                qFatal("Failed to create pipeline cache: %d", err);



            // Pipeline layout
            VkPipelineLayoutCreateInfo pipelineLayoutInfo;

            memset(&pipelineLayoutInfo, 0, sizeof(pipelineLayoutInfo));

            pipelineLayoutInfo.sType =
                VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

            pipelineLayoutInfo.pNext =
                nullptr;

            pipelineLayoutInfo.pushConstantRangeCount =
                0;

            pipelineLayoutInfo.pPushConstantRanges =
                nullptr;

            pipelineLayoutInfo.setLayoutCount =
                1;

            pipelineLayoutInfo.pSetLayouts =
                &m_descSetLayout;

            err =
                m_deviceFunctions->vkCreatePipelineLayout(
                    gpuDevice,
                    &pipelineLayoutInfo,
                    nullptr,
                    &m_pipelineLayout
            );

            if (err != VK_SUCCESS)
                qFatal(
                    "Failed to create pipeline layout: %d",
                    err
                );




            // Shaders
            VkShaderModule vertShaderModule =
                createShader(
                    QStringLiteral(
                        "../convertBlenderToMidnight/source/resource/shaders/color_vert.spv"
                    )
            );

            VkShaderModule fragShaderModule =
                createShader(
                    QStringLiteral(
                        "../convertBlenderToMidnight/source/resource/shaders/color_frag.spv"
                    )
            );



            // Graphics pipeline
            VkGraphicsPipelineCreateInfo pipelineInfo;

            memset(&pipelineInfo, 0, sizeof(pipelineInfo));

            pipelineInfo.sType =
                VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;



            VkPipelineShaderStageCreateInfo shaderStages[2] =
            {
                {
                    VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
                    nullptr,
                    0,
                    VK_SHADER_STAGE_VERTEX_BIT,
                    vertShaderModule,
                    "main",
                    nullptr
                },

                {
                    VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
                    nullptr,
                    0,
                    VK_SHADER_STAGE_FRAGMENT_BIT,
                    fragShaderModule,
                    "main",
                    nullptr
                }
            };

            pipelineInfo.stageCount =
                2;

            pipelineInfo.pStages =
                shaderStages;

            pipelineInfo.pVertexInputState = &vertexInputInfo;



            VkPipelineInputAssemblyStateCreateInfo ia = {};

            //memset(&ia, 0, sizeof(ia));

            ia.sType =
                VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;

            ia.pNext =
                nullptr;

            ia.flags =
                0;

            ia.primitiveRestartEnable =
                VK_FALSE;

            ia.topology =
                VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

            pipelineInfo.pInputAssemblyState = &ia;



            // The viewport and scissor will be set dynamically via vkCmdSetViewport/Scissor.
            // This way the pipeline does not need to be touched when resizing the window.
            VkPipelineViewportStateCreateInfo vp = {};

            //memset(&vp, 0, sizeof(vp));

            vp.sType =
                VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;

            vp.pNext =
                nullptr;

            vp.flags =
                0;

            vp.viewportCount =
                1;

            vp.scissorCount =
                1;

            vp.pScissors =
                nullptr;

            vp.pViewports =
                nullptr;

            pipelineInfo.pViewportState = &vp;



            VkPipelineRasterizationStateCreateInfo rs = {};

            //memset(&rs, 0, sizeof(rs));

            rs.sType =
                VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;

            rs.pNext =
                nullptr;

            rs.flags =
                0;

            rs.polygonMode =
                VK_POLYGON_MODE_FILL;

            rs.cullMode =
                VK_CULL_MODE_NONE; // we want the back face as well

            rs.frontFace =
                VK_FRONT_FACE_COUNTER_CLOCKWISE;

            rs.depthClampEnable =
                VK_TRUE;

            rs.rasterizerDiscardEnable =
                VK_FALSE;

            rs.depthBiasEnable =
                VK_FALSE;

            rs.depthBiasConstantFactor =
                0;

            rs.depthBiasClamp =
                0;

            rs.depthBiasSlopeFactor =
                0;

            rs.lineWidth =
                1.0f;

            pipelineInfo.pRasterizationState = &rs;



            VkPipelineMultisampleStateCreateInfo ms;

            //memset(&ms, 0, sizeof(ms));

            ms.sType =
                VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;

            ms.pNext =
                nullptr;

            ms.flags =
                0;

            ms.pSampleMask =
                nullptr;

            ms.rasterizationSamples =
                m_vulkanWindow->sampleCountFlagBits();

            ms.sampleShadingEnable =
                VK_FALSE;

            ms.alphaToCoverageEnable =
                VK_FALSE;

            ms.alphaToOneEnable =
                VK_FALSE;

            ms.minSampleShading =
                0.0f;

            pipelineInfo.pMultisampleState = &ms;



            VkPipelineDepthStencilStateCreateInfo ds;

            //memset(&ds, 0, sizeof(ds));

            ds.sType =
                VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;

            ds.pNext =
                nullptr;

            ds.flags =
                0;

            ds.depthTestEnable =
                VK_TRUE;

            ds.depthWriteEnable =
                VK_TRUE;

            ds.depthCompareOp =
                VK_COMPARE_OP_LESS_OR_EQUAL;

            ds.depthBoundsTestEnable =
                VK_FALSE;

            ds.minDepthBounds =
                0;

            ds.maxDepthBounds =
                0;

            ds.stencilTestEnable =
                VK_FALSE;

            ds.back.failOp =
                VK_STENCIL_OP_KEEP;

            ds.back.passOp =
                VK_STENCIL_OP_KEEP;

            ds.back.compareOp =
                VK_COMPARE_OP_ALWAYS;

            ds.back.compareMask =
                0;

            ds.back.reference =
                0;

            ds.back.depthFailOp =
                VK_STENCIL_OP_KEEP;

            ds.back.writeMask =
                0;

            ds.front =
                ds.back;

            pipelineInfo.pDepthStencilState = &ds;



            VkPipelineColorBlendStateCreateInfo cb = {};

            //memset(&cb, 0, sizeof(cb));

            cb.sType =
                VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;

            cb.pNext =
                nullptr;

            cb.flags =
                0;

            VkPipelineColorBlendAttachmentState att[1];

            //memset(&att, 0, sizeof(att));

            att[0].colorWriteMask =
                0xf;

            att[0].blendEnable =
                VK_FALSE;

            att[0].alphaBlendOp =
                VK_BLEND_OP_ADD;

            att[0].colorBlendOp =
                VK_BLEND_OP_ADD;

            att[0].srcColorBlendFactor =
                VK_BLEND_FACTOR_ZERO;

            att[0].dstColorBlendFactor =
                VK_BLEND_FACTOR_ZERO;

            att[0].srcAlphaBlendFactor =
                VK_BLEND_FACTOR_ZERO;

            att[0].dstAlphaBlendFactor =
                VK_BLEND_FACTOR_ZERO;

            cb.attachmentCount =
                1;

            cb.pAttachments =
                att;

            cb.logicOpEnable =
                VK_FALSE;

            cb.logicOp =
                VK_LOGIC_OP_NO_OP;

            cb.blendConstants[0] =
                1.0f;

            cb.blendConstants[1] =
                1.0f;

            cb.blendConstants[2] =
                1.0f;

            cb.blendConstants[3] =
                1.0f;

            pipelineInfo.pColorBlendState = &cb;



            VkDynamicState dynEnable[] =
            {
                VK_DYNAMIC_STATE_VIEWPORT,
                VK_DYNAMIC_STATE_SCISSOR
            };



            VkPipelineDynamicStateCreateInfo dyn;
            memset(&dyn, 0, sizeof(dyn));

            dyn.sType =
                VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;

            dyn.pNext =
                nullptr;

            dyn.dynamicStateCount =
                sizeof(dynEnable) /
                sizeof(VkDynamicState);

            dyn.pDynamicStates =
                dynEnable;



            pipelineInfo.pDynamicState =
                &dyn;

            pipelineInfo.layout =
                m_pipelineLayout;

            pipelineInfo.renderPass =
                m_vulkanWindow->defaultRenderPass();

            err =
                m_deviceFunctions->vkCreateGraphicsPipelines(
                gpuDevice,
                m_pipelineCache,
                1,
                &pipelineInfo,
                nullptr,
                &m_pipeline
            );

            if (err != VK_SUCCESS)
                qFatal(
                    "Failed to create graphics pipeline: %d",
                    err
                );



            if (vertShaderModule)
                m_deviceFunctions->vkDestroyShaderModule(
                    gpuDevice,
                    vertShaderModule,
                    nullptr
                );

            if (fragShaderModule)
                m_deviceFunctions->vkDestroyShaderModule(
                    gpuDevice,
                    fragShaderModule,
                    nullptr
                );
    }



    void VulkanRendering::initSwapChainResources()
    {
        qInfo() << "[VulkanRendering] initSwapChainResources active.";

        QVector3D cameraLocation = {2.0f, 2.0f, 2.0f};
        QVector3D cameraLookAt = {0.0f, 0.0f, 0.0f};
        QVector3D cameraUpDirection = {0.0f, 1.0f, 0.0f};

        const QSize sz =
            m_vulkanWindow->swapChainImageSize();

        // Projection matrix
        m_projectionMatrix.perspective(
            45.0f,
            sz.width() / (float) sz.height(),
            0.01f,
            100.0f
        );

        // View Matrix
        m_viewMatrix.lookAt(
            cameraLocation,
            cameraLookAt,
            cameraUpDirection
        );

        // model Matrix
        m_modelMatrix.setToIdentity();
    }

    void VulkanRendering::releaseSwapChainResources()
    {
        qInfo()
                << "\n[VulkanRendering] releaseSwapChainResources active.";
    }

    void VulkanRendering::releaseResources()
    {
        qInfo()
                << "[VulkanRendering] releaseResources active.";

        VkDevice dev =
            m_vulkanWindow->device();

            if (m_pipeline) {
                m_deviceFunctions->vkDestroyPipeline(dev, m_pipeline, nullptr);
                m_pipeline = VK_NULL_HANDLE;
            }

            if (m_pipelineLayout) {
                m_deviceFunctions->vkDestroyPipelineLayout(dev, m_pipelineLayout, nullptr);
                m_pipelineLayout = VK_NULL_HANDLE;
            }

            if (m_pipelineCache) {
                m_deviceFunctions->vkDestroyPipelineCache(dev, m_pipelineCache, nullptr);
                m_pipelineCache = VK_NULL_HANDLE;
            }

            if (m_descSetLayout) {
                m_deviceFunctions->vkDestroyDescriptorSetLayout(dev, m_descSetLayout, nullptr);
                m_descSetLayout = VK_NULL_HANDLE;
            }

            if (m_descPool) {
                m_deviceFunctions->vkDestroyDescriptorPool(dev, m_descPool, nullptr);
                m_descPool = VK_NULL_HANDLE;
            }

        if (m_buf)
        {

            m_deviceFunctions->vkDestroyBuffer(
                dev,
                m_buf,
                nullptr
            );

            m_buf =
                VK_NULL_HANDLE;

        }

        if (m_bufMem)
        {

            m_deviceFunctions->vkFreeMemory(
                dev,
                m_bufMem,
                nullptr
            );

            m_bufMem =
                VK_NULL_HANDLE;

        }
    }

    void VulkanRendering::startNextFrame()
    {
        const QSize sz = m_vulkanWindow->swapChainImageSize();
        VkDevice dev = m_vulkanWindow->device();
        VkCommandBuffer cmdBuf = m_vulkanWindow->currentCommandBuffer();

        m_fpsCounter++;
        if (m_curretTimer.remainingTime() <= 1)
            fpsUpdate();



        VkClearColorValue clearColor = {{ 0.0f, 0.0f, 0.05f, 1.0f }};
        VkClearDepthStencilValue clearDS = { 1.0f, 0 };
        VkClearValue clearValues[3];
        memset(clearValues, 0, sizeof(clearValues));
        clearValues[0].color = clearColor;
        clearValues[1].depthStencil = clearDS;


        VkRenderPassBeginInfo rpBeginInfo;

        //memset(&rpBeginInfo, 0, sizeof(rpBeginInfo));

        rpBeginInfo.sType =
            VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;

        rpBeginInfo.pNext =
            nullptr;

        rpBeginInfo.renderPass =
            m_vulkanWindow->defaultRenderPass();

        rpBeginInfo.framebuffer =
            m_vulkanWindow->currentFramebuffer();

        rpBeginInfo.renderArea.offset.x =
            0.0f;

        rpBeginInfo.renderArea.offset.y =
            0.0f;

        rpBeginInfo.renderArea.extent.width =
            sz.width();

        rpBeginInfo.renderArea.extent.height =
            sz.height();

        rpBeginInfo.clearValueCount =
            m_vulkanWindow->sampleCountFlagBits() >
                VK_SAMPLE_COUNT_1_BIT ? 3 : 2;

        rpBeginInfo.pClearValues =
            clearValues;


        // Render Begin
        m_deviceFunctions->vkCmdBeginRenderPass(
            cmdBuf,
            &rpBeginInfo,
            VK_SUBPASS_CONTENTS_INLINE
        );

//        /****** Main rendering ***************/

        // p is a pointer to the uniform mvp matrix
        // which we map to the gpu memory
        quint8 *p_gpuUniformLocation;

        VkResult err =
            m_deviceFunctions->vkMapMemory(
                dev,
                m_bufMem,
                m_uniformBufInfo[m_vulkanWindow->currentFrame()].offset,
                UNIFORM_DATA_SIZE,
                0,
                reinterpret_cast<void **>(
                    &p_gpuUniformLocation
                )
        );

        if (err != VK_SUCCESS)
            qFatal(
                "Failed to map memory: %d",
                err
            );

        m_modelMatrix.rotate(m_rotation, 0, 1, 0);

        QMatrix4x4 mvp =
            m_vulkanWindow->clipCorrectionMatrix() *
            m_projectionMatrix *
            m_viewMatrix *
            m_modelMatrix;

//        //m.rotate();


        memcpy(
            p_gpuUniformLocation,
            mvp.constData(),
            16 * sizeof(float)
        );

        m_deviceFunctions->vkUnmapMemory(
            dev, m_bufMem
        );

//        // Not exactly a real animation system, just advance on every frame for now.
        m_rotation += 0.01f;
        if(m_rotation > 2.0f) m_rotation -= 2.0f;


        m_deviceFunctions->vkCmdBindPipeline(
            cmdBuf,
            VK_PIPELINE_BIND_POINT_GRAPHICS,
            m_pipeline
        );

        m_deviceFunctions->vkCmdBindDescriptorSets(
            cmdBuf,
            VK_PIPELINE_BIND_POINT_GRAPHICS,
            m_pipelineLayout,
            0,
            1,
            &m_descSet[m_vulkanWindow->currentFrame()],
            0,
            nullptr
        );

        VkDeviceSize vbOffset = 0;

        m_deviceFunctions->vkCmdBindVertexBuffers(
            cmdBuf,
            0,
            1,
            &m_buf,
            &vbOffset);

        VkViewport viewport;
        viewport.x = viewport.y = 0;
        viewport.width = sz.width();
        viewport.height = sz.height();
        viewport.minDepth = 0;
        viewport.maxDepth = 1;
        m_deviceFunctions->vkCmdSetViewport(cmdBuf, 0, 1, &viewport);

        VkRect2D scissor;
        scissor.offset.x = scissor.offset.y = 0;
        scissor.extent.width = viewport.width;
        scissor.extent.height = viewport.height;
        m_deviceFunctions->vkCmdSetScissor(cmdBuf, 0, 1, &scissor);

        /*************************************/

        // Main Render command
        m_deviceFunctions->vkCmdDraw(cmdBuf, m_model->numIndices, 1, 0, 0);

        // Render end
        m_deviceFunctions->vkCmdEndRenderPass(
            cmdBuf
        );

        // swap buffers
        m_vulkanWindow->frameReady();

    }

    void VulkanRendering::fpsUpdate()
    {
        m_curretTimer.stop();

        m_fps = m_fpsCounter;
        m_fpsCounter = 0;

        m_curretTimer.start(1000);
    }

}
