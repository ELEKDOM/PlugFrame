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


#ifndef SERVICEIMPLEMENTATION_H
#define SERVICEIMPLEMENTATION_H

#include <QMutex>
#include "serviceimplementationinterface.h"
#include "pfcore-lib_forward.h"
#include "pfcore-lib_export.h"

namespace elekdom
{
namespace plugframe
{
namespace core
{
namespace service
{

class PFCORELIB_EXPORT ServiceImplementation : public ServiceImplementationInterface
{
private:
    bundle::BundleImplementation *m_implementation;

protected:
    QMutex m_mtx;

public:
    ServiceImplementation(bundle::BundleImplementation *implementation);
    ~ServiceImplementation() override;

protected:
    bundle::BundleImplementation *implementation() {return m_implementation;}
};

} //namespace service
} //namespace core
} //namespace plugframe
} //namespace elekdom
#endif // SERVICEIMPLEMENTATION_H
