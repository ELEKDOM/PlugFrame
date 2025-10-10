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
#include "cmd/levelcmdprocessor.h"
#include "console.h"

using namespace elekdom::plugframe::console::cmd;

LevelCmdProcessor::LevelCmdProcessor(const QString& logChannel,
                                           console::bundle::Console& console):
    CmdProcessor{logChannel,
                    console,
                    "level",
                    QObject::tr("Affiche le niveau d'exécution de la plateforme")}
{

}

LevelCmdProcessor::~LevelCmdProcessor()
{

}

bool LevelCmdProcessor::exec(const RawCmd &cmd)
{
    Q_UNUSED(cmd)

    QString msg{QObject::tr("\tniveau d'exécution de la plateforme\t%1\n").arg(console().runningLevel())};

    console().print(msg);
    return true;
}
