/*
 * stackModule.c
 *
 *  Created on: 28 июн. 2022 г.
 *      Author: Elvira
 */

// Тимербаева Эльвира Ильсур
// Работа со stack

#include "structsCalc.h"
#include <stdio.h>
#include <stdlib.h>

void initialStack (stack *S) {
	S->headValue = NULL;
}

void pushStack (stack *S, double num) {
	node * temp = malloc (sizeof (node));
	temp->x = num;
	temp->next = S->headValue;
	S->headValue = temp;
}

double popStack (stack *S) {
	node *temp;
	temp = malloc (sizeof (node));
	temp = S->headValue;
	S->headValue = S->headValue->next;
	return temp->x;
}
