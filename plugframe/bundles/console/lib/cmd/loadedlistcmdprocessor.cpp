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
#include "cmd/loadedlistcmdprocessor.h"
#include "plugin/bundleinterface.h"
#include "console.h"
#include "pfcore-lib_forward.h"

using namespace elekdom::plugframe::console::cmd;
using namespace elekdom::plugframe;

LoadedListCmdProcessor::LoadedListCmdProcessor(const QString& logChannel,
                                                     console::bundle::Console& console):
    CmdProcessor{logChannel,
                    console,
                    "loaded",
                    QObject::tr("Affiche la liste des bundles chargés et initialisés mais non démarrés avec leur start level")}
{

}

LoadedListCmdProcessor::~LoadedListCmdProcessor()
{

}

bool LoadedListCmdProcessor::exec(const RawCmd &cmd)
{
    Q_UNUSED(cmd)
    core::plugin::BundleList list{console().loadedBundleList()};
    core::plugin::BundleList_Iterator it;

    console().print(QObject::tr("\t Bundle\t\trang de démarrage\n"));
    for (it = list.begin(); it != list.end(); ++it)
    {
        QString msg{QString("%1\t\t\t\t%2\n").arg((*it)->getName()).arg((*it)->getStartLevel())};
        console().print(msg);
    }

    return true;
}
