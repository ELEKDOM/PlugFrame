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

#include "guiconfiguratorengine.h"
#include "guiconfiguratorenginefactory.h"
#include "gui/guidevelopermodecontrollertype.h"
#include "service-int/guiconfiguratorengineserviceinterface.h"

GuiConfiguratorEngine::GuiConfiguratorEngine():
    m_hasDeveloperMode{false}
{

}

GuiConfiguratorEngine::~GuiConfiguratorEngine()
{

}

QStringList GuiConfiguratorEngine::getLauncherConfFileList(const QString &projectName, const QString &applicationName)
{
    QStringList ret;

    //...

    return ret;
}

QStringList GuiConfiguratorEngine::getBundleConfFileList(const QString &projectName, const QString &applicationName, const QString &bundleName)
{
    QStringList ret;

    //...

    return ret;
}

plugframe::BundleFactory *GuiConfiguratorEngine::createFactory()
{
    return new GuiConfiguratorEngineFactory;
}

plugframe::ServiceInterface *GuiConfiguratorEngine::qtServiceInterface(const QString &sName)
{
    plugframe::ServiceInterface *ret{GuiEngine::qtServiceInterface(sName)};

    if (!ret && configurator::GuiConfiguratorEngineServiceInterface::serviceName() == sName)
    {
        ret = qobject_cast<configurator::GuiConfiguratorEngineServiceInterface*>(getQplugin());
    }

    return ret;
}

void GuiConfiguratorEngine::postRegister(const plugframe::QspGuiPageController &controller)
{
    if (controller->ctrlType() == configurator::GuiDeveloperModeControllerType::s_ctrlType)
    {
        controller->currentCtrl();
        m_hasDeveloperMode = true;
    }

}

bool GuiConfiguratorEngine::menuNames(const plugframe::QspGuiPageController &controller, plugframe::GuiMainMenuNames &menuNames)
{
    bool ret{GuiEngine::menuNames(controller,menuNames)};

    if(!ret)
    {
        if (controller->ctrlType() == configurator::GuiDeveloperModeControllerType::s_ctrlType)
        {
            ret = true;
            menuNames.functionalDomainName(QObject::tr("Mode Selector"));
            if (controller->ctrlType() == configurator::GuiDeveloperModeControllerType::s_ctrlType)
            {
                menuNames.controllerName(QObject::tr("&Developer"));
            }
            /*
            else if (controller->ctrlType() == ::s_ctrlType)
            {
                menuNames.controllerName(QObject::tr("&Release Manager"));
            }
            else if (controller->ctrlType() == ::s_ctrlType)
            {
                menuNames.controllerName(QObject::tr("&End User"));
            }
            */
        }
    }

    return ret;
}

QString GuiConfiguratorEngine::guiTitle()
{
    return QStringLiteral("PlugFrame Configurator");
}


