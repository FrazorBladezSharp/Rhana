#include "itemwarehouse.h"


namespace Night
{
    ItemWarehouse::ItemWarehouse(Ref<Scene> &world, int items)
        : m_World(world)
        , m_Items(items)
        , m_BaseItemObject(m_World->GetObject(items))
    {
        m_Weapons = new QVector <Scene::Object*>();
    }

    ItemWarehouse::~ItemWarehouse()
    {
        m_Weapons->clear();
        delete m_Weapons;
    }

    void ItemWarehouse::initialize()
    { 
        loadItemFile("source/assets/items/item_data.txt", m_Weapons);
    }

    //********************* Private ***************************

    void ItemWarehouse::loadItemFile(QString file, QVector<Scene::Object *> *shelf)
    {
        // read data from a text file for items
        Night::Ref<QStringList> list_output = Night::CreateRef<QStringList>();
        Night::Utils::FileReadText(file, list_output);

        // for each item in the text file
        for(int index = 0; index < list_output->count(); index++)
        {
            // dont take action on comments
            QString line = list_output->at(index);
            if (line.startsWith('#')) continue;

            // create our new Object using the ECS item as a template
            Scene::Object *weapon_new_item = new Scene::Object();
            memcpy(weapon_new_item, m_BaseItemObject, sizeof(Scene::Object));

            // create the new component to be added to our item
            Item_Component *weapon = new Item_Component();
            weapon->name = line.split(" ").at(0);
            weapon->damage = line.split(" ").at(1).toInt();


            // add data to the new Object
            weapon_new_item->uuid = QUuid::createUuid();
            weapon_new_item->components[(unsigned)Night::Component::COMP_ITEM] = weapon;

            // Store the Object for later use
            shelf->push_back(weapon_new_item);
        }
    }
}
