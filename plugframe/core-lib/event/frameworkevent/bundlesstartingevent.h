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


#ifndef BUNDLES_STARTING_EVENT_H
#define BUNDLES_STARTING_EVENT_H

#include <QString>
#include "pfcore-lib_export.h"
#include "pfcore-lib_forward.h"
#include "frameworkevent.h"

namespace elekdom
{
namespace plugframe
{
namespace core
{
namespace event
{

/**
 * @brief The BundlesStartingEvent class
 */
class PFCORELIB_EXPORT BundlesStartingEvent : public FrameworkEvent
{
public:
    static const QString s_typeId;

public:
    BundlesStartingEvent(plugin::BundleList& bundleList, int frameworkStartLevel, int currentStartLevel);
    ~BundlesStartingEvent() override;

public:
    plugin::BundleList& getBundlesList() {return m_bundlesList;}
    int getFrameworkStartLevel() {return m_frameworkStartLevel;}
    int getCurrentStartLevel() {return m_currentStartLevel;}

private:
   plugin::BundleList m_bundlesList;
   int m_frameworkStartLevel;
   int m_currentStartLevel;
};

} //namespace bundle
} //namespace core
} //namespace event
} //namespace elekdom

#endif // BUNDLES_STARTING_EVENT_H
