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

#ifndef SYSTEMSERVICE_H
#define SYSTEMSERVICE_H

#include <QSharedPointer>
#include "frameworkserviceimplementation.h"
#include "plugin/bundleinterface.h"

class SystemService : public FrameworkServiceImplementation
{
public:
    SystemService(plugframe::BundleImplementation *implementation);
    ~SystemService() override;

public:
    QString applicationName();
    bool registerListener(plugframe::BundleListener* observer);
    bool unregisterListener(plugframe::BundleListener* observer);
    plugframe::BundleList bundleList();
    int runningLevel();
    void quit();

protected:
    QString serviceName() override;
};
using QSpSystemService = QSharedPointer<SystemService>;
#endif // SYSTEMSERVICE_H
