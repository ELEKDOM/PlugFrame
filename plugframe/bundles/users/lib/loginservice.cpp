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

#include <QFile>
#include "loginservice.h"
#include "users.h"

LoginService::LoginService(plugframe::BundleImplementation *implementation):
    plugframe::ServiceImplementation{implementation}
{

}

LoginService::~LoginService()
{

}

void LoginService::login(QString frontendItf,
                         QString frontendIp,
                         QString identifier,
                         QString password,
                         plugframe::LoginServiceInterface::LoginStatus& loginStatus,
                         quint32 &sessionId,
                         QString& profil)
{
    Users *gacUsers{dynamic_cast<Users*>(implementation())};

    gacUsers->login(frontendItf,
                    frontendIp,
                    identifier,
                    password,
                    loginStatus,
                    sessionId,
                    profil);
}

void LoginService::logout(quint32 sessionId)
{
    Users *gacUsers{dynamic_cast<Users*>(implementation())};

    gacUsers->logout(sessionId);
}

QString LoginService::absoluteUserConfFileName(const QString &profil)
{
    QString ret;
    QString fileName{profil + QStringLiteral("_remote_monitoring.xml")};
    QFile file{implementation()->getConfDir() + fileName};

    if (file.exists())
    {
        ret = file.fileName();
    }

    return ret;
}

QString LoginService::serviceName()
{
    return plugframe::LoginServiceInterface::serviceName();
}
