// Copyright (C) 2025 ELEKDOM Christophe Mars c.mars@elekdom.fr
// 
// This file is part of PlugFrame.
// 
// PlugFrame is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// PlugFrame is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with PlugFrame. If not, see <https://www.gnu.org/licenses/>.
//


#include "digitalsuite.h"

using namespace elekdom::plugframe::core::scheduler;


DigitalSuite::DigitalSuite(const QString &strSuite)
{
    QStringList list = strSuite.split(',', Qt::SkipEmptyParts);
    for (int i = 0; i < list.size(); i++)
    {
        QStringList list2 = list.at(i).split('.', Qt::SkipEmptyParts);
        if (1 == list2.size())
        {
            append(list2.at(0).toInt());
        }
        else if (2 == list2.size())
        {
            int first{list2.at(0).toInt()};
            int last{list2.at(1).toInt()};
            for (int k = first; k <= last; k++)
            {
                append(k);
            }
        }
    }
}

bool DigitalSuite::isValid(int minValue, int maxValue)
{
    bool ret{true};
    int lastVal{0};

    for (int i = 0; i < size() && ret; i++)
    {
        int testedVal{at(i)};

        if (testedVal >= minValue && testedVal <= maxValue && testedVal > lastVal)
        {
            lastVal = testedVal;
        }
        else
        {
            ret = false;
        }
    }

    return ret;
}
