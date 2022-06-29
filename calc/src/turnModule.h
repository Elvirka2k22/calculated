/*
 * turnModule.h
 *
 *  Created on: 28 июн. 2022 г.
 *      Author: Elvira
 */

// Тимербаева Эльвира Ильсур

#include "structsCalc.h"
#ifndef QUEUE_H_
#define QUEUE_H_

void initialTurn (turn *T);

void endTurn (turn *T, calcEl *dataCalc);

calcEl* delTurn (turn *T);

#endif 
