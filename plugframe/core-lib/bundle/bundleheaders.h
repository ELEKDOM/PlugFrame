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

#ifndef BUNDLE_HEADERS_H
#define BUNDLE_HEADERS_H

#include <QMultiHash>
#include <QString>
#include <QSharedPointer>
#include "logger/loggable.h"
#include "pfcore-lib_export.h"

namespace plugframe
{
class PFCORELIB_EXPORT BundleHeaders : private QMultiHash<QString, QString>,
                                       public plugframe::Loggable
{
private:
    static const QString BUNDLE_MANIFEST_VERSION;  // Declared in the bundle's meta data but not used
    static const QString BUNDLE_VERSION; // Declared in the bundle's meta data but not used
    static const QString BUNDLE_NAME;
    static const QString STARTLEVEL_BEGING;
    static const QString BUNDLE_CONFIG_FILE_NAME;
    static const QString BUNDLE_PROVIDED_SERVICE; // Declares the name and version of the provided(exported) service. Can be declared zero or more times in the header.
    static const QString BUNDLE_REQUIRED_SERVICE; // Declares the name and version of the required service. Can be declared zero or more times in the header.

    static const QString DEFAULT_EMPTY_HEADER_VALUE;
    static const QString DEFAULT_STARTLEVEL_BEGING_VALUE;
    static const QString BUNDLE_DEFAULT_CONFIG_FILE_NAME;

public:
    static void splitNameVersionFromServiceDeclar(const QString& serviceDeclar,QString& name,QString& version);

public:
    BundleHeaders(const QString& logChannel);
    ~BundleHeaders();

public:
    void insertHeader(const QString& key,const QString& value);
    QString getName();
    int getStartLevel();
    void setStartLevel(const QString value);
    QString getConfFile();
    QList<QString> getProvidedServices();
    QList<QString> getRequiredServices();
};
using QspBundleHeaders = QSharedPointer<BundleHeaders>;
} //namespace plugframe

#endif // BUNDLE_HEADERS_H
