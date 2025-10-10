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


#ifndef CONSOLE_H
#define CONSOLE_H

#include "bundle/bundleimplementation.h"
#include "worker/worker.h"
#include "service-int/systemserviceinterface.h"
#include "service-int/displayserviceinterface.h"
#include "console_forward.h"
#include "pfcore-lib_forward.h"

namespace elekdom
{
namespace plugframe
{
namespace console
{
namespace bundle
{

class Console : public core::bundle::BundleImplementation,
                public core::worker::Worker
{

public:
    Console(int descriptionTab = 20);
    ~Console() override;

public:
    void startTerminal();
    int runningLevel();
    core::plugin::BundleList loadedBundleList();
    core::plugin::BundleList startedBundleList();
    void quit();
    void quitApp();
    void print(const QString& msg);
    void printDescription(const QString& cmd, const QString& usage);

protected:
    core::bundle::BundleFactory* createFactory() override;
    void _start(core::bundle::QspBundleContext bundleContext) override;

protected: // for SmfWorker
    core::worker::WorkerThread *createWorkerThread(QSharedPointer<core::worker::WorkerArgs> args) override;

protected:
    virtual void buildCommandProcessorSet();

protected:
    void addCmdProcessor(QSharedPointer<cmd::CmdProcessor> cmdProcessor);
    PF_qtServiceInterface_DECL

private:
    QspConsoleExit                                        m_exit;
    Terminal                                             *m_terminal;
    framework::service::SystemServiceInterface           *m_systemServiceItf;
    plugframe::display::service::DisplayServiceInterface *m_display;
    int                                                   m_descriptionTab;
};

} //namespace bundle
} //namespace console
} //namespace plugframe
} //namespace elekdom

#endif // CONSOLE_H
