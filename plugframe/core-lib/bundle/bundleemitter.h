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

#ifndef BUNDLEEMITTER_H
#define BUNDLEEMITTER_H

#include <QList>
#include <QMutex>
#include <QSharedPointer>
#include "bundleobject.h"
#include "event/event.h"
#include "pfcore-lib_export.h"
#include "pfcore-lib_forward.h"

namespace plugframe
{
class PFCORELIB_EXPORT BundleEmitter : public BundleObject
{
    Q_OBJECT

private:
    QMutex                    m_mutex;
    QList<BundleListener*> m_listenersRegister;

public:
    BundleEmitter(Bundle& bundle, QObject *parent = nullptr);
    ~BundleEmitter() override;

signals:
    void pfEvent(plugframe::QspEvent ev);

public:
    bool registerListener(BundleListener* observer);
    bool unregisterListener(BundleListener* observer);
    void postBundleStartingEvt();
    void postBundleStartedEvt();
    void postBundleStoppingEvt();
    void postBundleStoppedEvt();
};
using QspBundleEmitter = QSharedPointer<BundleEmitter>;
} //namespace plugframe
#endif // BUNDLEEMITTER_H
