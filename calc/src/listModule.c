/*
 * listModule.h
 *
 *  Created on: 28 июн. 2022 г.
 *      Author: Elvira
 */

// Тимербаева Эльвира Ильсур
// Модуль отвечающий за списки и функции работы с ними

#include "structsCalc.h"
#include <stdio.h>
#include <stdlib.h>

void initialList (list *listCalc) {
	listCalc->headValue = NULL;
	listCalc->tlValue = NULL;
}

void pushInList (list *listCalc, calcEl *dataCalc) {
	calcEl* temp = malloc (sizeof(calcEl));
	calcEl *lastVal = listCalc->headValue;
	
	temp->x = dataCalc->x;
	temp->y = dataCalc->y;
	temp->c = dataCalc->c;
	temp->rezhime = dataCalc->rezhime;
	temp->res = dataCalc->res;
	temp->size = dataCalc->size;
	temp->next = NULL;
	temp->result = dataCalc->result;
	if (listCalc->headValue==NULL) {
		listCalc->headValue = temp;
		return;
	}

	while (lastVal->next != NULL) {
		lastVal = lastVal->next;
	} lastVal->next = temp;
	
	return;
}

calcEl* nextList (list *listCalc) {
	listCalc->tlValue = listCalc->tlValue->next;
	return listCalc->tlValue;
}

void deleteList (list *listCalc) {
	calcEl *temp;
	if (&listCalc->headValue == NULL) 
		return;
	temp = listCalc->headValue;
	listCalc->headValue = listCalc->headValue->next;

	free (temp);
}


