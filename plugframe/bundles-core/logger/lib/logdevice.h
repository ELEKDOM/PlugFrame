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

#ifndef LOGDEVICE_H
#define LOGDEVICE_H

#include <QSharedPointer>

class LogDevice
{
public:
    LogDevice();
    virtual ~LogDevice();

public:
    void next(const QSharedPointer<LogDevice>& next) {m_next = next;}
    void log(const QString& msg);
    void close();

protected:
    virtual void _log(const QString& msg) = 0;
    virtual void _close() = 0;

private:
    QSharedPointer<LogDevice> m_next;
};
using QspLogDevice = QSharedPointer<LogDevice>;
#endif // LOGDEVICE_H
