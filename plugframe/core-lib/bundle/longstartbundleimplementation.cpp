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

plugframe::LongStartBundleImplementation::LongStartBundleImplementation(QString logBundleName):
    plugframe::BundleImplementation{logBundleName}
{

}

plugframe::LongStartBundleImplementation::~LongStartBundleImplementation()
{

}

void plugframe::LongStartBundleImplementation::start(plugframe::QspBundleContext bundleContext)
{
    setState(plugframe::BundleInterface::BundleState::Starting);
    //notify starting
    getEmitter()->postBundleStartingEvt();
    _start(bundleContext);
}

void plugframe::LongStartBundleImplementation::defaultListening()
{
    // Long start are performed by a series of small procedures
    // whose sequence is determined by a series of internal events!
    getEmitter()->registerListener(getListener().get());
}

void plugframe::LongStartBundleImplementation::started()
{
    setState(plugframe::BundleInterface::BundleState::Started);
    getEmitter()->postBundleStartedEvt();
}
