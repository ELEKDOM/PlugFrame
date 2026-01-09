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

#include "loggerfactory.h"
#include "logfilter.h"
#include "logdisplay.h"
#include "logfile.h"

LoggerFactory::LoggerFactory() {}

LoggerFactory::~LoggerFactory()
{

}

LogFilter *LoggerFactory::createLogFilter(const QString &name, const QString &timestampFormat, uint dFlags, uint wFlags, uint iFlags)
{
    return new LogFilter{name,timestampFormat,dFlags,wFlags,iFlags};
}

LogDevice *LoggerFactory::createLogDisplay(plugframe::DisplayServiceInterface *display)
{
    return new LogDisplay{display};
}

LogDevice *LoggerFactory::createLogFile(const QString &logFileName)
{
    return new LogFile{logFileName};
}
