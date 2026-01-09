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

FrameworkStarterListener::FrameworkStarterListener(plugframe::Bundle& fwk):
    plugframe::BundleListener{fwk}
{

}

FrameworkStarterListener::~FrameworkStarterListener()
{

}

void FrameworkStarterListener::onEvent(plugframe::QspEvent ev)
{
    plugframe::Event* event{ev.get()};
    QString evtTypeId {ev->getTypeId()};

    if (evtTypeId == plugframe::BundlesStartingEvent::s_typeId)
    {
        onBundlesStartingEvent(dynamic_cast<plugframe::BundlesStartingEvent*>(event));
    }
    else if (evtTypeId == plugframe::StartBundleEvent::s_typeId)
    {
        onStartBundleEvent(dynamic_cast<plugframe::StartBundleEvent*>(event));
    }
    else if (evtTypeId == plugframe::FrameworkStartedEvent::s_typeId)
    {
        onFrameworkStartedEvent(dynamic_cast<plugframe::FrameworkStartedEvent*>(event));
    }
    else if (evtTypeId == plugframe::BundlesStoppingEvent::s_typeId)
    {
        onBundlesStoppingEvent(dynamic_cast<plugframe::BundlesStoppingEvent*>(event));
    }
    else if (evtTypeId == plugframe::StopBundleEvent::s_typeId)
    {
        onStopBundleEvent(dynamic_cast<plugframe::StopBundleEvent*>(event));
    }
    else if (evtTypeId == plugframe::BundleStartingEvent::s_typeId)
    {
        onBundleStartingEvent(dynamic_cast<plugframe::BundleStartingEvent*>(event));
    }
    else if (evtTypeId == plugframe::BundleStartedEvent::s_typeId)
    {
        onBundleStartedEvent(dynamic_cast<plugframe::BundleStartedEvent*>(event));
    }
    else if (evtTypeId == plugframe::BundleStoppingEvent::s_typeId)
    {
        onBundleStoppingEvent(dynamic_cast<plugframe::BundleStoppingEvent*>(event));
    }
    else if (evtTypeId == plugframe::BundleStoppedEvent::s_typeId)
    {
        onBundleStoppedEvent(dynamic_cast<plugframe::BundleStoppedEvent*>(event));
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
void FrameworkStarterListener::onBundlesStartingEvent(plugframe::BundlesStartingEvent *evt)
{
    pfDebug3(getLogBundleName()) << "->SmfFrameworkStarterListener::onBundlesStartingEvent";

    if (evt == nullptr)
    {
        pfWarning1(getLogBundleName()) << tr("l'adresse de l'évènement est (nullptr) !");
    }
    else
    {
        Framework& fwk{dynamic_cast<Framework&>(getBundle())};
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
                plugframe::BundleList_Iterator it, curIt;
                plugframe::BundleList& bundlesToStart {evt->getBundlesList()};
                bool found {false};
                int pos, curPos = 0;

                for (it = bundlesToStart.begin(), pos = 0; (found == false) && (it != bundlesToStart.end()); ++pos, ++it)
                {
                     plugframe::BundleInterface *curBundle = *it;
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

void FrameworkStarterListener::onStartBundleEvent(plugframe::StartBundleEvent *evt)
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

void FrameworkStarterListener::onFrameworkStartedEvent(plugframe::FrameworkStartedEvent *evt)
{
    pfDebug3(getLogBundleName()) << "->SmfFrameworkStarterListener::onFrameworkStartedEvent";

    Q_UNUSED(evt)
    Framework& fwk{dynamic_cast<Framework&>(getBundle())};

    pfDebug5(getLogBundleName()) << tr("Plateforme démarrée au niveau [ %1 ]").arg(fwk.runningLevel());

    // No evt to receive !
    fwk.fwkStarted();

    plugframe::BundleList_Iterator it;
    plugframe::BundleList bundlesList {fwk.bundleList()};

    pfDebug5(getLogBundleName()) << tr("== Liste des bundles démarrés ==");
    for (it = bundlesList.begin(); it != bundlesList.end(); ++it)
    {
        if ( plugframe::BundleInterface::BundleState::Started == (*it)->getState() )
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
void FrameworkStarterListener::onBundlesStoppingEvent(plugframe::BundlesStoppingEvent *evt)
{
    //pfDebug3(getLogBundleName()) << "->SmfFrameworkStarterListener::onBundlesStoppingEvent";

    Framework& fwk{dynamic_cast<Framework&>(getBundle())};

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
            plugframe::BundleList_Iterator it, curIt;
            plugframe::BundleList& bundlesToStop {evt->getBundlesList()};
            bool found {false};
            int pos, curPos = 0;

            for (it = bundlesToStop.begin(), pos = 0; (found == false) && (it != bundlesToStop.end()); ++pos, ++it)
            {
                 plugframe::BundleInterface *curBundle = *it;
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

void FrameworkStarterListener::onStopBundleEvent(plugframe::StopBundleEvent *evt)
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
        plugframe::BundleInterface *bundleItf {evt->getBundleToStop()};

        bundleItf->stop();
    }

    //pfDebug3(getLogBundleName()) << "<-SmfFrameworkStarterListener::onStopBundleEvent";
}

void FrameworkStarterListener::onBundleStartingEvent(plugframe::BundleStartingEvent *evt)
{
    pfDebug5(getLogBundleName()) << tr("Démarrage du bundle [ %1 ]").arg(evt->getBundle()->getName());
}

void FrameworkStarterListener::onBundleStartedEvent(plugframe::BundleStartedEvent *evt)
{
    pfDebug5(getLogBundleName()) << tr("Bundle [ %1 ], démarré").arg(evt->getBundle()->getName());
    Framework& fwk{dynamic_cast<Framework&>(getBundle())};
    int nbOfBundlesToStart{fwk.getNumberOfBundlesToStart()};

    if (++m_started_bundles_cpt == nbOfBundlesToStart)
    {
        // All bundles have been started
        fwk.postFrameworkStartedEvt();
    }
}

void FrameworkStarterListener::onBundleStoppingEvent(plugframe::BundleStoppingEvent *evt)
{
    pfInfo4(getLogBundleName()) << tr("Arrêt du bundle [ %1 ]").arg(evt->getBundle()->getName());
}

void FrameworkStarterListener::onBundleStoppedEvent(plugframe::BundleStoppedEvent *evt)
{
    pfInfo4(getLogBundleName()) << tr("Bundle [ %1 ], Arrêté" ).arg(evt->getBundle()->getName());
    Framework& fwk{dynamic_cast<Framework&>(getBundle())};

    if (++m_started_bundles_cpt >= fwk.getNumberOfBundlesToStart())
    {
        fwk.fwkStopped();
    }
}

void FrameworkStarterListener::startBundle(plugframe::BundleInterface *bundleItf)
{
    Framework& fwk{dynamic_cast<Framework&>(getBundle())};

    if (bundleItf == nullptr)
    {
        pfWarning1(getLogBundleName()) << tr("l'adresse du bundle (plugin) est (nullptr) !");
    }
    else
    {
        // Start the bundle
        //_________________
        FrameworkFactory& myFactory = dynamic_cast<FrameworkFactory&>(getFactory());
        plugframe::Bundle *bundleImpl{bundleItf->getImpl()};

        // connect to the bundle emitter
        bundleImpl->registerListener(this);

        // and start with bundlecontext
        plugframe::QspBundleContext bundleCtx{myFactory.createBundleContext(fwk.getRegistryService())};
        bundleItf->start(bundleCtx);
     }
}

