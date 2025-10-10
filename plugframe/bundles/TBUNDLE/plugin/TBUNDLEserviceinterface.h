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


#ifndef TBUNDLESERVICEINTERFACE_H
#define TBUNDLESERVICEINTERFACE_H

#include <QString>
#include "service-int/serviceinterface.h"

namespace elekdom
{
namespace plugframe
{
namespace tbundle
{
namespace service
{

class TBUNDLEServiceInterface : public core::plugin::ServiceInterface
{
public:
    static QString serviceName() {return QStringLiteral("TBUNDLEServiceInterface");}

public:
    virtual ~TBUNDLEServiceInterface() {}

public:
};

}//namespace service
}//namespace tbundle
}//namespace plugframe
}//namespace elekdom

#define PfTBUNDLEService_iid "elekdom.plugframe.tbundle.service.TBUNDLEServiceInterface"
Q_DECLARE_INTERFACE(elekdom::plugframe::tbundle::service::TBUNDLEServiceInterface, PfTBUNDLEService_iid)

#endif // TBUNDLESERVICEINTERFACE_H
