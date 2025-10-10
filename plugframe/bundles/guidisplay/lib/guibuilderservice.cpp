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


#include "service-int/guibuilderserviceinterface.h"
#include "guibuilderservice.h"
#include "guidisplay.h"

using namespace elekdom::plugframe::guidisplay::service;
using namespace elekdom::plugframe::guidisplay::bundle;

GuiBuilderService::GuiBuilderService(core::bundle::BundleImplementation *implementation):
    core::service::ServiceImplementation{implementation}
{}

GuiBuilderService::~GuiBuilderService()
{

}

void GuiBuilderService::addGuiController(const core::gui::QspGuiPageController &controller)
{
    GuiDisplay *console{dynamic_cast<GuiDisplay*>(implementation())};

    console->addGuiController(controller);
}

void GuiBuilderService::removeAllPages(const core::gui::QspGuiPageController &controller)
{
    GuiDisplay *console{dynamic_cast<GuiDisplay*>(implementation())};

    console->removeAllPages(controller);
}

void GuiBuilderService::setMainWindowTitle(const QString &title)
{
    GuiDisplay *console{dynamic_cast<GuiDisplay*>(implementation())};

    console->setMainWindowTitle(title);
}

QString GuiBuilderService::serviceName()
{
    return guidisplay::service::GuiBuilderServiceInterface::serviceName();
}
