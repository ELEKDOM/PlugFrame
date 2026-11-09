// Copyright (C) 2026 ELEKDOM Christophe Mars c.mars@elekdom.fr
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
#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <QHash>
#include "bundle/bundleimplementation.h"
#include "network/backend/serverconnectionsnotifier.h"
#include "network/backend/clientconnection.h"
#include "pfcore-lib_export.h"

namespace plugframe
{
class PFCORELIB_EXPORT Publisher : public BundleImplementation
{
public:
    Publisher(QString logBundleName);
    ~Publisher() override;

public:
    void newClientConnection(plugframe::ChannelManager *channel);
    void disconnectedFromClient(plugframe::ChannelManager *channel);

protected:
    void _start(QspBundleContext bundleContext) override;
    PF_qtServiceInterface_DECL

private:
    void registerConnectionsNotifier();

private:
    QspServerConnectionsNotifier                          m_serverConnectionsNotifier;
    QHash<plugframe::ChannelManager*,QspClientConnection> m_clientConnectionHash;
};
}//namespace plugframe
#endif // PUBLISHER_H
