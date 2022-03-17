#ifndef INTROPICTURE_H
#define INTROPICTURE_H

#include "source/night_common.h"
#include <QGraphicsView>
#include <QDir>

namespace Night
{
    class IntroPicture : public QGraphicsView
    {
        Q_OBJECT

    public:
        IntroPicture(QWidget *parent);

        ~IntroPicture();


    private:
        QGraphicsScene* m_Gfx;
    };
}
#endif // INTROPICTURE_H
