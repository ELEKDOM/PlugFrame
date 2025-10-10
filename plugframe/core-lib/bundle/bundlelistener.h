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


#ifndef BUNDLELISTENER_H
#define BUNDLELISTENER_H

#include <QObject>
#include "pfcore-lib_export.h"
#include "pfcore-lib_forward.h"
#include "bundleobject.h"

namespace elekdom
{
namespace plugframe
{
namespace core
{
namespace bundle
{

class PFCORELIB_EXPORT BundleListener : public BundleObject
{
    Q_OBJECT

public:
    BundleListener(Bundle& bundle, QObject *parent = nullptr);
    ~BundleListener() override;

public slots:
    virtual void onEvent(plugframe::core::event::QspEvent ev);
};

} //namespace bundle
} //namespace core
} //namespace plugframe
} //namespace elekdom

#endif // BUNDLELISTENER_H
