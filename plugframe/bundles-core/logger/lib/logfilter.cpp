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

#include <QTextStream>
#include <QDateTime>
#include "logfilter.h"
#include "logdevice.h"

LogFilter::LogFilter(const QString &name, const QString &timestampFormat, uint dFlags, uint wFlags, uint iFlags):
    m_name{name},
    m_timestampFormat{timestampFormat},
    m_dFlags{dFlags},
    m_wFlags{wFlags},
    m_iFlags{iFlags}
{

}

LogFilter::~LogFilter()
{

}

void LogFilter::addOutput(const QspLogDevice& logDevice)
{
    logDevice->next(m_firstOutput);
    m_firstOutput = logDevice;
}

void LogFilter::log(QtMsgType type, uint level, const QString &headerlessMsg)
{
    if (ok4log(type, level))
    {
        QString line;
        QTextStream txtStream(&line);
        QDateTime timestamp{QDateTime::currentDateTime()};

        if (type == QtDebugMsg)
        {
            txtStream << "D";
        }
        else if (type == QtInfoMsg)
        {
            txtStream << "I";
        }
        else if (type == QtWarningMsg)
        {
            txtStream << "W";
        }

        txtStream << level << " " << timestamp.toString(m_timestampFormat) << "[" << m_name << "]  " << headerlessMsg << "\n";

        if (!m_firstOutput.isNull())
        {
            m_firstOutput->log(line);
        }

    } //if (filter->ok4log(type, level))
}

void LogFilter::close()
{
    m_firstOutput->close();
}

bool LogFilter::ok4log(QtMsgType type, uint level)
{
    bool ret{false};

    if (type == QtMsgType::QtDebugMsg)
    {
        ret = testDebug(level);
    }
    else if (type == QtMsgType::QtWarningMsg)
    {
        ret = testWarning(level);
    }
    else if(type == QtMsgType::QtInfoMsg)
    {
        ret = testInfo(level);
    }
    return ret;
}

bool LogFilter::testDebug(uint level)
{
    return testFlags(m_dFlags,level);
}

bool LogFilter::testWarning(uint level)
{
    return testFlags(m_wFlags,level);
}

bool LogFilter::testInfo(uint level)
{
    return testFlags(m_iFlags,level);
}

bool LogFilter::testFlags(uint flags, uint level)
{
    return flags & (0x01 << (level - 1));
}
