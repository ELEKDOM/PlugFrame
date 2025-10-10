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


#ifndef LOGDISPLAY_H
#define LOGDISPLAY_H

#include "logdevice.h"
#include "service-int/displayserviceinterface.h"

namespace elekdom
{
namespace plugframe
{
namespace logger
{
namespace bundle
{

class LogDisplay : public LogDevice
{
public:
    LogDisplay(plugframe::display::service::DisplayServiceInterface *display);
    ~LogDisplay() override;

protected:
    void _log(const QString& msg) override;
    void _close() override;

private:
    plugframe::display::service::DisplayServiceInterface *m_display;
};

} //namespace bundle
} //namespace logger
} //namespace plugframe
} //namespace elekdom

#endif // LOGDISPLAY_H
