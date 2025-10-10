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


#ifndef LOCATION_H
#define LOCATION_H

#include <QString>
#include <QDir>
#include "pfcore-lib_export.h"

namespace elekdom
{
namespace plugframe
{
namespace core
{
namespace launcher
{

class PFCORELIB_EXPORT Location
{
private:
    static const QString BUNDLES_SUBDIR;
    static const QString FRAMEWORK_SUBDIR;

public:
    Location(const QString & applicationDirPath);

    bool cdFrameworkBundleDir(QDir& dir);
    bool cdBundlesDir(QDir& dir);
    bool isBundleSubDir(const QString& subdirName);

private:
    QString m_applicationDirPath;
};

} //namespace launcher
} //namespace core
} //namespace plugframe
} //namespace elekdom

#endif // LOCATION_H
