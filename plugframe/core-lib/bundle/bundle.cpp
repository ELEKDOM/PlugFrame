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
#include <QFile>
#include <QJsonArray>
#include "logger/pflog.h"
#include "bundle.h"
#include "bundlecontext.h"
#include "bundlebuilder.h"
#include "bundleheaders.h"
#include "bundleemitter.h"
#include "bundlelistener.h"
#include "factory/bundlefactory.h"

using namespace elekdom::plugframe::core::bundle;

/**
 * @brief Bundle::Bundle
 */
Bundle::Bundle(QString logBundleName):
    logger::Loggable(logBundleName),
    m_state{core::plugin::BundleInterface::BundleState::Loaded}
{
}

/**
 * @brief Bundle::~Bundle
 */
Bundle::~Bundle()
{
}

BundleFactory &Bundle::getFactory()
{
    return *m_factory;
}

QObject *Bundle::getQplugin()
{
    return m_qplugin;
}

QString Bundle::getConfPath()
{
    QString ret;
    QString confFile = getHeaders().getConfFile();

    ret = getConfDir() + confFile;

    return ret;
}

QString Bundle::getConfDir()
{
    QString ret{m_absolutePath + "/" + "conf" + "/"};
    return ret;
}

bool Bundle::registerListener(BundleListener *observer)
{
    return getEmitter()->registerListener(observer);
}

bool Bundle::unregisterListener(BundleListener *observer)
{
    return getEmitter()->unregisterListener(observer);
}

//////////////////////////////////
// for Bundle4BuilderInterface
//////////////////////////////////

Bundle &Bundle::getBundle()
{
    return *this;
}

const QString& Bundle::getLogBundleName()
{
    return logChannel();
}

void Bundle::setHeaders(BundleHeaders* bundleHeaders)
{
    m_headers.reset(bundleHeaders);
}

void Bundle::loadManifestHeaders()
{
    // populate the headers from the plugin's metadata
    //-------------------------------------------------
    QJsonValue keyvalues{m_metadata.value("MetaData")};
    QJsonObject keyvaluesobj{keyvalues.toObject()};

    foreach(const QString& key, keyvaluesobj.keys())
    {
        QJsonValue value = keyvaluesobj.value(key);
        pfDebug5(logChannel()) << "ManifestHeader => key : " << key << ", value : " << value.toString();

        // a new key value to keept into the bundle's header
        m_headers->insertHeader(key, value.toString());
    }
}

void Bundle::setEmitter(BundleEmitter *emitter)
{
    m_emitter.reset(emitter);
}

void Bundle::setListener(BundleListener *listener)
{
    m_listener.reset(listener);
}

void Bundle::defaultListening()
{
    // No listening event by default !
}

QspBundleEmitter& Bundle::getEmitter()
{
    return m_emitter;
}

QspBundleListener& Bundle::getListener()
{
    return m_listener;
}

//////////////////////////////////
// for Bundle4PluginInterface
//////////////////////////////////

void Bundle::setQplugin(QObject *qplugin)
{
    m_qplugin = qplugin;
}

void Bundle::setFileName(const QString& fileName)
{
    m_fileName = fileName;
}

void Bundle::setAbsolutePath(const QString& absolutePath)
{
    m_absolutePath = absolutePath;
}

void Bundle::setMetaData(const QJsonObject &metaData)
{
    m_metadata = metaData;
}

/**
 * @brief Bundle::init
 */
void Bundle::init()
{
    // All bundle's objects are created by a factory allowing bundle extending
    m_factory.reset(createFactory());

    // Get the Bundle's builder
    QScopedPointer <BundleBuilder> builder(m_factory->createBuilder(*this));

    // Build the bundle's internal structure
    builder->build();

    m_state = core::plugin::BundleInterface::BundleState::Initialized;
}

void Bundle::start(QspBundleContext bundleContext)
{
    //pfDebug3(logChannel()) << "->Bundle::start()";

    m_state = core::plugin::BundleInterface::BundleState::Starting;

    //notify starting
    m_emitter->postBundleStartingEvt();

    //starting implementation
    _start(bundleContext);

    m_state = core::plugin::BundleInterface::BundleState::Started;

    //Notify started
    m_emitter->postBundleStartedEvt();

    //pfDebug3(logChannel()) << "<-Bundle::start()";
}

void Bundle::stop()
{
    m_state = core::plugin::BundleInterface::BundleState::Stopping;

    //notify stopping
    m_emitter->postBundleStoppingEvt();

    //stopping implementation
    _stop();

    m_state = core::plugin::BundleInterface::BundleState::Stopped;

    //Notify stopped
    m_emitter->postBundleStoppedEvt();
}

QString Bundle::getName()
{
    return getHeaders().getName();
}

Bundle *Bundle::getImpl()
{
    return this;
}

int Bundle::getStartLevel()
{
    return getHeaders().getStartLevel();
}

elekdom::plugframe::core::plugin::BundleInterface::BundleState Bundle::getState()
{
    return m_state;
}

/////////////////////
// internals methods
/////////////////////

BundleHeaders& Bundle::getHeaders()
{
    if (m_headers.isNull())
    {
        pfWarning8(logChannel()) << QObject::tr("Le bundle n'a pas de header !");
    }

    return *m_headers;
}
