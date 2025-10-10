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


#include "guipagecontroller.h"
#include "guipageview.h"

using namespace elekdom::plugframe::core::gui;

GuiPageController::GuiPageController(const QString& ctrlName,
                                     QStringList menusNames,
                                     QObject *parent)
    : QObject{parent}
    , m_ctrlName{ctrlName}
    , m_curView{nullptr}
    , m_ctrlSelectionMenu{nullptr}
    , m_menusNames{menusNames}
{}

GuiPageController::~GuiPageController()
{

}

void GuiPageController::updateViewsIdx()
{
    emit updatePageIdx(this);
}

///
/// \brief GuiPageController::currentCtrl
/// controller selected by the bundle !
///
void GuiPageController::currentCtrl()
{
    notifyCurCtrl();
}

///
/// \brief GuiPageController::onTriggeredActionMenu
/// controller activated by the ui !
/// \param checked
///
void GuiPageController::onTriggeredActionMenu(bool checked)
{
    Q_UNUSED(checked)

    notifyCurCtrl();
}

void GuiPageController::addView(GuiPageView *view)
{
    m_viewList.append(view);
    m_curView = view;
}

void GuiPageController::onCurrent()
{
}

void GuiPageController::statusMsg(QString msg)
{
    m_statusMsg = msg;
    emit statusMessage(m_statusMsg);
}

void GuiPageController::clearStatusMsg()
{
    m_statusMsg = "";
    emit clearStatusMessage();
}

void GuiPageController::clear()
{
    deleteAllViews();
    clearStatusMsg();
    m_curView = nullptr;
}

void GuiPageController::notifyCurCtrl()
{
    emit curCtrl(this);
    if (m_curView)
    {
        emit showPage(m_curView->stackedPageIndex());
    }
    else
    {
        statusMsg(tr("No view for this controller!"));
    }

    onCurrent();
}

void GuiPageController::deleteAllViews()
{
    /*
    for (int i = 0; i < m_viewList.size(); i++)
    {
        delete m_viewList.at(i);
    }
    */
    m_viewList.clear();
}
