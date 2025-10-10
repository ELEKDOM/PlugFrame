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


#ifndef FRAMEWORKSTARTER_H
#define FRAMEWORKSTARTER_H

#include "bundle/bundleemitter.h"
#include "pfcore-lib_forward.h"

namespace elekdom
{
namespace plugframe
{
namespace framework
{
namespace bundle
{
class FrameworkStarter : public core::bundle::BundleEmitter
{
public:
    FrameworkStarter(core::bundle::Bundle& fwk);
    ~FrameworkStarter() override;

public:
    void start();
    void stop();
    void postBundlesStartingEvt(core::plugin::BundleList& bundlesToStart, int frameworkStartLevel, int curStartLevel);
    void postStartBundleEvt(core::plugin::BundleInterface *toStart);
    void postFrameworkStartedEvt();
    void postBundlesStoppingEvt(core::plugin::BundleList& bundlesToStop, int curStopLevel);
    void postStopBundleEvt(core::plugin::BundleInterface *toStop);

protected:
    virtual void startAllBundles();
    virtual void stopAllBundles();
};

using QspSmfFrameworkStarter = QSharedPointer<FrameworkStarter>;

} //namespace bundle
} //namespace framework
} //namespace plugframe
} //namespace elekdom

#endif // FRAMEWORKSTARTER_H
