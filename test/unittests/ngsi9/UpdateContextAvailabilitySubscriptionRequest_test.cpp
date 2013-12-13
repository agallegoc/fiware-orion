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

#include "common/globals.h"
#include "jsonParse/jsonRequest.h"
#include "ngsi/ParseData.h"
#include "rest/ConnectionInfo.h"
#include "xmlParse/xmlRequest.h"
#include "ngsi9/UpdateContextAvailabilitySubscriptionResponse.h"

#include "testDataFromFile.h"



/* ****************************************************************************
*
* xml_ok - 
*/
TEST(UpdateContextAvailabilitySubscriptionRequest, xml_ok)
{
  ParseData       reqData;
  const char*     fileName = "ngsi9.updateContextAvailabilitySubscriptionRequest.ok2.valid.xml";
  ConnectionInfo  ci("", "POST", "1.1");  
  
  EXPECT_EQ("OK", testDataFromFile(testBuf, sizeof(testBuf), fileName)) << "Error getting test data from '" << fileName << "'";

  lmTraceLevelSet(LmtDump, true);
  std::string result = xmlTreat(testBuf, &ci, &reqData, UpdateContextAvailabilitySubscription, "updateContextAvailabilitySubscriptionRequest", NULL);
  lmTraceLevelSet(LmtDump, false);
  EXPECT_EQ("OK", result) << "this test should be OK";
}



/* ****************************************************************************
*
* xml_invalidEntityAttribute - 
*/
TEST(UpdateContextAvailabilitySubscriptionRequest, xml_invalidEntityAttribute)
{
  ParseData       reqData;
  const char*     fileName = "ngsi9.updateContextAvailabilitySubscriptionRequest.entityIdAttribute.invalid.xml";
  ConnectionInfo  ci("", "POST", "1.1");  
  std::string     expected = "<updateContextAvailabilitySubscriptionResponse>\n  <subscriptionId>012345678901234567890123</subscriptionId>\n  <errorCode>\n    <code>400</code>\n    <reasonPhrase>unsupported attribute for EntityId</reasonPhrase>\n  </errorCode>\n</updateContextAvailabilitySubscriptionResponse>\n";

  EXPECT_EQ("OK", testDataFromFile(testBuf, sizeof(testBuf), fileName)) << "Error getting test data from '" << fileName << "'";

  lmTraceLevelSet(LmtDump, true);
  std::string result = xmlTreat(testBuf, &ci, &reqData, UpdateContextAvailabilitySubscription, "updateContextAvailabilitySubscriptionRequest", NULL);
  lmTraceLevelSet(LmtDump, false);
  EXPECT_EQ(expected, result);
}



/* ****************************************************************************
*
* json_ok - 
*/
TEST(UpdateContextAvailabilitySubscriptionRequest, json_ok)
{
  ConnectionInfo  ci("", "POST", "1.1");
  ParseData       parseData;
  const char*     fileName      = "updateContextAvailabilitySubscriptionRequest_ok.json";
  const char*     expectedFile1 = "ngsi9.updateContextAvailabilitySubscriptionRequest.expected1.valid.json";
  const char*     expectedFile2 = "ngsi9.updateContextAvailabilitySubscriptionRequest.expected2.valid.json";
  const char*     expectedFile3 = "ngsi9.updateContextAvailabilitySubscriptionRequest.expected3.valid.json";
  std::string     rendered;
  std::string     check;

  ci.inFormat      = JSON;
  ci.outFormat     = JSON;

  EXPECT_EQ("OK", testDataFromFile(testBuf,     sizeof(testBuf), fileName)) << "Error getting test data from '" << fileName << "'";

  lmTraceLevelSet(LmtDump, true);
  std::string result = jsonTreat(testBuf, &ci, &parseData, UpdateContextAvailabilitySubscription, "updateContextAvailabilitySubscriptionRequest", NULL);
  lmTraceLevelSet(LmtDump, false);
  EXPECT_EQ("OK", result) << "this test should be OK";

  UpdateContextAvailabilitySubscriptionRequest* ucasP = &parseData.ucas.res;

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), expectedFile1)) << "Error getting test data from '" << expectedFile1 << "'";
  rendered = ucasP->render(UpdateContextAvailabilitySubscription, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), expectedFile2)) << "Error getting test data from '" << expectedFile2 << "'";
  check = ucasP->check(UpdateContextAvailabilitySubscription, JSON, "", "predetected error", 0);
  EXPECT_STREQ(expectedBuf, check.c_str());
  
  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), expectedFile3)) << "Error getting test data from '" << expectedFile3 << "'";
  ucasP->duration.set("eeeee");
  check = ucasP->check(UpdateContextAvailabilitySubscription, JSON, "", "", 0);
  EXPECT_STREQ(expectedBuf, check.c_str());
}



