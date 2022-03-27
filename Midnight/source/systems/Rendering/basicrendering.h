#ifndef BASICRENDERING_H
#define BASICRENDERING_H


#include "source/night_common.h"

#include "source/implementation/output/textoutput.h"

namespace Night
{
    class BasicRendering
    {
    public:
        BasicRendering();

        void textRendering(
                Ref<TextOutput> &output,
                QString textView);
    };
}

#endif // BASICRENDERING_H
