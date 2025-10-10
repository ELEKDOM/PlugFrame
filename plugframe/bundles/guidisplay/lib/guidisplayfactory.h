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


#ifndef GUIDISPLAYFACTORY_H
#define GUIDISPLAYFACTORY_H

#include "factory/bundlefactory.h"
#include "guidisplay_forward.h"

namespace elekdom
{
namespace plugframe
{
namespace guidisplay
{
namespace factory
{

class GuiDisplayFactory : public core::bundle::BundleFactory
{
public:
    GuiDisplayFactory();
    ~GuiDisplayFactory() override;

public:
    virtual Gui *createGui();
    virtual GuiHook *createGuiHook(Gui* parent, bundle::GuiDisplay& bundle);
    virtual GuiLogsController *createLogsPageController();

protected:
    virtual service::GuiDisplayService *createDisplayService(core::bundle::BundleImplementation *implementation);
    virtual service::GuiBuilderService *createBuilderService(core::bundle::BundleImplementation *implementation);
    core::service::ServiceImplementationInterface *createServiceImplementation(core::bundle::BundleImplementation *implementation,
                                                                               const QString& sName,
                                                                               const QString& serviceVersion) override;

};

} //namespace factory
} //namespace guidisplay
} //namespace plugframe
} //namespace elekdom

#endif // GUIDISPLAYFACTORY_H
