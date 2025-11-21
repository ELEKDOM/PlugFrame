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

#ifndef USERS_H
#define USERS_H

#include <QHash>
#include "bundle/bundleimplementation.h"
#include "service-int/loginserviceinterface.h"
#include "loggeduser.h"

class Users: public plugframe::BundleImplementation
{
public:
    Users();
    ~Users() override;

public:
    void login(QString                                      frontendItf,
               QString                                      frontendIp,
               QString                                      identifier,
               QString                                      password,
               plugframe::LoginServiceInterface::LoginStatus& loginStatus,
               quint32&                                     sessionId,
               QString&                                     profil);
    void logout(quint32 sessionId);

protected:
    plugframe::BundleFactory* createFactory() override;
    plugframe::ServiceInterface *qtServiceInterface(const QString& sName) override;

private:
    plugframe::LoginServiceInterface::LoginStatus checkLogin(QString identifier,
                                                             QString password,
                                                             QString frontendItf,
                                                             QString frontendIp,
                                                             QString& profil);
    quint32 generateSessionId();
    void addLoggedUser(const quint32& sessionId,
                       const QString& frontendItf,
                       const QString& identifier);

private:
    QHash<quint32, QspLoggedUser> m_loggedUsers;
};
#endif // USERS_H
