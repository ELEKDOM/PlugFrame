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


#include "usersplugin.h"
#include "users.h"

using namespace elekdom::plugframe::users::plugin;

UsersPlugin::UsersPlugin()
{

}

UsersPlugin::~UsersPlugin()
{

}

elekdom::plugframe::core::bundle::Bundle4PluginInterface *UsersPlugin::createImplementation()
{
    return new users::bundle::Users;
}

void UsersPlugin::bindServicesImplementations()
{
    plugframe::core::service::QspServiceImplementationInterface serviceImplementationItf;

    serviceImplementationItf = implementation()->getServiceImplementation(plugframe::users::service::LoginServiceInterface::serviceName());
    m_loginServiceImpl = serviceImplementationItf.dynamicCast<service::LoginService>();
}

void UsersPlugin::login(QString frontendItf,
                        QString frontendIp,
                        QString identifier,
                        QString password,
                        service::LoginServiceInterface::LoginStatus& loginStatus,
                        quint32 &sessionId,
                        QString& profil)
{
    m_loginServiceImpl->login(frontendItf,
                              frontendIp,
                              identifier,
                              password,
                              loginStatus,
                              sessionId,
                              profil);
}

void UsersPlugin::logout(quint32 sessionId)
{
    m_loginServiceImpl->logout(sessionId);
}

QString UsersPlugin::absoluteUserConfFileName(const QString &profil)
{
    return m_loginServiceImpl->absoluteUserConfFileName(profil);
}
