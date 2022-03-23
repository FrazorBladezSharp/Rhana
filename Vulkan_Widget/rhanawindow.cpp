#include "rhanawindow.h"
#include "ui_rhanawindow.h"


RhanaWindow::RhanaWindow(Night::VulkanWidget *vkWidget)
    : ui(new Ui::RhanaWindow)
    , m_VkWidget(vkWidget)
    , m_VulkanWidget(vkWidget->GetVulkanWidget())
{

    ui->setupUi(this);

    ui->Display_Layout->insertWidget(0, m_VulkanWidget);

    connect(&m_Timer, SIGNAL(timeout()), this, SLOT(MainGameLoop()));

    this->show();
}

RhanaWindow::~RhanaWindow()
{
    delete ui;
}

void RhanaWindow::Go()
{
    m_Timer.start(10);
}

void RhanaWindow::MainGameLoop()
{
    m_Timer.stop();

    // render continuously, throttled by the presentation rate
    m_VkWidget->requestUpdate();

    // Update the fps display
    ui->FPS_Display->display(m_VkWidget->GetRenderer()->getFPS());


    m_Timer.start(10);
}


