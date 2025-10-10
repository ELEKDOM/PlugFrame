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


#ifndef GUIBUILDERSERVICEINTERFACE_H
#define GUIBUILDERSERVICEINTERFACE_H

#include "service-int/serviceinterface.h"
#include "pfcore-lib_forward.h"

namespace elekdom
{
namespace plugframe
{
namespace guidisplay
{
namespace service
{

class GuiBuilderServiceInterface : public core::plugin::ServiceInterface
{
public:
    static QString serviceName() {return QStringLiteral("GuiBuilderServiceInterface");}

public:
    ~GuiBuilderServiceInterface() override {}

public:
    virtual void addGuiController(const core::gui::QspGuiPageController& controller) = 0;
    virtual void removeAllPages(const core::gui::QspGuiPageController& controller) = 0;
    virtual void setMainWindowTitle(const QString& title) = 0;
};

}//namespace service
}//namespace guidisplay
}//namespace plugframe
}//namespace elekdom

#define PfBuilderService_iid "elekdom.plugframe.guidisplay.service.GuiBuilderServiceInterface"
Q_DECLARE_INTERFACE(elekdom::plugframe::guidisplay::service::GuiBuilderServiceInterface, PfBuilderService_iid)

#endif // GUIBUILDERSERVICEINTERFACE_H
