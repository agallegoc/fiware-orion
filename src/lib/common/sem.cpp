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
* Author: Fermin Galan
*/

#include "sem.h"
#include <semaphore.h>
#include <errno.h>
#include "logMsg/logMsg.h"

/* ****************************************************************************
*
* Globals -
*/
static sem_t sem;

/* ****************************************************************************
*
* semInit -
*
* Return Value (of sem_init)
*   0 on success,
*  -1 on failure
*
*/
int semInit(void) {
  // sem_init: 
  //   parameter #1: 0 - the semaphore is to be shared between threads,
  //   parameter #2: 1 - initially the semaphore is free
  return sem_init(&sem, 0, 1);
}

/* ****************************************************************************
*
* semTake -
*/
int semTake(void) {
  return sem_wait(&sem);
}

/* ****************************************************************************
*
* semGive -
*/
int semGive(void) {
  return sem_post(&sem);
}
