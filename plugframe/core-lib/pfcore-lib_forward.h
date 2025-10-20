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

#ifndef PFCORELIB_FORWARD_H
#define PFCORELIB_FORWARD_H

namespace plugframe
{
    class FrameworkInterface;
    //
    class Bundle;
    class BundleImplementation;
    class BundleFactory;
    class BundleBuilder;
    class Bundle4BuilderInterface;
    class BundleHeaders;
    class BundleEmitter;
    class BundleListener;
    //
    class ServiceImplementationInterface;
    //
    class GuiPageController;
    //
    class WorkerOuts;
    class WorkerSignal;
    //
    class Scheduler;
    //
    class TcpChannelDeserializer;
    class TcpChannelMessage;
    class TcpChannel;
    class TcpServer;
    class TcpServerConnManager;
    class TcpServerChannelManager;
    class TcpServerService;
    class TcpClient;
    class TcpClientSlots;
    class TcpClientChannelManager;
    class TcpClientService;
} //namespace plugframe

#endif // PFCORELIB_FORWARD_H
