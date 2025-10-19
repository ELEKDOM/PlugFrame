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

#include <QCoreApplication>
#include "framework.h"
#include "frameworkfactory.h"
#include "frameworkstarter.h"
#include "frameworkstarterlistener.h"
#include "bundle/bundleheaders.h"
#include "logger/pflog.h"
#include "launcher/bundlesstore.h"
#include "launcher/launchingproperties.h"
#include "service-int/systemserviceinterface.h"
#include "serviceregistry.h"

Framework::Framework(plugframe::QspBundlesStore bundlesStore,
                     plugframe::QspLaunchingProperties launchingProperties):
    plugframe::LongStartBundleImplementation{"Framework"},
    m_bundlesStore{bundlesStore},
    m_launchingProperties{launchingProperties},
    m_numberOfBundlesToStart{0}
{
    qRegisterMetaType<plugframe::QspEvent>("plugframe::QspEvent");
}

Framework::~Framework()
{

}

plugframe::BundleList Framework::bundleList()
{
    return m_ListBundles;
}

int Framework::runningLevel()
{
    return getStartLevel();
}

void Framework::quit()
{
    stop();
}

int Framework::startLevelToReach()
{
    return getStartLevel();
}

void Framework::setNumberOfBundlesToStart(int nb)
{
    m_numberOfBundlesToStart = nb;
}

void Framework::postBundlesStartingEvt(plugframe::BundleList &bundlesToStart,
                                       int frameworkStartLevel,
                                       int curStartLevel)
{
    QspSmfFrameworkStarter fwkStarter{getEmitter().dynamicCast<FrameworkStarter>()};

    fwkStarter->postBundlesStartingEvt(bundlesToStart,frameworkStartLevel,curStartLevel);
}

void Framework::postBundlesStoppingEvt(plugframe::BundleList &bundlesToStop,int curStopLevel)
{
    QspSmfFrameworkStarter fwkStarter{getEmitter().dynamicCast<FrameworkStarter>()};

    fwkStarter->postBundlesStoppingEvt(bundlesToStop,curStopLevel);
}

void Framework::postFrameworkStartedEvt()
{
    QspSmfFrameworkStarter fwkStarter{getEmitter().dynamicCast<FrameworkStarter>()};

    fwkStarter->postFrameworkStartedEvt();
}

int Framework::getNumberOfBundlesToStart()
{
    return m_numberOfBundlesToStart;
}

plugframe::SystemServiceRegistryInterface *Framework::getRegistryService()
{
    plugframe::SystemServiceRegistryInterface *ret{qobject_cast<plugframe::SystemServiceRegistryInterface*>(getQplugin())};
    return ret;
}

void Framework::fwkStarted()
{
    started();
}

void Framework::fwkStopped()
{
    setState(plugframe::BundleInterface::BundleState::Stopped);
    pfInfo1(getLogBundleName()) << QObject::tr("Framework, Arrêté" );

    // All bundles have been stopped
    QCoreApplication::quit();
}

plugframe::BundleFactory *Framework::createFactory()
{
    return new FrameworkFactory;
}

void Framework::init()
{
    // Bundle initialization : creation and build
    //--------------------------------------------
    Bundle::init();

    // Overide Framework startlevel from properties
    if (m_launchingProperties->hasStartlevel())
    {
        getHeaders().setStartLevel(m_launchingProperties->getStartlevel());
    }

    // Step 1: load all bundles. After loading, the bundles are in LOADED state
    pfDebug5(getLogBundleName()) << QObject::tr("Chargement des bundles...");
    m_bundlesStore->loadPlugins(getLogBundleName(), m_ListBundles);
}

void Framework::_start(plugframe::QspBundleContext bundleContext)
{
    Q_UNUSED(bundleContext)

    BundleImplementation::_start(bundleContext); // To register services!

    plugframe::QspBundleEmitter emitter{getEmitter()};
    QspSmfFrameworkStarter fwkStarter{emitter.dynamicCast<FrameworkStarter>()};
    plugframe::QspBundleListener listener{getListener()};
    QspFrameworkStarterListener fwkStarterListener{listener.dynamicCast<FrameworkStarterListener>()};

    fwkStarterListener->reset(); // number of bundles to start reset to 0!
    fwkStarter->start();
}

void Framework::stop()
{
    plugframe::QspBundleEmitter emitter{getEmitter()};
    QspSmfFrameworkStarter fwkStarter{emitter.dynamicCast<FrameworkStarter>()};

    setState(plugframe::BundleInterface::BundleState::Stopping);

    //notify stopping
    fwkStarter->postBundleStoppingEvt();

    //stopping implementation
    _stop();
}

void Framework::_stop()
{
    //pfDebug3(getLogBundleName()) << "->SmfFramework::_stop";

    plugframe::QspBundleEmitter emitter{getEmitter()};
    QspSmfFrameworkStarter fwkStarter{emitter.dynamicCast<FrameworkStarter>()};
    plugframe::QspBundleListener listener{getListener()};
    QspFrameworkStarterListener fwkStarterListener{listener.dynamicCast<FrameworkStarterListener>()};

    fwkStarterListener->reset(); // number of bundles to stop reset to 0!
    fwkStarter->stop();

    //pfDebug3(getLogBundleName()) << "<-SmfFramework::_stop";
}

plugframe::ServiceInterface *Framework::qtServiceInterface(const QString &sName)
{
    plugframe::ServiceInterface *ret{nullptr};

    if (plugframe::SystemServiceRegistryInterface::serviceName() == sName)
    {
        ret = qobject_cast<plugframe::SystemServiceRegistryInterface*>(getQplugin());
    }
    else if (plugframe::SystemServiceInterface::serviceName() == sName)
    {
        ret = qobject_cast<plugframe::SystemServiceInterface*>(getQplugin());
    }

    return ret;
}

bool Framework::registerService(const QString &serviceInterfaceName,plugframe::ServiceInterface *service)
{
    bool ret{true};

    if (plugframe::SystemServiceRegistryInterface::serviceName() != serviceInterfaceName)
    {
        plugframe::QspServiceImplementationInterface qspSii;
        ServiceRegistry *sr;

        qspSii = getService(plugframe::SystemServiceRegistryInterface::serviceName());
        sr =  dynamic_cast<ServiceRegistry*>(qspSii.get());
        if (sr)
        {
            sr->registerService(serviceInterfaceName,service);
        }
    }

    return ret;
}
