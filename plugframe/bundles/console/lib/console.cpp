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

#include "console.h"
#include "consolefactory.h"
#include "terminal.h"
#include "consoleexit.h"
#include "cmd/cmdprocessor.h"
#include "logger/pflog.h"
#include "bundle/bundlecontext.h"
#include "worker/workerargs.h"
#include "service-int/systemserviceinterface.h"
#include "service-int/displayserviceinterface.h"

Console::Console(int descriptionTab):
    plugframe::BundleImplementation{"Console"},
    m_exit{new ConsoleExit{*this}},
    m_terminal{nullptr},
    m_systemServiceItf{nullptr},
    m_display{nullptr},
    m_descriptionTab{descriptionTab}
{
    m_exit->connectWorker(this);
}

Console::~Console()
{

}

void Console::startTerminal()
{
    plugframe::QspWorkerArgs args; // no args!

    startWork(args);
}

int Console::runningLevel()
{
    return m_systemServiceItf->runningLevel();
}

plugframe::BundleList Console::loadedBundleList()
{
    plugframe::BundleList ret;
    plugframe::BundleList bundleL{m_systemServiceItf->bundleList()};
    plugframe::BundleList_Iterator it;

    for (it = bundleL.begin(); it != bundleL.end(); ++it)
    {
        pfDebug4(getLogBundleName()) << tr("%1 state %2").arg((*it)->getName(), (*it)->stateStr());
        if ((*it)->getState() == plugframe::BundleInterface::BundleState::Initialized)
        {
            ret.append(*it);
        }
    }

    return ret;
}

plugframe::BundleList Console::startedBundleList()
{
    plugframe::BundleList ret;
    plugframe::BundleList bundleL{m_systemServiceItf->bundleList()};
    plugframe::BundleList_Iterator it;

    for (it = bundleL.begin(); it != bundleL.end(); ++it)
    {
        if ((*it)->getState() == plugframe::BundleInterface::BundleState::Started)
        {
            ret.append(*it);
        }
    }

    return ret;
}

void Console::quit()
{
    if (m_terminal)
    {
        m_terminal->stopFlag();
    }
}

void Console::quitApp()
{
    m_systemServiceItf->quit();
}

void Console::print(const QString &msg)
{
    if (m_display)
    {
        m_display->print(msg);
    }
}

void Console::printDescription(const QString &cmd, const QString &usage)
{
    qsizetype cmdwidth{cmd.size()};
    QString   padding;

    padding.fill(' ', m_descriptionTab - cmdwidth);
    QString msg{QString("%1%2%3\n").arg(cmd, padding, usage)};

    print(msg);
}

plugframe::BundleFactory *Console::createFactory()
{
    return new ConsoleFactory;
}

void Console::_start(plugframe::QspBundleContext bundleContext)
{
    plugframe::BundleImplementation::_start(bundleContext);

    m_systemServiceItf = bundleContext->getService<plugframe::SystemServiceInterface>(plugframe::SystemServiceInterface::serviceName());
    m_display = bundleContext->getService<plugframe::DisplayServiceInterface>(plugframe::DisplayServiceInterface::serviceName());

    // Register the listener to wait for framework started evt
    m_systemServiceItf->registerListener(getListener().get());
}

plugframe::WorkerThread *Console::createWorkerThread(plugframe::QspWorkerArgs args)
{
    QString appName{m_systemServiceItf->applicationName()};

    m_terminal = new Terminal{appName, this, args, *this};
    buildCommandProcessorSet();

    return m_terminal;
}

void Console::buildCommandProcessorSet()
{
    ConsoleFactory& factory{dynamic_cast<ConsoleFactory&>(getFactory())};
    QspCmdProcessor cmdProcessor, first;

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

void Console::addCmdProcessor(QspCmdProcessor cmdProcessor)
{
    m_terminal->addCmdProcessor(cmdProcessor);
}

PF_qtServiceInterface_DEF(Console)
