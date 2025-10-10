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


#include "displayfactory.h"
#include "bundle/bundle.h"
#include "displayservice.h"
#include "display.h"
#include "service-int/displayserviceinterface.h"

using namespace elekdom::plugframe;
using namespace elekdom::plugframe::display;
using namespace elekdom::plugframe::display::factory;

DisplayFactory::DisplayFactory()
{

}

DisplayFactory::~DisplayFactory()
{

}

service::DisplayService *DisplayFactory::createDisplayService(core::bundle::BundleImplementation *implementation)
{
    return new service::DisplayService{implementation};
}

core::service::ServiceImplementationInterface *DisplayFactory::createServiceImplementation(core::bundle::BundleImplementation *implementation,
                                                                                           const QString &sName,
                                                                                           const QString &serviceVersion)
{
    core::service::ServiceImplementationInterface *ret{nullptr};

    if (service::DisplayServiceInterface::serviceName() == sName)
    {
        if (plugframe::core::plugin::ServiceInterface::V_100() == serviceVersion)
        {
            ret = createDisplayService(implementation);
        }
    }

    return ret;
}
