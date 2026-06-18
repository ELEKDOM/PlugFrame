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
#include "gui/guicontrollertype.h"
#include "gui/guipageview.h"
#include "pfgui-lib_export.h"

namespace plugframe
{
class PFGUILIB_EXPORT GuiPageController : public QObject
{
    Q_OBJECT

public:
    explicit GuiPageController(GuiControllerType ctrlType,
                               QObject *parent = nullptr);
    ~GuiPageController() override;

public:
    virtual void buildViews() = 0;
    void updateViewsIdx();
    const GuiPageViewList& viewList() {return m_viewList;}
    GuiControllerType ctrlType() {return m_ctrlType;}
    void currentCtrl();
    void ctrlSelectionMenu(QAction *a) {m_ctrlSelectionMenu = a;}
    QAction *ctrlSelectionMenu() {return m_ctrlSelectionMenu;}

public slots:
    virtual void onTriggeredActionMenu(bool checked);

signals:
    void showPage(int idx);
    void updatePageIdx(plugframe::GuiPageController* ctrl);
    void curCtrl(plugframe::GuiPageController* ctrl);
    void statusMessage(QString msg);
    void clearStatusMessage();

protected:
    void addView(GuiPageView *view);
    virtual void onCurrent();

protected:
    void statusMsg(QString msg);
    void clearStatusMsg();
    void clear();

private:
    void notifyCurCtrl();
    void deleteAllViews();

private:
    GuiControllerType m_ctrlType;
    GuiPageView      *m_curView;
    QAction          *m_ctrlSelectionMenu; // not null only if the controller has an input in the main menu
    GuiPageViewList   m_viewList;
    QString           m_statusMsg;
};
using QspGuiPageController = QSharedPointer<GuiPageController>;
}//namespace plugframe
#endif // GUIPAGECONTROLLER_H
