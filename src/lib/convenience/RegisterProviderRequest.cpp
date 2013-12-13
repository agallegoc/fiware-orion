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

#include "common/globals.h"
#include "common/Format.h"
#include "common/tag.h"
#include "convenience/RegisterProviderRequest.h"
#include "ngsi/StatusCode.h"
#include "ngsi/MetadataVector.h"
#include "ngsi/Duration.h"
#include "ngsi/ProvidingApplication.h"
#include "ngsi/RegistrationId.h"
#include "ngsi9/DiscoverContextAvailabilityResponse.h"



/* ****************************************************************************
*
* Constructor - 
*/
RegisterProviderRequest::RegisterProviderRequest()
{
}



/* ****************************************************************************
*
* RegisterProviderRequest::render - 
*/
std::string RegisterProviderRequest::render(Format format, std::string indent)
{
  std::string  out                            = "";
  std::string  xmlTag                         = "registerProviderRequest";
  bool         durationRendered               = duration.get() != "";
  bool         providingApplicationRendered   = providingApplication.get() != "";
  bool         registrationIdRendered         = registrationId.get() != "";
  bool         commaAfterRegistrationId       = false;    // Last element
  bool         commaAfterProvidingApplication = registrationIdRendered;
  bool         commaAfterDuration             = registrationIdRendered || providingApplicationRendered;
  bool         commaAfterMetadataVector       = registrationIdRendered || providingApplicationRendered || durationRendered;

  out += startTag(indent, xmlTag, "", format, false, false);
  out += metadataVector.render(format,       indent + "  ", commaAfterMetadataVector);
  out += duration.render(format,             indent + "  ", commaAfterDuration);
  out += providingApplication.render(format, indent + "  ", commaAfterProvidingApplication);
  out += registrationId.render(format,       indent + "  ", commaAfterRegistrationId);
  out += endTag(indent, xmlTag, format, false);

  return out;   
}



/* ****************************************************************************
*
* RegisterProviderRequest::check - 
*/
std::string RegisterProviderRequest::check(RequestType requestType, Format format, std::string indent, std::string predetectedError, int counter)
{
   DiscoverContextAvailabilityResponse  response;
   std::string                          res;

   if (predetectedError != "")
   {
      response.errorCode.code         = SccBadRequest;
      response.errorCode.reasonPhrase = predetectedError;
   }
   else if ((res = metadataVector.check(requestType, format, indent, predetectedError, counter)) != "OK")
   {
      response.errorCode.code = SccBadRequest;
      response.errorCode.reasonPhrase = res;
   }
   else
      return "OK";

   LM_W(("RegisterProviderRequest Error"));
   return response.render(DiscoverContextAvailability, format, indent);
}



/* ****************************************************************************
*
* RegisterProviderRequest::present - 
*/
void RegisterProviderRequest::present(std::string indent)
{
   PRINTF("%sRegisterProviderRequest:\n", indent.c_str());
   metadataVector.present("Registration", indent + "  ");
   duration.present(indent + "  ");
   providingApplication.present(indent + "  ");
   registrationId.present(indent + "  ");
   PRINTF("\n");
}



/* ****************************************************************************
*
* RegisterProviderRequest::release - 
*/
void RegisterProviderRequest::release(void)
{
   metadataVector.release();
}
