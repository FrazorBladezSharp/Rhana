#include <QCoreApplication>
#include <QDir>
#include <QDebug>

#include <QStringList>

#include "night_common.h"
#include "source/core/utils/utilities.h"


int main(int argc, char *argv[])
{
    qDebug()
            << "Welcome to Util Development.";

    QCoreApplication a(argc, argv);

    QDir::setCurrent(a.applicationDirPath());

    // test for text file input
    Night::Ref<QStringList> list_output = Night::CreateRef<QStringList>();
    {
        QString file = "source/assets/items/item_data.txt";
        Night::Utils::FileReadText(file, list_output);
        qDebug()
                << *list_output;
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

    return 0;//a.exec();
}

// Psst dont forget QByteArray
