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

#include <QAction>
#include <QCloseEvent>
#include "gui.h"
#include "ui_mainwindow.h"
#include "guipageselector.h"
#include "guilogsview.h"
#include "gui/guipagecontroller.h"
#include "gui/guipageview.h"

Gui::Gui(QWidget *parent):
    QMainWindow{parent},
    ui(new Ui::MainWindow),
    m_elekdomIcon{":/img/elekdom_logo.png"},
    m_iconLbl{new QLabel},
    m_currentCtrl{nullptr},
    m_logsView{nullptr}
{
    ui->setupUi(this);
}

Gui::~Gui()
{
    delete ui;
}

void Gui::initGui()
{
    setAppliIcon();

    // MenuBar
    buildMenuBar();
}

void Gui::onLog(QString msg)
{
    if (m_logsView)
    {
        m_logsView->log(msg);
    }
}

void Gui::onStatusMessage(QString msg)
{
    statusBar()->showMessage(msg);
}

void Gui::onClearStatusMessages()
{
    statusBar()->clearMessage();
}

void Gui::onAddGuiController(plugframe::QspGuiPageController controller)
{
    // Add a controller to manage
    m_ctrlSet.insert(controller->ctrlName(),controller);
    checkForMenu(controller);

    // Add all views into the central widget
    addViews(controller);

    // Connect signals/slots for mainwindow/ctrl link
    connect(controller.get(),SIGNAL(showPage(int)),SLOT(onShowPage(int)));
    connect(controller.get(),SIGNAL(updatePageIdx(plugframe::GuiPageController*)),SLOT(onUpdatePageIdx(plugframe::GuiPageController*)));
    connect(controller.get(),SIGNAL(curCtrl(plugframe::GuiPageController*)),SLOT(onCurrentCtrl(plugframe::GuiPageController*)));
    connect(controller.get(),SIGNAL(statusMessage(QString)),SLOT(onStatusMessage(QString)));
    connect(controller.get(),SIGNAL(clearStatusMessage()),SLOT(onClearStatusMessages()));
}

///
/// \brief Gui::onRemoveAllPages
/// Removes all controller's pages from stackedwidget and toolbar
/// \param controller
///
void Gui::onRemoveAllPages(plugframe::QspGuiPageController controller)
{
    const plugframe::GuiPageViewList& vl{controller->viewList()};

    for (qsizetype i = 0; i < vl.size(); i++)
    {
        plugframe::GuiPageView *pv{vl.at(i)};
        int idx{pv->stackedPageIndex()};

        //remove from central widget
        ui->stackedWidget->removeWidget(pv);

        //remove selector from toolbar
        GuiPageSelector *selec{nullptr};
        for (qsizetype j = 0; j < m_actionSet.size() && !selec; j++)
        {
            if (m_actionSet.at(j)->idx() == idx)
            {
                selec = m_actionSet.at(j);
            }
        }

        if (selec)
        {
            m_actionSet.removeOne(selec);
        }
    }
}

void Gui::onShowPage(int idx)
{
    showPage(idx);
}

///
/// \brief Gui::onUpdatePageIdx
///        adds unindexed pages to the central widget
/// \param controller
///
void Gui::onUpdatePageIdx(plugframe::GuiPageController *controller)
{
    const plugframe::GuiPageViewList& vl{controller->viewList()};

    for (qsizetype i = 0; i < vl.size(); i++)
    {
        plugframe::GuiPageView *pv{vl.at(i)};

        if (pv->stackedPageIndex() == -1)
        {
            // A new page to index

            int idx = ui->stackedWidget->addWidget(pv);
            pv->stackedPageIndex(idx);

            // Add an action into the toolBar ?
            if (!pv->toolActionName().isEmpty())
            {
                GuiPageSelector *action{new GuiPageSelector(idx,
                                                            pv->toolActionName(),
                                                            controller,
                                                            this)};

                ui->toolBar->addAction(action);
                m_actionSet.append(action);

                connect(action, SIGNAL(selectedPage(int)), SLOT(onPageSelected(int)));
            }
        }
    }
}

void Gui::onSetMainWindowTitle(const QString &title)
{
    m_windowTitle = title;
    setWindowTitle(m_windowTitle);
}

void Gui::setAppliIcon()
{
    m_iconLbl->setPixmap(m_elekdomIcon);
    statusBar()->addPermanentWidget(m_iconLbl);
}

