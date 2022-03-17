#ifndef COMPONENTS_H
#define COMPONENTS_H


#include <QVector>


namespace Night
{

    enum class Component
    {
        COMP_POSITION,
        COMP_TOTAL
    };

    struct Position_Component
    {
        float x = 0.0f;
        float y = 0.0f;
    };


}



#endif // COMPONENTS_H
