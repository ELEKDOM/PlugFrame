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
#include "guicontrollerviewsloader.h"
#include "guicontrollerviewsfactory.h"
#include "service-int/guiregistercontrollerserviceinterface.h"
#include "gui/guipagecontroller.h"

plugframe::GuiControllerViewsLoader::GuiControllerViewsLoader(QString logBundleName):
    plugframe::BundleImplementation{logBundleName}
{

}

plugframe::GuiControllerViewsLoader::~GuiControllerViewsLoader()
{

}

void plugframe::GuiControllerViewsLoader::_start(QspBundleContext bundleContext)
{
    BundleImplementation::_start(bundleContext);
    buildRegisterGuiController();
}

void plugframe::GuiControllerViewsLoader::buildRegisterGuiController()
{
    plugframe::GuiRegisterControllerServiceInterface *registerControllerServiceItf;
    registerControllerServiceItf = bundleContext()->getService<plugframe::GuiRegisterControllerServiceInterface>(plugframe::GuiRegisterControllerServiceInterface::serviceName());

    if (registerControllerServiceItf != nullptr)
    {
        GuiControllerViewsFactory &factory{dynamic_cast<GuiControllerViewsFactory&>(getFactory())};
        QspGuiPageController guiCtrl;

        guiCtrl.reset(factory.createGuiController());
        if (!guiCtrl.isNull())
        {
            postBuildController(guiCtrl);
            guiCtrl->buildViews();
            registerControllerServiceItf->registerController(guiCtrl);
        }
    }
}

void plugframe::GuiControllerViewsLoader::postBuildController(QspGuiPageController guiCtrl)
{
    Q_UNUSED(guiCtrl)
}

PF_qtServiceInterface_DEF(plugframe::GuiControllerViewsLoader)