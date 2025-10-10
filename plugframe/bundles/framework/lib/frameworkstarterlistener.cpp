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


#include "frameworkstarterlistener.h"
#include "framework.h"
#include "bundle/bundlecontext.h"
#include "frameworkfactory.h"
#include "logger/pflog.h"
#include "event/frameworkevent/bundlesstartingevent.h"
#include "event/frameworkevent/startbundleevent.h"
#include "event/frameworkevent/frameworkstartedevent.h"
#include "event/frameworkevent/bundlesstoppingevent.h"
#include "event/frameworkevent/stopbundleevent.h"
#include "event/bundleevent/bundlestartingevent.h"
#include "event/bundleevent/bundlestartedevent.h"
#include "event/bundleevent/bundlestoppingevent.h"
#include "event/bundleevent/bundlestoppedevent.h"

using namespace elekdom::plugframe;

framework::bundle::FrameworkStarterListener::FrameworkStarterListener(core::bundle::Bundle& fwk):
    core::bundle::BundleListener{fwk}
{

}

framework::bundle::FrameworkStarterListener::~FrameworkStarterListener()
{

}

void framework::bundle::FrameworkStarterListener::onEvent(plugframe::core::event::QspEvent ev)
{
    core::event::Event* event{ev.get()};
    QString evtTypeId {ev->getTypeId()};

    if (evtTypeId == core::event::BundlesStartingEvent::s_typeId)
    {
        onBundlesStartingEvent(dynamic_cast<core::event::BundlesStartingEvent*>(event));
    }
    else if (evtTypeId == core::event::StartBundleEvent::s_typeId)
    {
        onStartBundleEvent(dynamic_cast<core::event::StartBundleEvent*>(event));
    }
    else if (evtTypeId == core::event::FrameworkStartedEvent::s_typeId)
    {
        onFrameworkStartedEvent(dynamic_cast<core::event::FrameworkStartedEvent*>(event));
    }
    else if (evtTypeId == core::event::BundlesStoppingEvent::s_typeId)
    {
        onBundlesStoppingEvent(dynamic_cast<core::event::BundlesStoppingEvent*>(event));
    }
    else if (evtTypeId == core::event::StopBundleEvent::s_typeId)
    {
        onStopBundleEvent(dynamic_cast<core::event::StopBundleEvent*>(event));
    }
    else if (evtTypeId == core::event::BundleStartingEvent::s_typeId)
    {
        onBundleStartingEvent(dynamic_cast<core::event::BundleStartingEvent*>(event));
    }
    else if (evtTypeId == core::event::BundleStartedEvent::s_typeId)
    {
        onBundleStartedEvent(dynamic_cast<core::event::BundleStartedEvent*>(event));
    }
    else if (evtTypeId == core::event::BundleStoppingEvent::s_typeId)
    {
        onBundleStoppingEvent(dynamic_cast<core::event::BundleStoppingEvent*>(event));
    }
    else if (evtTypeId == core::event::BundleStoppedEvent::s_typeId)
    {
        onBundleStoppedEvent(dynamic_cast<core::event::BundleStoppedEvent*>(event));
    }
    else
    {
        //pfWarning8(getLogBundleName()) << tr("Framework Listener évènement non géré : ") << evtTypeId;
    }
}

/**
 * @brief smf::core::framework::FrameworkStarterListener::onBundlesStartingEvent
 * Event management of the bundles start loop : each bundle to start is starting into this handler
 * @param evt
 */
