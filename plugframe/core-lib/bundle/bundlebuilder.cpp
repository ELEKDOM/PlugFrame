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
#include "bundle/bundlebuilder.h"
#include "bundle/bundle.h"
#include "bundle/bundleheaders.h"
#include "factory/bundlefactory.h"

plugframe::BundleBuilder::BundleBuilder(Bundle4BuilderInterface& myBundle) :
    m_bundleItf{myBundle}
{
}

plugframe::BundleBuilder::~BundleBuilder()
{
}

/**
 * @brief smf::core::bundle::BundleBuilder::build
 * @param myBundle
 */
void plugframe::BundleBuilder::build()
{
    plugframe::BundleFactory& factory {getFactory()};

    // Bundle's internal structure building
    //-------------------------------------

    // Build the bundle's headers
    //---------------------------
    BundleHeaders *headers{factory.createHeaders(getBundle().logChannel())};
    setHeaders(headers);

    // Populate the headers from the manifest file
    loadManifestHeaders();

    // Build bundle's emitter and listener
    setEmitter(factory.createBundleEmitter(getBundle()));
    setListener(factory.createBundleListener(getBundle()));

    // Default listener connections
    defaultListening();

    // Build the exported services
    buildExportedServices(headers->getProvidedServices());

    // Build internal bundle structure
    //-------------------------------
    specificBuild();
}

plugframe::Bundle& plugframe::BundleBuilder::getBundle()
{
    return m_bundleItf.getBundle();
}

plugframe::BundleImplementation *plugframe::BundleBuilder::getImplementation()
{
    return m_bundleItf.getImplementation();
}

const QString& plugframe::BundleBuilder::getLogBundleName()
{
    return m_bundleItf.getLogBundleName();
}

plugframe::BundleFactory& plugframe::BundleBuilder::getFactory()
{
    return m_bundleItf.getFactory();
}

void plugframe::BundleBuilder::setHeaders(BundleHeaders *bundleHeaders)
{
    m_bundleItf.setHeaders(bundleHeaders);
}

void plugframe::BundleBuilder::loadManifestHeaders()
{
    m_bundleItf.loadManifestHeaders();
}

void plugframe::BundleBuilder::setEmitter(BundleEmitter *emitter)
{
    m_bundleItf.setEmitter(emitter);
}

void plugframe::BundleBuilder::setListener(BundleListener *listener)
{
    m_bundleItf.setListener(listener);
}

void plugframe::BundleBuilder::addExportedService(plugframe::QspServiceImplementationInterface newService)
{
    m_bundleItf.addExportedService(newService);
}

void plugframe::BundleBuilder::defaultListening()
{
    m_bundleItf.defaultListening();
}

void plugframe::BundleBuilder::specificBuild()
{
    // No op by default !
}

void plugframe::BundleBuilder::buildExportedServices(const QList<QString>& providedServices)
{
    plugframe::BundleFactory& factory {getFactory()};
    plugframe::QspServiceImplementationInterface servImpl;
    qsizetype nbServices{providedServices.size()};

    for (qsizetype i=0;i<nbServices;i++)
    {
        const QString& name_version{providedServices.at(i)};
        QString serviceName,serviceVersion;

        plugframe::BundleHeaders::splitNameVersionFromServiceDeclar(name_version,serviceName,serviceVersion);

        servImpl.reset(factory.createServiceImplementation(getImplementation(),serviceName,serviceVersion));
        if (servImpl.isNull())
        {
            pfErr(getLogBundleName()) << QObject::tr("service %1 version %2 non créé").arg(serviceName,serviceVersion);
        }
        else
        {
            addExportedService(servImpl);  // Add internal implementation
        }
    }
}
