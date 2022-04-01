#include "rhanawindow.h"
#include "ui_rhanawindow.h"


RhanaWindow::RhanaWindow(Night::VulkanWidget *vkWidget)
    : m_ui(new Ui::RhanaWindow)
    , m_vkWidget(vkWidget)
    , m_vulkanWidget(vkWidget->getVulkanWidget())
{

    m_ui->setupUi(this);
    this->show();

    m_ui->displayLayout->insertWidget(0, m_vulkanWidget);

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(mainGameLoop()));

    qInfo()
            << "\nRhanaWindow Created\n";
}

RhanaWindow::~RhanaWindow()
{
    delete m_vulkanWidget;
    delete m_vkWidget;
    delete m_ui;
}

void RhanaWindow::go()
{
    m_timer.start(10);
}

void RhanaWindow::mainGameLoop()
{
    m_timer.stop();

    // render continuously, throttled by the presentation rate
    m_vkWidget->requestUpdate();

    // Update the fps display
    m_ui->fpsDisplay->display(m_vkWidget->getRenderer()->getFPS());


    m_timer.start(10);
}


