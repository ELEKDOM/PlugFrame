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
#include "publisher.h"
#include "publisherfactory.h"
#include "network/channel/channelmanager.h"
#include "network/channel/messagescodec.h"
#include "service-int/backendservernotifierregisterserviceinterface.h"

plugframe::Publisher::Publisher(QString logBundleName):
    plugframe::BundleImplementation{logBundleName}
{

}

plugframe::Publisher::~Publisher()
{

}

void plugframe::Publisher::newClientConnection(ChannelManager *channel)
{
    PublisherFactory &factory{dynamic_cast<PublisherFactory&>(getFactory())};
    MessagesCodec *messagesCodec{factory.createMessagesCodec()};
    QspClientConnection clientConnection{factory.createClientConnection(this,messagesCodec)};

    m_clientConnectionHash.insert(channel,clientConnection);
    channel->registerMessagesCodec(messagesCodec);
}

void plugframe::Publisher::disconnectedFromClient(ChannelManager *channel)
{
    QspClientConnection clientConnection;

    clientConnection = m_clientConnectionHash.value(channel);
    if (!clientConnection.isNull())
    {
        channel->unregisterMessagesCodec(clientConnection->messagesCodec());
        m_clientConnectionHash.remove(channel);
    }
}

void plugframe::Publisher::_start(QspBundleContext bundleContext)
{
    BundleImplementation::_start(bundleContext);
    registerConnectionsNotifier();
}

void plugframe::Publisher::registerConnectionsNotifier()
{
    QList<plugframe::BackendServerNotifierRegisterServiceInterface*> registerNotifierServiceItfList; // more than one bundle can export this service!

    registerNotifierServiceItfList = bundleContext()->getServices<plugframe::BackendServerNotifierRegisterServiceInterface>(plugframe::BackendServerNotifierRegisterServiceInterface::serviceName());
    if (registerNotifierServiceItfList.size() > 0)
    {
        PublisherFactory &factory{dynamic_cast<PublisherFactory&>(getFactory())};

        m_serverConnectionsNotifier.reset(factory.createConnectionsNotifier(this));
        //register the notifier to all interfaces
        for (auto i=0;i<registerNotifierServiceItfList.size();i++)
        {
            registerNotifierServiceItfList.at(i)->registerConnectionNotifier(m_serverConnectionsNotifier.get());
        }
    }
}

PF_qtServiceInterface_DEF(plugframe::Publisher)