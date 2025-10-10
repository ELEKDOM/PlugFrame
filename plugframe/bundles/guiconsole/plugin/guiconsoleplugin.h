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


#ifndef GUICONSOLEPLUGIN_H
#define GUICONSOLEPLUGIN_H

#include "plugin/plugin.h"

namespace elekdom
{
namespace plugframe
{
namespace guiconsole
{
namespace plugin
{

class GuiConsolePlugin : public core::plugin::Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "elekdom.plugframe.guiconsole.plugin" FILE "../guiconsolebundle.json")
    Q_INTERFACES(elekdom::plugframe::core::plugin::BundleInterface)

public:
    GuiConsolePlugin();
    virtual ~GuiConsolePlugin();

protected: // SmfPLugin
    core::bundle::Bundle4PluginInterface *createImplementation() override;
    PF_bindServicesImplementations_DECL

protected: // SmfTemplateServiceInterface
};

} //namespace plugin
} //namespace guiconsole
} //namespace plugframe
} //namespace elekdom

#endif // GUICONSOLEPLUGIN_H
