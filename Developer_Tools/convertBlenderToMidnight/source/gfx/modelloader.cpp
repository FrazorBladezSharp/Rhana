#include "modelloader.h"

namespace Night
{
    namespace Util
    {

        GameModel *ModelLoader(const std::string &path)
        {
            GameModel *loadedAsset = new GameModel();
            loadedAsset->numIndices = 0;
            loadedAsset->modelMatrix.setToIdentity();
            loadedAsset->vboStorage = new QList<float>;

            Assimp::Importer *loader = new Assimp::Importer();

            const struct aiScene* scene =
                    loader->ReadFile(path, aiProcess_Triangulate);

            if (scene == nullptr)
            {
                qInfo()
                        << "\n[ModelLoader] : unable to load 3D Model."
                        << loader->GetErrorString();

                //return loadedAsset;
            }
                else
                qInfo("\n[ModelLoader] : 3D Model Loaded.");



            aiMesh* mesh = scene->mMeshes[0];
            loadedAsset->numIndices = mesh->mNumFaces *3;

            for (uint32_t index = 0; index <= mesh->mNumVertices; index++)
            {
                // 3 floats for position
                loadedAsset->vboStorage->push_back(mesh->mVertices[index][0]);
                loadedAsset->vboStorage->push_back(mesh->mVertices[index][1]);
                loadedAsset->vboStorage->push_back(mesh->mVertices[index][2]);

                //4 floats for the color
                loadedAsset->vboStorage->push_back(0.1f);
                loadedAsset->vboStorage->push_back(0.8f);
                loadedAsset->vboStorage->push_back(0.1f);
                loadedAsset->vboStorage->push_back(1.0f);
            }

            return loadedAsset;
        }

    }
}
