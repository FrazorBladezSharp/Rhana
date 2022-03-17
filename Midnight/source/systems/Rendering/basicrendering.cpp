#include "basicrendering.h"


namespace Night
{
    BasicRendering::BasicRendering()
    {
        // Empty
    }

    void BasicRendering::TextRendering(
            Ref<TextOutput> &output,
            QString textView)
    {
        output->setPlainText(textView);
        output->update();
    }

}
