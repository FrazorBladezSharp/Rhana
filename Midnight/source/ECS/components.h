#ifndef COMPONENTS_H
#define COMPONENTS_H


#include <QVector>
#include <QUuid>


namespace Night
{

    enum class Component
    {
        COMP_POSITION,
        COMP_ITEM,
        COMP_TOTAL
    };

    struct PositionComponent
    {
        float x = 0.0f;
        float y = 0.0f;
    };

    struct ItemComponent
    {
        QString name = "Default";
        int damage = -6;
    };


}



#endif // COMPONENTS_H
