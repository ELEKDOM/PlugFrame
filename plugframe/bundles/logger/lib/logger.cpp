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


#include <QSettings>
#include "logger.h"
#include "logfilter.h"
#include "logdevice.h"
#include "loggerfactory.h"
#include "bundle/bundlecontext.h"

using namespace elekdom::plugframe::core::bundle;
using namespace elekdom::plugframe::logger::bundle;
using namespace elekdom::plugframe::logger;
using namespace elekdom::plugframe;

Logger *Logger::s_logger = nullptr;

void logger::bundle::myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    if (Logger::s_logger)
    {
        Logger::s_logger->log(type,context,msg);
    }
}

Logger::Logger():
    core::bundle::BundleImplementation{"Logger"}
{

}

Logger::~Logger()
{

}

void Logger::log(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QMutexLocker mtxLck(&m_mutex);
    Q_UNUSED(context)

    QString message{msg};
    QRegExp rx{"^\\{(\\d)\\}\\[(\\w*)\\]"}; // raw message > {level}[channel]msg
    int index{rx.indexIn(message)};
    QStringList list{rx.capturedTexts()};

    if (index >= 0)
    {
        QString channelName{list[2]};
        QspLogFilter filter{m_channelFilter.value(channelName)};
        if (false == filter.isNull())
        {
            uint level{list[1].toUInt()};

            message = message.remove(list[0]);
            filter->log(type,level,message);
        } //if (false == filter.isNull())
    } //if (index >= 0)
    else
    {
        // Without format, log are just displayed to stderr
        m_display->log(message);
    }
}

BundleFactory *Logger::createFactory()
{
    return new factory::LoggerFactory;
}

void Logger::_start(QspBundleContext bundleContext)
{
    core::bundle::BundleImplementation::_start(bundleContext);

    m_display = bundleContext->getService<display::service::DisplayServiceInterface>(display::service::DisplayServiceInterface::serviceName());
    open();
}

void Logger::_stop()
{
    core::bundle::BundleImplementation::_stop();

    close();
}

void Logger::open()
{
    s_logger = this;

    // load log settings
    loadIniFile();

    // install q message handler
    qInstallMessageHandler(myMessageOutput);
}

void Logger::loadIniFile()
{
    factory::LoggerFactory& loggerFactory{dynamic_cast<factory::LoggerFactory&>(getFactory())};
    QString   file{getConfPath()},channelName,logFileName,timestampFormat;
    QSettings logsettings{file,QSettings::IniFormat};  // conf/log.ini
    uint      dFlags,wFlags,iFlags,outputFlags;

    timestampFormat = logsettings.value("timestamp_format").toString();

    int size = logsettings.beginReadArray("Channels");
    for (int i = 0; i < size; ++i) {
        logsettings.setArrayIndex(i);
        channelName = logsettings.value("channel_name").toString();
        logFileName = logsettings.value("log_file_name").toString();
        dFlags = logsettings.value("debug_flags").toUInt();
        wFlags = logsettings.value("warning_flags").toUInt();
        iFlags = logsettings.value("info_flags").toUInt();
        outputFlags = logsettings.value("outputs_flag").toUInt();

        // insert a new filter into the channelFilter
        QspLogFilter logFilter{loggerFactory.createLogFilter(channelName,timestampFormat,dFlags,wFlags,iFlags)};
        m_channelFilter.insert(channelName,logFilter);

        // add outputs for this filter
        QspLogDevice logDevice;
        if (outputFlags == 1 || outputFlags == 3)
        {
            logDevice.reset(loggerFactory.createLogDisplay(m_display));
            logFilter->addOutput(logDevice);
        }
        if (outputFlags == 2 || outputFlags == 3)
        {
            logDevice.reset(loggerFactory.createLogFile(logFileName));
            logFilter->addOutput(logDevice);
        }
    }
    logsettings.endArray();
}

void Logger::close()
{
    qInstallMessageHandler(0);

    QHash<QString, QspLogFilter>::const_iterator i = m_channelFilter.constBegin();
    while (i != m_channelFilter.constEnd())
    {
        (i.value())->close();
        ++i;
    }
}

PF_qtServiceInterface_DEF(Logger)
