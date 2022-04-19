#include "source/rhanawindow.h"

#include <QApplication>
#include <QLoggingCategory>
#include <QVulkanInstance>
#include <QFile>
#include <QByteArray>


#include "source/gfx/vulkanwidget.h"
#include "source/gfx/modelloader.h"


int main(int argc, char *argv[])
{
    QApplication application(argc, argv);


    //QLoggingCategory::setFilterRules(QStringLiteral("qt.vulkan=true"));

    QVulkanInstance ourInstance;

    qInfo() << "\nSupported Vulkan API: "
            << ourInstance.supportedApiVersion();

    ourInstance.setApiVersion(
        ourInstance.supportedApiVersion()
    );

    //ourInstance.setLayers({ "VK_LAYER_KHRONOS_validation" });

    if (!ourInstance.create())
        qFatal("Failed to create Vulkan instance: %d", ourInstance.errorCode());
    else
        qInfo("\n[main]Vulkan Instance Created.\n ");

    Night::GameModel *model = new Night::GameModel();
    Night::Util::ModelLoader("baseFloorTile.obj", *model);
    Night::VulkanWidget *vulkanWidget = new Night::VulkanWidget(model, &ourInstance);



    RhanaWindow *window = new RhanaWindow(vulkanWidget);
    window->go();


    for (uint index = 0; index < model->vboStorage->size(); index++)
        qInfo() << "\nindex: "
                << index
                << "    data: "
                << model->vboStorage[0][index];

    // save buffer to binary file
    // ready to be used in any Midnight library game

    // Midnight Model Data
    QString fileExtention = ".mmd";

    QFile file("baseFloorTile" + fileExtention);
    file.open(QIODevice::WriteOnly);

    QDataStream output(&file);
    output << *model->vboStorage;

    file.close();

    application.exec();

    ourInstance.destroy();

    return 0;
}
