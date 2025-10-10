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


#ifndef LOGINSERVICEINTERFACE_H
#define LOGINSERVICEINTERFACE_H

#include "service-int/serviceinterface.h"

namespace elekdom
{
namespace plugframe
{
namespace users
{
namespace service
{

class LoginServiceInterface : public plugframe::core::plugin::ServiceInterface
{
public:
    static QString serviceName() {return QStringLiteral("LoginServiceInterface");}
    enum class LoginStatus : quint8 {Ok,
                                     PasswordErr,
                                     IdentifierErr};

public:
    ~LoginServiceInterface() override {}

public: // service interface definition = 0

    // sigin attempt
    virtual void login(QString      frontendItf,
                       QString      frontendIp,
                       QString      identifier,
                       QString      password,
                       LoginStatus& loginStatus,
                       quint32&     sessionId,
                       QString&     profil)=0;
    virtual void logout(quint32 sessionId)=0;
    // returns the full path of a file if the file exists into the conf dir.
    // Else, returns an empty string.
    virtual QString absoluteUserConfFileName(const QString& profil)=0;
};

}//namespace service
}//namespace users
}//namespace plugframe
}//namespace elekdom

#define PfLoginService_iid "elekdom.plugframe.users.service.LoginServiceInterface"
Q_DECLARE_INTERFACE(elekdom::plugframe::users::service::LoginServiceInterface, PfLoginService_iid)

#endif // LOGINSERVICEINTERFACE_H
