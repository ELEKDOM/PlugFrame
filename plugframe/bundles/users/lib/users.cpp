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


#include <QMutexLocker>
#include <QSettings>
#include <QRandomGenerator>
#include "bundle/bundlecontext.h"
#include "users.h"
#include "usersfactory.h"
#include "loggeduser.h"
#include "logger/pflog.h"

using namespace elekdom::plugframe::users::service;
using namespace elekdom::plugframe::users::bundle;

Users::Users():
    plugframe::core::bundle::BundleImplementation{"Users"}
{
}

Users::~Users()
{

}

elekdom::plugframe::core::bundle::BundleFactory *Users::createFactory()
{
    return new users::factory::UsersFactory;
}

elekdom::plugframe::core::plugin::ServiceInterface *Users::qtServiceInterface(const QString &sName)
{
    core::plugin::ServiceInterface *ret{nullptr};

    if (service::LoginServiceInterface::serviceName() == sName)
    {
        ret = qobject_cast<service::LoginServiceInterface*>(getQplugin());
    }

    return ret;
}

void Users::login(QString                             frontendItf,
                  QString                             frontendIp,
                  QString                             identifier,
                  QString                             password,
                  LoginServiceInterface::LoginStatus& loginStatus,
                  quint32&                            sessionId,
                  QString&                            profil)
{
    QMutexLocker lock(&m_mutex);

    pfInfo1(logChannel()) << QObject::tr("Demande de connexion. Utilisateur : ") << identifier << QObject::tr(" interface : ") << frontendItf << QObject::tr(" adresse : ") << frontendIp;

    loginStatus = checkLogin(identifier,
                             password,
                             frontendItf,
                             frontendIp,
                             profil);
    if (loginStatus == service::LoginServiceInterface::LoginStatus::Ok)
    {
        sessionId = generateSessionId();
        addLoggedUser(sessionId, frontendItf, identifier);

        pfInfo1(logChannel()) << QObject::tr("Utilisateur : ") << identifier << QObject::tr(" connecté, sessionId : ") << sessionId << QObject::tr(" profil : ") << profil;
    }
    else
    {
        pfInfo1(logChannel()) << QObject::tr("Utilisateur : ") << identifier << QObject::tr(" . Connexion refusée");
    }
}

void Users::logout(quint32 sessionId)
{
    QMutexLocker lock(&m_mutex);

    pfInfo1(logChannel()) << QObject::tr("Déconnexion de la sessionId : ") << sessionId;

    m_loggedUsers.remove(sessionId);
}

LoginServiceInterface::LoginStatus  Users::checkLogin(QString identifier,
                                                      QString password,
                                                      QString frontendItf,
                                                      QString frontendIp,
                                                      QString& profil)
{
    quint8    found{false};
    LoginServiceInterface::LoginStatus ret{service::LoginServiceInterface::LoginStatus::PasswordErr};
    int       size;
    QString   userIdentifier;
    QString   userPassword;
    QSettings usersSettings{getConfPath(),QSettings::IniFormat};  // conf/users.ini
    Q_UNUSED(frontendItf) // To perform checks on the origin of the connection.
    Q_UNUSED(frontendIp)  // Not yet implemented.

    size = usersSettings.beginReadArray(QStringLiteral("Profils"));
    for (int i = 0; i < size && !found; ++i) {
        usersSettings.setArrayIndex(i);
        userIdentifier = usersSettings.value(QStringLiteral("identifier")).toString();
        found = userIdentifier == identifier;
        if (found)
        {
            profil = usersSettings.value(QStringLiteral("profil")).toString();
            userPassword = usersSettings.value(QStringLiteral("password")).toString();
            if (userPassword == password)
            {
                ret = service::LoginServiceInterface::LoginStatus::Ok;
            }
        }
    }
    usersSettings.endArray();

    if (!found)
    {
        ret = service::LoginServiceInterface::LoginStatus::IdentifierErr;
    }

    return ret;
}

quint32 Users::generateSessionId()
{
    quint32 ret;

    do
    {
        ret = QRandomGenerator::global()->generate();
    }while(m_loggedUsers.contains(ret));

    return ret;
}

void Users::addLoggedUser(const quint32& sessionId, const QString& frontendItf, const QString& identifier)
{
    QspLoggedUser loggedUser;
    factory::UsersFactory& usersFactory{dynamic_cast<factory::UsersFactory&>(getFactory())};

    loggedUser.reset(usersFactory.createLoggedUser(frontendItf,identifier,sessionId));
    m_loggedUsers.insert(sessionId, loggedUser);
}
