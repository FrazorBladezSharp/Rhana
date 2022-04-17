
#include <QApplication>
#include <QVulkanInstance>

int main(int argc, char *argv[])
{
    bool running = false;

    QApplication application(
        argc,
        argv
    );



    QVulkanInstance vulkanInstance;

    qInfo() << "\nSupported Vulkan API: "
            << vulkanInstance.supportedApiVersion();

    vulkanInstance.setApiVersion(
        vulkanInstance.supportedApiVersion()
    );

    vulkanInstance.setLayers(
        { "VK_LAYER_KHRONOS_validation" }
    );

    if (!vulkanInstance.create())
        qFatal(
            "Failed to create Vulkan instance: %d",
            vulkanInstance.errorCode()
        );
    else
        qInfo(
            "\n[main]Vulkan Instance Created.\n "
        );




    vulkanInstance.destroy();

    if(running)
        return application.exec();

    return 0;
}
