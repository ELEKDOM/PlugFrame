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


#ifndef SERVICEINTERFACE_H
#define SERVICEINTERFACE_H

#include <QString>
#include <QSharedPointer>
#include <QHash>
#include <QList>

namespace elekdom
{
namespace plugframe
{
namespace core
{
namespace plugin
{

class ServiceInterface
{
public:
    static QString V_100() {return QStringLiteral("1.0.0");}

public:
    virtual ~ServiceInterface() {}
};

using ServiceInterfaceHash = QHash<QString, plugin::ServiceInterface*>;
using ServiceInterfaceList = QList<plugin::ServiceInterface*>;
using ServiceInterfaceList_Iterator = ServiceInterfaceList::iterator;

}//namespace plugin
}//namespace core
}//namespace plugframe
}//namespace elekdom

#endif // SERVICEINTERFACE_H
