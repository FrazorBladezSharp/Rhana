#ifndef ASSET_H
#define ASSET_H


#include "source/night_common.h"
#include "basemobile.h"

namespace Night
{
    class Asset : public BaseMobile
    {

    public:
        Asset(int id, Ref<Scene> &scene);

        virtual PositionComponent* getPosition() override;
    };

}

#endif // ASSET_H
