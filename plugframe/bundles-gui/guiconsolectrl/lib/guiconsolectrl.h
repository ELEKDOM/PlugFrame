// Copyright (C) 2026 ELEKDOM Christophe Mars c.mars@elekdom.fr
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
#ifndef GUICONSOLECTRL_H
#define GUICONSOLECTRL_H

#include "abstract_controllerviews_loader/guicontrollerviewsloader.h"

class GuiConsoleCtrl : public plugframe::GuiControllerViewsLoader
{
public:
    GuiConsoleCtrl();
    ~GuiConsoleCtrl() override;

protected:
    plugframe::BundleFactory* createFactory() override;
    void postBuildController(plugframe::QspGuiPageController guiCtrl) override;
    PF_qtServiceInterface_DECL
};

#endif // GUICONSOLECTRL_H
