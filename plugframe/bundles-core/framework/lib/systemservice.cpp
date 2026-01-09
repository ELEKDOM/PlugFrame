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

#include <QCoreApplication>
#include "systemservice.h"
#include "framework.h"
#include "service-int/systemserviceinterface.h"

SystemService::SystemService(plugframe::BundleImplementation *implementation):
    FrameworkServiceImplementation{implementation}
{

}

SystemService::~SystemService()
{

}

QString SystemService::applicationName()
{
    return QCoreApplication::applicationName();
}

bool SystemService::registerListener(plugframe::BundleListener *observer)
{
    QMutexLocker mtxLck{&m_mtx};
    bool         ret{framework()->registerListener(observer)};

    return ret;
}

bool SystemService::unregisterListener(plugframe::BundleListener *observer)
{
    QMutexLocker    mtxLck{&m_mtx};

    return framework()->unregisterListener(observer);
}

plugframe::BundleList SystemService::bundleList()
{
    QMutexLocker    mtxLck{&m_mtx};

    return framework()->bundleList();
}

int SystemService::runningLevel()
{
    QMutexLocker    mtxLck{&m_mtx};

    return framework()->runningLevel();
}

void SystemService::quit()
{
    QMutexLocker    mtxLck{&m_mtx};

    framework()->quit();
}

QString SystemService::serviceName()
{
    return plugframe::SystemServiceInterface::serviceName();
}
