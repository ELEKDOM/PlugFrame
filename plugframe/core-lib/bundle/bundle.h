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

#ifndef PF_BUNDLE
#define PF_BUNDLE

#include <QJsonObject>
#include "logger/loggable.h"
#include "bundle4builderinterface.h"
#include "bundle4plugininterface.h"
#include "bundleemitter.h"
#include "bundlelistener.h"
#include "bundleheaders.h"
#include "factory/bundlefactory.h"
#include "pfcore-lib_export.h"
#include "pfcore-lib_forward.h"

namespace plugframe
{
class PFCORELIB_EXPORT Bundle : public Loggable,
                                public Bundle4BuilderInterface,
                                public Bundle4PluginInterface
{
public:
   Bundle(QString logBundleName);
   ~Bundle() override;

public:
   BundleFactory& getFactory() override;
   QString getConfPath();
   QString getConfDir();
   bool registerListener(BundleListener* observer);
   bool unregisterListener(BundleListener* observer);
   QObject* getQplugin();

protected: // for Bundle4BuilderInterface
   Bundle& getBundle() override;
   const QString& getLogBundleName() override;
   void setHeaders(BundleHeaders* bundleHeaders) override;
   void loadManifestHeaders() override;
   void setEmitter(BundleEmitter *emitter) override;
   void setListener(BundleListener *listener) override;
   void defaultListening() override;

protected: // for Bundle4PluginInterface
   void setQplugin(QObject *qplugin) override;
   void setFileName(const QString& fileName) override;
   void setAbsolutePath(const QString& absolutePath) override;
   void setMetaData(const QJsonObject& metaData) override;
   void init() override;
   void start(QspBundleContext bundleContext) override;
   void stop() override;
   QString getName() override;
   Bundle *getImpl() override;
   int getStartLevel() override;
   BundleInterface::BundleState getState() override;

protected: // internals methods
   BundleHeaders& getHeaders();
   QspBundleEmitter& getEmitter();
   QspBundleListener& getListener();
   void setState(BundleInterface::BundleState state) {m_state = state;}
   virtual BundleFactory* createFactory()=0;
   virtual void _start(QspBundleContext bundleContext)=0;
   virtual void _stop()=0;

private:
   QObject*                     m_qplugin;     // plugin loaded by Qt for services interfaces extracting
   QString                      m_fileName;    // plugin file name
   QString                      m_absolutePath;// plugin location
   QJsonObject                  m_metadata;    // plugin metadata
   QspBundleFactory             m_factory;     // Bundle's object factory
   QspBundleHeaders             m_headers;     // Manifest's headers properties
   QspBundleEmitter             m_emitter;     // bundle's event emitter
   QspBundleListener            m_listener;    // events listener
   BundleInterface::BundleState m_state;       // Bundle life state
};
} //namespace plugframe

#endif // PF_BUNDLE

