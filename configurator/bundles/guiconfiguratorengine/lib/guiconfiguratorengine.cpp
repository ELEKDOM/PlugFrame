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
#include "gui/guilaunchersconfiguratorcontrollertype.h"
#include "gui/guibundleconfiguratorcontrollertype.h"
#include "service-int/guiconfiguratorengineserviceinterface.h"
#include "logger/pflog.h"

GuiConfiguratorEngine::GuiConfiguratorEngine():
    m_hasDeveloperMode{false}
{

}

GuiConfiguratorEngine::~GuiConfiguratorEngine()
{

}

QStringList GuiConfiguratorEngine::getLauncherConfFileList(const QString& confFilesRepository,const QString &applicationName)
{
    QStringList ret;
    bool found{false};

    for (auto i=0;i<m_registeredLaunchersConfiguratorControllers.size() && !found; i++)
    {
        ret = m_registeredLaunchersConfiguratorControllers[i]->getLauncherConfFileList(confFilesRepository,applicationName);
        found = !ret.isEmpty();
    }

    pfInfo5(getLogBundleName()) << QObject::tr("Configuration files for launcher [") << applicationName << "] :" << ret;

    return ret;
}

QStringList GuiConfiguratorEngine::getBundleConfFileList(const QString& confFilesRepository,const QString &bundleName)
{
    QStringList ret;

    bool found{false};

    for (auto i=0;i<m_registeredBundleConfiguratorControllers.size() && !found; i++)
    {
        ret = m_registeredBundleConfiguratorControllers[i]->getBundleConfFileList(confFilesRepository,bundleName);
        found = !ret.isEmpty();
    }

    pfInfo5(getLogBundleName()) << QObject::tr("Configuration files for bundle [") << bundleName << "] :" << ret;

    return ret;
}

bool GuiConfiguratorEngine::hasLauncherConfFiles(const QString &applicationName)
{
    bool ret{false};

    for (auto i=0;i<m_registeredLaunchersConfiguratorControllers.size() && !ret; i++)
    {
        ret = m_registeredLaunchersConfiguratorControllers[i]->hasLauncherConfFiles(applicationName);
    }

    return ret;
}

bool GuiConfiguratorEngine::hasBundleConfFiles(const QString &bundleName)
{
    bool ret{false};

    for (auto i=0;i<m_registeredBundleConfiguratorControllers.size() && !ret; i++)
    {
        ret = m_registeredBundleConfiguratorControllers[i]->hasBundleConfFiles(bundleName);
    }

    return ret;
}

void GuiConfiguratorEngine::editLauncherConfFiles(const QString &projectSourcePath,
                                                  const QString &projectName,
                                                  const QString &applicationName,
                                                  const QString &confFilesRepository)
{
    bool editing{false};

    for (auto i=0;i<m_registeredLaunchersConfiguratorControllers.size() && !editing; i++)
    {
        editing = m_registeredLaunchersConfiguratorControllers[i]->editLauncherConfFiles(projectSourcePath,
                                                                                         projectName,
                                                                                         applicationName,
                                                                                         confFilesRepository);
    }
}

void GuiConfiguratorEngine::editBundleConfFiles(const QString &projectSourcePath,
                                                const QString &projectName,
                                                const QString &applicationName,
                                                const QString &bundleName,
                                                const QString &confFilesRepository)
{
    bool editing{false};

    for (auto i=0;i<m_registeredBundleConfiguratorControllers.size() && !editing; i++)
    {
        editing = m_registeredBundleConfiguratorControllers[i]->editBundleConfFiles(projectSourcePath,
                                                                                    projectName,
                                                                                    applicationName,
                                                                                    bundleName,
                                                                                    confFilesRepository);
    }
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
    plugframe::GuiControllerType ctrlT{controller->ctrlType()};

    if (ctrlT == configurator::GuiDeveloperModeControllerType::s_ctrlType)
    {
        controller->currentCtrl();
        m_hasDeveloperMode = true;
    }
    else if (ctrlT == configurator::GuiLaunchersConfiguratorControllerType::s_ctrlType)
    {
        appendLaunchersConfigurator(controller.dynamicCast<configurator::GuiLaunchersConfiguratorController>());
        pfDebug5(getLogBundleName()) << "Append a launcher configurator";
    }
    else if (ctrlT == configurator::GuiBundleConfiguratorControllerType::s_ctrlType)
    {
        appendBundleConfigurator(controller.dynamicCast<configurator::GuiBundleConfiguratorController>());
        pfDebug5(getLogBundleName()) << "Append a bundle configurator";
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

void GuiConfiguratorEngine::appendLaunchersConfigurator(configurator::QspGuiLaunchersConfiguratorController controller)
{
    m_registeredLaunchersConfiguratorControllers.append(controller);
}

void GuiConfiguratorEngine::appendBundleConfigurator(configurator::QspGuiBundleConfiguratorController controller)
{
    m_registeredBundleConfiguratorControllers.append(controller);
}