void framework::bundle::FrameworkStarterListener::onBundlesStartingEvent(core::event::BundlesStartingEvent *evt)
{
    pfDebug3(getLogBundleName()) << "->SmfFrameworkStarterListener::onBundlesStartingEvent";

    if (evt == nullptr)
    {
        pfWarning1(getLogBundleName()) << tr("l'adresse de l'évènement est (nullptr) !");
    }
    else
    {
        framework::bundle::Framework& fwk{dynamic_cast<framework::bundle::Framework&>(getBundle())};
        int nbOfBundlesToStart{fwk.getNumberOfBundlesToStart()};

        if (m_started_bundles_cpt < nbOfBundlesToStart)
        {
            int currentLevelToStart {evt->getCurrentStartLevel()};
            int levelToReach {evt->getFrameworkStartLevel()};

            if (currentLevelToStart <= levelToReach)
            {
                pfDebug5(getLogBundleName()) << tr("Démarrage du Framework en cours au niveau [ %1 ]").arg(currentLevelToStart);

                // Looking for the next bundle to start for the current level
                //-----------------------------------------------------------
                core::plugin::BundleList_Iterator it, curIt;
                core::plugin::BundleList& bundlesToStart {evt->getBundlesList()};
                bool found {false};
                int pos, curPos = 0;

                for (it = bundlesToStart.begin(), pos = 0; (found == false) && (it != bundlesToStart.end()); ++pos, ++it)
                {
                     core::plugin::BundleInterface *curBundle = *it;
                     int bundleStartLevel = curBundle->getStartLevel();

                     found = bundleStartLevel == currentLevelToStart;
                     if (found)
                     {
                         curPos = pos;
                         curIt = it;
                     }
                }

                if (found)
                {
                    // The selected bundle must be started
                    pfDebug5(getLogBundleName()) << tr("Bundle [ %1 ] à démarrer pour le niveau [ %2 ]").arg((*curIt)->getName()).arg(currentLevelToStart);

                    //fwk.postStartBundleEvt(*curIt);
                    startBundle(*curIt);

                    // One less bundle to start
                    bundlesToStart.removeAt(curPos);
                }

                // Is that all the bundles have been started for the current level ?
                if (!found)//(it == bundlesToStart.end())
                {
                     ++currentLevelToStart;
                }

                // Generate the next iteration
                //----------------------------
                fwk.postBundlesStartingEvt(bundlesToStart, levelToReach, currentLevelToStart);

            } // if (currentLevelToStart <= levelToReach)
        } // if (m_cpt < nbOfBundlesToStart)
    } // else (evt == nullptr)

    pfDebug3(getLogBundleName()) << "<-SmfFrameworkStarterListener::onBundlesStartingEvent";
}

void framework::bundle::FrameworkStarterListener::onStartBundleEvent(core::event::StartBundleEvent *evt)
{
    if (evt == nullptr)
    {
        pfWarning1(getLogBundleName()) << tr("l'adresse de l'évènement est (nullptr) !");
    }
    else
    {
        startBundle(evt->getBundleToStart());
    }
}

void framework::bundle::FrameworkStarterListener::onFrameworkStartedEvent(core::event::FrameworkStartedEvent *evt)
{
    pfDebug3(getLogBundleName()) << "->SmfFrameworkStarterListener::onFrameworkStartedEvent";

    Q_UNUSED(evt)
    framework::bundle::Framework& fwk{dynamic_cast<framework::bundle::Framework&>(getBundle())};

    pfDebug5(getLogBundleName()) << tr("Plateforme démarrée au niveau [ %1 ]").arg(fwk.runningLevel());

    // No evt to receive !
    fwk.fwkStarted();

    core::plugin::BundleList_Iterator it;
    core::plugin::BundleList bundlesList {fwk.bundleList()};

    pfDebug5(getLogBundleName()) << tr("== Liste des bundles démarrés ==");
    for (it = bundlesList.begin(); it != bundlesList.end(); ++it)
    {
        if ( core::plugin::BundleInterface::BundleState::Started == (*it)->getState() )
        {
            pfDebug5(getLogBundleName()) << (*it)->getName() << " start level : " << (*it)->getStartLevel();
        }
    }
    pfDebug5(getLogBundleName()) << tr("================");


    pfDebug3(getLogBundleName()) << "<-SmfFrameworkStarterListener::onFrameworkStartedEvent";
}

/**
 * @brief FrameworkStarterListener::onBundlesStoppingEvent
 * Main loop for stopping bundles
 * @param evt
 */
