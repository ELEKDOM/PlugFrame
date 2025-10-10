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


#include <QObject>
#include "logger/pflog.h"
#include "terminal.h"
#include "cmd/quitcmdprocessor.h"
#include "console.h"

using namespace elekdom::plugframe::console::cmd;

QuitCmdProcessor::QuitCmdProcessor(const QString& logChannel,
                                         console::bundle::Console& console):
    CmdProcessor{logChannel,
                    console,
                    "quit",
                    QObject::tr("Quitte l'application après confirmation")}
{

}

QuitCmdProcessor::~QuitCmdProcessor()
{

}

bool QuitCmdProcessor::exec(const RawCmd &cmd)
{
    Q_UNUSED(cmd)

    console().print(QObject::tr("Etes-vous sûr de vouloir quitter l'application (oui/non)?"));

    QTextStream stream(stdin);
    QString line;

    stream.readLineInto(&line);
    line = line.toLower();
    if (line == QObject::tr("oui"))
    {
        console().quit();
    }

    return true;
}

