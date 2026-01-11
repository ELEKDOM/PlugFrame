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

#include "guidisplayplugin.h"
#include "guidisplay.h"
#include "guidisplayservice.h"
#include "guibuilderservice.h"

GuiDisplayPlugin::GuiDisplayPlugin()
{

}

GuiDisplayPlugin::~GuiDisplayPlugin()
{

}

plugframe::Bundle4PluginInterface *GuiDisplayPlugin::createImplementation()
{
    return new GuiDisplay;
}

void GuiDisplayPlugin::bindServicesImplementations()
{
    plugframe::QspServiceImplementationInterface serviceImplementationItf;

    serviceImplementationItf = implementation()->getServiceImplementation(plugframe::DisplayServiceInterface::serviceName());
    m_displayServiceImpl = serviceImplementationItf.dynamicCast<GuiDisplayService>();

    serviceImplementationItf = implementation()->getServiceImplementation(plugframe::GuiBuilderServiceInterface::serviceName());
    m_guiBuilderServiceImpl = serviceImplementationItf.dynamicCast<GuiBuilderService>();
}

void GuiDisplayPlugin::print(const QString &msg)
{
    Q_UNUSED(msg)
}

void GuiDisplayPlugin::log(const QString &msg)
{
    m_displayServiceImpl->log(msg);
}

void GuiDisplayPlugin::statusMessage(const QString &msg)
{
    m_displayServiceImpl->statusMessage(msg);
}

void GuiDisplayPlugin::clearStatusMessages()
{
    m_displayServiceImpl->clearStatusMessages();
}

void GuiDisplayPlugin::addGuiController(const plugframe::QspGuiPageController &controller)
{
    m_guiBuilderServiceImpl->addGuiController(controller);
}

void GuiDisplayPlugin::removeAllPages(const plugframe::QspGuiPageController &controller)
{
    m_guiBuilderServiceImpl->removeAllPages(controller);
}

void GuiDisplayPlugin::setMainWindowTitle(const QString &title)
{
    m_guiBuilderServiceImpl->setMainWindowTitle(title);
}
