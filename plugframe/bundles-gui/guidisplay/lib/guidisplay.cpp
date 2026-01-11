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
#include "service-int/displayserviceinterface.h"
#include "service-int/guibuilderserviceinterface.h"
#include "service-int/systemserviceinterface.h"
#include "bundle/bundlecontext.h"

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

void GuiDisplay::addGuiController(const plugframe::QspGuiPageController &controller)
{
    m_guiHook->addGuiController(controller);
}

void GuiDisplay::removeAllPages(const plugframe::QspGuiPageController &controller)
{
    m_guiHook->removeAllPages(controller);
}

void GuiDisplay::setMainWindowTitle(const QString &title)
{
    m_guiHook->setMainWindowTitle(title);
}

void GuiDisplay::closeApp()
{
    plugframe::SystemServiceInterface *systemServiceItf;

    systemServiceItf = bundleContext()->getService<plugframe::SystemServiceInterface>(plugframe::SystemServiceInterface::serviceName());

    if (systemServiceItf != nullptr)
    {
        systemServiceItf->quit();
    }
}

plugframe::BundleFactory *GuiDisplay::createFactory()
{
    return new GuiDisplayFactory;
}

plugframe::ServiceInterface *GuiDisplay::qtServiceInterface(const QString &sName)
{
    plugframe::ServiceInterface *ret{nullptr};

    if (plugframe::DisplayServiceInterface::serviceName() == sName)
    {
        ret = qobject_cast<plugframe::DisplayServiceInterface*>(getQplugin());
    }
    else if (plugframe::GuiBuilderServiceInterface::serviceName() == sName)
    {
        ret = qobject_cast<plugframe::GuiBuilderServiceInterface*>(getQplugin());
    }

    return ret;
}

void GuiDisplay::_start(plugframe::QspBundleContext bundleContext)
{
    BundleImplementation::_start(bundleContext);
    buildGui();
}

/// \brief GuiDisplay::buildGui
/// \details basic Gui is a mainwindow with StackedWidget as central Widget
/// basic page view/controller are build for logs view
void GuiDisplay::buildGui()
{
    GuiDisplayFactory &factory{dynamic_cast<GuiDisplayFactory&>(getFactory())};
    plugframe::QspGuiPageController pageCtrl{factory.createLogsPageController()};

    // Gui build & init
    m_guiHook = factory.createGuiHook(factory.createGui(),*this);
    m_guiHook->initGui();
    pageCtrl->buildViews();
    addGuiController(pageCtrl);
    pageCtrl->currentCtrl();

    // Gui on screen
    m_guiHook->showGui();
}


