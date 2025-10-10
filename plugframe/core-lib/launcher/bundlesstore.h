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


#ifndef BUNDLESSTORE_H
#define BUNDLESSTORE_H

#include <QString>
#include "pfcore-lib_export.h"
#include "pfcore-lib_forward.h"

namespace elekdom
{
namespace plugframe
{
namespace core
{
namespace launcher
{

/**
 * @brief The BundlesStore class
 */
class PFCORELIB_EXPORT BundlesStore
{
public:
    BundlesStore(QspLocation location);

public:
    plugframe::framework::plugin::FrameworkInterface* loadFrameworkPlugin(QString caller);
    void loadPlugins(QString caller, plugin::BundleList& bundleList);

private:
    QspLocation m_location;
};

} //namespace bundle
} //namespace core
} //namespace plugframe
} //namespace elekdom

#endif // BUNDLESSTORE_H
