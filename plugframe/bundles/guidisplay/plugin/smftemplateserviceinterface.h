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


#ifndef SMFTEMPLATESERVICEINTERFACE_H
#define SMFTEMPLATESERVICEINTERFACE_H

#include <QString>
#include "smfserviceinterface.h"

namespace elekdom
{
namespace smf
{
namespace "template"
{
namespace service
{

class SmfTemplateServiceInterface : public core::plugin::SmfServiceInterface
{
public:
    static QString serviceName() {return QStringLiteral("SmfTemplateServiceInterface");}

public:
    virtual ~SmfTemplateServiceInterface() {};

public:
};

}//namespace service
}//namespace template
}//namespace smf
}//namespace elekdom

#define SmfTemplateService_iid "elekdom.smf.template.service.SmfTemplateServiceInterface"
Q_DECLARE_INTERFACE(elekdom::smf::template::service::SmfTemplateServiceInterface, SmfTemplateService_iid)

#endif // SMFTEMPLATESERVICEINTERFACE_H
