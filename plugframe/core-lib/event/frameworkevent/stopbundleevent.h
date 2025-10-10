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


#ifndef STOPBUNDLEEVENT_H
#define STOPBUNDLEEVENT_H

#include "pfcore-lib_export.h"
#include "frameworkevent.h"
#include "plugin/bundleinterface.h"

namespace elekdom
{
namespace plugframe
{
namespace core
{
namespace event
{

class PFCORELIB_EXPORT StopBundleEvent : public FrameworkEvent
{
private:
    plugin::BundleInterface *m_bundleToStop;

public:
    static const QString s_typeId;

public:
    StopBundleEvent(plugin::BundleInterface *toStop);
    ~StopBundleEvent() override;

public:
    plugin::BundleInterface *getBundleToStop();

};

} //namespace event
} //namespace core
} //namespace plugframe
} //namespace elekdom

#endif // STOPBUNDLEEVENT_H
