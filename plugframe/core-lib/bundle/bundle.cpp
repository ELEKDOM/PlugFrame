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
#include "bundlebuilder.h"
#include "bundleheaders.h"
#include "bundleemitter.h"
#include "bundlelistener.h"
#include "factory/bundlefactory.h"

/**
 * @brief Bundle::Bundle
 */
plugframe::Bundle::Bundle(QString logBundleName):
    plugframe::Loggable(logBundleName),
    m_state{plugframe::BundleInterface::BundleState::Loaded}
{
}

/**
 * @brief Bundle::~Bundle
 */
plugframe::Bundle::~Bundle()
{
}

plugframe::BundleFactory &plugframe::Bundle::getFactory()
{
    return *m_factory;
}

QObject *plugframe::Bundle::getQplugin()
{
    return m_qplugin;
}

QString plugframe::Bundle::getConfPath()
{
    QString ret;
    QString confFile = getHeaders().getConfFile();

    ret = getConfDir() + confFile;

    return ret;
}

QString plugframe::Bundle::getConfDir()
{
    QString ret{m_absolutePath + "/" + "conf" + "/"};
    return ret;
}

bool plugframe::Bundle::registerListener(BundleListener *observer)
{
    return getEmitter()->registerListener(observer);
}

bool plugframe::Bundle::unregisterListener(BundleListener *observer)
{
    return getEmitter()->unregisterListener(observer);
}

//////////////////////////////////
// for Bundle4BuilderInterface
//////////////////////////////////

plugframe::Bundle& plugframe::Bundle::getBundle()
{
    return *this;
}

const QString& plugframe::Bundle::getLogBundleName()
{
    return logChannel();
}

void plugframe::Bundle::setHeaders(plugframe::BundleHeaders* bundleHeaders)
{
    m_headers.reset(bundleHeaders);
}

void plugframe::Bundle::loadManifestHeaders()
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

void plugframe::Bundle::setEmitter(plugframe::BundleEmitter *emitter)
{
    m_emitter.reset(emitter);
}

void plugframe::Bundle::setListener(plugframe::BundleListener *listener)
{
    m_listener.reset(listener);
}

void plugframe::Bundle::defaultListening()
{
    // No listening event by default !
}

plugframe::QspBundleEmitter& plugframe::Bundle::getEmitter()
{
    return m_emitter;
}

plugframe::QspBundleListener& plugframe::Bundle::getListener()
{
    return m_listener;
}

//////////////////////////////////
// for Bundle4PluginInterface
//////////////////////////////////

void plugframe::Bundle::setQplugin(QObject *qplugin)
{
    m_qplugin = qplugin;
}

void plugframe::Bundle::setFileName(const QString& fileName)
{
    m_fileName = fileName;
}

void plugframe::Bundle::setAbsolutePath(const QString& absolutePath)
{
    m_absolutePath = absolutePath;
}

void plugframe::Bundle::setMetaData(const QJsonObject &metaData)
{
    m_metadata = metaData;
}

/**
 * @brief Bundle::init
 */
void plugframe::Bundle::init()
{
    // All bundle's objects are created by a factory allowing bundle extending
    m_factory.reset(createFactory());

    // Get the Bundle's builder
    QScopedPointer <plugframe::BundleBuilder> builder(m_factory->createBuilder(*this));

    // Build the bundle's internal structure
    builder->build();

    m_state = plugframe::BundleInterface::BundleState::Initialized;
}

void plugframe::Bundle::start(plugframe::QspBundleContext bundleContext)
{
    //pfDebug3(logChannel()) << "->Bundle::start()";

    m_state = plugframe::BundleInterface::BundleState::Starting;

    //notify starting
    m_emitter->postBundleStartingEvt();

    //starting implementation
    _start(bundleContext);

    m_state = plugframe::BundleInterface::BundleState::Started;

    //Notify started
    m_emitter->postBundleStartedEvt();

    //pfDebug3(logChannel()) << "<-Bundle::start()";
}

void plugframe::Bundle::stop()
{
    m_state = plugframe::BundleInterface::BundleState::Stopping;

    //notify stopping
    m_emitter->postBundleStoppingEvt();

    //stopping implementation
    _stop();

    m_state = plugframe::BundleInterface::BundleState::Stopped;

    //Notify stopped
    m_emitter->postBundleStoppedEvt();
}

QString plugframe::Bundle::getName()
{
    return getHeaders().getName();
}

plugframe::Bundle *plugframe::Bundle::getImpl()
{
    return this;
}

int plugframe::Bundle::getStartLevel()
{
    return getHeaders().getStartLevel();
}

plugframe::BundleInterface::BundleState plugframe::Bundle::getState()
{
    return m_state;
}

/////////////////////
// internals methods
/////////////////////

plugframe::BundleHeaders& plugframe::Bundle::getHeaders()
{
    if (m_headers.isNull())
    {
        pfWarning8(logChannel()) << QObject::tr("Le bundle n'a pas de header !");
    }

    return *m_headers;
}
