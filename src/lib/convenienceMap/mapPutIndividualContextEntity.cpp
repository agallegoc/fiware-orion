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
#include "logMsg/logMsg.h"

#include "convenience/UpdateContextElementRequest.h"
#include "convenience/UpdateContextElementResponse.h"
#include "convenienceMap/mapPutIndividualContextEntity.h"
#include "mongoBackend/MongoGlobal.h"
#include "mongoBackend/mongoUpdateContext.h"
#include "ngsi/ContextElementResponse.h"
#include "ngsi10/UpdateContextRequest.h"
#include "ngsi10/UpdateContextResponse.h"



/* ****************************************************************************
*
* mapPutIndividualContextEntity - 
*/
HttpStatusCode mapPutIndividualContextEntity(std::string entityId, UpdateContextElementRequest* ucerP, UpdateContextElementResponse* response)
{
  HttpStatusCode          ms;
  UpdateContextRequest    ucRequest;
  UpdateContextResponse*  ucResponseP = new UpdateContextResponse();
  ContextElement          ce;

  ce.entityId.fill(entityId, "", "false");
  ce.attributeDomainName    = ucerP->attributeDomainName;
  ce.contextAttributeVector = ucerP->contextAttributeVector;
  
  ucRequest.contextElementVector.push_back(&ce);
  ucRequest.updateActionType.set("Update");

  ms = mongoUpdateContext(&ucRequest, ucResponseP);

  if (ucResponseP->contextElementResponseVector.size() > 1)
  {
     response->errorCode.fill(SccReceiverInternalError, "Internal error", "Bad size of contextElementResponseVector from mongoUpdateContext");
     return ms;
  }

  if (ucResponseP->contextElementResponseVector.size() == 0)
  {
     response->errorCode = ucResponseP->errorCode;
     return ms;
  }

  ContextAttributeResponse* carP = new ContextAttributeResponse();

  carP->contextAttributeVector = ucResponseP->contextElementResponseVector.get(0)->contextElement.contextAttributeVector;
  response->contextResponseVector.push_back(carP);
  response->errorCode.fill(&ucResponseP->contextElementResponseVector.get(0)->statusCode);

  return ms;
}