void Gui::buildMenuBar()
{
    // By default, no early construction of the main menu !
}

QMenu *Gui::createMainMenuItem(const QString &menuName)
{
    QMenu *ret{nullptr};

    ret = ui->menubar->addMenu(menuName);
    if (ret)
    {
        addMenu(menuName,ret);
    }

    return ret;
}

void Gui::closeEvent(QCloseEvent *event)
{
    event->ignore();
    emit sigGuiCloseEvt();
}

void Gui::onPageSelected(int idx)
{
    showPage(idx);
}

void Gui::onCurrentCtrl(plugframe::GuiPageController *controller)
{
    if(m_currentCtrl)
    {
        enableCtrlSelectionMenu();
    }
    m_currentCtrl = controller;
    disableCtrlSelectionMenu();

    // Mainwindow title
    setWindowTitle(m_windowTitle + " - " + m_currentCtrl->ctrlName());
}

void Gui::addMenu(const QString &menuName, QMenu *menu)
{
    m_ctrlSelectionMenu.insert(menuName,menu);
}

QMenu *Gui::menu(const QString &menuName)
{
    return m_ctrlSelectionMenu.value(menuName);
}

void Gui::checkForMenu(plugframe::QspGuiPageController controller)
{
    const QStringList& ctrlMenusNames{controller->menusNames()};
    const QString& mainMenuName{ctrlMenusNames[0]}, ctrlMenuName{ctrlMenusNames[1]};

    if (!mainMenuName.isEmpty() && !ctrlMenuName.isEmpty())
    {
        // A controller menu selection must be added
        //------------------------------------------
        QMenu *m{menu(mainMenuName)};

        if (m == nullptr)
        {
            m = createMainMenuItem(mainMenuName);
        }

        if (m)
        {
            QAction *a;

            a = m->addAction(ctrlMenuName);
            connect(a,SIGNAL(triggered(bool)),controller.get(),SLOT(onTriggeredActionMenu(bool)));
            controller->ctrlSelectionMenu(a);
        }
    }
}

void Gui::addViews(plugframe::QspGuiPageController controller)
{
    const plugframe::GuiPageViewList& vl{controller->viewList()};

    for (qsizetype i = 0; i < vl.size(); i++)
    {
        plugframe::GuiPageView *pv{vl.at(i)};

        // New widget into the stacked container
        int idx = ui->stackedWidget->addWidget(pv);
        pv->stackedPageIndex(idx);

        // Add an action into the toolBar ?
        if (!pv->toolActionName().isEmpty())
        {
            GuiPageSelector *action{new GuiPageSelector(idx,
                                                        pv->toolActionName(),
                                                        controller.get(),
                                                        this)};

            ui->toolBar->addAction(action);
            m_actionSet.append(action);

            connect(action, SIGNAL(selectedPage(int)), SLOT(onPageSelected(int)));
        }

        // Hold logsview. The logs controller must be inserted first !
        if (!m_logsView)
        {
            m_logsView = dynamic_cast<GuiLogsView*>(pv);
        }
    }
}

///
/// \brief Gui::showPage
///        Selects the page of index "pageIdx" of the stackedWidget
/// \param pageIdx : page's index into the central widget
///
void Gui::showPage(int pageIdx)
{
    updateToolBar(pageIdx);
    ui->stackedWidget->setCurrentIndex(pageIdx);
}

///
/// \brief Gui::updateToolBar
///        Only displays unselected page selectors for the current controller in the toolbar
/// \param idx
///
void Gui::updateToolBar(int idx)
{
    if (idx >= 0)
    {
        for (qsizetype i = 0; i < m_actionSet.size(); ++i)
        {
            bool flag{true};
            GuiPageSelector *curSelector{m_actionSet.at(i)};

            if (curSelector->ctrl() != m_currentCtrl)
            {
                // Do not activate actions from another controller
                flag = false;
            }
            else if (curSelector->idx() == idx)
            {
                // Only non-visible pages can be activated
                flag = false;
            }

            curSelector->setVisible(flag);
        }
    }
}

void Gui::enableCtrlSelectionMenu()
{
    QAction *a{m_currentCtrl->ctrlSelectionMenu()};
    a->setVisible(true);
}

void Gui::disableCtrlSelectionMenu()
{
    QAction *a{m_currentCtrl->ctrlSelectionMenu()};
    a->setVisible(false);
}
