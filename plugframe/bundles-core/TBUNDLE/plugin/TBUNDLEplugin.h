// Copyright (C) 2026 ELEKDOM Christophe Mars c.mars@elekdom.fr
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

#ifndef TBUNDLEPLUGIN_H
#define TBUNDLEPLUGIN_H

#include "plugin/plugin.h"
#include "TBUNDLEserviceinterface.h"
#include "TBUNDLEservice.h"

class TBUNDLEPlugin : public plugframe::Plugin,
                      public plugframe::TBUNDLEServiceInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "plugframe.tbundle.plugin" FILE "../TBUNDLEbundle.json")
    Q_INTERFACES(plugframe::BundleInterface)

public:
    TBUNDLEPlugin();
    ~TBUNDLEPlugin() override;

protected: // Plugin
    plugframe::Bundle4PluginInterface *createImplementation() override;
    PF_bindServicesImplementations_DECL

private:
    QspTBUNDLEService m_TBUNDLEServiceImpl;
};

#endif // TBUNDLEPLUGIN_H
