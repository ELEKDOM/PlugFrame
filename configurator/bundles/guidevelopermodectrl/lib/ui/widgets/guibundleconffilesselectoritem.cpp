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
#include "guibundleconffilesselectoritem.h"
#include "ui/guidevelopermodeview.h"
#include "ui_guibundleconffilesselector.h"

GuiBundleConfFilesSelectorItem::GuiBundleConfFilesSelectorItem(qsizetype dIndex,
                                                               const QString &appliName,
                                                               const QString &bundleName,
                                                               GuiDeveloperModeView *developerView):
    plugframe::GuiWidgetListItem{dIndex,developerView},
    ui(new Ui::guiBundleConfFilesSelector),
    m_view(developerView),
    m_appliName{appliName}
{
    ui->setupUi(this);
    ui->bundleNameLineEdit->setText(bundleName);

    connect(ui->confFileEditButton,SIGNAL(clicked(bool)),this,SLOT(onConfFileClicked()));
}

GuiBundleConfFilesSelectorItem::~GuiBundleConfFilesSelectorItem()
{
    delete ui;
}

void GuiBundleConfFilesSelectorItem::onConfFileClicked()
{
    m_view->editBundleConfFile(m_appliName,ui->bundleNameLineEdit->text());
}
