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


#include "bundle/bundle.h"
#include "usersfactory.h"
#include "loggeduser.h"
#include "loginservice.h"
#include "users.h"
#include "service-int/loginserviceinterface.h"

using namespace elekdom::plugframe;
using namespace elekdom::plugframe::users;
using namespace elekdom::plugframe::users::factory;


UsersFactory::UsersFactory()
{

}

UsersFactory::~UsersFactory()
{

}

core::service::ServiceImplementationInterface *UsersFactory::createServiceImplementation(core::bundle::BundleImplementation *implementation,
                                                                                         const QString &sName,
                                                                                         const QString &serviceVersion)
{
    core::service::ServiceImplementationInterface *ret{nullptr};

    if (service::LoginServiceInterface::serviceName() == sName)
    {
        if (plugframe::core::plugin::ServiceInterface::V_100() == serviceVersion)
        {
            ret = createLoginService(implementation);
        }
    }

    return ret;
}

service::LoginService *UsersFactory::createLoginService(core::bundle::BundleImplementation *implementation)
{
    return new service::LoginService{implementation};
}

bundle::LoggedUser *UsersFactory::createLoggedUser(const QString &frontendItf,const QString &identifier,const quint32& sessionId)
{
    return new bundle::LoggedUser{frontendItf,identifier,sessionId};
}


