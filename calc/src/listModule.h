/*
 * listModule.h
 *
 *  Created on: 28 июн. 2022 г.
 *      Author: Elvira
 */

// Тимербаева Эльвира Ильсур
#include "structsCalc.h"
#ifndef LIST_H_
#define LIST_H_

void initialList (list *listCalc);

void pushInList (list *listCalc, calcEl *dataCalc);

void deleteList (list *listCalc);

calcEl* nextList (list *listCalc);

#endif
