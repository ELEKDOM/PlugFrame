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
#include <QCryptographicHash>
#include "guilogincontroller.h"
#include "gui/guilogincontrollertype.h"

plugframe::GuiLoginController::GuiLoginController(QObject *parent):
    GuiPageController{plugframe::GuiLoginControllerType::s_ctrlType,
                      parent},
    m_maxSigninAttempts{2},
    m_numberOfSigninAttempts{0},
    m_state{State::WaitingForAuthenticationAvailable}
{
}

plugframe::GuiLoginController::~GuiLoginController()
{

}

void plugframe::GuiLoginController::maxAttempts(int maxSigninAttempt)
{
    m_maxSigninAttempts = maxSigninAttempt;
}

void plugframe::GuiLoginController::onAuthenticationAvailable(bool available)
{
    bool enabled{false};

    if (available)
    {
        m_state = State::WaitingForUserLogin;
        m_numberOfSigninAttempts = 0;
        enabled = true;
        emit waitingForUserLogin();
    }
    else
    {
        m_state = State::WaitingForAuthenticationAvailable;
        emit waitingForAuthenticationAvailable();
    }

    emit enableLoginForm(enabled);
}

void plugframe::GuiLoginController::onSigninAttempt(QString identifier, QString password)
{
    if (m_state == State::WaitingForUserLogin)
    {
        QString cryptedPasswd{cryptPassword(password)};

        m_identifier = identifier;
        emit
    }
}

void plugframe::GuiLoginController::onSigninAttemptResult(bool success)
{
    if (m_state == State::WaitingForUserLogin)
    {
        m_numberOfSigninAttempts++;
        if (success)
        {
            m_state = State::Logged;
            emit loginSuccess(m_identifier);
        }
        else
        {
            if (m_maxSigninAttempts >= m_numberOfSigninAttempts)
            {
                emit enableLoginForm(false);
                emit loginLocked();
            }
            else
            {
                emit loginFailed(m_maxSigninAttempts - m_numberOfSigninAttempts);
            }
        }
    }
}

void plugframe::GuiLoginController::onSignout()
{
    onAuthenticationAvailable(true);
}

void plugframe::GuiLoginController::buildViews()
{
    GuiLoginView *view{createLoginView()};

    //specific view/controller connections
    connect(this, SIGNAL(enableLoginForm(bool)), view, SLOT(onEnableLoginForm(bool)));
    connect(this, SIGNAL(loginSuccess(QString)), view, SLOT(onUserLogged()));
    connect(view, SIGNAL(signinAttempt(QString,QString)), this, SLOT(onSigninAttempt(QString,QString)));
    connect(view, SIGNAL(signout()), this, SLOT(onSignout()));

    addView(view);
}

plugframe::GuiLoginView *plugframe::GuiLoginController::createLoginView()
{
    return new GuiLoginView;
}

QString plugframe::GuiLoginController::cryptPassword(QString password)
{
    QByteArray bytePasswd(password.toUtf8());
    QByteArray hash_Keccak_256;
    QString ret;

    hash_Keccak_256 = QCryptographicHash::hash(bytePasswd, QCryptographicHash::Keccak_256).toHex(':');
    ret = QString(hash_Keccak_256);

    return ret;
}