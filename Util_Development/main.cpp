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
        Night::Utils::FileReadText(file, listOutput);
        qDebug()
                << *listOutput;
    }

    // test for random number generation (3d6)
    {
        Night::Utils::Dice_Initialize();

        int test_skill = 10;

        for (int index = 0; index < 10; index ++)
        {
            int die_roll = Night::Utils::Dice_Roll(3, 6);

            bool is_crit_success = Night::Utils::Dice_Critical_Success(test_skill, die_roll);
            bool is_crit_failure = Night::Utils::Dice_Critical_Failure(test_skill, die_roll);

            qDebug()
                    << "Dice Roll: "
                    << die_roll
                    << "    Crit Success: "
                    << is_crit_success
                    << "    Crit Failure: "
                    << is_crit_failure;
        }
    }

    // test and display a simple Item warehouse list
    {
        // the setup and initiaslization
        Night::Ref<Night::Scene> scene = Night::CreateRef<Night::Scene>();

        int itemsEntity = scene->AddEntity();
        Night::Ref<Night::ItemWarehouse> items = Night::CreateRef<Night::ItemWarehouse>(scene,  itemsEntity);
        scene->Initialize();
        items->initialize();

        // the system requirements to view weapons
        const QVector<Night::Scene::Object*> weapon_view = items->viewWeapons();

        // example on data access
        for (int index = 0; index < weapon_view.size(); index++)
        {
            qDebug()
                    << "Weapon entity: "
                    << weapon_view[index]->entity_ID
                    << weapon_view[index]->uuid;

            Night::Item_Component *weapon_component = static_cast<Night::Item_Component*>( weapon_view[index]->components[(int)Night::Component::COMP_ITEM]);
            qDebug()
                    << weapon_component->name
                    << "    Damage: "
                    << weapon_component->damage;
        }

    }

    return 0;//a.exec();
}

// Psst dont forget QByteArray
