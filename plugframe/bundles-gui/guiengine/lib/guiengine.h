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
#ifndef GUIENGINE_H
#define GUIENGINE_H

#include "bundle/bundleimplementation.h"
#include "gui/guipagecontroller.h"
#include "service-int/guibuilderserviceinterface.h"

class GuiEngine : public plugframe::BundleImplementation
{
public:
    GuiEngine();
    ~GuiEngine() override;

public:
    void registerController(const plugframe::QspGuiPageController& controller);

protected:
    virtual void preRegister(const plugframe::QspGuiPageController& controller);
    virtual void postRegister(const plugframe::QspGuiPageController& controller);
    virtual bool menuNames(const plugframe::QspGuiPageController& controller,plugframe::GuiMainMenuNames& menuNames);

protected:
    plugframe::BundleFactory* createFactory() override;
    plugframe::ServiceInterface *qtServiceInterface(const QString& sName) override;
    void _start(plugframe::QspBundleContext bundleContext) override;
    virtual QString guiTitle();

private:
    plugframe::GuiBuilderServiceInterface *builderGuiServiceItf();

};
#endif // GUIENGINE_H
