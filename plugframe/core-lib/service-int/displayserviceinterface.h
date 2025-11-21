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

#ifndef DISPLAYSERVICEINTERFACE_H
#define DISPLAYSERVICEINTERFACE_H

#include <QString>
#include "service-int/serviceinterface.h"

namespace plugframe
{
class DisplayServiceInterface : public ServiceInterface
{
public:
    static QString serviceName() {return QStringLiteral("DisplayServiceInterface");}

public:
    ~DisplayServiceInterface() override {}

public:
    virtual void print(const QString& msg) = 0;
    virtual void log(const QString& msg) = 0;
    virtual void statusMessage(const QString& msg) = 0;
    virtual void clearStatusMessages() = 0;
};
}//namespace plugframe

#define PfDisplayService_iid "plugframe.DisplayServiceInterface"
Q_DECLARE_INTERFACE(plugframe::DisplayServiceInterface, PfDisplayService_iid)

#endif // DISPLAYSERVICEINTERFACE_H
