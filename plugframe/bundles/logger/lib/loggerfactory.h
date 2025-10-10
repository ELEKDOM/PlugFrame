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


#ifndef LOGGERFACTORY_H
#define LOGGERFACTORY_H

#include "factory/defaultbundlefactory.h"
#include "service-int/displayserviceinterface.h"
#include "logger_forward.h"

namespace elekdom
{
namespace plugframe
{
namespace logger
{
namespace factory
{

class LoggerFactory : public core::bundle::DefaultBundleFactory
{
public:
    LoggerFactory();
    ~LoggerFactory() override;

public:
    virtual bundle::LogFilter *createLogFilter(const QString& name,const QString& timestampFormat,uint dFlags,uint wFlags,uint iFlags);
    virtual bundle::LogDevice *createLogDisplay(plugframe::display::service::DisplayServiceInterface *display);
    virtual bundle::LogDevice *createLogFile(const QString& logFileName);
};

} //namespace factory
} //namespace logger
} //namespace plugframe
} //namespace elekdom

#endif // LOGGERFACTORY_H