void framework::bundle::FrameworkStarterListener::onBundlesStoppingEvent(core::event::BundlesStoppingEvent *evt)
{
    //pfDebug3(getLogBundleName()) << "->SmfFrameworkStarterListener::onBundlesStoppingEvent";

    framework::bundle::Framework& fwk{dynamic_cast<framework::bundle::Framework&>(getBundle())};

    if (evt == nullptr)
    {
        pfWarning1(getLogBundleName()) << tr("l'adresse de l'évènement est (nullptr) !");
    }
    else
    {
        int currentLevelToStop {evt->getCurrentStopLevel()};
        if (currentLevelToStop > 0)
        {
            pfDebug5(getLogBundleName()) << tr("Arrêt du Framework en cours au niveau [ %1 ]").arg(currentLevelToStop);

            // Looking for the next bundle to stop for the current level
            //-----------------------------------------------------------
            core::plugin::BundleList_Iterator it, curIt;
            core::plugin::BundleList& bundlesToStop {evt->getBundlesList()};
            bool found {false};
            int pos, curPos = 0;

            for (it = bundlesToStop.begin(), pos = 0; (found == false) && (it != bundlesToStop.end()); ++pos, ++it)
            {
                 core::plugin::BundleInterface *curBundle = *it;
                 int bundleStartLevel = curBundle->getStartLevel();

                 found = bundleStartLevel == currentLevelToStop;
                 if (found)
                 {
                     curPos = pos;
                     curIt = it;
                 }
            }

            if (found)
            {
                // The selected bundle must be stopped
                pfDebug5(getLogBundleName()) << tr("Bundle [ %1 ] à stopper pour le niveau [ %2 ]").arg((*curIt)->getName()).arg(currentLevelToStop);

                //fwk.postStopBundleEvt(*curIt);
                (*curIt)->stop();

                // One less bundle to stop
                bundlesToStop.removeAt(curPos);
            }

            // Have all bundles been stopped for the current level ?
            if (!found)
            {
                 --currentLevelToStop;
            }

            // Generate the next iteration
            //----------------------------
            fwk.postBundlesStoppingEvt(bundlesToStop, currentLevelToStop);
        } // if (currentLevelToStop > 0)
    } // else (evt == nullptr)

    //pfDebug3(getLogBundleName()) << "<-SmfFrameworkStarterListener::onBundlesStoppingEvent";
}

void framework::bundle::FrameworkStarterListener::onStopBundleEvent(core::event::StopBundleEvent *evt)
{
    //pfDebug3(getLogBundleName()) << "->SmfFrameworkStarterListener::onStopBundleEvent";

    if (evt == nullptr)
    {
        pfWarning1(getLogBundleName()) << tr("l'adresse de l'évènement est (nullptr) !");
    }
    else
    {
        // Stop the bundle
        //_________________
        core::plugin::BundleInterface *bundleItf {evt->getBundleToStop()};

        bundleItf->stop();
    }

    //pfDebug3(getLogBundleName()) << "<-SmfFrameworkStarterListener::onStopBundleEvent";
}

void framework::bundle::FrameworkStarterListener::onBundleStartingEvent(core::event::BundleStartingEvent *evt)
{
    pfDebug5(getLogBundleName()) << tr("Démarrage du bundle [ %1 ]").arg(evt->getBundle()->getName());
}

void framework::bundle::FrameworkStarterListener::onBundleStartedEvent(core::event::BundleStartedEvent *evt)
{
    pfDebug5(getLogBundleName()) << tr("Bundle [ %1 ], démarré").arg(evt->getBundle()->getName());
    framework::bundle::Framework& fwk{dynamic_cast<framework::bundle::Framework&>(getBundle())};
    int nbOfBundlesToStart{fwk.getNumberOfBundlesToStart()};

    if (++m_started_bundles_cpt == nbOfBundlesToStart)
    {
        // All bundles have been started
        fwk.postFrameworkStartedEvt();
    }
}

void framework::bundle::FrameworkStarterListener::onBundleStoppingEvent(core::event::BundleStoppingEvent *evt)
{
    pfInfo4(getLogBundleName()) << tr("Arrêt du bundle [ %1 ]").arg(evt->getBundle()->getName());
}

void framework::bundle::FrameworkStarterListener::onBundleStoppedEvent(core::event::BundleStoppedEvent *evt)
{
    pfInfo4(getLogBundleName()) << tr("Bundle [ %1 ], Arrêté" ).arg(evt->getBundle()->getName());
    framework::bundle::Framework& fwk{dynamic_cast<framework::bundle::Framework&>(getBundle())};

    if (++m_started_bundles_cpt >= fwk.getNumberOfBundlesToStart())
    {
        fwk.fwkStopped();
    }
}

void framework::bundle::FrameworkStarterListener::startBundle(core::plugin::BundleInterface *bundleItf)
{
    framework::bundle::Framework& fwk{dynamic_cast<framework::bundle::Framework&>(getBundle())};

    if (bundleItf == nullptr)
    {
        pfWarning1(getLogBundleName()) << tr("l'adresse du bundle (plugin) est (nullptr) !");
    }
    else
    {
        // Start the bundle
        //_________________
        framework::factory::FrameworkFactory& myFactory = dynamic_cast<framework::factory::FrameworkFactory&>(getFactory());
        core::bundle::Bundle *bundleImpl{bundleItf->getImpl()};

        // connect to the bundle emitter
        bundleImpl->registerListener(this);

        // and start with bundlecontext
        core::bundle::QspBundleContext bundleCtx{myFactory.createBundleContext(fwk.getRegistryService())};
        bundleItf->start(bundleCtx);
     }
}

