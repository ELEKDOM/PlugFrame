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
#include "guiapplicationsconffilesselector.h"
#include "guiapplicationsconffilesselectoritem.h"

GuiApplicationsConfFilesSelector::GuiApplicationsConfFilesSelector(GuiDeveloperModeView *parent):
    plugframe::GuiWidgetList(parent),
    m_view(parent)
{
    //setScrollListMinimumSize(QSize(0,600));
}

void GuiApplicationsConfFilesSelector::display(const QList<ApplicationArtefact> &applicationArtefactList)
{
    for (auto i=0;i<applicationArtefactList.size();i++)
    {

        if(applicationArtefactList[i].m_confFilesFlag)
        {
            plugframe::GuiWidgetListItem *item;
            QString appliName{applicationArtefactList[i].m_applicationName};
            QList<BundleArtefact> bundleArtefactList{applicationArtefactList[i].m_bundleArtefactList};

            item = new GuiApplicationsConfFilesSelectorItem{i,
                                                            appliName,
                                                            bundleArtefactList,
                                                            m_view};
            displayItem(item);
        }
    }
}