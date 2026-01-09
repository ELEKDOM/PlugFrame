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

#ifndef USERSPLUGIN_H
#define USERSPLUGIN_H

#include "plugin/plugin.h"
#include "loginservice.h"
#include "service-int/loginserviceinterface.h"

class UsersPlugin : public plugframe::Plugin,
                    public plugframe::LoginServiceInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "plugframe.users.plugin" FILE "../usersbundle.json")
    Q_INTERFACES(plugframe::BundleInterface
                 plugframe::LoginServiceInterface)

private:
    QspLoginService m_loginServiceImpl;

public:
    UsersPlugin();
    ~UsersPlugin() override;

protected:
    plugframe::Bundle4PluginInterface *createImplementation() override;
    void bindServicesImplementations() override;

protected: // GacServiceTemplate1Interface
    void login(QString                                      frontendItf,
               QString                                      frontendIp,
               QString                                      identifier,
               QString                                      password,
               plugframe::LoginServiceInterface::LoginStatus& loginStatus,
               quint32&                                     sessionId,
               QString&                                     profil) override;
    void logout(quint32 sessionId) override;
    QString absoluteUserConfFileName(const QString& profil) override;
};
#endif // USERSPLUGIN_H
