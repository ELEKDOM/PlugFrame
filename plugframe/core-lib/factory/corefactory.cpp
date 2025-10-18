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

#include "corefactory.h"
#include "launcher/launchingproperties.h"
#include "launcher/location.h"
#include "launcher/bundlesstore.h"

plugframe::CoreFactory::~CoreFactory()
{
}

plugframe::QspLaunchingProperties plugframe::CoreFactory::createLaunchingProperties(const QString& fileName)
{
    return plugframe::QspLaunchingProperties(new plugframe::LaunchingProperties(fileName));
}

plugframe::QspLocation plugframe::CoreFactory::createLocation(const QString & applicationDirPath)
{
    return plugframe::QspLocation(new plugframe::Location(applicationDirPath));
}

plugframe::QspBundlesStore plugframe::CoreFactory::createBundlesStore(QspLocation location)
{
    return plugframe::QspBundlesStore(new plugframe::BundlesStore(location));
}

