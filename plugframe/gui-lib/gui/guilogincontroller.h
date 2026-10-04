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
#ifndef GUILOGINCONTROLLER_H
#define GUILOGINCONTROLLER_H

#include "gui/guipagecontroller.h"
#include "guiloginview.h"

namespace plugframe
{
class PFGUILIB_EXPORT GuiLoginController : public plugframe::GuiPageController
{
    Q_OBJECT

private:
    enum class State : quint8 {WaitingForAuthenticationAvailable,WaitingForUserLogin,Logged,Locked};

public:
    GuiLoginController(QObject *parent = nullptr);
    ~GuiLoginController() override;

public:
    void maxAttempts(int maxSigninAttempt);

public slots:
    void onAuthenticationAvailable(bool available);
    void onSigninAttempt(QString identifier,QString password);
    void onSigninAttemptResult(bool success);
    void onSignout();

signals:
    void enableLoginForm(bool enabled);
    void waitingForUserLogin();
    void waitingForAuthenticationAvailable();
    void loginSuccess(QString identifier);
    void loginFailed(int remainingAttempts);
    void loginLocked();
    void signinAttempt(QString identifier,QString cryptedPassword);

protected:
    void buildViews() override;
    virtual plugframe::GuiLoginView *createLoginView();

private:
    QString cryptPassword(QString password);

private:
    int     m_maxSigninAttempts;
    int     m_numberOfSigninAttempts;
    QString m_identifier;
    State   m_state;
};
using QspGuiLoginController = QSharedPointer<GuiLoginController>;
}//namespace plugframe
#endif // GUILOGINCONTROLLER_H
