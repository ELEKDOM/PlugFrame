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


#include "bundle/bundle.h"
#include "TBUNDLEfactory.h"
#include "TBUNDLEbuilder.h"
#include "TBUNDLEservice.h"
#include "TBUNDLE.h"

using namespace elekdom::plugframe::core::bundle;
using namespace elekdom::plugframe::tbundle::factory;
using namespace elekdom::plugframe::tbundle::builder;
using namespace elekdom::plugframe::tbundle::bundle;
using namespace elekdom::plugframe::tbundle::service;

TBUNDLEFactory::TBUNDLEFactory()
{

}

TBUNDLEFactory::~TBUNDLEFactory()
{

}

BundleBuilder *TBUNDLEFactory::createBuilder(Bundle &myBundle)
{
    return new TBUNDLEBuilder{myBundle};
}

TBUNDLEService *TBUNDLEFactory::createTBUNDLEService(TBUNDLE *implementation)
{
    return new TBUNDLEService{implementation};
}
