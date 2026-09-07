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
#ifndef GUICONFIGURATORENGINE_H
#define GUICONFIGURATORENGINE_H

#include "guiengine/lib/guiengine.h"
#include "gui/guipagecontroller.h"

class GuiConfiguratorEngine : public GuiEngine
{
public:
    GuiConfiguratorEngine();
    ~GuiConfiguratorEngine() override;

public:
    QStringList getLauncherConfFileList(const QString& projectName,const QString& applicationName);
    QStringList getBundleConfFileList(const QString& projectName,const QString& applicationName,const QString& bundleName);

protected:
    plugframe::BundleFactory* createFactory() override;
    plugframe::ServiceInterface *qtServiceInterface(const QString& sName) override;
    void postRegister(const plugframe::QspGuiPageController& controller) override;
    bool menuNames(const plugframe::QspGuiPageController& controller,plugframe::GuiMainMenuNames& menuNames) override;
    QString guiTitle() override;

private:
    bool m_hasDeveloperMode;
};
#endif // GUICONFIGURATORENGINE_H
