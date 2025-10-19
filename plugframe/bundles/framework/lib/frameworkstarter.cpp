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
#include "event/event.h"

FrameworkStarter::FrameworkStarter(plugframe::Bundle& fwk):
    BundleEmitter{fwk}
{

}

FrameworkStarter::~FrameworkStarter()
{

}

void FrameworkStarter::start()
{
    //pfDebug3(getLogBundleName()) << "->SmfFrameworkStarter::start";

    // Start all bundles according to their "starting level".
    // Create a "BundleContext" for each of them to start
    startAllBundles();

    //pfDebug3(getLogBundleName()) << "<-SmfFrameworkStarter::start";
}

void FrameworkStarter::stop()
{
    //pfDebug3(getLogBundleName()) << "->SmfFrameworkStarter::stop";

    // Stop all bundles according to their "starting level".
    stopAllBundles();

    //pfDebug3(getLogBundleName()) << "<-SmfFrameworkStarter::stop";
}

void FrameworkStarter::postBundlesStartingEvt(plugframe::BundleList& bundlesToStart,
                                              int frameworkStartLevel,
                                              int curStartLevel)
{
    // Create the event
    FrameworkFactory& myFactory = dynamic_cast<FrameworkFactory&>(getFactory());
    plugframe::QspEvent evt{myFactory.createBundlesStartingEvent(bundlesToStart,
                                                                 frameworkStartLevel,
                                                                 curStartLevel)};
    // Post the event
    emit pfEvent(evt);
}

void FrameworkStarter::postStartBundleEvt(plugframe::BundleInterface *toStart)
{
    // Create the event
    FrameworkFactory& myFactory = dynamic_cast<FrameworkFactory&>(getFactory());
    plugframe::QspEvent evt{myFactory.createStartBundleEvent(toStart)};

    // Post the event
    emit pfEvent(evt);
}

void FrameworkStarter::postFrameworkStartedEvt()
{
    // Create the event
    FrameworkFactory& myFactory = dynamic_cast<FrameworkFactory&>(getFactory());
    plugframe::QspEvent evt{myFactory.createFrameworkStartedEvent()};

    // Post the event
    emit pfEvent(evt);
}

void FrameworkStarter::postBundlesStoppingEvt(plugframe::BundleList &bundlesToStop,
                                              int curStopLevel)
{
    // Create the event
    FrameworkFactory& myFactory = dynamic_cast<FrameworkFactory&>(getFactory());
    plugframe::QspEvent evt{myFactory.createBundlesStoppingEvent(bundlesToStop, curStopLevel)};

    // Post the event
    emit pfEvent(evt);
}

void FrameworkStarter::postStopBundleEvt(plugframe::BundleInterface *toStop)
{
    // Create the event
    FrameworkFactory& myFactory = dynamic_cast<FrameworkFactory&>(getFactory());
    plugframe::QspEvent evt{myFactory.createStopBundleEvent(toStop)};

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
void FrameworkStarter::startAllBundles()
{
    //pfDebug3(getLogBundleName()) << "->SmfFrameworkStarter::startAllBundles";

    Framework&                     fwk{dynamic_cast<Framework&>(getBundle())};
    int                            frameworkStartLevelToReach;
    plugframe::BundleList          bundlesToStart;
    plugframe::BundleList_Iterator iter;
    plugframe::BundleList          listBundles{fwk.bundleList()};

    frameworkStartLevelToReach = fwk.startLevelToReach();

    pfDebug5(getLogBundleName()) << tr("Niveau de fonctionnement de la plateforme : ") << frameworkStartLevelToReach;

    // bundles with startlevel <= frameworkStartLevelToReach must be started
    for (iter = listBundles.begin(); iter != listBundles.end(); ++iter)
    {
        plugframe::BundleInterface *curBundle = *iter;

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

void FrameworkStarter::stopAllBundles()
{
    Framework&                     fwk{dynamic_cast<Framework&>(getBundle())};
    plugframe::BundleList          bundlesToStop;
    plugframe::BundleList_Iterator iter;
    plugframe::BundleList          listBundles{fwk.bundleList()};

    for (iter = listBundles.begin(); iter != listBundles.end(); ++iter)
    {
        plugframe::BundleInterface *curBundle{*iter};
        if (plugframe::BundleInterface::BundleState::Started == curBundle->getState())
        {
            bundlesToStop.append(curBundle);
        }
    }

    // Post the first occurence of the BundlesStopping event.
    // See onBundlesStoppingEvent of the listener
    postBundlesStoppingEvt(bundlesToStop, fwk.runningLevel());
 }
