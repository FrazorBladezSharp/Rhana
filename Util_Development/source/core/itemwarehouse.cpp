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
        int items = m_World->AddEntity();
        Scene::Object *base_item_object = m_World->GetObject(items);


        Night::Ref<QStringList> list_output = Night::CreateRef<QStringList>();

        QString file = "source/assets/items/item_data.txt";
        Night::Utils::FileReadText(file, list_output);

        for(int index = 0; index < list_output->count(); index++)
        {
            QString line = list_output->at(index);
            if (line.startsWith('#')) continue;

            Scene::Object *weapon_new_item = new Scene::Object();
            memcpy(weapon_new_item, base_item_object, sizeof(Scene::Object));

            Combat_Component *weapon = new Combat_Component();

            weapon->name = line.split(" ").at(0);
            weapon->damage = line.split(" ").at(1).toInt();

            weapon_new_item->entity_ID = items;     // this line may not be needed

            weapon_new_item->uuid = QUuid::createUuid();
            weapon_new_item->components[(unsigned)Night::Component::COMP_COMBAT] = weapon;

            m_Weapons->push_back(weapon_new_item);
        }

    }

}
