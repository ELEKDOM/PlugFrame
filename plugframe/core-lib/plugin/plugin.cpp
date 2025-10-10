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


#include "plugin/plugin.h"
#include "bundle/bundlecontext.h"
#include "bundle/bundle4plugininterface.h"

using namespace elekdom::plugframe::core::plugin;

Plugin::Plugin():
    m_qplugin{nullptr}
{

}

Plugin::~Plugin()
{

}

void Plugin::setFileName(const QString &fileName)
{
    m_fileName = fileName;
}

void Plugin::setAbsolutePath(const QString &absolutePath)
{
    m_absolutePath = absolutePath;
}

void Plugin::setMetaData(const QJsonObject &metaData)
{
    m_metadata = metaData;
}

void Plugin::setQplugin(QObject *qplugin)
{
    m_qplugin = qplugin;
}

void Plugin::init()
{
    _init();
}

void Plugin::start(bundle::QspBundleContext bundleContext)
{
    if (!m_implementation.isNull())
    {
        m_implementation->start(bundleContext);
    }
}

void Plugin::stop()
{
    if (!m_implementation.isNull())
    {
        m_implementation->stop();
    }
}

QString Plugin::getName()
{
    QString ret;

    if (!m_implementation.isNull())
    {
        ret = m_implementation->getName();
    }

    return ret;
}

elekdom::plugframe::core::bundle::Bundle *Plugin::getImpl()
{
    elekdom::plugframe::core::bundle::Bundle *ret{nullptr};

    if (!m_implementation.isNull())
    {
        ret = m_implementation->getImpl();
    }

    return ret;
}

int Plugin::getStartLevel()
{
    int ret{0};

    if (!m_implementation.isNull())
    {
        ret = m_implementation->getStartLevel();
    }

    return ret;
}

BundleInterface::BundleState Plugin::getState()
{
   BundleInterface::BundleState ret{BundleInterface::BundleState::Unknown};

   if (!m_implementation.isNull())
   {
       ret = m_implementation->getState();
   }

   return ret;
}

QString Plugin::state2String(BundleInterface::BundleState state)
{
    switch (state)
    {
        case BundleInterface::BundleState::Unknown:
                return QStringLiteral("Unknown");
        case BundleInterface::BundleState::Loaded:
                return QStringLiteral("Loaded");
        case BundleInterface::BundleState::Initialized:
                return QStringLiteral("Initialized");
        case BundleInterface::BundleState::Starting:
                return QStringLiteral("Starting");
        case BundleInterface::BundleState::Started:
            return QStringLiteral("Started");
        case BundleInterface::BundleState::Stopping:
                return QStringLiteral("Stopping");
        case BundleInterface::BundleState::Stopped:
                return QStringLiteral("Stopped");
    }
    return "";
}

void Plugin::_init()
{
    m_implementation.reset(createImplementation());

    if (!m_implementation.isNull())
    {
        m_implementation->setFileName(m_fileName);
        m_implementation->setAbsolutePath(m_absolutePath);
        m_implementation->setMetaData(m_metadata);
        m_implementation->setQplugin(m_qplugin);
        m_implementation->init();
        bindServicesImplementations();
    }
}

elekdom::plugframe::core::bundle::QspBundle4PluginInterface &Plugin::implementation()
{
    return m_implementation;
}
