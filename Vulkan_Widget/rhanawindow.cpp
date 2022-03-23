#include "rhanawindow.h"
#include "ui_rhanawindow.h"



RhanaWindow::RhanaWindow(Night::VulkanWidget *vkWidget)
    : ui(new Ui::RhanaWindow)
    , m_VulkanWidget(vkWidget->GetVulkanWidget())
{

    ui->setupUi(this);

    ui->Display_Layout->insertWidget(0, m_VulkanWidget);

}

RhanaWindow::~RhanaWindow()
{
    delete ui;
}


