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

#ifndef LOGINSERVICE_H
#define LOGINSERVICE_H

#include <QSharedPointer>
#include "service/serviceimplementation.h"
#include "service-int/loginserviceinterface.h"

class LoginService : public plugframe::ServiceImplementation
{
public:
    LoginService(plugframe::BundleImplementation *implementation);
    ~LoginService() override;

public: // service interface implementation
    void login(QString                             frontendItf,
               QString                             frontendIp,
               QString                             identifier,
               QString                             password,
               plugframe::LoginServiceInterface::LoginStatus& loginStatus,
               quint32&                            sessionId,
               QString&                            profil);
    void logout(quint32 sessionId);
    QString absoluteUserConfFileName(const QString& profil);

protected:
    QString serviceName() override;
};
using QspLoginService = QSharedPointer<LoginService>;
#endif // LOGINSERVICE_H
