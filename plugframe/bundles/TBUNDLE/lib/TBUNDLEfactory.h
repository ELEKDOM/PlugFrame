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


#ifndef TBUNDLEFACTORY_H
#define TBUNDLEFACTORY_H

#include "factory/bundlefactory.h"
#include "TBUNDLE_forward.h"

namespace elekdom
{
namespace plugframe
{
namespace tbundle
{
namespace factory
{

class TBUNDLEFactory : public core::bundle::BundleFactory
{
public:
    TBUNDLEFactory();
    virtual ~TBUNDLEFactory();

public:
    virtual core::bundle::BundleBuilder *createBuilder(core::bundle::Bundle& myBundle);
    virtual service::TBUNDLEService *createTBUNDLEService(bundle::TBUNDLE *implementation);
};

} //namespace factory
} //namespace tbundle
} //namespace plugframe
} //namespace elekdom

#endif // TBUNDLEFACTORY_H
