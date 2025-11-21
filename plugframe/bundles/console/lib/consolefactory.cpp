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

#include "consolefactory.h"
#include "consolelistener.h"
#include "cmd/loadedlistcmdprocessor.h"
#include "cmd/startedlistcmdprocessor.h"
#include "cmd/levelcmdprocessor.h"
#include "cmd/quitcmdprocessor.h"
#include "cmd/helpcmdprocessor.h"

ConsoleFactory::ConsoleFactory()
{

}

ConsoleFactory::~ConsoleFactory()
{

}

plugframe::BundleListener *ConsoleFactory::createBundleListener(plugframe::Bundle& myBundle)
{
    return new ConsoleListener{myBundle};
}

QspCmdProcessor ConsoleFactory::createStartedListCmdProcessor(const QString& logChannel,
                                                              Console& console)
{
    return QspCmdProcessor(new StartedListCmdProcessor{logChannel, console});
}

QspCmdProcessor ConsoleFactory::createLoadedListCmdProcessor(const QString& logChannel,
                                                             Console& console)
{
    return QspCmdProcessor(new LoadedListCmdProcessor{logChannel, console});
}

QspCmdProcessor ConsoleFactory::createLevelCmdProcessor(const QString& logChannel,
                                                        Console& console)
{
    return QspCmdProcessor(new LevelCmdProcessor{logChannel, console});
}

QspCmdProcessor ConsoleFactory::createQuitCmdProcessor(const QString& logChannel,
                                                       Console& console)
{
    return QspCmdProcessor(new QuitCmdProcessor{logChannel, console});
}

QspCmdProcessor ConsoleFactory::createHelpCmdProcessor(const QString& logChannel,
                                                       Console& console,
                                                       QspCmdProcessor firstProc)
{
    return QspCmdProcessor(new HelpCmdProcessor{logChannel, console, firstProc});
}

PF_createServiceImplementation_DEF(ConsoleFactory)

