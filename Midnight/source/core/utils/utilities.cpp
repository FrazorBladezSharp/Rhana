#include "utilities.h"

namespace Night
{
    namespace Utils
    {
        void fileReadText(
                const QString filepath,
                Ref<QStringList> &list)
        {
            QDir build_directory;
            QByteArray result;

            QString relative = "../Midnight/" + filepath;
            QFile file(build_directory.absoluteFilePath(relative));
            file.open(QIODevice::ReadOnly | QIODevice::Text);

            while (!file.atEnd())
                result = file.read(file.size());

            file.close();

            // remove the last EOF character
            result.chop(1);

            *list = QString(result).split("\n");
        }


        // Main Random Utilities
        void diceInitialize()
        {
            srand((uint) time(NULL));
        }

        int diceRoll(int numDiceToRoll, int typeOfDice)
        {
            int result = 0;

                for (int i = 0; i < numDiceToRoll; i++){

                    result += (rand() % typeOfDice) + 1;
                }

                return result;
        }

        // using a 3d6 system we have the following :
        bool diceCriticalSuccess(int effectiveSkill, int diceRoll)
        {
            bool ret;
            int crit = 4;

            // max effective skill = 20
            effectiveSkill -= ((effectiveSkill - 20) * (effectiveSkill >= 21));

            // increase critical chance for effective skill > 14
            crit += ((effectiveSkill - 14) * (effectiveSkill >= 15));

            // assign true or false dependant on the dice roll
            ret = (diceRoll <= crit);

            return ret;
        }

        bool diceCriticalFailure(int effectiveSkill, int diceRoll)
        {
            bool ret = false;

            // max effective skill = 20
            effectiveSkill -= ((effectiveSkill - 20) * (effectiveSkill >= 21));

            // min effective skill = 3
            effectiveSkill += ((3 - effectiveSkill) * (effectiveSkill <= 3));

            // greater chance for crit failure on lower effective skills
            ret = (diceRoll == 18)
                    || ((diceRoll == 17) && (effectiveSkill < 16))
                    || (diceRoll >= effectiveSkill + 10);

            return ret;
        }
    }
}
