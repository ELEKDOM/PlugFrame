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

#ifndef PLUGIN_H
#define PLUGIN_H

#include <QObject>
#include "bundleinterface.h"
#include "bundle/bundle4plugininterface.h"
#include "pfcore-lib_export.h"
#include "pfcore-lib_forward.h"

namespace plugframe
{
class PFCORELIB_EXPORT Plugin : public QObject, public BundleInterface
{

public:
    Plugin();
    ~Plugin() override;

protected:
    void setFileName(const QString& fileName) override;
    void setAbsolutePath(const QString& absolutePath) override;
    void setMetaData(const QJsonObject& metaData) override;
    void setQplugin(QObject *qplugin) override;
    void init() override;
    void start(QspBundleContext bundleContext) override;
    void stop() override;
    QString getName() override;
    Bundle *getImpl() override;
    int getStartLevel() override;
    BundleState getState() override;
    QString state2String(BundleState state) override;

protected:
    void _init();

protected:
    QspBundle4PluginInterface &implementation();
    virtual Bundle4PluginInterface *createImplementation() = 0;
    virtual void bindServicesImplementations() = 0;

private:
    QString                   m_fileName;
    QString                   m_absolutePath;
    QJsonObject               m_metadata;
    QObject                  *m_qplugin;
    QspBundle4PluginInterface m_implementation;
};
}//namespace plugframe

#define PF_bindServicesImplementations_DECL void bindServicesImplementations()override;
#define PF_bindServicesImplementations_DEF(TYPE) void TYPE::bindServicesImplementations(){}

#endif // PLUGIN_H
