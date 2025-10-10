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


#ifndef PF_LOG_H
#define PF_LOG_H

#include <QDebug>

#define PFDEBUG(n,m) qDebug().nospace().noquote() <<"{" << (m) << "}["<<(n)<<"]"
#define pfDebug1(n) PFDEBUG(n,1)
#define pfDebug2(n) PFDEBUG(n,2)
#define pfDebug3(n) PFDEBUG(n,3)
#define pfDebug4(n) PFDEBUG(n,4)
#define pfDebug5(n) PFDEBUG(n,5)
#define pfDebug6(n) PFDEBUG(n,6)
#define pfDebug7(n) PFDEBUG(n,7)
#define pfDebug8(n) PFDEBUG(n,8)

#define PFINFO(n,m) qInfo().nospace().noquote() <<"{" << (m) << "}["<<(n)<<"]"
#define pfInfo1(n) PFINFO(n,1)
#define pfInfo2(n) PFINFO(n,2)
#define pfInfo3(n) PFINFO(n,3)
#define pfInfo4(n) PFINFO(n,4)
#define pfInfo5(n) PFINFO(n,5)
#define pfInfo6(n) PFINFO(n,6)
#define pfInfo7(n) PFINFO(n,7)
#define pfInfo8(n) PFINFO(n,8)

#define PFWARNING(n,m) qWarning().nospace().noquote() <<"{" << (m) << "}["<<(n)<<"]"
#define pfWarning1(n) PFWARNING(n,1)
#define pfWarning2(n) PFWARNING(n,2)
#define pfWarning3(n) PFWARNING(n,3)
#define pfWarning4(n) PFWARNING(n,4)
#define pfWarning5(n) PFWARNING(n,5)
#define pfWarning6(n) PFWARNING(n,6)
#define pfWarning7(n) PFWARNING(n,7)
#define pfWarning8(n) PFWARNING(n,8)

#define pfErr(n) pfWarning8(n) << QObject::tr("[ fichier : ") << __FILE__ << QObject::tr(", ligne : ") << __LINE__ << " ]"

#endif // PF_LOG_H
