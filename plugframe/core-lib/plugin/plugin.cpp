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
#include "bundle/bundle4plugininterface.h"

plugframe::Plugin::Plugin():
    m_qplugin{nullptr}
{

}

plugframe::Plugin::~Plugin()
{

}

void plugframe::Plugin::setFileName(const QString &fileName)
{
    m_fileName = fileName;
}

void plugframe::Plugin::setAbsolutePath(const QString &absolutePath)
{
    m_absolutePath = absolutePath;
}

void plugframe::Plugin::setMetaData(const QJsonObject &metaData)
{
    m_metadata = metaData;
}

void plugframe::Plugin::setQplugin(QObject *qplugin)
{
    m_qplugin = qplugin;
}

void plugframe::Plugin::init()
{
    _init();
}

void plugframe::Plugin::start(plugframe::QspBundleContext bundleContext)
{
    if (!m_implementation.isNull())
    {
        m_implementation->start(bundleContext);
    }
}

void plugframe::Plugin::stop()
{
    if (!m_implementation.isNull())
    {
        m_implementation->stop();
    }
}

QString plugframe::Plugin::getName()
{
    QString ret;

    if (!m_implementation.isNull())
    {
        ret = m_implementation->getName();
    }

    return ret;
}

plugframe::Bundle *plugframe::Plugin::getImpl()
{
    plugframe::Bundle *ret{nullptr};

    if (!m_implementation.isNull())
    {
        ret = m_implementation->getImpl();
    }

    return ret;
}

int plugframe::Plugin::getStartLevel()
{
    int ret{0};

    if (!m_implementation.isNull())
    {
        ret = m_implementation->getStartLevel();
    }

    return ret;
}

plugframe::BundleInterface::BundleState plugframe::Plugin::getState()
{
   BundleInterface::BundleState ret{BundleInterface::BundleState::Unknown};

   if (!m_implementation.isNull())
   {
       ret = m_implementation->getState();
   }

   return ret;
}

QString plugframe::Plugin::state2String(BundleInterface::BundleState state)
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

void plugframe::Plugin::_init()
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

plugframe::QspBundle4PluginInterface& plugframe::Plugin::implementation()
{
    return m_implementation;
}
