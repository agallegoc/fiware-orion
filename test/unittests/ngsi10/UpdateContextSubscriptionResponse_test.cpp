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
#include "gtest/gtest.h"

#include "logMsg/logMsg.h"
#include "logMsg/traceLevels.h"

#include "ngsi10/UpdateContextSubscriptionResponse.h"
#include "unittest.h"



/* ****************************************************************************
*
* constructors - 
*/
TEST(UpdateContextSubscriptionResponse, constructors)
{
  UpdateContextSubscriptionResponse  ucsr1;
  ErrorCode                          ec(SccBadRequest, "RP", "D");
  UpdateContextSubscriptionResponse  ucsr2(ec);
  std::string                        rendered;
  std::string                        expected1 = "<updateContextSubscriptionResponse>\n  <subscribeResponse>\n    <subscriptionId>000000000000000000000000</subscriptionId>\n  </subscribeResponse>\n</updateContextSubscriptionResponse>\n";
  std::string                        expected2 = "<updateContextSubscriptionResponse>\n  <subscribeError>\n    <subscriptionId>0</subscriptionId>\n    <errorCode>\n      <code>400</code>\n      <reasonPhrase>RP</reasonPhrase>\n      <details>D</details>\n    </errorCode>\n  </subscribeError>\n</updateContextSubscriptionResponse>\n";
  
  rendered = ucsr1.render(UpdateContextSubscription, XML, "");
  EXPECT_STREQ(expected1.c_str(), rendered.c_str());

  rendered = ucsr2.render(UpdateContextSubscription, XML, "");
  EXPECT_STREQ(expected2.c_str(), rendered.c_str());
}



/* ****************************************************************************
*
* jsonRender - 
*/
TEST(UpdateContextSubscriptionResponse, json_render)
{
  const char*                         filename1  = "ngsi10.updateContextSubscriptionResponse.jsonRender1.valid.json";
  const char*                         filename2  = "ngsi10.updateContextSubscriptionResponse.jsonRender2.valid.json";
  const char*                         filename3  = "ngsi10.updateContextSubscriptionResponse.jsonRender3.valid.json";
  const char*                         filename4  = "ngsi10.updateContextSubscriptionResponse.jsonRender4.valid.json";
  const char*                         filename5  = "ngsi10.updateContextSubscriptionResponse.jsonRender5.valid.json";
  const char*                         filename6  = "ngsi10.updateContextSubscriptionResponse.jsonRender6.valid.json";
  UpdateContextSubscriptionResponse*  ucsrP;
  std::string                         rendered;

  utInit();

  // Preparations
  ucsrP = new UpdateContextSubscriptionResponse();

  // 1. subscribeError, -subscriptionId, with details
  // 2. subscribeError, +subscriptionId, no details
  // 3. subscribeResponse: +subscription -duration -throttling
  // 4. subscribeResponse: +subscription -duration +throttling
  // 5. subscribeResponse: +subscription +duration -throttling
  // 6. subscribeResponse: +subscription +duration +throttling

  // 1.
  ucsrP->subscribeError.errorCode.fill(SccBadRequest, "Bad Request", "details");

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename1)) << "Error getting test data from '" << filename1 << "'";
  rendered = ucsrP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());



  // 2.
  ucsrP->subscribeError.errorCode.fill(SccBadRequest, "Bad Request", "");
  ucsrP->subscribeError.subscriptionId.set("012345678901234567890123");

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename2)) << "Error getting test data from '" << filename2 << "'";
  rendered = ucsrP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());

  ucsrP->subscribeError.errorCode.fill(NO_ERROR_CODE, "", "");



  // 3.
  ucsrP->subscribeResponse.subscriptionId.set("012345678901234567890123");

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename3)) << "Error getting test data from '" << filename3 << "'";
  rendered = ucsrP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());



  // 4.
  ucsrP->subscribeResponse.throttling.set("PT1M");

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename4)) << "Error getting test data from '" << filename4 << "'";
  rendered = ucsrP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());



  // 5.
  ucsrP->subscribeResponse.throttling.set("");
  ucsrP->subscribeResponse.duration.set("PT1H");
  
  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename5)) << "Error getting test data from '" << filename5 << "'";
  rendered = ucsrP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());



  // 6.
  ucsrP->subscribeResponse.throttling.set("PT1M");

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename6)) << "Error getting test data from '" << filename6 << "'";
  rendered = ucsrP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());

  utExit();
}
