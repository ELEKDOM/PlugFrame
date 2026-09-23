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
#include "guiapplicationsconffilesselectoritem.h"
#include "ui/guidevelopermodeview.h"
#include "guibundlesconffilesselector.h"
#include "ui_guiapplicationconffilesselector.h"

GuiApplicationsConfFilesSelectorItem::GuiApplicationsConfFilesSelectorItem(qsizetype dIndex,
                                                                           const QString &appliName,
                                                                           const QList<BundleArtefact> &bundleArtefactList,
                                                                           GuiDeveloperModeView *developerView):
    plugframe::GuiWidgetListItem{dIndex,developerView},
    ui(new Ui::guiApplicationConfFilesSelector),
    m_view(developerView)
{
    ui->setupUi(this);
    ui->applicationNameLineEdit->setText(appliName);

    connect(ui->confFileEditButton,SIGNAL(clicked(bool)),this,SLOT(onConfFileClicked()));

    // bundles conf files selector list
    m_bundlesConfFilesSelector = new GuiBundlesConfFilesSelector{developerView};
    ui->bundlesConfFilesLocationLayout->addWidget(m_bundlesConfFilesSelector);
    m_bundlesConfFilesSelector->display(appliName,bundleArtefactList);
}

GuiApplicationsConfFilesSelectorItem::~GuiApplicationsConfFilesSelectorItem()
{
    delete ui;
    delete m_bundlesConfFilesSelector;
}

void GuiApplicationsConfFilesSelectorItem::onConfFileClicked()
{
    m_view->editAppConfFile(ui->applicationNameLineEdit->text());
}
