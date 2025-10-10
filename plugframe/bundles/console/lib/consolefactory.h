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


#ifndef CONSOLEFACTORY_H
#define CONSOLEFACTORY_H

#include "factory/bundlefactory.h"
#include "console_forward.h"

namespace elekdom
{
namespace plugframe
{
namespace console
{
namespace factory
{

class ConsoleFactory : public core::bundle::BundleFactory
{
public:
    ConsoleFactory();
    virtual ~ConsoleFactory();

public:
    PF_createServiceImplementation_DECL
    virtual core::bundle::BundleListener *createBundleListener(core::bundle::Bundle& myBundle)override;
    virtual QSharedPointer<cmd::CmdProcessor> createStartedListCmdProcessor(const QString& logChannel,
                                                                               console::bundle::Console& console);
    virtual QSharedPointer<cmd::CmdProcessor> createLoadedListCmdProcessor(const QString& logChannel,
                                                                              console::bundle::Console& console);
    virtual QSharedPointer<cmd::CmdProcessor> createLevelCmdProcessor(const QString& logChannel,
                                                                         console::bundle::Console& console);
    virtual QSharedPointer<cmd::CmdProcessor> createQuitCmdProcessor(const QString& logChannel,
                                                                        console::bundle::Console& console);
    virtual QSharedPointer<cmd::CmdProcessor> createHelpCmdProcessor(const QString& logChannel,
                                                                        console::bundle::Console& console,
                                                                        QSharedPointer<cmd::CmdProcessor> firstProc);
};

} //namespace factory
} //namespace console
} //namespace plugframe
} //namespace elekdom

#endif // CONSOLEFACTORY_H
