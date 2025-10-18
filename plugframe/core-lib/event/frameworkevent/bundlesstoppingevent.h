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

#ifndef BUNDLESSTOPPINGEVENT_H
#define BUNDLESSTOPPINGEVENT_H

#include <QString>
#include "frameworkevent.h"
#include "plugin/bundleinterface.h"
#include "pfcore-lib_export.h"

namespace plugframe
{
class PFCORELIB_EXPORT BundlesStoppingEvent : public FrameworkEvent
{
public:
    static const QString s_typeId;

public:
    BundlesStoppingEvent(BundleList& bundleList, int currentStopLevel);
    ~BundlesStoppingEvent() override;

public:
    BundleList& getBundlesList() {return m_bundlesList;}
    int getCurrentStopLevel() {return m_currentStopLevel;}

private:
    BundleList m_bundlesList;
    int        m_currentStopLevel;
};
} //namespace plugframe

#endif // BUNDLESSTOPPINGEVENT_H
