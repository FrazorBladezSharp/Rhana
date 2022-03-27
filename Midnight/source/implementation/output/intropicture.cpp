#include "intropicture.h"
#include <QDebug>


namespace Night
{
    IntroPicture::IntroPicture(QWidget *parent)
        : QGraphicsView(parent)
    {
        QImage image;

        m_gfx = new QGraphicsScene(this);

        QDir buildDirectory;

        image.load(
            buildDirectory.absoluteFilePath(
                "../Midnight/source/assets/pictures/midnight.jpg"
            )
        );

        if (image.isNull())
            qDebug() << "Error: Unable to find file";


        m_gfx->addPixmap(QPixmap::fromImage(image));

        this->setScene(m_gfx);

    }

    IntroPicture::~IntroPicture()
    {
        delete m_gfx;
    }
}
