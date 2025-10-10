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


#include "bundle/longstartbundleimplementation.h"
#include "bundle/bundleemitter.h"
#include "bundle/bundlecontext.h"

using namespace elekdom::plugframe::core::bundle;

elekdom::plugframe::core::bundle::LongStartBundleImplementation::LongStartBundleImplementation(QString logBundleName):
    BundleImplementation{logBundleName}
{

}

LongStartBundleImplementation::~LongStartBundleImplementation()
{

}

void LongStartBundleImplementation::start(QspBundleContext bundleContext)
{
    setState(core::plugin::BundleInterface::BundleState::Starting);
    //notify starting
    getEmitter()->postBundleStartingEvt();
    _start(bundleContext);
}

void LongStartBundleImplementation::defaultListening()
{
    // Long start are performed by a series of small procedures
    // whose sequence is determined by a series of internal events!
    getEmitter()->registerListener(getListener().get());
}

void LongStartBundleImplementation::started()
{
    setState(core::plugin::BundleInterface::BundleState::Started);
    getEmitter()->postBundleStartedEvt();
}
