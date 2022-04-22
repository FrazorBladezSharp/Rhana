
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



//    Night::GameModel *model =
//        new Night::GameModel();

//    Night::Util::ModelLoader(
//        "baseFloorTile.obj",
//        *model
//    );



    Night::GameModel *midnightModel =
        new Night::GameModel();

    midnightModel->modelMatrix.setToIdentity();
    midnightModel->numIndices = 0;
    midnightModel->vboStorage = new QList<float>();

    QFile file(
        "baseFloorTile.mmd"
    );

    file.open(
        QIODevice::ReadOnly
    );

    QDataStream input(
        &file
    );

    input >> *midnightModel->vboStorage;

    file.close();

    midnightModel->numIndices = midnightModel->vboStorage->size() / 8;
    QVector3D modelLocation = {0.0f, -0.5f, 0.0f};
    midnightModel->modelMatrix.translate(modelLocation);



    Night::VulkanWidget *vulkanWidget =
        new Night::VulkanWidget(
            midnightModel,
            &vulkanInstance
    );

    RhanaWindow *window =
        new RhanaWindow(
            vulkanWidget
    );

    window->go();



    if(running)
        application.exec();

    vulkanInstance.destroy();

//    qInfo() << "\n[main] Vulkan Instance Destroyed."
//            << "\n Model Verts ="
//            << model->vboStorage->size()
//            << "\n Midnight Verts ="
//            << midnightModel->vboStorage->size()
//            << "\n Model Indices ="
//            << model->numIndices
//            << "\n Midnight Indices ="
//            << model->numIndices;

//    for(int i = 280; i < 288; i++)
//    {
//        qInfo() << "\n "
//                << model->vboStorage[0][i]
//                << " :"
//                <<midnightModel->vboStorage[0][i];
//    }

    return 0;
}
