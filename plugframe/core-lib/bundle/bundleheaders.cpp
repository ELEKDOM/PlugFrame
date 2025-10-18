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

#include <QStringList>
#include <QRegularExpression>
#include "bundleheaders.h"
#include "logger/pflog.h"

const QString plugframe::BundleHeaders::BUNDLE_MANIFEST_VERSION{"bundle-manifest-version"};
const QString plugframe::BundleHeaders::BUNDLE_VERSION{"bundle-version"};
const QString plugframe::BundleHeaders::BUNDLE_NAME{"bundle-name"};
const QString plugframe::BundleHeaders::STARTLEVEL_BEGING{"startlevel-beging"};
const QString plugframe::BundleHeaders::BUNDLE_CONFIG_FILE_NAME{"bundle-config-file-name"};
const QString plugframe::BundleHeaders::BUNDLE_PROVIDED_SERVICE{"service-provided"};
const QString plugframe::BundleHeaders::BUNDLE_REQUIRED_SERVICE{"service-required"};

const QString plugframe::BundleHeaders::DEFAULT_EMPTY_HEADER_VALUE{""};
const QString plugframe::BundleHeaders::DEFAULT_STARTLEVEL_BEGING_VALUE{"1"};
const QString plugframe::BundleHeaders::BUNDLE_DEFAULT_CONFIG_FILE_NAME{"config.xml"};

void plugframe::BundleHeaders::splitNameVersionFromServiceDeclar(const QString &serviceDeclar, QString &name, QString &version)
{
    QStringList list{serviceDeclar.split(',')};

    name = list[0];
    version= list[1];
}

plugframe::BundleHeaders::BundleHeaders(const QString& logChannel):
    plugframe::Loggable{logChannel}
{
}

plugframe::BundleHeaders::~BundleHeaders()
{
}

///
/// \brief BundleHeaders::insertHeader
/// \param key
/// \param value
/// \details
/// CAUTION: Qt does not allow multiple declarations in metadata json.
/// Also, to allow for such declarations, multiple entries will be numbered.
/// These entries are recreated when loading.
/// This is the case for service declarations!
void plugframe::BundleHeaders::insertHeader(const QString &key, const QString &value)
{
    // New (key,value) to keept into the bundle's header
    // Remove the optional digital part at the end of the string!
    QStringList splitKey;
    QString realkey;
    QRegularExpression regEx("[0-9]{1,2}$");// optional end: 0 to 99

    splitKey = key.split(regEx);
    realkey = splitKey[0];

    pfDebug5(logChannel()) << "insert into ManifestHeader => key : " << realkey << ", value : " << value;
    insert(realkey, value);
}

QString plugframe::BundleHeaders::getName()
{
    return value(plugframe::BundleHeaders::BUNDLE_NAME,
                 plugframe::BundleHeaders::DEFAULT_EMPTY_HEADER_VALUE);
}

int plugframe::BundleHeaders::getStartLevel()
{
    QString start_level = value(plugframe::BundleHeaders::STARTLEVEL_BEGING,
                                plugframe::BundleHeaders::DEFAULT_STARTLEVEL_BEGING_VALUE);
    int bundleStartLevel = start_level.toInt();

    return bundleStartLevel;
}

void plugframe::BundleHeaders::setStartLevel(const QString value)
{
    insert(plugframe::BundleHeaders::STARTLEVEL_BEGING, value);
}

QString plugframe::BundleHeaders::getConfFile()
{
    return value(plugframe::BundleHeaders::BUNDLE_CONFIG_FILE_NAME,
                 plugframe::BundleHeaders::BUNDLE_DEFAULT_CONFIG_FILE_NAME);
}

QList<QString> plugframe::BundleHeaders::getProvidedServices()
{
    return values(BUNDLE_PROVIDED_SERVICE);
}

QList<QString> plugframe::BundleHeaders::getRequiredServices()
{
    return values(BUNDLE_REQUIRED_SERVICE);
}
