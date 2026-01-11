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
#include "cmd/cmdprocessor.h"

class ConsoleFactory : public plugframe::BundleFactory
{
public:
    ConsoleFactory();
    virtual ~ConsoleFactory();

public:
    PF_createServiceImplementation_DECL
    virtual plugframe::BundleListener *createBundleListener(plugframe::Bundle& myBundle)override;
    virtual QspCmdProcessor createStartedListCmdProcessor(const QString& logChannel,
                                                          Console& console);
    virtual QspCmdProcessor createLoadedListCmdProcessor(const QString& logChannel,
                                                         Console& console);
    virtual QspCmdProcessor createLevelCmdProcessor(const QString& logChannel,
                                                    Console& console);
    virtual QspCmdProcessor createQuitCmdProcessor(const QString& logChannel,
                                                   Console& console);
    virtual QspCmdProcessor createHelpCmdProcessor(const QString& logChannel,
                                                   Console& console,
                                                   QspCmdProcessor firstProc);
};
#endif // CONSOLEFACTORY_H
