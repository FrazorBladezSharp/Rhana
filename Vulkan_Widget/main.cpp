

#include <QDir>
#include <QApplication>
#include <QLoggingCategory>
#include <QVulkanInstance>

#include "source/gfx/vulkanwidget.h"
#include "rhanawindow.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);


    QLoggingCategory::setFilterRules(QStringLiteral("qt.vulkan=true"));

    QVulkanInstance ourInstance;
    ourInstance.setLayers({ "VK_LAYER_KHRONOS_validation" });

    if (!ourInstance.create())
        qFatal("Failed to create Vulkan instance: %d", ourInstance.errorCode());



    Night::VulkanWidget *vulkanWidget = new Night::VulkanWidget(&ourInstance);
    RhanaWindow *window = new RhanaWindow(vulkanWidget);
    //vulkanWidget->setVulkanInstance(&ourInstance);
    window->go();

    qInfo()
            << "\nProject working directory: "
            << QDir::currentPath()
            << "\n";

    int errorValue = application.exec();

    return errorValue;
}
