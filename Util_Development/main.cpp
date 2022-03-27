#include <QCoreApplication>
#include <QDir>
#include <QDebug>

#include <QStringList>

#include <source/night_common.h>
#include <source/ECS/scene.h>
#include <source/core/utils/utilities.h>
#include "source/core/itemwarehouse.h"



int main(int argc, char *argv[])
{
    qDebug()
            << "Welcome to Util Development.";

    QCoreApplication a(argc, argv);

    QDir::setCurrent(a.applicationDirPath());

    // test for text file input
    Night::Ref<QStringList> listOutput = Night::CreateRef<QStringList>();
    {
        QString file = "source/assets/items/item_data.txt";
        Night::Utils::fileReadText(file, listOutput);
        qDebug()
                << *listOutput;
    }

    // test for random number generation (3d6)
    {
        Night::Utils::diceInitialize();

        int testskill = 10;

        for (int index = 0; index < 10; index ++)
        {
            int dieRoll = Night::Utils::diceRoll(3, 6);

            bool isCritSuccess = Night::Utils::diceCriticalSuccess(testskill, dieRoll);
            bool isCritFailure = Night::Utils::diceCriticalFailure(testskill, dieRoll);

            qDebug()
                    << "Dice Roll: "
                    << dieRoll
                    << "    Crit Success: "
                    << isCritSuccess
                    << "    Crit Failure: "
                    << isCritFailure;
        }
    }

    // test and display a simple Item warehouse list
    {
        // the setup and initiaslization
        Night::Ref<Night::Scene> scene = Night::CreateRef<Night::Scene>();

        int itemsEntity = scene->addEntity();
        Night::Ref<Night::ItemWarehouse> items = Night::CreateRef<Night::ItemWarehouse>(scene,  itemsEntity);
        scene->initialize();
        items->initialize();

        // the system requirements to view weapons
        const QVector<Night::Scene::Object*> weaponView = items->viewHandTool();

        // example on data access
        for (int index = 0; index < weaponView.size(); index++)
        {
            qDebug()
                    << "Weapon entity: "
                    << weaponView[index]->entityID
                    << weaponView[index]->uuid;

            Night::ItemComponent *weaponComponent = static_cast<Night::ItemComponent*>( weaponView[index]->components[(int)Night::Component::COMP_ITEM]);
            qDebug()
                    << weaponComponent->name
                    << "    Damage: "
                    << weaponComponent->damage;
        }

    }

    return 0;//a.exec();
}

// Psst dont forget QByteArray
