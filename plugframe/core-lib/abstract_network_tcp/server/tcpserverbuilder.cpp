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


#include "tcpserverbuilder.h"
#include "tcpserverfactory.h"
#include "tcpserver.h"
#include "tcpserverconnmanager.h"

using namespace elekdom::plugframe::core::tcp::server::builder;
using namespace elekdom::plugframe::core::tcp::server::factory;
using namespace elekdom::plugframe::core::tcp::server::bundle;

TcpServerBuilder::TcpServerBuilder(core::bundle::Bundle4BuilderInterface& myBundle):
    core::bundle::BundleBuilder{myBundle}
{}

TcpServerBuilder::~TcpServerBuilder()
{

}

void TcpServerBuilder::specificBuild()
{
    TcpServer& tcpBundle{dynamic_cast<TcpServer&>(getBundle())};
    TcpServerFactory& tcpServerFactory{dynamic_cast<TcpServerFactory&>(tcpBundle.getFactory())};
    TcpServerConnManager *connManager;

    connManager = tcpServerFactory.createTcpServerConnManager(tcpBundle);
    tcpBundle.tcpServerConnManager(connManager);
}
