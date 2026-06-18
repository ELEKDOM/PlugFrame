// Copyright (C) 2026 ELEKDOM Christophe Mars c.mars@elekdom.fr
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

namespace plugframe
{
class TBUNDLEServiceInterface : public ServiceInterface
{
public:
    static QString serviceName() {return QStringLiteral("TBUNDLEServiceInterface");}

public:
    ~TBUNDLEServiceInterface() override {}

public:
};
}//namespace plugframe

#define PfTBUNDLEService_iid "plugframe.TBUNDLEServiceInterface"
Q_DECLARE_INTERFACE(plugframe::TBUNDLEServiceInterface, PfTBUNDLEService_iid)

#endif // TBUNDLESERVICEINTERFACE_H
