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
#include <stdio.h>
#include <string>
#include <vector>

#include "logMsg/logMsg.h"

#include "common/globals.h"
#include "common/Format.h"
#include "common/tag.h"
#include "convenience/UpdateContextAttributeRequest.h"
#include "ngsi/StatusCode.h"



/* ****************************************************************************
*
* Constructor - 
*/
UpdateContextAttributeRequest::UpdateContextAttributeRequest()
{
  metadataVector.tagSet("metadata");
}



/* ****************************************************************************
*
* render - 
*/
std::string UpdateContextAttributeRequest::render(Format format, std::string indent)
{
  std::string tag = "updateContextAttributeRequest";
  std::string out = "";
  std::string indent2 = indent + "  ";

  out += startTag(indent, tag, format, false);
  out += valueTag(indent2, "type", type, format, true);
  out += valueTag(indent2, "contextValue", contextValue, format, true);
  out += metadataVector.render(format, indent2);
  out += endTag(indent, tag, format);

  return out;
}



/* ****************************************************************************
*
* check - 
*/
std::string UpdateContextAttributeRequest::check(RequestType requestType, Format format, std::string indent, std::string predetectedError, int counter)
{
  StatusCode       response;
  std::string      res;

  if (format == (Format) 0)
     format = XML;

  if (predetectedError != "")
  {
    response.code         = SccBadRequest;
    response.reasonPhrase = predetectedError;
  }
  else if (contextValue == "")
  {
    response.code         = SccBadRequest;
    response.reasonPhrase = "empty context value";
  }
  else if ((res = metadataVector.check(requestType, format, indent, predetectedError, counter)) != "OK")
  {
    response.code         = SccBadRequest;
    response.reasonPhrase = res;
  }
  else
    return "OK";
   
  return response.render(format, indent);
}



/* ****************************************************************************
*
* present - 
*/
void UpdateContextAttributeRequest::present(std::string indent)
{
  PRINTF("%stype:         %s", indent.c_str(), type.c_str());
  PRINTF("%scontextValue: %s", indent.c_str(), contextValue.c_str());
  metadataVector.present("ContextMetadata", indent);
}



/* ****************************************************************************
*
* release - 
*/
void UpdateContextAttributeRequest::release(void)
{
   metadataVector.release();
}
