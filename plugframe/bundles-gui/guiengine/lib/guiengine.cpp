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

#include "guiengine.h"
#include "guienginefactory.h"
#include "bundle/bundlecontext.h"
#include "service-int/guibuilderserviceinterface.h"
#include "service-int/guiregistercontrollerserviceinterface.h"
#include "gui/guilogscontrollertype.h"
#include "gui/guiconsolecontrollertype.h"

GuiEngine::GuiEngine():
    BundleImplementation{"GuiEngine"}
{

}

GuiEngine::~GuiEngine()
{

}

void GuiEngine::registerController(const plugframe::QspGuiPageController &controller)
{
    plugframe::GuiMainMenuNames names;
    plugframe::GuiBuilderServiceInterface *guiServiceItf{builderGuiServiceItf()};

    preRegister(controller);

    if (guiServiceItf)
    {
        menuNames(controller,names);
        guiServiceItf->addGuiController(controller,names);
    }

    postRegister(controller);
}

void GuiEngine::preRegister(const plugframe::QspGuiPageController &controller)
{
    Q_UNUSED(controller)
}

void GuiEngine::postRegister(const plugframe::QspGuiPageController &controller)
{
    controller->currentCtrl();
}

bool GuiEngine::menuNames(const plugframe::QspGuiPageController &controller, plugframe::GuiMainMenuNames &menuNames)
{
    bool ret{false};

    menuNames.reset();
    if (controller->ctrlType() == plugframe::GuiLogsControllerType::s_ctrlType ||
        controller->ctrlType() == plugframe::GuiConsoleControllerType::s_ctrlType)
    {
        ret = true;
        menuNames.functionalDomainName(QObject::tr("Plateforme"));
        if (controller->ctrlType() == plugframe::GuiLogsControllerType::s_ctrlType)
        {
            menuNames.controllerName(QObject::tr("&Journal"));
        }
        else if (controller->ctrlType() == plugframe::GuiConsoleControllerType::s_ctrlType)
        {
            menuNames.controllerName(QObject::tr("&Console"));
        }
    }

    return ret;
}

plugframe::BundleFactory *GuiEngine::createFactory()
{
    return new GuiEngineFactory;
}

plugframe::ServiceInterface *GuiEngine::qtServiceInterface(const QString &sName)
{
    plugframe::ServiceInterface *ret{nullptr};

    if (plugframe::GuiRegisterControllerServiceInterface::serviceName() == sName)
    {
        ret = qobject_cast<plugframe::GuiRegisterControllerServiceInterface*>(getQplugin());
    }

    return ret;
}

void GuiEngine::_start(plugframe::QspBundleContext bundleContext)
{
    BundleImplementation::_start(bundleContext);

    plugframe::GuiBuilderServiceInterface *guiServiceItf{builderGuiServiceItf()};

    // MainWindow's  title
    if (guiServiceItf)
    {
        guiServiceItf->setMainWindowTitle(guiTitle());
    }
}

QString GuiEngine::guiTitle()
{
    return QStringLiteral("GuiPlugFrame");
}

plugframe::GuiBuilderServiceInterface *GuiEngine::builderGuiServiceItf()
{
    return bundleContext()->getService<plugframe::GuiBuilderServiceInterface>(plugframe::GuiBuilderServiceInterface::serviceName());
}

