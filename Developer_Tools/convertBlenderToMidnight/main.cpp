#include "source/rhanawindow.h"

#include <QApplication>
#include <QLoggingCategory>
#include <QVulkanInstance>

#include "source/gfx/vulkanwidget.h"
#include "source/gfx/modelloader.h"


int main(int argc, char *argv[])
{
    QApplication application(argc, argv);


    QLoggingCategory::setFilterRules(QStringLiteral("qt.vulkan=true"));

    QVulkanInstance ourInstance;
    ourInstance.setLayers({ "VK_LAYER_KHRONOS_validation" });

    if (!ourInstance.create())
        qFatal("Failed to create Vulkan instance: %d", ourInstance.errorCode());
    else
        qInfo("\n[main]Vulkan Instance Created.\n ");

    Night::GameModel *model = Night::Util::ModelLoader("baseFloorTile.obj");
    Night::VulkanWidget *vulkanWidget = new Night::VulkanWidget(model, &ourInstance);



    RhanaWindow *window = new RhanaWindow(vulkanWidget);
    window->go();




    if (model== nullptr) qInfo("\n[main] 3D Model did not load\n");
    else
        qInfo()
                << "\n[main] : 3D model loaded"
                << *model->vboStorage
                << "\n";




    int errorValue = application.exec();

    return errorValue;
}
