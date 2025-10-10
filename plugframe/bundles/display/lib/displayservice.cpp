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


#include "displayservice.h"
#include "display.h"
#include "service-int/displayserviceinterface.h"

using namespace elekdom::plugframe::display;
using namespace elekdom::plugframe::display::service;

DisplayService::DisplayService(core::bundle::BundleImplementation *implementation):
    core::service::ServiceImplementation{implementation}
{

}

DisplayService::~DisplayService()
{

}

void DisplayService::print(const QString &msg)
{
    bundle::Display *logger{dynamic_cast<bundle::Display*>(implementation())};

    logger->print(msg);
}

void DisplayService::log(const QString &msg)
{
    print(msg);
}

QString DisplayService::serviceName()
{
    return DisplayServiceInterface::serviceName();
}
