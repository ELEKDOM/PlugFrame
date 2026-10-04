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
#include "guiloginview.h"
#include "ui_loginview.h"

plugframe::GuiLoginView::GuiLoginView(QWidget *parent):
    GuiPageView{"",parent},
    ui(new Ui::loginView)
{
    ui->setupUi(this);
    ui->signinButton->hide();
    ui->signoutButton->hide();

    // UI connections
    connect(ui->identifier, SIGNAL(editingFinished()), SLOT(onIdentifierEdited()));
    connect(ui->password, SIGNAL(editingFinished()), SLOT(onPasswordEdited()));
    connect(ui->signinButton, SIGNAL(pressed()), SLOT(onSigninButtonPressed()));
    connect(ui->signoutButton, SIGNAL(pressed()), SLOT(onSignoutButtonPressed()));
}

plugframe::GuiLoginView::~GuiLoginView()
{

}

void plugframe::GuiLoginView::onEnableLoginForm(bool enabled)
{
    ui->signinButton->show();
    ui->signinButton->setEnabled(false);
    ui->signoutButton->hide();

    if(enabled)
    {
        ui->identifier->setEnabled(true);
        ui->identifier->clear();
        ui->identifier->setFocus();
        ui->password->setEnabled(false);
        ui->password->clear();
    }
    else
    {
        ui->identifier->clear();
        ui->identifier->setEnabled(false);
        ui->password->clear();
        ui->password->setEnabled(false);
    }
}

void plugframe::GuiLoginView::onUserLogged()
{
    ui->identifier->setEnabled(false);
    ui->password->clear();
    ui->password->setEnabled(false);
    ui->signinButton->hide();
    ui->signoutButton->show();
    ui->signoutButton->setEnabled(true);
}

void plugframe::GuiLoginView::onIdentifierEdited()
{
    if (ui->identifier->text().isEmpty() == false)
    {
        ui->password->setEnabled(true);
        ui->password->setFocus();
    }
}

void plugframe::GuiLoginView::onPasswordEdited()
{
    if (ui->password->text().isEmpty() == false)
    {
        ui->signinButton->setEnabled(true);
        ui->signinButton->setFocus();
    }
}

void plugframe::GuiLoginView::onSigninButtonPressed()
{
    emit signinAttempt(ui->identifier->text(), ui->password->text());
}

void plugframe::GuiLoginView::onSignoutButtonPressed()
{
    emit signout();
    ui->signoutButton->setEnabled(false);
}