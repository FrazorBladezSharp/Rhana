#ifndef UTILITIES_H
#define UTILITIES_H


#include <night_common.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QDir>
#include <QFile>

namespace Night
{
    namespace Utils
    {

        void FileReadText(
                const QString filepath,
                Ref<QStringList>& list);


        // Main Random Utilities
        void Dice_Initialize();

        int Dice_Roll(
                int num_of_dice_to_roll,
                int type_of_dice);

        // using a 3d6 system we have the following :
        bool Dice_Critical_Success(
            int effectiveSkill,
            int diceRoll);


        bool Dice_Critical_Failure(
            int effectiveSkill,
            int diceRoll);


    }
}

#endif // UTILITIES_H
