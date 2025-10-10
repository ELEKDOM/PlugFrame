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


#include "logger/pflog.h"
#include "frameworkstarter.h"
#include "frameworkfactory.h"
#include "framework.h"
#include "event/frameworkevent/bundlesstartingevent.h"
#include "event/frameworkevent/startbundleevent.h"
#include "event/frameworkevent/frameworkstartedevent.h"
#include "event/frameworkevent/bundlesstoppingevent.h"
#include "event/frameworkevent/stopbundleevent.h"

using namespace elekdom::plugframe;

framework::bundle::FrameworkStarter::FrameworkStarter(core::bundle::Bundle& fwk):
    BundleEmitter{fwk}
{

}

framework::bundle::FrameworkStarter::~FrameworkStarter()
{

}

void framework::bundle::FrameworkStarter::start()
{
    //pfDebug3(getLogBundleName()) << "->SmfFrameworkStarter::start";

    // Start all bundles according to their "starting level".
    // Create a "BundleContext" for each of them to start
    startAllBundles();

    //pfDebug3(getLogBundleName()) << "<-SmfFrameworkStarter::start";
}

void framework::bundle::FrameworkStarter::stop()
{
    //pfDebug3(getLogBundleName()) << "->SmfFrameworkStarter::stop";

    // Stop all bundles according to their "starting level".
    stopAllBundles();

    //pfDebug3(getLogBundleName()) << "<-SmfFrameworkStarter::stop";
}

void framework::bundle::FrameworkStarter::postBundlesStartingEvt(core::plugin::BundleList& bundlesToStart,
                                                            int frameworkStartLevel,
                                                            int curStartLevel)
{
    // Create the event
    framework::factory::FrameworkFactory& myFactory = dynamic_cast<framework::factory::FrameworkFactory&>(getFactory());
    core::event::QspEvent evt{myFactory.createBundlesStartingEvent(bundlesToStart,
                                                                      frameworkStartLevel,
                                                                      curStartLevel)};

    // Post the event
    emit pfEvent(evt);
}

void framework::bundle::FrameworkStarter::postStartBundleEvt(core::plugin::BundleInterface *toStart)
{
    // Create the event
    framework::factory::FrameworkFactory& myFactory = dynamic_cast<framework::factory::FrameworkFactory&>(getFactory());
    core::event::QspEvent evt{myFactory.createStartBundleEvent(toStart)};

    // Post the event
    emit pfEvent(evt);
}

void framework::bundle::FrameworkStarter::postFrameworkStartedEvt()
{
    // Create the event
    framework::factory::FrameworkFactory& myFactory = dynamic_cast<framework::factory::FrameworkFactory&>(getFactory());
    core::event::QspEvent evt{myFactory.createFrameworkStartedEvent()};

    // Post the event
    emit pfEvent(evt);
}

void framework::bundle::FrameworkStarter::postBundlesStoppingEvt(core::plugin::BundleList &bundlesToStop,
                                                            int curStopLevel)
{
    // Create the event
    framework::factory::FrameworkFactory& myFactory = dynamic_cast<framework::factory::FrameworkFactory&>(getFactory());
    core::event::QspEvent evt{myFactory.createBundlesStoppingEvent(bundlesToStop, curStopLevel)};

    // Post the event
    emit pfEvent(evt);
}

void framework::bundle::FrameworkStarter::postStopBundleEvt(core::plugin::BundleInterface *toStop)
{
    // Create the event
    framework::factory::FrameworkFactory& myFactory = dynamic_cast<framework::factory::FrameworkFactory&>(getFactory());
    core::event::QspEvent evt{myFactory.createStopBundleEvent(toStop)};

    // Post the event
    emit pfEvent(evt);
}

/**
 * @brief FrameworkStarter::startAllBundle
 *
 * Starts all bundle according their startlevel.beging value.
 * The framework's StartLevel begins from one by one step and ends when all
 * bunbles have been started.
 *
 * Caution : During the starting stage, the QtEvent Queue must be still available.
 * So, the loop is implemented by an event/event handler couple according to
 * the  Qt event mechanism !
 */
void framework::bundle::FrameworkStarter::startAllBundles()
{
    //pfDebug3(getLogBundleName()) << "->SmfFrameworkStarter::startAllBundles";

    framework::bundle::Framework&     fwk{dynamic_cast<framework::bundle::Framework&>(getBundle())};
    int                               frameworkStartLevelToReach;
    core::plugin::BundleList          bundlesToStart;
    core::plugin::BundleList_Iterator iter;
    core::plugin::BundleList          listBundles{fwk.bundleList()};

    frameworkStartLevelToReach = fwk.startLevelToReach();

    pfDebug5(getLogBundleName()) << tr("Niveau de fonctionnement de la plateforme : ") << frameworkStartLevelToReach;

    // bundles with startlevel <= frameworkStartLevelToReach must be started
    for (iter = listBundles.begin(); iter != listBundles.end(); ++iter)
    {
        core::plugin::BundleInterface *curBundle = *iter;

        pfDebug4(getLogBundleName()) << "curBundle name = " << curBundle->getName() << " StartLevel = " << curBundle->getStartLevel();

        if (curBundle->getStartLevel() > 0 && curBundle->getStartLevel() <= frameworkStartLevelToReach)
        {
            pfDebug5(getLogBundleName()) << tr("Le Bundle %1 est à démarrer").arg(curBundle->getName());

            bundlesToStart.append(curBundle);
        }
    }

    fwk.setNumberOfBundlesToStart(bundlesToStart.size());

    // Post the first occurence of the BundlesStarting event.
    // See onBundlesStartingEvent of the listener
    postBundlesStartingEvt(bundlesToStart, frameworkStartLevelToReach, 1);

    //pfDebug3(getLogBundleName()) << "<-SmfFrameworkStarter::startAllBundles";
}

void framework::bundle::FrameworkStarter::stopAllBundles()
{
    framework::bundle::Framework&     fwk{dynamic_cast<framework::bundle::Framework&>(getBundle())};
    core::plugin::BundleList          bundlesToStop;
    core::plugin::BundleList_Iterator iter;
    core::plugin::BundleList          listBundles{fwk.bundleList()};

    for (iter = listBundles.begin(); iter != listBundles.end(); ++iter)
    {
        core::plugin::BundleInterface *curBundle{*iter};
        if (core::plugin::BundleInterface::BundleState::Started == curBundle->getState())
        {
            bundlesToStop.append(curBundle);
        }
    }

    // Post the first occurence of the BundlesStopping event.
    // See onBundlesStoppingEvent of the listener
    postBundlesStoppingEvt(bundlesToStop, fwk.runningLevel());
 }
