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

using namespace elekdom::plugframe::framework;
using namespace elekdom::plugframe;

bundle::Framework::Framework(core::launcher::QspBundlesStore bundlesStore,
                                   core::launcher::QspLaunchingProperties launchingProperties):
    core::bundle::LongStartBundleImplementation{"Framework"},
    m_bundlesStore{bundlesStore},
    m_launchingProperties{launchingProperties},
    m_numberOfBundlesToStart{0}
{
    qRegisterMetaType<plugframe::core::event::QspEvent>("plugframe::core::event::QspEvent");
}

bundle::Framework::~Framework()
{

}

core::plugin::BundleList bundle::Framework::bundleList()
{
    return m_ListBundles;
}

int bundle::Framework::runningLevel()
{
    return getStartLevel();
}

void bundle::Framework::quit()
{
    stop();
}

int bundle::Framework::startLevelToReach()
{
    return getStartLevel();
}

void bundle::Framework::setNumberOfBundlesToStart(int nb)
{
    m_numberOfBundlesToStart = nb;
}

void bundle::Framework::postBundlesStartingEvt(core::plugin::BundleList &bundlesToStart,
                                          int frameworkStartLevel,
                                          int curStartLevel)
{
    QspSmfFrameworkStarter fwkStarter{getEmitter().dynamicCast<FrameworkStarter>()};

    fwkStarter->postBundlesStartingEvt(bundlesToStart,frameworkStartLevel,curStartLevel);
}

void bundle::Framework::postBundlesStoppingEvt(core::plugin::BundleList &bundlesToStop, int curStopLevel)
{
    QspSmfFrameworkStarter fwkStarter{getEmitter().dynamicCast<FrameworkStarter>()};

    fwkStarter->postBundlesStoppingEvt(bundlesToStop,curStopLevel);
}

void bundle::Framework::postFrameworkStartedEvt()
{
    QspSmfFrameworkStarter fwkStarter{getEmitter().dynamicCast<FrameworkStarter>()};

    fwkStarter->postFrameworkStartedEvt();
}

int bundle::Framework::getNumberOfBundlesToStart()
{
    return m_numberOfBundlesToStart;
}

service::SystemServiceRegistryInterface *bundle::Framework::getRegistryService()
{
    service::SystemServiceRegistryInterface *ret{qobject_cast<service::SystemServiceRegistryInterface*>(getQplugin())};
    return ret;
}

void bundle::Framework::fwkStarted()
{
    started();
}

void bundle::Framework::fwkStopped()
{
    setState(core::plugin::BundleInterface::BundleState::Stopped);
    pfInfo1(getLogBundleName()) << QObject::tr("Framework, Arrêté" );

    // All bundles have been stopped
    QCoreApplication::quit();
}

core::bundle::BundleFactory *bundle::Framework::createFactory()
{
    return new factory::FrameworkFactory;
}

void bundle::Framework::init()
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

void bundle::Framework::_start(elekdom::plugframe::core::bundle::QspBundleContext bundleContext)
{
    Q_UNUSED(bundleContext)

    BundleImplementation::_start(bundleContext); // To register services!

    core::bundle::QspBundleEmitter emitter{getEmitter()};
    QspSmfFrameworkStarter fwkStarter{emitter.dynamicCast<FrameworkStarter>()};
    core::bundle::QspBundleListener listener{getListener()};
    QspFrameworkStarterListener fwkStarterListener{listener.dynamicCast<FrameworkStarterListener>()};

    fwkStarterListener->reset(); // number of bundles to start reset to 0!
    fwkStarter->start();
}

void bundle::Framework::stop()
{
    core::bundle::QspBundleEmitter emitter{getEmitter()};
    QspSmfFrameworkStarter fwkStarter{emitter.dynamicCast<FrameworkStarter>()};

    setState(core::plugin::BundleInterface::BundleState::Stopping);

    //notify stopping
    fwkStarter->postBundleStoppingEvt();

    //stopping implementation
    _stop();
}

void bundle::Framework::_stop()
{
    //pfDebug3(getLogBundleName()) << "->SmfFramework::_stop";

    core::bundle::QspBundleEmitter emitter{getEmitter()};
    QspSmfFrameworkStarter fwkStarter{emitter.dynamicCast<FrameworkStarter>()};
    core::bundle::QspBundleListener listener{getListener()};
    QspFrameworkStarterListener fwkStarterListener{listener.dynamicCast<FrameworkStarterListener>()};

    fwkStarterListener->reset(); // number of bundles to stop reset to 0!
    fwkStarter->stop();

    //pfDebug3(getLogBundleName()) << "<-SmfFramework::_stop";
}

core::plugin::ServiceInterface *bundle::Framework::qtServiceInterface(const QString &sName)
{
    core::plugin::ServiceInterface *ret{nullptr};

    if (service::SystemServiceRegistryInterface::serviceName() == sName)
    {
        ret = qobject_cast<elekdom::plugframe::framework::service::SystemServiceRegistryInterface*>(getQplugin());
    }
    else if (service::SystemServiceInterface::serviceName() == sName)
    {
        ret = qobject_cast<elekdom::plugframe::framework::service::SystemServiceInterface*>(getQplugin());
    }

    return ret;
}

bool bundle::Framework::registerService(const QString &serviceInterfaceName, core::plugin::ServiceInterface *service)
{
    bool ret{true};

    if (service::SystemServiceRegistryInterface::serviceName() != serviceInterfaceName)
    {
        plugframe::core::service::QspServiceImplementationInterface qspSii;
        service::ServiceRegistry *sr;

        qspSii = getService(service::SystemServiceRegistryInterface::serviceName());
        sr =  dynamic_cast<service::ServiceRegistry*>(qspSii.get());
        if (sr)
        {
            sr->registerService(serviceInterfaceName,service);
        }
    }

    return ret;
}
