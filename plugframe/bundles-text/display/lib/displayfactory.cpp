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
#include "displayservice.h"
#include "service-int/displayserviceinterface.h"

DisplayFactory::DisplayFactory()
{

}

DisplayFactory::~DisplayFactory()
{

}

DisplayService *DisplayFactory::createDisplayService(plugframe::BundleImplementation *implementation)
{
    return new DisplayService{implementation};
}

plugframe::ServiceImplementationInterface *DisplayFactory::createServiceImplementation(plugframe::BundleImplementation *implementation,
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

    return ret;
}
