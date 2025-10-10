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
#include "guidisplay_forward.h"

namespace elekdom
{
namespace plugframe
{
namespace guidisplay
{
namespace plugin
{

class GuiDisplayPlugin : public core::plugin::Plugin,
                         public display::service::DisplayServiceInterface,
                         public service::GuiBuilderServiceInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "elekdom.plugframe.guidisplay.plugin" FILE "../guidisplaybundle.json")
    Q_INTERFACES(elekdom::plugframe::core::plugin::BundleInterface
                 elekdom::plugframe::display::service::DisplayServiceInterface
                 elekdom::plugframe::guidisplay::service::GuiBuilderServiceInterface)

private:
    QSharedPointer<service::GuiDisplayService> m_displayServiceImpl;
    QSharedPointer<service::GuiBuilderService> m_guiBuilderServiceImpl;

public:
    GuiDisplayPlugin();
    virtual ~GuiDisplayPlugin();

protected: // SmfPLugin
    core::bundle::Bundle4PluginInterface *createImplementation() override;
    void bindServicesImplementations() override;

protected: // SmfDisplayServiceInterface
    void print(const QString& msg) override;
    void log(const QString& msg) override;
    void statusMessage(const QString& msg) override;
    void clearStatusMessages() override;

protected: // SmfGuiBuilderServiceInterface
    void addGuiController(const core::gui::QspGuiPageController& controller) override;
    void removeAllPages(const core::gui::QspGuiPageController& controller) override;
    void setMainWindowTitle(const QString& title) override;
};

} //namespace plugin
} //namespace guidisplay
} //namespace plugframe
} //namespace elekdom

#endif // GUIDISPLAYPLUGIN_H
