#include "rhanawindow.h"

#include <QApplication>
#include <QLoggingCategory>
#include <QVulkanInstance>

#include "source/gfx/vulkanwidget.h"


int main(int argc, char *argv[])
{
    QApplication application(argc, argv);


    QLoggingCategory::setFilterRules(QStringLiteral("qt.vulkan=true"));

    QVulkanInstance our_instance;
    our_instance.setLayers({ "VK_LAYER_KHRONOS_validation" });

    if (!our_instance.create())
        qFatal("Failed to create Vulkan instance: %d", our_instance.errorCode());

    Night::VulkanWidget *vulkanWidget = new Night::VulkanWidget;
    vulkanWidget->setVulkanInstance(&our_instance);


    RhanaWindow *window = new RhanaWindow(vulkanWidget);
    window->Go();

    int error_value = application.exec();

    return error_value;
}
