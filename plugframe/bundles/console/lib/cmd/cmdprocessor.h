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


#ifndef CMDPROCESSOR_H
#define CMDPROCESSOR_H

#include <QSharedPointer>
#include <QStringList>
#include "logger/loggable.h"
#include "console_forward.h"

namespace elekdom
{
namespace plugframe
{
namespace console
{
namespace cmd
{

using RawCmd = QStringList;

class CmdProcessor : public core::logger::Loggable
{
public:
    CmdProcessor(const QString& logChannel,
                 console::bundle::Console& console,
                 QString cmdName,
                 QString description);
    virtual ~CmdProcessor();

public:
    void next(QspCmdProcessor procCmd);
    bool execCmd(const RawCmd& cmd);
    void printCmdDescription();

protected:
    console::bundle::Console& console();
    virtual bool exec(const RawCmd& cmd) = 0;

private:
    virtual void printDescription();

private:
    console::bundle::Console& m_console;
    QString                      m_cmdName;
    QString                      m_description;
    QspCmdProcessor              m_nextProcessor;
};

} //namespace cmd
} //namespace console
} //namespace plugframe
} //namespace elekdom

#endif // CMDPROCESSOR_H
