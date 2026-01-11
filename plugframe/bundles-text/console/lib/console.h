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
#include "cmd/cmdprocessor.h"
#include "consoleexit.h"

class Console : public plugframe::BundleImplementation,
                public plugframe::Worker
{
public:
    Console(int descriptionTab = 20);
    ~Console() override;

public:
    void startTerminal();
    int runningLevel();
    plugframe::BundleList loadedBundleList();
    plugframe::BundleList startedBundleList();
    void quit();
    void quitApp();
    void print(const QString& msg);
    void printDescription(const QString& cmd, const QString& usage);

protected:
    plugframe::BundleFactory* createFactory() override;
    void _start(plugframe::QspBundleContext bundleContext) override;

protected: // for SmfWorker
    plugframe::WorkerThread *createWorkerThread(plugframe::QspWorkerArgs args) override;

protected:
    virtual void buildCommandProcessorSet();

protected:
    void addCmdProcessor(QspCmdProcessor cmdProcessor);
    PF_qtServiceInterface_DECL

private:
    QspConsoleExit                      m_exit;
    Terminal                           *m_terminal;
    plugframe::SystemServiceInterface  *m_systemServiceItf;
    plugframe::DisplayServiceInterface *m_display;
    qsizetype                           m_descriptionTab;
};
#endif // CONSOLE_H
