#include "rhanawindow.h"
#include "ui_rhanawindow.h"



RhanaWindow::RhanaWindow(Night::VulkanWidget *vkWidget)
    : ui(new Ui::RhanaWindow)
    , m_VulkanWidget(vkWidget->GetVulkanWidget())
{

    ui->setupUi(this);

    m_VulkanWidget->setMinimumSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    m_VulkanWidget->setMaximumSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    ui->centralwidget->layout()->addWidget(m_VulkanWidget);
}

RhanaWindow::~RhanaWindow()
{
    delete ui;
}


