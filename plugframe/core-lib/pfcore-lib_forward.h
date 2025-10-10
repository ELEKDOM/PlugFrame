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

#include <QSharedPointer>
#include <QList>

namespace elekdom
{
namespace plugframe
{
    namespace framework
    {
        namespace plugin
        {
            class  FrameworkInterface;
        }
    }
    namespace core
    {
        namespace event
        {
            class Event;
            class StartBundleEvent;
            class BundleStartingEvent;
            class BundleStartedEvent;
            class BundleStoppingEvent;
            class BundleStoppedEvent;
            class BundlesStartingEvent;
            class BundlesStoppingEvent;
            class StopBundleEvent;
            class FrameworkStartedEvent;

            using QspEvent = QSharedPointer<Event>;
        }
        namespace bundle
        {
            class Bundle;
            class BundleImplementation;
            class BundleContext;
            class BundleFactory;
            class BundleBuilder;
            class Bundle4BuilderInterface;
            class Bundle4PluginInterface;
            class BundleHeaders;
            class BundleEmitter;
            class BundleListener;

            using QspBundle = QSharedPointer<Bundle>;
            using QspBundle4PluginInterface = QSharedPointer<Bundle4PluginInterface>;
            using QspBundleListener = QSharedPointer<BundleListener>;
            using QspBundleEmitter = QSharedPointer<BundleEmitter>;
            using QspBundleContext = QSharedPointer<BundleContext>;
            using QspBundleHeaders = QSharedPointer<BundleHeaders>;
            using QspBundleFactory = QSharedPointer<BundleFactory>;
        }
        namespace service
        {
            class ServiceImplementationInterface;

            using QspServiceImplementationInterface = QSharedPointer<ServiceImplementationInterface>;
        }
        namespace launcher
        {
            class LaunchingProperties;
            class Location;
            class BundlesStore;
            class CoreFactory;

            using QspLaunchingProperties = QSharedPointer<LaunchingProperties>;
            using QspLocation = QSharedPointer<Location>;
            using QspBundlesStore = QSharedPointer<BundlesStore>;
            using QspCoreFactory = QSharedPointer<CoreFactory>;
        }
        namespace plugin
        {
            class BundleInterface;
            class ServiceInterface;

            using BundleList = QList<core::plugin::BundleInterface*>;
            using BundleList_Iterator = BundleList::iterator;
        }
        namespace worker
        {
            class Worker;
            class WorkerOuts;
            class WorkerThread;
            class WorkerArgs;
            class WorkerSignal;
            class WorkerWatcher;

            using QspWorker = QSharedPointer<Worker>;
            using QspWorkerOuts = QSharedPointer<WorkerOuts>;
            using QspWorkerArgs = QSharedPointer<WorkerArgs>;
            using QspWorkerWatcher = QSharedPointer<WorkerWatcher>;
            using QspWorkerThread = QSharedPointer<WorkerThread>;
            using QspWorkerSignal = QSharedPointer<WorkerSignal>;
        }
        namespace scheduler
        {
            class SchedulerElement;
            class SchedulerElementHook;
            class Scheduler;
            class SchedulerBuilder;
            class DailyScheduler;
            class ScheduledEvent;
            class WeeklyScheduler;
            class DigitalSuite;

            using QspScheduler = QSharedPointer<Scheduler>;
            using QspSchedulerBuilder = QSharedPointer<SchedulerBuilder>;
            using QspDailyScheduler = QSharedPointer<DailyScheduler>;
            using QspScheduledEvent = QSharedPointer<ScheduledEvent>;
            using QspWeeklyScheduler = QSharedPointer<WeeklyScheduler>;
        }
        namespace gui
        {
            class GuiPageController;
            class GuiPageView;

            using QspGuiPageController = QSharedPointer<GuiPageController>;
            using GuiPageViewList = QList<GuiPageView*>;
        }
        namespace tcp
        {
            class TcpChannelDeserializer;
            class TcpChannelMessage;
            class TcpChannel;

            namespace server
            {
                namespace bundle
                {
                    class TcpServer;
                    class TcpServerConnManager;
                    class TcpServerChannelManager;

                    using QspTcpServerChannelManager = QSharedPointer<TcpServerChannelManager>;
                }
                namespace service
                {
                    class TcpServerService;

                    using QspTcpServerService = QSharedPointer<TcpServerService>;
                }
            }
            namespace client
            {
                namespace bundle
                {
                    class TcpClient;
                    class TcpClientSlots;
                    class TcpClientChannelManager;
                }
                namespace service
                {
                    class TcpClientService;

                    using QspTcpClientService = QSharedPointer<TcpClientService>;
                }
            }
        }

    } //namespace core
} //namespace plugframe
} //namespace elekdom

#endif // PFCORELIB_FORWARD_H
