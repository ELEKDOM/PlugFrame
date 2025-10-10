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

#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QtCore>
#include <QScopedPointer>
#include <QCoreApplication>
#include "pfcore-lib_export.h"
#include "pfcore-lib_forward.h"

class QCoreApplication;

namespace elekdom
{
namespace plugframe
{
namespace core
{
namespace launcher
{
class PFCORELIB_EXPORT Launcher : public QObject
{
    Q_OBJECT

public:
    Launcher();
    ~Launcher() override;

public:
    virtual int exec(int argc, char *argv[]);

protected:
    virtual void createApp(int& argc, char *argv[]) = 0;
    virtual void setStyleSheet();
    const QspLaunchingProperties& launchingProperties() {return m_spSmfLaunchingProperties;}

protected:
    virtual CoreFactory *createFactory();
    void setFactory(CoreFactory *theFactory);
    QspCoreFactory getFactory();

private:
    void setLaunchingProperties();

private slots:
    void startPlatform();
    void onAboutToQuit();

protected:
    QScopedPointer<QCoreApplication>          m_spApp;

private:
    QspCoreFactory                         m_spSmfCoreFactory;
    QspLaunchingProperties                 m_spSmfLaunchingProperties;
    QspLocation                            m_spSmfLocation;
    QspBundlesStore                        m_spBundlesStore;
    framework::plugin::FrameworkInterface *m_newFwk;
};
} // namespace launcher
} // namespace core
} // namespace smf
} // namespace elekdom

#endif // LAUNCHER_H
