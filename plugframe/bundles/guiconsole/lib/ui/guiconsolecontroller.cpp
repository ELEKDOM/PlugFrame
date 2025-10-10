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


#include "guiconsolecontroller.h"
#include "guiconsoleview.h"

using namespace elekdom::plugframe::core::gui;
using namespace elekdom::plugframe::core::plugin;
using namespace elekdom::plugframe::framework::service;
using namespace elekdom::plugframe::guiconsole;

GuiConsoleController::GuiConsoleController(SystemServiceInterface *systemServiceItf,QObject *parent):
    GuiPageController{ConsolePageCtrlName(),
                      QStringList{systemMenuName(),ConsoleMenuName() },
                      parent},
    m_systemServiceItf{systemServiceItf}
{}

GuiConsoleController::~GuiConsoleController()
{

}

void GuiConsoleController::buildViews()
{
    GuiConsoleView *view{createConsoleView()};

    connect(view,SIGNAL(sigLevelCmd()),SLOT(onLevelCmd()));
    connect(view,SIGNAL(sigLoadedCmd()),SLOT(onLoadedCmd()));
    connect(view,SIGNAL(sigStartedCmd()),SLOT(onStartedCmd()));
    connect(this,SIGNAL(sigPrint(QString)),view,SLOT(print(QString)));

    addView(view);
}

GuiConsoleView *GuiConsoleController::createConsoleView()
{
    return new GuiConsoleView;
}

void GuiConsoleController::onLevelCmd()
{
    int rl{m_systemServiceItf->runningLevel()};
    QString msg{QObject::tr("Niveau d'exécution de la plateforme\t%1").arg(rl)};

    emit sigPrint(msg);
}

void GuiConsoleController::onLoadedCmd()
{
    displayBundlesList(BundleInterface::BundleState::Initialized);
}

void GuiConsoleController::onStartedCmd()
{
    displayBundlesList(BundleInterface::BundleState::Started);
}

void GuiConsoleController::displayBundlesList(BundleInterface::BundleState state)
{
    core::plugin::BundleList list{bundlesList(state)};
    core::plugin::BundleList_Iterator it;
    int firstColSize{padding(list)};
    QString spaces;

    spaces.fill(' ', firstColSize - 6);
    emit sigPrint(QObject::tr("Bundle%1rang de démarrage").arg(spaces));

    for (it = list.begin(); it != list.end(); ++it)
    {
        BundleInterface* bItf{*it};
        int namewidth{(bItf->getName()).size()};

        spaces.fill(' ', firstColSize - namewidth);
        QString msg{QString("%1%2%3").arg(bItf->getName(), spaces, QString::number(bItf->getStartLevel()))};

        emit sigPrint(msg);
    }
}

BundleList GuiConsoleController::bundlesList(BundleInterface::BundleState state)
{
    BundleList ret;
    BundleList bundleL{m_systemServiceItf->bundleList()};
    BundleList_Iterator it;

    for (it = bundleL.begin(); it != bundleL.end(); ++it)
    {
        if ((*it)->getState() == state)
        {
            ret.append(*it);
        }
    }

    return ret;
}

int GuiConsoleController::padding(BundleList &listToDisplay)
{
    BundleList_Iterator it;
    int maxWidthSize{6};

    for (it = listToDisplay.begin(); it != listToDisplay.end(); ++it)
    {
        int curS{((*it)->getName()).size()};
        if (curS > maxWidthSize)
        {
            maxWidthSize = curS;
        }
    }
    maxWidthSize +=4;
    return maxWidthSize;
}
