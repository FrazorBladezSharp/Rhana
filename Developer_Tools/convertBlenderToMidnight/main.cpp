#include "source/rhanawindow.h"

#include <QApplication>
#include <QLoggingCategory>
#include <QVulkanInstance>

#include "source/gfx/vulkanwidget.h"


int main(int argc, char *argv[])
{
    QApplication application(argc, argv);


    QLoggingCategory::setFilterRules(QStringLiteral("qt.vulkan=true"));

    QVulkanInstance ourInstance;
    ourInstance.setLayers({ "VK_LAYER_KHRONOS_validation" });

    if (!ourInstance.create())
        qFatal("Failed to create Vulkan instance: %d", ourInstance.errorCode());

    Night::VulkanWidget *vulkanWidget = new Night::VulkanWidget();
    vulkanWidget->setVulkanInstance(&ourInstance);


    RhanaWindow *window = new RhanaWindow(vulkanWidget);
    window->go();

    int errorValue = application.exec();

    return errorValue;
}
