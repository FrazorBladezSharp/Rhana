#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <string>
#include <QMatrix4x4>
#include <QVector4D>

#include <QList>

/* assimp include files. These three are usually needed. */
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Night
{
    typedef struct GameModel{

        uint32_t numIndices;
        QMatrix4x4 modelMatrix;
        QList<float> *vboStorage;

    } GameModel;

    namespace Util
    {

        void ModelLoader(const std::string& path, GameModel& loadedAsset);

    }

}

#endif // MODELLOADER_H
