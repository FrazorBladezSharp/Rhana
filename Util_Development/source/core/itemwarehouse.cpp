#include "itemwarehouse.h"


namespace Night
{
    ItemWarehouse::ItemWarehouse(Ref<Scene> &world)
        : m_World(world)
    {
        m_Weapons = new QVector <Scene::Object*>();
    }

    ItemWarehouse::~ItemWarehouse()
    {
        m_Weapons->clear();
        delete m_Weapons;
    }

    void ItemWarehouse::Initialize()
    {
        // this is example code on how to generate items
        // please note you want to generate items on the fly !

        // create a base item entity within the ECS
        int items = m_World->AddEntity();
        Scene::Object *base_item_object = m_World->GetObject(items);

        // read data from a text file for items
        Night::Ref<QStringList> list_output = Night::CreateRef<QStringList>();
        QString file = "source/assets/items/item_data.txt";
        Night::Utils::FileReadText(file, list_output);

        // for each item in the text file
        for(int index = 0; index < list_output->count(); index++)
        {
            // dont take action on comments
            QString line = list_output->at(index);
            if (line.startsWith('#')) continue;

            // create our new Object using the ECS item as a template
            Scene::Object *weapon_new_item = new Scene::Object();
            memcpy(weapon_new_item, base_item_object, sizeof(Scene::Object));

            // create the new component to be added to our item
            Combat_Component *weapon = new Combat_Component();
            weapon->name = line.split(" ").at(0);
            weapon->damage = line.split(" ").at(1).toInt();


            // add data to the new Object
            weapon_new_item->uuid = QUuid::createUuid();
            weapon_new_item->components[(unsigned)Night::Component::COMP_COMBAT] = weapon;

            // Store the Object for later use
            m_Weapons->push_back(weapon_new_item);
        }

    }

}
