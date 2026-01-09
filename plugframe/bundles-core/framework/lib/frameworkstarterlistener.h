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

#include <QSharedPointer>
#include "bundle/bundlelistener.h"
#include "event/frameworkevent/bundlesstartingevent.h"
#include "event/frameworkevent/bundlesstoppingevent.h"
#include "event/frameworkevent/startbundleevent.h"
#include "event/frameworkevent/stopbundleevent.h"
#include "event/frameworkevent/frameworkstartedevent.h"
#include "event/bundleevent/bundlestartingevent.h"
#include "event/bundleevent/bundlestartedevent.h"
#include "event/bundleevent/bundlestoppingevent.h"
#include "event/bundleevent/bundlestoppedevent.h"

class FrameworkStarterListener : public plugframe::BundleListener
{
public:
    FrameworkStarterListener(plugframe::Bundle& fwk);
    ~FrameworkStarterListener() override;

public:
    void reset() {m_started_bundles_cpt = 0;}

protected:
    void onEvent(plugframe::QspEvent ev) override;
    virtual void onBundlesStartingEvent(plugframe::BundlesStartingEvent *evt);
    virtual void onStartBundleEvent(plugframe::StartBundleEvent *evt);
    virtual void onFrameworkStartedEvent(plugframe::FrameworkStartedEvent *evt);
    virtual void onBundlesStoppingEvent(plugframe::BundlesStoppingEvent *evt);
    virtual void onStopBundleEvent(plugframe::StopBundleEvent *evt);
    virtual void onBundleStartingEvent(plugframe::BundleStartingEvent *evt);
    virtual void onBundleStartedEvent(plugframe::BundleStartedEvent *evt);
    virtual void onBundleStoppingEvent(plugframe::BundleStoppingEvent *evt);
    virtual void onBundleStoppedEvent(plugframe::BundleStoppedEvent *evt);

private:
    void startBundle(plugframe::BundleInterface* bundleItf);

private:
    int m_started_bundles_cpt; // number of started bundles
};
using QspFrameworkStarterListener = QSharedPointer<FrameworkStarterListener>;
#endif // FRAMEWORKSTARTERLISTENER_H
