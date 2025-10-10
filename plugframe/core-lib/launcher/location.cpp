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


#include "location.h"

using namespace elekdom::plugframe::core::launcher;

const QString Location::BUNDLES_SUBDIR = "bundles";
const QString Location::FRAMEWORK_SUBDIR = "framework";

Location::Location(const QString & applicationDirPath):
    m_applicationDirPath(applicationDirPath)
{
}

bool Location::cdFrameworkBundleDir(QDir& dir)
{
    bool ret;

    ret = cdBundlesDir(dir);
    if (true == ret)
    {
        ret = dir.cd(FRAMEWORK_SUBDIR);
    }

    return ret;
}

bool Location::cdBundlesDir(QDir& dir)
{
    bool ret(false);

    dir.setPath(m_applicationDirPath);

#if defined(Q_OS_WIN)
    if (dir.dirName().toLower() == "debug" || dir.dirName().toLower() == "release")
        dir.cdUp();
#elif defined(Q_OS_MAC)
    if (dir.dirName() == "MacOS") {
        dir.cdUp();
        dir.cdUp();
        dir.cdUp();
    }
#endif
    ret = dir.cd(BUNDLES_SUBDIR);

    return ret;
}

bool Location::isBundleSubDir(const QString& subdirName)
{
    return FRAMEWORK_SUBDIR != subdirName;
}
