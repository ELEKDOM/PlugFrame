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

#include "guidisplayfactory.h"
#include "guidisplay.h"
#include "guidisplayservice.h"
#include "guibuilderservice.h"
#include "ui/guihook.h"
#include "ui/gui.h"
#include "ui/guilogscontroller.h"
#include "service-int/displayserviceinterface.h"
#include "service-int/guibuilderserviceinterface.h"

GuiDisplayFactory::GuiDisplayFactory()
{

}

GuiDisplayFactory::~GuiDisplayFactory()
{

}

GuiDisplayService *GuiDisplayFactory::createDisplayService(plugframe::BundleImplementation *implementation)
{
    return new GuiDisplayService{implementation};
}

GuiBuilderService *GuiDisplayFactory::createBuilderService(plugframe::BundleImplementation *implementation)
{
    return new GuiBuilderService{implementation};
}

plugframe::ServiceImplementationInterface *GuiDisplayFactory::createServiceImplementation(plugframe::BundleImplementation *implementation,
                                                                                          const QString &sName,
                                                                                          const QString &serviceVersion)
{
    plugframe::ServiceImplementationInterface *ret{nullptr};

    if (plugframe::DisplayServiceInterface::serviceName() == sName)
    {
        if (plugframe::ServiceInterface::V_100() == serviceVersion)
        {
            ret = createDisplayService(implementation);
        }
    }
    else if(plugframe::GuiBuilderServiceInterface::serviceName() == sName)
    {
        if (plugframe::ServiceInterface::V_100() == serviceVersion)
        {
            ret = createBuilderService(implementation);
        }
    }

    return ret;
}

Gui *GuiDisplayFactory::createGui()
{
    return new Gui;
}

GuiHook *GuiDisplayFactory::createGuiHook(Gui* parent,GuiDisplay& bundle)
{
    return new GuiHook{parent, bundle};
}

GuiLogsController *GuiDisplayFactory::createLogsPageController()
{
    return new GuiLogsController;
}

