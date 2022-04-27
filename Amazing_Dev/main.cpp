#include "source/appCore/applicationwindow.h"

#include <QApplication>
#include <QScreen>
#include <QDir>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ApplicationWindow w;

    QDir::setCurrent(a.applicationDirPath());

    int screenWidth = w.screen()->geometry().width();
    int screenHeight = w.screen()->geometry().height();

    w.setGeometry(
                (screenWidth/2)-(w.geometry().width()/2),
                (screenHeight/2)-(w.geometry().height()/2),
                w.geometry().width(),
                w.geometry().height()
                );
    w.show();

    w.Run();

    return a.exec();
}
