#ifndef COMPONENTS_H
#define COMPONENTS_H


#include <QVector>
#include <QUuid>


namespace Night
{

    enum class Component
    {
        COMP_POSITION,
        COMP_COMBAT,
        COMP_TOTAL
    };

    struct Position_Component
    {
        float x = 0.0f;
        float y = 0.0f;
    };

    struct Combat_Component
    {
        QString name = "Default";
        int damage = -6;
    };


}



#endif // COMPONENTS_H
