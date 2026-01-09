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

#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QPixmap>
#include <QLabel>
#include <QString>
#include <QHash>
#include <QMenu>
#include "gui/guipagecontroller.h"
#include "guidisplay_forward.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class Gui : public QMainWindow
{
    Q_OBJECT

public:
    Gui(QWidget *parent = nullptr);
    ~Gui() override;

public:
    virtual void initGui();

public slots:
    virtual void onLog(QString msg);
    virtual void onStatusMessage(QString msg);
    virtual void onClearStatusMessages();
    virtual void onAddGuiController(plugframe::QspGuiPageController controller);
    virtual void onRemoveAllPages(plugframe::QspGuiPageController controller);
    void onShowPage(int idx);
    void onUpdatePageIdx(plugframe::GuiPageController *controller);
    void onSetMainWindowTitle(const QString& title);

protected:
    void setAppliIcon();
    virtual void buildMenuBar();
    virtual QMenu *createMainMenuItem(const QString& menuName);
    void closeEvent(QCloseEvent *event) override;

signals:
    void sigGuiCloseEvt();

private slots:
    void onPageSelected(int idx);
    void onCurrentCtrl(plugframe::GuiPageController *controller);

private:
    void addMenu(const QString& menuName,QMenu* menu);
    QMenu *menu(const QString& menuName);
    void checkForMenu(plugframe::QspGuiPageController controller);
    void addViews(plugframe::QspGuiPageController controller);
    void showPage(int pageIdx);
    void updateToolBar(int idx);
    void enableCtrlSelectionMenu();
    void disableCtrlSelectionMenu();

private:
    Ui::MainWindow                                *ui;
    QString                                        m_windowTitle;       // Gui's window name
    QPixmap                                        m_elekdomIcon;       // Gui's window icon
    QLabel                                        *m_iconLbl;           // Gui's window label for icon
    QHash<QString,QMenu*>                          m_ctrlSelectionMenu; // set of selection menus
    QHash<QString,plugframe::QspGuiPageController> m_ctrlSet;           // set of controllers
    plugframe::GuiPageController                  *m_currentCtrl;       // active controller
    QList<GuiPageSelector*>                        m_actionSet;         // toolbar page selector set
    GuiLogsView                                   *m_logsView;          // the logs are viewed in the display
};
#endif // GUI_H
