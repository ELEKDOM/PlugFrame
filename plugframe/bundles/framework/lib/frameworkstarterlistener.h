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


#ifndef FRAMEWORKSTARTERLISTENER_H
#define FRAMEWORKSTARTERLISTENER_H

#include "bundle/bundlelistener.h"
#include "pfcore-lib_forward.h"

namespace elekdom
{
namespace plugframe
{
namespace framework
{
namespace bundle
{

class FrameworkStarterListener : public core::bundle::BundleListener
{
public:
    FrameworkStarterListener(core::bundle::Bundle& fwk);
    ~FrameworkStarterListener() override;

public:
    void reset() {m_started_bundles_cpt = 0;}

protected:
    void onEvent(core::event::QspEvent ev) override;
    virtual void onBundlesStartingEvent(core::event::BundlesStartingEvent *evt);
    virtual void onStartBundleEvent(core::event::StartBundleEvent *evt);
    virtual void onFrameworkStartedEvent(core::event::FrameworkStartedEvent *evt);
    virtual void onBundlesStoppingEvent(core::event::BundlesStoppingEvent *evt);
    virtual void onStopBundleEvent(core::event::StopBundleEvent *evt);
    virtual void onBundleStartingEvent(core::event::BundleStartingEvent *evt);
    virtual void onBundleStartedEvent(core::event::BundleStartedEvent *evt);
    virtual void onBundleStoppingEvent(core::event::BundleStoppingEvent *evt);
    virtual void onBundleStoppedEvent(core::event::BundleStoppedEvent *evt);

private:
    void startBundle(core::plugin::BundleInterface* bundleItf);

private:
    int m_started_bundles_cpt; // number of started bundles
};

} //namespace bundle
} //namespace framework
} //namespace plugframe
} //namespace elekdom

#endif // FRAMEWORKSTARTERLISTENER_H
