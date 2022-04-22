#include "modelloader.h"

namespace Night
{
    namespace Util
    {

        void ModelLoader(const std::string &path, GameModel &loadedAsset)
        {
            //GameModel *loadedAsset = new GameModel();
            loadedAsset.numIndices = 0;
            loadedAsset.modelMatrix.setToIdentity();
            loadedAsset.vboStorage = new QList<float>;

            Assimp::Importer loader;// = new Assimp::Importer();

            const aiScene* scene =
                    loader.ReadFile(path, aiProcess_Triangulate | 0); //aiProcessPreset_TargetRealtime_Quality);

            if (scene == nullptr)
            {
                qInfo()
                        << "\n[ModelLoader] : unable to load 3D Model."
                        << loader.GetErrorString();

                return;
            }
                else
                qInfo("\n[ModelLoader] : 3D Model Loaded.");



            aiMesh* mesh = scene->mMeshes[0];
            loadedAsset.numIndices = mesh->mNumFaces *3;

            for (uint32_t index = 0; index < mesh->mNumVertices; index++)
            {
                // 3 floats for position + 1
                loadedAsset.vboStorage->push_back(mesh->mVertices[index][0]);
                loadedAsset.vboStorage->push_back(mesh->mVertices[index][1]);
                loadedAsset.vboStorage->push_back(mesh->mVertices[index][2]);
                loadedAsset.vboStorage->push_back(1.0f);


                //4 floats for the color
                // TODO: (Bladez) can we do better than this?
                loadedAsset.vboStorage->push_back(0.1f);
                loadedAsset.vboStorage->push_back(0.8f);
                loadedAsset.vboStorage->push_back(0.1f);
                loadedAsset.vboStorage->push_back(1.0f);
            }

            qInfo()
                    << "\nModel loaded :"
                    << "\nNumber of Indices = "
                    << loadedAsset.numIndices
                    << "\nNumber of Vertices = "
                    << loadedAsset.vboStorage->size() / 7
                    << "\n";
        }
    }
}
