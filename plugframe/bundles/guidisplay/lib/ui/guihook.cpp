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


#include <QMenuBar>
#include <QMessageBox>
#include "guihook.h"
#include "guidisplay.h"
#include "ui/gui.h"
#include "gui/guipagecontroller.h"

using namespace elekdom::plugframe::guidisplay;

GuiHook::GuiHook(Gui* parent,bundle::GuiDisplay& bundle):
    QObject{parent},
    m_mainWindow{parent},
    m_bundle{bundle}
{
    qRegisterMetaType<QspGuiPageController>("QspGuiPageController");
}

GuiHook::~GuiHook()
{
    m_mainWindow->deleteLater();
}

void GuiHook::initGui()
{
    m_mainWindow->initGui();

    // Display's services
    connect(this,SIGNAL(sigLog(QString)),m_mainWindow,SLOT(onLog(QString)),Qt::QueuedConnection);
    connect(this,SIGNAL(sigStatusMessage(QString)),m_mainWindow,SLOT(onStatusMessage(QString)),Qt::QueuedConnection);
    connect(this,SIGNAL(sigClearStatusMessages()),m_mainWindow,SLOT(onClearStatusMessages()),Qt::QueuedConnection);

    // GuiBuilder's services
    connect(this,SIGNAL(sigAddGuiController(QspGuiPageController)),m_mainWindow,SLOT(onAddGuiController(QspGuiPageController)));
    connect(this,SIGNAL(sigRemoveAllPages(QspGuiPageController)),m_mainWindow,SLOT(onRemoveAllPages(QspGuiPageController)));
    connect(this,SIGNAL(sigSetWindowTitle(QString)),m_mainWindow,SLOT(onSetMainWindowTitle(QString)));

    // To Manage Gui CLose Event
    connect(m_mainWindow,SIGNAL(sigGuiCloseEvt()),SLOT(onGuiCloseEvt()));
}

void GuiHook::showGui()
{
    m_mainWindow->show();
}

void GuiHook::log(const QString &msg)
{
    emit sigLog(msg);
}

void GuiHook::statusMessage(const QString &msg)
{
    emit sigStatusMessage(msg);
}

void GuiHook::clearStatusMessages()
{
    emit sigClearStatusMessages();
}

void GuiHook::addGuiController(const core::gui::QspGuiPageController &controller)
{
    emit sigAddGuiController(controller);
}

void GuiHook::removeAllPages(QspGuiPageController controller)
{
    emit sigRemoveAllPages(controller);
}

void GuiHook::setMainWindowTitle(const QString &title)
{
    emit sigSetWindowTitle(title);
}

void GuiHook::onGuiCloseEvt()
{
    QMessageBox msgBox;

    msgBox.setText(tr("Voulez-vous quitter l'application ?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    int ret = msgBox.exec();
    if (ret == QMessageBox::Yes)
    {
        m_bundle.closeApp();
    }
}
