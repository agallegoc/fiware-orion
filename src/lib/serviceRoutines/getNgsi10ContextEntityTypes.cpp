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
#include <vector>

#include "logMsg/logMsg.h"
#include "logMsg/traceLevels.h"

#include "ngsi/ParseData.h"
#include "rest/ConnectionInfo.h"
#include "serviceRoutines/postQueryContext.h"
#include "serviceRoutines/getNgsi10ContextEntityTypes.h"



/* ****************************************************************************
*
* getNgsi10ContextEntityTypes - 
*
* GET /ngsi10/contextEntityTypes/{typeName}
*/
std::string getNgsi10ContextEntityTypes(ConnectionInfo* ciP, int components, std::vector<std::string> compV, ParseData* parseDataP)
{
  std::string typeName = compV[2];

  LM_T(LmtConvenience, ("CONVENIENCE: got a  'GET' request for entity type '%s'", typeName.c_str()));
  parseDataP->qcr.res.fill(".*", typeName, "");
  std::string answer = postQueryContext(ciP, components, compV, parseDataP);
  parseDataP->qcr.res.release();
  
  return answer;
}
