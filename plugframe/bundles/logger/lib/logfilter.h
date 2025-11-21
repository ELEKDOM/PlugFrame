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

#ifndef LOGFILTER_H
#define LOGFILTER_H

#include <QSharedPointer>
#include "logdevice.h"

class LogFilter
{
public:
    LogFilter(const QString& name,const QString& timestampFormat,uint dFlags,uint wFlags,uint iFlags);
    virtual ~LogFilter();

public:
    void addOutput(const QspLogDevice& logDevice);
    void log(QtMsgType type,uint level,const QString& headerlessMsg);
    void close();

private:
    bool ok4log(QtMsgType type, uint level);
    bool testDebug(uint level);
    bool testWarning(uint level);
    bool testInfo(uint level);
    bool testFlags(uint flags, uint level);

private:
    QString      m_name;
    QString      m_timestampFormat;
    uint         m_dFlags;
    uint         m_wFlags;
    uint         m_iFlags;
    QspLogDevice m_firstOutput;
};
using QspLogFilter= QSharedPointer<LogFilter>;
#endif // LOGFILTER_H
