#include "applicationwindow.h"
#include "ui_applicationwindow.h"

#include <QVector>
#include <QEvent>

ApplicationWindow::ApplicationWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ApplicationWindow)
    , m_Timer(new QTimer(this))
    , m_Midnight(new Night::Midnight(this))
    , m_gameEngine(new GameEngine(this))
{
    ui->setupUi(this);

    ui->display_layers->setCurrentWidget(ui->intro);
    ui->display_layers->setFocus();

    InitializeEngine();

    // *** Game app stuff goes here ***



    // ********************************

    m_Timer->setTimerType(Qt::PreciseTimer);

    connect(m_Timer, &QTimer::timeout, this, &ApplicationWindow::OnUpdate);

    qInfo() << "Welcome to the Midnight Sandbox.";
}

ApplicationWindow::~ApplicationWindow()
{
    delete m_Midnight;
    delete m_Timer;
    delete ui;
}

void ApplicationWindow::Run()
{
    m_Timer->start(15);
}

void ApplicationWindow::OnUpdate()
{
    m_Timer->stop();

    // update main engine - our first interface
    m_Midnight->onUpdate();

    m_Timer->start(15);
}

void ApplicationWindow::keyPressEvent(QKeyEvent *event)
{
    // true = 1 : false = 0
    if (event->key() == Qt::Key::Key_Any && ui->display_layers->currentWidget() == ui->intro)
        ui->display_layers->setCurrentWidget(ui->output_text_display);

    if(ui->display_layers->currentWidget() == ui->output_text_display)
    m_Midnight->movePlayer(event);
}

void ApplicationWindow::InitializeEngine()
{    
    qInfo()
            << "Registry of Midnight Output Device = "
            << m_Midnight->registerOutput(ui->text_display);

    m_Midnight->setPlayerPosition(10, 5);

    qInfo()
            << "Registry of Application Output Device = "
            << m_gameEngine->registerOutput(ui->maze_display, SCENE_WIDTH, SCENE_HEIGHT);

    m_gameEngine->setPlayerPosition(10, 5);
}
