
#include <QApplication>
#include <QVulkanInstance>

#include "source/rhanawindow.h"
#include "source/gfx/vulkanwidget.h"
#include "source/gfx/modelloader.h"

int main(int argc, char *argv[])
{
    bool running = true;

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

//    vulkanInstance.setLayers(
//        { "VK_LAYER_KHRONOS_validation" }
//    );

    if (!vulkanInstance.create())
        qFatal(
            "Failed to create Vulkan instance: %d",
            vulkanInstance.errorCode()
        );
    else
        qInfo(
            "\n[main]Vulkan Instance Created.\n "
        );

    Night::GameModel *model =
        new Night::GameModel();

    Night::Util::ModelLoader(
        "baseFloorTile.obj",
        *model
    );

    Night::VulkanWidget *vulkanWidget =
        new Night::VulkanWidget(
            model,
            &vulkanInstance
    );

    RhanaWindow *window =
        new RhanaWindow(
            vulkanWidget
    );

    window->go();






    if(running)
        return application.exec();

    vulkanInstance.destroy();

    return 0;
}
