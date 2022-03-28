#include "itemwarehouse.h"


namespace Night
{
    ItemWarehouse::ItemWarehouse(Ref<Scene> &world, int items)
        : m_world(world)
        , m_items(items)
        , m_baseItemObject(m_world->getObject(items))
    {
        m_handTool = new QVector <Scene::Object*>();
    }

    ItemWarehouse::~ItemWarehouse()
    {
        m_handTool->clear();
        delete m_handTool;
    }

    void ItemWarehouse::initialize()
    { 
        loadItemFile("source/assets/items/item_data.txt", m_handTool);
    }

    //********************* Private ***************************

    void ItemWarehouse::loadItemFile(QString file, QVector<Scene::Object *> *shelf)
    {
        // read data from a text file for items
        Night::Ref<QStringList> listOutput = Night::CreateRef<QStringList>();
        Night::Utils::fileReadText(file, listOutput);

        // for each item in the text file
        for(int index = 0; index < listOutput->count(); index++)
        {
            // dont take action on comments
            QString line = listOutput->at(index);
            if (line.startsWith('#')) continue;

            // create our new Object using the ECS item as a template
            Scene::Object *item = new Scene::Object();
            memcpy(item, m_baseItemObject, sizeof(Scene::Object));

            // create the new component to be added to our item
            ItemComponent *itemComponent = new ItemComponent();
            itemComponent->name = line.split(" ").at(0);
            itemComponent->damage = line.split(" ").at(1).toInt();


            // add data to the new Object
            item->uuid = QUuid::createUuid();
            item->components[(unsigned)Night::Component::COMP_ITEM] = itemComponent;

            // Store the Object for later use
            shelf->push_back(item);
        }
    }
}
