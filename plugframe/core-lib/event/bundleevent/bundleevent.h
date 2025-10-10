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


#ifndef SMF_BUNDLE_EVENT_H
#define SMF_BUNDLE_EVENT_H

#include "pfcore-lib_export.h"
#include "event/event.h"
#include "plugin/bundleinterface.h"

namespace elekdom
{
namespace plugframe
{
namespace core
{
namespace event
{

class PFCORELIB_EXPORT BundleEvent : public Event
{
private:
    core::plugin::BundleInterface *m_bundleItf;

public:
    BundleEvent(const QString& typeId, core::plugin::BundleInterface *bundleItf);
    ~BundleEvent() override;

public:
    core::plugin::BundleInterface *getBundle() {return m_bundleItf;}

};

} //namespace event
} //namespace core
} //namespace plugframe
} //namespace elekdom

#endif // SMF_BUNDLE_EVENT_H
