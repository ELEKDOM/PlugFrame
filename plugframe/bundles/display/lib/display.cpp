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
#include "display.h"
#include "displayfactory.h"
#include "service-int/displayserviceinterface.h"

using namespace elekdom::plugframe;
using namespace elekdom::plugframe::display;

bundle::Display::Display():
    core::bundle::BundleImplementation{"Display"}
{

}

bundle::Display::~Display()
{

}

void bundle::Display::print(const QString &msg)
{
    QMutexLocker lock(&m_mutex);

    std::cout << msg.toStdString();
}

core::bundle::BundleFactory *bundle::Display::createFactory()
{
    return new factory::DisplayFactory;
}

core::plugin::ServiceInterface *bundle::Display::qtServiceInterface(const QString &sName)
{
    core::plugin::ServiceInterface *ret{nullptr};

    if (service::DisplayServiceInterface::serviceName() == sName)
    {
        ret = qobject_cast<service::DisplayServiceInterface*>(getQplugin());
    }

    return ret;
}
