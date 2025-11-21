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

#ifndef GUIDISPLAYSERVICE_H
#define GUIDISPLAYSERVICE_H

#include <QSharedPointer>
#include "service/serviceimplementation.h"

class GuiDisplayService : public plugframe::ServiceImplementation
{
public:
    GuiDisplayService(plugframe::BundleImplementation *implementation);
    ~GuiDisplayService()override;

public:
    void log(const QString &msg);
    void statusMessage(const QString& msg);
    void clearStatusMessages();

protected:
    QString serviceName() override;
};
using QspGuiDisplayService = QSharedPointer<GuiDisplayService>;
#endif // GUIDISPLAYSERVICE_H
