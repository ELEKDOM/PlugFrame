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


#include "displayplugin.h"
#include "displayservice.h"
#include "display.h"

using namespace elekdom::plugframe;
using namespace elekdom::plugframe::display::plugin;

DisplayPlugin::DisplayPlugin()
{

}

DisplayPlugin::~DisplayPlugin()
{

}

core::bundle::Bundle4PluginInterface *DisplayPlugin::createImplementation()
{
    return new bundle::Display;
}

void DisplayPlugin::bindServicesImplementations()
{
    core::service::QspServiceImplementationInterface serviceImplementationItf;

    serviceImplementationItf = implementation()->getServiceImplementation(DisplayServiceInterface::serviceName());
    m_displayServiceImpl = serviceImplementationItf.dynamicCast<service::DisplayService>();
}

void DisplayPlugin::print(const QString &msg)
{
    m_displayServiceImpl->print(msg);
}

void DisplayPlugin::log(const QString &msg)
{
    m_displayServiceImpl->log(msg);
}

void DisplayPlugin::statusMessage(const QString &msg)
{
    // only for gui
    Q_UNUSED(msg)
}

void DisplayPlugin::clearStatusMessages()
{
    // only for gui
}
