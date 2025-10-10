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

using namespace elekdom::plugframe::console;
using namespace elekdom::plugframe;

factory::ConsoleFactory::ConsoleFactory()
{

}

factory::ConsoleFactory::~ConsoleFactory()
{

}

core::bundle::BundleListener *factory::ConsoleFactory::createBundleListener(core::bundle::Bundle& myBundle)
{
    return new ConsoleListener{myBundle};
}

cmd::QspCmdProcessor factory::ConsoleFactory::createStartedListCmdProcessor(const QString& logChannel,
                                                                                  console::bundle::Console& console)
{
    return cmd::QspCmdProcessor(new cmd::StartedListCmdProcessor{logChannel, console});
}

cmd::QspCmdProcessor factory::ConsoleFactory::createLoadedListCmdProcessor(const QString& logChannel,
                                                                                 console::bundle::Console& console)
{
    return cmd::QspCmdProcessor(new cmd::LoadedListCmdProcessor{logChannel, console});
}

cmd::QspCmdProcessor factory::ConsoleFactory::createLevelCmdProcessor(const QString& logChannel,
                                                                            console::bundle::Console& console)
{
    return cmd::QspCmdProcessor(new cmd::LevelCmdProcessor{logChannel, console});
}

cmd::QspCmdProcessor factory::ConsoleFactory::createQuitCmdProcessor(const QString& logChannel,
                                                                           console::bundle::Console& console)
{
    return cmd::QspCmdProcessor(new cmd::QuitCmdProcessor{logChannel, console});
}

cmd::QspCmdProcessor factory::ConsoleFactory::createHelpCmdProcessor(const QString& logChannel,
                                                                           console::bundle::Console& console,
                                                                           cmd::QspCmdProcessor firstProc)
{
    return cmd::QspCmdProcessor(new cmd::HelpCmdProcessor{logChannel, console, firstProc});
}

PF_createServiceImplementation_DEF(factory::ConsoleFactory)

