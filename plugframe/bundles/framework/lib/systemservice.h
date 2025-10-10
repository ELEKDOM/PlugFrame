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

#include "frameworkserviceimplementation.h"
#include "pfcore-lib_forward.h"

namespace elekdom
{
namespace plugframe
{
namespace framework
{
namespace service
{

class SystemService : public FrameworkServiceImplementation
{
public:
    SystemService(core::bundle::BundleImplementation *implementation);
    ~SystemService() override;

public:
    QString applicationName();
    bool registerListener(core::bundle::BundleListener* observer);
    bool unregisterListener(core::bundle::BundleListener* observer);
    core::plugin::BundleList bundleList();
    int runningLevel();
    void quit();

protected:
    QString serviceName() override;
};

} //namespace service
} //namespace framework
} //namespace plugframe
} //namespace elekdom

#endif // SYSTEMSERVICE_H
