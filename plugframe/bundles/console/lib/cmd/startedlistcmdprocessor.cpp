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


#include <QObject>
#include "logger/pflog.h"
#include "terminal.h"
#include "cmd/startedlistcmdprocessor.h"
#include "plugin/bundleinterface.h"
#include "console.h"
#include "pfcore-lib_forward.h"

using namespace elekdom::plugframe::console::cmd;
using namespace elekdom::plugframe::core;

StartedListCmdProcessor::StartedListCmdProcessor(const QString& logChannel,
                                                       console::bundle::Console& console):
    CmdProcessor{logChannel,
                    console,
                    "started",
                    QObject::tr("Affiche la liste des bundles démarrés avec leur start level")}
{

}

StartedListCmdProcessor::~StartedListCmdProcessor()
{

}

bool StartedListCmdProcessor::exec(const RawCmd &cmd)
{
    Q_UNUSED(cmd)
    core::plugin::BundleList list{console().startedBundleList()};
    core::plugin::BundleList_Iterator it;
    int maxWidthSize{0};
    QString padding;

    for (it = list.begin(); it != list.end(); ++it)
    {
        int curS{((*it)->getName()).size()};
        if (curS > maxWidthSize)
        {
            maxWidthSize = curS;
        }
    }
    maxWidthSize +=2;

    padding.fill(' ', maxWidthSize - 6);
    console().print(QObject::tr("Bundle%1rang de démarrage\n").arg(padding));

    for (it = list.begin(); it != list.end(); ++it)
    {
        core::plugin::BundleInterface* bItf{*it};
        int namewidth{(bItf->getName()).size()};

        padding.fill(' ', maxWidthSize - namewidth);
        QString msg{QString("%1%2%3\n").arg(bItf->getName(), padding, QString::number(bItf->getStartLevel()))};
        console().print(msg);
    }

    return true;
}

