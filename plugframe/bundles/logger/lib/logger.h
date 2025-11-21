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

#ifndef LOGGER_H
#define LOGGER_H

#include <QMutex>
#include <QHash>
#include <QtGlobal>
#include <QRegularExpression>
#include "bundle/bundleimplementation.h"
#include "service-int/displayserviceinterface.h"
#include "logfilter.h"

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

class Logger : public plugframe::BundleImplementation
{
    friend void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

public:
    Logger();
    virtual ~Logger();

public:
    void log(QtMsgType type, const QMessageLogContext &context, const QString &msg);

protected:
    plugframe::BundleFactory* createFactory() override;
    void _start(plugframe::QspBundleContext bundleContext) override;
    void _stop() override;
    PF_qtServiceInterface_DECL

private:
    void open();
    void loadIniFile();
    void close();

private:
    static Logger *s_logger;
private:
    QHash<QString, QspLogFilter>        m_channelFilter;
    plugframe::DisplayServiceInterface *m_display;
    QRegularExpression                  m_re;
    QRegularExpressionMatch             m_match;
};
#endif // LOGGER_H
