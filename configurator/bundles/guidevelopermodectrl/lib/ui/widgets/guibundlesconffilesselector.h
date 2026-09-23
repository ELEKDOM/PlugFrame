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
#ifndef GUIBUNDLESCONFFILESSELECTOR_H
#define GUIBUNDLESCONFFILESSELECTOR_H

#include "gui/widgets/guiwidgetlist.h"
#include "ui/guidevelopermodeview.h"

class GuiBundlesConfFilesSelector : public plugframe::GuiWidgetList
{
    Q_OBJECT

public:
    explicit GuiBundlesConfFilesSelector(GuiDeveloperModeView *parent = nullptr);

public:
    void display(const QString& appliName, const QList<BundleArtefact>& bundleArtefactList);

signals:

private:
    GuiDeveloperModeView *m_view;
};

#endif // GUIBUNDLESCONFFILESSELECTOR_H
