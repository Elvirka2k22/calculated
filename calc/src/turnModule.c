/*
 * turnModule.c
 *
 *  Created on: 28 июн. 2022 г.
 *      Author: Elvira
 */

// Тимербаева Эльвира Ильсур
// Модуль работы с очередями

#include "structsCalc.h"
#include <stdio.h>
#include <stdlib.h>

void initialTurn (turn *T) {
	T->headValue = NULL;
	T->tlValue = NULL;
}

void endTurn (turn *T, calcEl *dataCalc) {
	calcEl* temp = malloc (sizeof(calcEl));
	temp->x = dataCalc->x;
	temp->y = dataCalc->y;
	temp->rezhime = dataCalc->rezhime;
	temp->size = dataCalc->size;
	temp->result = dataCalc->result;
	temp->c = dataCalc->c;
	temp->res = dataCalc->res;
	temp->next = NULL;
	if (T->tlValue != NULL) {
		T->tlValue->next = temp;
	}
	T->tlValue = temp;
	if (T->headValue == NULL) {
		T->headValue = temp;
	}
}

calcEl* delTurn (turn *T) {
	calcEl *outVal;
	outVal = malloc (sizeof (calcEl));
	if (T->headValue == NULL) {
		outVal = NULL;
		return outVal;
	}
	calcEl *temp = T->headValue;
	outVal->result = temp->result;
	outVal->x = temp->x;
	outVal->y = temp->y;
	outVal->size = temp->size;
	outVal->rezhime = temp->rezhime;
	T->headValue = T->headValue->next;
	outVal->res = temp->res;
	outVal->c = temp->c;
	if (T->headValue == NULL) {
		T->tlValue = NULL;
	}

	free (temp);
	return outVal;
}
