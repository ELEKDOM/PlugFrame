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

#ifndef GUIDISPLAYPLUGIN_H
#define GUIDISPLAYPLUGIN_H

#include "plugin/plugin.h"
#include "service-int/displayserviceinterface.h"
#include "service-int/guibuilderserviceinterface.h"
#include "guibuilderservice.h"
#include "guidisplayservice.h"

class GuiDisplayPlugin : public plugframe::Plugin,
                         public plugframe::DisplayServiceInterface,
                         public plugframe::GuiBuilderServiceInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "plugframe.guidisplay.plugin" FILE "../guidisplaybundle.json")
    Q_INTERFACES(plugframe::BundleInterface
                 plugframe::DisplayServiceInterface
                 plugframe::GuiBuilderServiceInterface)
public:
    GuiDisplayPlugin();
    virtual ~GuiDisplayPlugin();

protected: // SmfPLugin
    plugframe::Bundle4PluginInterface *createImplementation() override;
    void bindServicesImplementations() override;

protected: // SmfDisplayServiceInterface
    void print(const QString& msg) override;
    void log(const QString& msg) override;
    void statusMessage(const QString& msg) override;
    void clearStatusMessages() override;

protected: // SmfGuiBuilderServiceInterface
    void addGuiController(const plugframe::QspGuiPageController& controller) override;
    void removeAllPages(const plugframe::QspGuiPageController& controller) override;
    void setMainWindowTitle(const QString& title) override;

private:
    QspGuiDisplayService m_displayServiceImpl;
    QspGuiBuilderService m_guiBuilderServiceImpl;
};

#endif // GUIDISPLAYPLUGIN_H
