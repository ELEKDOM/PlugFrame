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


#ifndef LOGGEDUSER_H
#define LOGGEDUSER_H

#include <QSharedPointer>
#include <QString>

namespace elekdom
{
namespace plugframe
{
namespace users
{
namespace bundle
{

class LoggedUser
{
public:
    LoggedUser(const QString& frontendItf,const QString& identifier,const quint32& sessionId);
    ~LoggedUser();

public:
    QString frontendItf() {return m_frontendItf;}
    QString identifier() {return m_identifier;}
    quint32 sessionId() {return m_sessionId;}

private:
    QString m_frontendItf;
    QString m_identifier;
    quint32 m_sessionId;
};

}//namespace bundle
}//namespace users
}//namespace plugframe
}//namespace elekdom

#endif // LOGGEDUSER_H
