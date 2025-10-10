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


#ifndef GUIBUILDERSERVICE_H
#define GUIBUILDERSERVICE_H

#include "service/serviceimplementation.h"

namespace elekdom
{
namespace plugframe
{
namespace guidisplay
{
namespace service
{

class GuiBuilderService : public core::service::ServiceImplementation
{
public:
    GuiBuilderService(core::bundle::BundleImplementation *implementation);
    ~GuiBuilderService() override;

public:
    void addGuiController(const core::gui::QspGuiPageController& controller);
    void removeAllPages(const core::gui::QspGuiPageController& controller);
    void setMainWindowTitle(const QString& title);

protected:
    QString serviceName() override;
};

} //namespace service
} //namespace guidisplay
} //namespace plugframe
} //namespace elekdom

#endif // GUIBUILDERSERVICE_H
