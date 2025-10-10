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


#include <iostream>
#include "console.h"
#include "consolefactory.h"
#include "terminal.h"
#include "consoleexit.h"
#include "cmd/cmdprocessor.h"
#include "logger/pflog.h"
#include "bundle/bundlecontext.h"
#include "worker/workerargs.h"
#include "worker/workerouts.h"
#include "service-int/systemserviceinterface.h"
#include "service-int/displayserviceinterface.h"

using namespace elekdom::plugframe::console;
using namespace elekdom::plugframe;

bundle::Console::Console(int descriptionTab):
    core::bundle::BundleImplementation{"Console"},
    m_exit{new ConsoleExit{*this}},
    m_terminal{nullptr},
    m_systemServiceItf{nullptr},
    m_display{nullptr},
    m_descriptionTab{descriptionTab}
{
    m_exit->connectWorker(this);
}

bundle::Console::~Console()
{

}

void bundle::Console::startTerminal()
{
    core::worker::QspWorkerArgs args; // no args!

    startWork(args);
}

int bundle::Console::runningLevel()
{
    return m_systemServiceItf->runningLevel();
}

core::plugin::BundleList bundle::Console::loadedBundleList()
{
    core::plugin::BundleList ret;
    core::plugin::BundleList bundleL{m_systemServiceItf->bundleList()};
    core::plugin::BundleList_Iterator it;

    for (it = bundleL.begin(); it != bundleL.end(); ++it)
    {
        pfDebug4(getLogBundleName()) << tr("%1 state %2").arg((*it)->getName(), (*it)->stateStr());
        if ((*it)->getState() == core::plugin::BundleInterface::BundleState::Initialized)
        {
            ret.append(*it);
        }
    }

    return ret;
}

core::plugin::BundleList bundle::Console::startedBundleList()
{
    core::plugin::BundleList ret;
    core::plugin::BundleList bundleL{m_systemServiceItf->bundleList()};
    core::plugin::BundleList_Iterator it;

    for (it = bundleL.begin(); it != bundleL.end(); ++it)
    {
        if ((*it)->getState() == core::plugin::BundleInterface::BundleState::Started)
        {
            ret.append(*it);
        }
    }

    return ret;
}

void bundle::Console::quit()
{
    if (m_terminal)
    {
        m_terminal->stopFlag();
    }
}

void bundle::Console::quitApp()
{
    m_systemServiceItf->quit();
}

void bundle::Console::print(const QString &msg)
{
    if (m_display)
    {
        m_display->print(msg);
    }
}

void bundle::Console::printDescription(const QString &cmd, const QString &usage)
{
    int     cmdwidth{cmd.size()};
    QString padding;

    padding.fill(' ', m_descriptionTab - cmdwidth);
    QString msg{QString("%1%2%3\n").arg(cmd, padding, usage)};

    print(msg);
}

core::bundle::BundleFactory *bundle::Console::createFactory()
{
    return new factory::ConsoleFactory;
}

void bundle::Console::_start(core::bundle::QspBundleContext bundleContext)
{
    core::bundle::BundleImplementation::_start(bundleContext);

    m_systemServiceItf = bundleContext->getService<framework::service::SystemServiceInterface>(framework::service::SystemServiceInterface::serviceName());
    m_display = bundleContext->getService<display::service::DisplayServiceInterface>(display::service::DisplayServiceInterface::serviceName());

    // Register the listener to wait for framework started evt
    m_systemServiceItf->registerListener(getListener().get());
}

core::worker::WorkerThread *bundle::Console::createWorkerThread(core::worker::QspWorkerArgs args)
{
    QString appName{m_systemServiceItf->applicationName()};

    m_terminal = new Terminal{appName, this, args, *this};
    buildCommandProcessorSet();

    return m_terminal;
}

void bundle::Console::buildCommandProcessorSet()
{
    factory::ConsoleFactory&      factory{dynamic_cast<factory::ConsoleFactory&>(getFactory())};
    cmd::QspCmdProcessor cmdProcessor, first;

    // started command processor
    //-----------------------
    cmdProcessor = factory.createStartedListCmdProcessor(logChannel(), *this);
    m_terminal->addCmdProcessor(cmdProcessor);

    // loaded command processor
    //-----------------------
    cmdProcessor = factory.createLoadedListCmdProcessor(logChannel(), *this);
    m_terminal->addCmdProcessor(cmdProcessor);

    // level command processor
    //-----------------------
    cmdProcessor = factory.createLevelCmdProcessor(logChannel(), *this);
    m_terminal->addCmdProcessor(cmdProcessor);

    // quit command processor
    //-----------------------
    first = factory.createQuitCmdProcessor(logChannel(), *this);

    // help command processor
    //-----------------------
    cmdProcessor = factory.createHelpCmdProcessor(logChannel(), *this, first);
    m_terminal->addCmdProcessor(cmdProcessor);
    m_terminal->addCmdProcessor(first);
}

void bundle::Console::addCmdProcessor(cmd::QspCmdProcessor cmdProcessor)
{
    m_terminal->addCmdProcessor(cmdProcessor);
}

PF_qtServiceInterface_DEF(bundle::Console)
