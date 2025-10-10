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


#include <iostream>
#include "guiconsole.h"
#include "guiconsolefactory.h"
#include "ui/guiconsolecontroller.h"
#include "bundle/bundlecontext.h"
#include "service-int/systemserviceinterface.h"

using namespace elekdom::plugframe;
using namespace elekdom::plugframe::core::bundle;
using namespace elekdom::plugframe::guiconsole::bundle;
using namespace elekdom::plugframe::guidisplay::service;

GuiConsole::GuiConsole():
    BundleImplementation{"Console"}
{

}

GuiConsole::~GuiConsole()
{

}

BundleFactory *GuiConsole::createFactory()
{
    return new factory::GuiConsoleFactory;
}

void GuiConsole::_start(core::bundle::QspBundleContext bundleContext)
{
    BundleImplementation::_start(bundleContext);
    buildGui();
}

void GuiConsole::buildGui()
{
    GuiBuilderServiceInterface *builderGuiServiceItf{bundleContext()->getService<GuiBuilderServiceInterface>(GuiBuilderServiceInterface::serviceName())};

    // MainWindow's  title
    builderGuiServiceItf->setMainWindowTitle(guiTitle());

    // Build base console's Controller/View
    buildConsoleController(builderGuiServiceItf);

    // Build specific Controller/Views sets
    buildControllerViews(builderGuiServiceItf);
}

void GuiConsole::buildConsoleController(guidisplay::service::GuiBuilderServiceInterface *builderGuiServiceItf)
{
    factory::GuiConsoleFactory &factory{dynamic_cast<factory::GuiConsoleFactory&>(getFactory())};
    SystemServiceInterface *systemServiceItf{bundleContext()->getService<SystemServiceInterface>(SystemServiceInterface::serviceName())};
    GuiConsoleController *ptrCtrl{factory.createGuiConsoleController(systemServiceItf)};
    core::gui::QspGuiPageController pageCtrl{ptrCtrl};

    pageCtrl->buildViews();
    builderGuiServiceItf->addGuiController(pageCtrl);
    pageCtrl->currentCtrl();
}

void GuiConsole::buildControllerViews(GuiBuilderServiceInterface *builderGuiServiceItf)
{
    Q_UNUSED(builderGuiServiceItf)
}

QString GuiConsole::guiTitle()
{
    return QStringLiteral("PlugFrame");
}

PF_qtServiceInterface_DEF(GuiConsole)
