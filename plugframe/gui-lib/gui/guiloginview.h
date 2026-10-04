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
#ifndef GUILOGINVIEW_H
#define GUILOGINVIEW_H

#include "gui/guipageview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class loginView;
}
QT_END_NAMESPACE

namespace plugframe
{
class PFGUILIB_EXPORT GuiLoginView : public plugframe::GuiPageView
{
    Q_OBJECT

public:
    GuiLoginView(QWidget *parent = nullptr);
    ~GuiLoginView() override;

public slots:
    void onEnableLoginForm(bool enabled);
    void onUserLogged();

signals:
    void signinAttempt(QString identidier, QString password);
    void signout();

private slots:
    void onIdentifierEdited();
    void onPasswordEdited();
    void onSigninButtonPressed();
    void onSignoutButtonPressed();

private:
    Ui::loginView *ui;
};
}//namespace plugframe
#endif // GUILOGINVIEW_H
