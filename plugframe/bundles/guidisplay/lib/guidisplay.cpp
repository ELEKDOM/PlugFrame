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


#include "guidisplay.h"
#include "guidisplayfactory.h"
#include "ui/guihook.h"
#include "ui/guilogscontroller.h"
#include "service-int/displayserviceinterface.h"
#include "service-int/guibuilderserviceinterface.h"
#include "service-int/systemserviceinterface.h"
#include "bundle/bundlecontext.h"

using namespace elekdom::plugframe::display::service;
using namespace elekdom::plugframe::guidisplay::service;
using namespace elekdom::plugframe::core::bundle;
using namespace elekdom::plugframe::guidisplay::bundle;

GuiDisplay::GuiDisplay():
    BundleImplementation{"Display"},
    m_guiHook{nullptr}
{
}

GuiDisplay::~GuiDisplay()
{
}

void GuiDisplay::log(const QString &msg)
{
    m_guiHook->log(msg);
}

void GuiDisplay::statusMessage(const QString &msg)
{
    m_guiHook->statusMessage(msg);
}

void GuiDisplay::clearStatusMessages()
{
    m_guiHook->clearStatusMessages();
}

void GuiDisplay::addGuiController(const core::gui::QspGuiPageController &controller)
{
    m_guiHook->addGuiController(controller);
}

void GuiDisplay::removeAllPages(const core::gui::QspGuiPageController &controller)
{
    m_guiHook->removeAllPages(controller);
}

void GuiDisplay::setMainWindowTitle(const QString &title)
{
    m_guiHook->setMainWindowTitle(title);
}

void GuiDisplay::closeApp()
{
    framework::service::SystemServiceInterface *systemServiceItf;

    systemServiceItf = bundleContext()->getService<framework::service::SystemServiceInterface>(framework::service::SystemServiceInterface::serviceName());

    if (systemServiceItf != nullptr)
    {
        systemServiceItf->quit();
    }
}

BundleFactory *GuiDisplay::createFactory()
{
    return new factory::GuiDisplayFactory;
}

elekdom::plugframe::core::plugin::ServiceInterface *GuiDisplay::qtServiceInterface(const QString &sName)
{
    core::plugin::ServiceInterface *ret{nullptr};

    if (DisplayServiceInterface::serviceName() == sName)
    {
        ret = qobject_cast<DisplayServiceInterface*>(getQplugin());
    }
    else if (GuiBuilderServiceInterface::serviceName() == sName)
    {
        ret = qobject_cast<GuiBuilderServiceInterface*>(getQplugin());
    }

    return ret;
}

void GuiDisplay::_start(QspBundleContext bundleContext)
{
    BundleImplementation::_start(bundleContext);
    buildGui();
}

/// \brief GuiDisplay::buildGui
/// \details basic Gui is a mainwindow with StackedWidget as central Widget
/// basic page view/controller are build for logs view
void GuiDisplay::buildGui()
{
    factory::GuiDisplayFactory &factory{dynamic_cast<factory::GuiDisplayFactory&>(getFactory())};
    QspGuiPageController pageCtrl{factory.createLogsPageController()};

    // Gui build & init
    m_guiHook = factory.createGuiHook(factory.createGui(),*this);
    m_guiHook->initGui();
    pageCtrl->buildViews();
    addGuiController(pageCtrl);
    pageCtrl->currentCtrl();

    // Gui on screen
    m_guiHook->showGui();
}


