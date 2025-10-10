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


#ifndef GUIDISPLAY_H
#define GUIDISPLAY_H

#include <QString>
#include "bundle/bundleimplementation.h"
#include "guidisplay_forward.h"

namespace elekdom
{
namespace plugframe
{
namespace guidisplay
{
namespace bundle
{

class GuiDisplay : public core::bundle::BundleImplementation
{

public:
    GuiDisplay();
    ~GuiDisplay() override;

public:
    void log(const QString& msg);
    void statusMessage(const QString& msg);
    void clearStatusMessages();
    void addGuiController(const core::gui::QspGuiPageController& controller);
    void removeAllPages(const core::gui::QspGuiPageController& controller);
    void setMainWindowTitle(const QString& title);
    void closeApp();

protected:
    core::bundle::BundleFactory* createFactory() override;
    core::plugin::ServiceInterface *qtServiceInterface(const QString& sName) override;
    void _start(core::bundle::QspBundleContext bundleContext) override;
    virtual void buildGui();

private:
    GuiHook *m_guiHook;  // mainwindow's child, deleted by Qt
};

} //namespace bundle
} //namespace guidisplay
} //namespace plugframe
} //namespace elekdom

#endif // GUIDISPLAY_H
