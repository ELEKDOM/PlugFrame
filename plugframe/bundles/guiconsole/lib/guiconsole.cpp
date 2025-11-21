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

#include "guiconsole.h"
#include "guiconsolefactory.h"
#include "ui/guiconsolecontroller.h"
#include "bundle/bundlecontext.h"
#include "service-int/systemserviceinterface.h"

GuiConsole::GuiConsole():
    BundleImplementation{"Console"}
{

}

GuiConsole::~GuiConsole()
{

}

plugframe::BundleFactory *GuiConsole::createFactory()
{
    return new GuiConsoleFactory;
}

void GuiConsole::_start(plugframe::QspBundleContext bundleContext)
{
    BundleImplementation::_start(bundleContext);
    buildGui();
}

void GuiConsole::buildGui()
{
    plugframe::GuiBuilderServiceInterface *builderGuiServiceItf{bundleContext()->getService<plugframe::GuiBuilderServiceInterface>(plugframe::GuiBuilderServiceInterface::serviceName())};

    // MainWindow's  title
    builderGuiServiceItf->setMainWindowTitle(guiTitle());

    // Build base console's Controller/View
    buildConsoleController(builderGuiServiceItf);

    // Build specific Controller/Views sets
    buildControllerViews(builderGuiServiceItf);
}

void GuiConsole::buildConsoleController(plugframe::GuiBuilderServiceInterface *builderGuiServiceItf)
{
    GuiConsoleFactory &factory{dynamic_cast<GuiConsoleFactory&>(getFactory())};
    plugframe::SystemServiceInterface *systemServiceItf{bundleContext()->getService<plugframe::SystemServiceInterface>(plugframe::SystemServiceInterface::serviceName())};
    GuiConsoleController *ptrCtrl{factory.createGuiConsoleController(systemServiceItf)};
    plugframe::QspGuiPageController pageCtrl{ptrCtrl};

    pageCtrl->buildViews();
    builderGuiServiceItf->addGuiController(pageCtrl);
    pageCtrl->currentCtrl();
}

void GuiConsole::buildControllerViews(plugframe::GuiBuilderServiceInterface *builderGuiServiceItf)
{
    Q_UNUSED(builderGuiServiceItf)
}

QString GuiConsole::guiTitle()
{
    return QStringLiteral("PlugFrame");
}

PF_qtServiceInterface_DEF(GuiConsole)
