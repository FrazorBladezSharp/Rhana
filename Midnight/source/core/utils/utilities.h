#ifndef UTILITIES_H
#define UTILITIES_H


#include <source/night_common.h>
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

        void fileReadText(
                const QString filepath,
                Ref<QStringList>& list);


        // Main Random Utilities
        void diceInitialize();

        int diceRoll(
                int numDiceToRoll,
                int typeOfDice);

        // using a 3d6 system we have the following :
        bool diceCriticalSuccess(
            int effectiveSkill,
            int diceRoll);


        bool diceCriticalFailure(
            int effectiveSkill,
            int diceRoll);

    }
}

#endif // UTILITIES_H
