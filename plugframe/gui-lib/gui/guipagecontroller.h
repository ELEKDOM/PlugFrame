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

#ifndef GUIPAGECONTROLLER_H
#define GUIPAGECONTROLLER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QAction>
#include <QSharedPointer>
#include "gui/guipageview.h"
#include "pfgui-lib_export.h"

namespace plugframe
{
class PFGUILIB_EXPORT GuiPageController : public QObject
{
    Q_OBJECT

protected:
    static inline QString systemMenuName() {return tr("&PlugFrame");}

public:
    explicit GuiPageController(const QString& ctrlName,
                               QStringList menusNames = QStringList(),
                               QObject *parent = nullptr);

    ~GuiPageController() override;

public:
    virtual void buildViews() = 0;
    void updateViewsIdx();
    const GuiPageViewList& viewList() {return m_viewList;}
    const QStringList& menusNames() {return m_menusNames;}
    const QString& ctrlName() {return m_ctrlName;}
    void currentCtrl();
    void ctrlSelectionMenu(QAction *a) {m_ctrlSelectionMenu = a;}
    QAction *ctrlSelectionMenu() {return m_ctrlSelectionMenu;}

public slots:
    virtual void onTriggeredActionMenu(bool checked);

protected:
    void addView(GuiPageView *view);
    virtual void onCurrent();

protected:
    void statusMsg(QString msg);
    void clearStatusMsg();
    void clear();

signals:
    void showPage(int idx);
    void updatePageIdx(plugframe::GuiPageController* ctrl);
    void curCtrl(plugframe::GuiPageController* ctrl);
    void statusMessage(QString msg);
    void clearStatusMessage();

private:
    void notifyCurCtrl();
    void deleteAllViews();

private:
    QString         m_ctrlName;
    GuiPageView    *m_curView;
    QAction        *m_ctrlSelectionMenu; // only if m_menusNames[0] is not null
    GuiPageViewList m_viewList;
    QStringList     m_menusNames; // To manage controller selection into menubar. m_menusNames[0] is the main menu name. If not empty, m_menusNames[1] is the controller selection name if not empty
    QString         m_statusMsg;
};
using QspGuiPageController = QSharedPointer<GuiPageController>;
}//namespace plugframe
#endif // GUIPAGECONTROLLER_H
