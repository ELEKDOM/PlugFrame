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
#include "bundleemitter.h"
#include "bundlelistener.h"
#include "bundle.h"
#include "factory/bundlefactory.h"

plugframe::BundleEmitter::BundleEmitter(plugframe::Bundle& bundle, QObject *parent):
    plugframe::BundleObject{bundle, parent}
{
}

plugframe::BundleEmitter::~BundleEmitter()
{
}

bool plugframe::BundleEmitter::registerListener(plugframe::BundleListener *observer)
{
    QMutexLocker locker(&m_mutex);
    bool ret {true};

    for (int i = 0; ret && i < m_listenersRegister.size(); ++i)
    {
        ret = m_listenersRegister.at(i) != observer;
    }

    if (ret)
    {
        bool valid = connect(this, SIGNAL(pfEvent(plugframe::QspEvent)),observer,SLOT(onEvent(plugframe::QspEvent)),Qt::QueuedConnection);
        if (!valid)
        {
            pfWarning8(getLogBundleName()) << tr("Echec de connexion entre Emitter et Listener !");
        }
        m_listenersRegister.append(observer);
    }

    return ret;
}

bool plugframe::BundleEmitter::unregisterListener(plugframe::BundleListener *observer)
{
    //pfDebug3(getLogBundleName()) << "->SmfObject::unregisterListener observer" << observer;

    QMutexLocker locker(&m_mutex);

    bool ret {m_listenersRegister.removeOne(observer)};
    if (ret)
    {
        ret = disconnect(this, SIGNAL(pfEvent(plugframe::QspEvent)),observer,SLOT(onEvent(plugframe::QspEvent)));
        pfDebug4(getLogBundleName()) << "-- SmfObject::unregisterListener disconnect processed";
    }

    //pfDebug3(getLogBundleName()) << "<-SmfObject::unregisterListener ret = " << ret;
    return ret;
}

void plugframe::BundleEmitter::postBundleStartingEvt()
{
    //pfDebug3(getLogBundleName()) << "->BundleEmitter::postBundleStartingEvt";

    // Create the event
    BundleFactory& myFactory = getFactory();
    plugframe::QspEvent evt{myFactory.createBundleStartingEvent(getBundleItf())};

    // Post the event
    emit pfEvent(evt);

    //pfDebug3(getLogBundleName()) << "<-BundleEmitter::postBundleStartingEvt";
}

void plugframe::BundleEmitter::postBundleStartedEvt()
{
    //pfDebug3(getLogBundleName()) << "->BundleEmitter::postBundleStartedEvt";

    // Create the event
    plugframe::QspEvent evt{getFactory().createBundleStartedEvent(getBundleItf())};

    // Post the event
    emit pfEvent(evt);

    //pfDebug3(getLogBundleName()) << "<-BundleEmitter::postBundleStartedEvt";
}

void plugframe::BundleEmitter::postBundleStoppingEvt()
{
    //pfDebug3(getLogBundleName()) << "->BundleEmitter::postBundleStoppingEvt";

    // Create the event
    plugframe::QspEvent evt{getFactory().createBundleStoppingEvent(getBundleItf())};

    // Post the event
    emit pfEvent(evt);

    //pfDebug3(getLogBundleName()) << "<-BundleEmitter::postBundleStoppingEvt";
}

void plugframe::BundleEmitter::postBundleStoppedEvt()
{
    //pfDebug3(getLogBundleName()) << "->BundleEmitter::postBundleStoppedEvt";

    // Create the event
    plugframe::QspEvent evt{getFactory().createBundleStoppedEvent(getBundleItf())};

    // Post the event
    emit pfEvent(evt);

    //pfDebug3(getLogBundleName()) << "<-BundleEmitter::postBundleStoppedEvt";
}
