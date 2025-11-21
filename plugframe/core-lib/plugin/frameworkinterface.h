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

#ifndef FRAMEWORKINTERFACE_H
#define FRAMEWORKINTERFACE_H

#include <QObject>
#include "launcher/bundlesstore.h"
#include "launcher/launchingproperties.h"
#include "pfcore-lib_forward.h"

namespace plugframe
{
class  FrameworkInterface
{
public:
    virtual ~FrameworkInterface() {}

public:
    virtual void initFwk(QspBundlesStore bundlesStore,
                         QspLaunchingProperties launchingProperties) = 0;
    virtual BundleInterface *getBundleInterface() = 0;
};
} //namespace plugframe

#define PfFramework_iid "plugframe.FrameworkInterface"
Q_DECLARE_INTERFACE(plugframe::FrameworkInterface, PfFramework_iid)

#endif // FRAMEWORKINTERFACE_H

