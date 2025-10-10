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


#ifndef GUICONSOLE_H
#define GUICONSOLE_H

#include "bundle/bundleimplementation.h"
#include "service-int/guibuilderserviceinterface.h"

namespace elekdom
{
namespace plugframe
{
namespace guiconsole
{
namespace bundle
{

class GuiConsole : public core::bundle::BundleImplementation
{

public:
    GuiConsole();
    ~GuiConsole() override;

protected:
    core::bundle::BundleFactory* createFactory() override;
    void _start(core::bundle::QspBundleContext bundleContext) override;
    virtual void buildGui();
    virtual void buildConsoleController(guidisplay::service::GuiBuilderServiceInterface *builderGuiServiceItf);
    virtual void buildControllerViews(guidisplay::service::GuiBuilderServiceInterface *builderGuiServiceItf);
    virtual QString guiTitle();
    PF_qtServiceInterface_DECL
};

} //namespace bundle
} //namespace guiconsole
} //namespace plugframe
} //namespace elekdom

#endif // GUICONSOLE_H
