/*
*
* Copyright 2013 Telefonica Investigacion y Desarrollo, S.A.U
*
* This file is part of Orion Context Broker.
*
* Orion Context Broker is free software: you can redistribute it and/or
* modify it under the terms of the GNU Affero General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* Orion Context Broker is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero
* General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with Orion Context Broker. If not, see http://www.gnu.org/licenses/.
*
* For those usages not covered by this license please contact with
* fermin at tid dot es
*
* Author: Ken Zangelin
*/
#include <string>

#include "logMsg/logMsg.h"
#include "logMsg/traceLevels.h"

#include "convenience/RegisterProviderRequest.h"
#include "convenienceMap/mapPostEntityByIdAttributeByName.h"
#include "mongoBackend/mongoRegisterContext.h"
#include "ngsi/ContextRegistration.h"
#include "ngsi9/RegisterContextRequest.h"
#include "ngsi9/RegisterContextResponse.h"



/* ****************************************************************************
*
* mapPostEntityByIdAttributeByName - 
*/
HttpStatusCode mapPostEntityByIdAttributeByName(std::string id, std::string attributeName, RegisterProviderRequest* rpr, RegisterContextResponse* response)
{
   RegisterContextRequest        request;
   ContextRegistration           cr;
   EntityId                      entityId(id, "", "false");
   ContextRegistrationAttribute  cra(attributeName, "", "false");

   cr.entityIdVector.push_back(&entityId);
   cr.registrationMetadataVector = rpr->metadataVector;
   cr.providingApplication       = rpr->providingApplication;

   cr.contextRegistrationAttributeVector.push_back(&cra);

   request.duration              = rpr->duration;
   request.registrationId        = rpr->registrationId;

   request.contextRegistrationVector.push_back(&cr);

   return mongoRegisterContext(&request, response);
}