/* ****************************************************************************
*
* json_invalidIsPattern - 
*/
TEST(UpdateContextAvailabilitySubscriptionRequest, json_invalidIsPattern)
{
  ParseData       reqData;
  const char*     fileName = "updateContextAvailabilitySubscriptionRequest_invalidIsPattern.json";
  ConnectionInfo  ci("", "POST", "1.1");
  std::string     expected = "{\n  \"subscriptionId\" : \"012345678901234567890123\",\n  \"errorCode\" : {\n    \"code\" : \"400\",\n    \"reasonPhrase\" : \"bad value for 'isPattern'\"\n  }\n}\n";

  ci.inFormat      = JSON;
  ci.outFormat     = JSON;

  EXPECT_EQ("OK", testDataFromFile(testBuf, sizeof(testBuf), fileName)) << "Error getting test data from '" << fileName << "'";

  std::string result = jsonTreat(testBuf, &ci, &reqData, UpdateContextAvailabilitySubscription, "updateContextAvailabilitySubscriptionRequest", NULL);
  EXPECT_EQ(expected, result);
}



/* ****************************************************************************
*
* response - 
*/
TEST(UpdateContextAvailabilitySubscriptionRequest, response)
{
  UpdateContextAvailabilitySubscriptionResponse  ucas;
  ErrorCode                                      ec(SccBadRequest, "Reason", "Detail");
  UpdateContextAvailabilitySubscriptionResponse  ucas2(ec);
  std::string                                    render;
  std::string                                    check;
  std::string                                    expected1 = "<updateContextAvailabilitySubscriptionResponse>\n  <subscriptionId>012345678901234567890123</subscriptionId>\n</updateContextAvailabilitySubscriptionResponse>\n";
  std::string                                    expected2 = "<updateContextAvailabilitySubscriptionResponse>\n  <subscriptionId>012345678901234567890123</subscriptionId>\n  <errorCode>\n    <code>400</code>\n    <reasonPhrase>Reason</reasonPhrase>\n    <details>Detail</details>\n  </errorCode>\n</updateContextAvailabilitySubscriptionResponse>\n";
  std::string                                    expected3 = "<updateContextAvailabilitySubscriptionResponse>\n  <subscriptionId>012345678901234567890123</subscriptionId>\n  <duration>ddd</duration>\n  <errorCode>\n    <code>400</code>\n    <reasonPhrase>syntax error in duration string</reasonPhrase>\n  </errorCode>\n</updateContextAvailabilitySubscriptionResponse>\n";
  std::string                                    expected4 = "<updateContextAvailabilitySubscriptionResponse>\n  <subscriptionId>012345678901234567890123</subscriptionId>\n  <duration>ddd</duration>\n  <errorCode>\n    <code>400</code>\n    <reasonPhrase>predetected error</reasonPhrase>\n  </errorCode>\n</updateContextAvailabilitySubscriptionResponse>\n";
  
  EXPECT_EQ(ucas2.errorCode.code, SccBadRequest);

  ucas.subscriptionId.set("012345678901234567890123");

  check = ucas.check(UpdateContextAvailabilitySubscription, XML, "", "", 0);
  EXPECT_EQ("OK", check);
  
  render = ucas.render(UpdateContextAvailabilitySubscription, XML, "", 0);
  EXPECT_EQ(expected1, render);

  ucas.errorCode.fill(SccBadRequest, "Reason", "Detail");
  render = ucas.render(UpdateContextAvailabilitySubscription, XML, "", 0);
  EXPECT_EQ(expected2, render);
  
  ucas.errorCode.fill(NO_ERROR_CODE, "", "");
  ucas.duration.set("ddd");
  check = ucas.check(UpdateContextAvailabilitySubscription, XML, "", "", 0);
  EXPECT_EQ(expected3, check);

  check = ucas.check(UpdateContextAvailabilitySubscription, XML, "", "predetected error", 0);
  EXPECT_EQ(expected4, check);
}
