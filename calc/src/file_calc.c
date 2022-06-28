/*
 ============================================================================
 Name        : calc.c
 Author      : Elvira
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

// Тимербаева Эльвира Ильсур
#include <stdio.h>
#include <stdlib.h>

typedef struct calcEl {
	char c;
	char rezhime;
	double *res;

	double result;
	double *x,*y;
	
	int size;
	struct calcEl *next;
} calcEl;

typedef struct queue {
	calcEl *tlValue;

	calcEl *headValue;
} queue;

void turnInit (queue *Z) {
	Z->tlValue = NULL;
	Z->headValue = NULL;
	
}

void turn (queue *W, calcEl *dataCalc) {
	calcEl* tempValue = malloc (sizeof(calcEl));
	tempValue->x = dataCalc->x;
	tempValue->y = dataCalc->y;
	tempValue->c = dataCalc->c;

	tempValue->rezhime = dataCalc->rezhime;
	
	tempValue->size = dataCalc->size;
	tempValue->next = NULL;
	tempValue->res = dataCalc->res;
	tempValue->result = dataCalc->result;
	if (W->tlValue != NULL)
	{
		W->tlValue->next = tempValue;
	}
	W->tlValue = tempValue;
	if (W->headValue == NULL)
	{
		W->headValue = tempValue;
	}
}

calcEl* turnDel (queue *J)
{
	calcEl *outVal;
	outVal = malloc (sizeof (calcEl));
	if (J->headValue == NULL) {
		outVal = NULL;
		return outVal;
	}
	calcEl *temp = J->headValue;
	outVal->c = temp->c;
	outVal->res = temp->res;

	outVal->result = temp->result;

	outVal->x = temp->x;
	outVal->y = temp->y;

	outVal->size = temp->size;
	outVal->rezhime = temp->rezhime;

	J->headValue = J->headValue->next;
	if (J->headValue == NULL) {
		J->tlValue = NULL;
	}
	free (temp);
	return outVal;
}

FILE *fileInput, *fileOut;
int main(int argc, char *argv[]) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	char inputFileName[259], outputFileName[259];
	char h;
	double d, res;
	double *result;
	calcEl *varVal;
	queue qCalc1, qCalc2;
	do {
		turnInit (&qCalc1);
		turnInit (&qCalc2);
		puts ("Имя входного файла");
		scanf ("%s", inputFileName);

		puts ("Имя выходного файла");
		scanf ("%s", outputFileName);

		fileInput = fopen (inputFileName, "r");
		varVal = malloc (sizeof (calcEl));
		while (feof(fileInput) == 0) {
			fscanf (fileInput, " %c %c", &varVal->c, &varVal->rezhime);
			switch (varVal->rezhime) { //конструкция для выбора режима работы
				case 'V':
					fscanf (fileInput, "%i", &varVal->size); //считываем длину вектора
					varVal->x = malloc (varVal->size*sizeof(double));
					varVal->y = malloc (varVal->size*sizeof(double));
					for (int i=0; i < varVal->size; i++) 
						fscanf (fileInput, "%lf", &varVal->x[i]);
					for (int i=0; i < varVal->size; i++) 
						fscanf (fileInput, "%lf", &varVal->y[i]);
					break;
				case 'N':
					varVal->size = 1;
					if (varVal->c == '!') {
						varVal->x = malloc (sizeof (double));
						fscanf (fileInput, "%lf", &varVal->x[0]);
						varVal->y = NULL;
					} else {
						varVal->x = malloc (sizeof(double));
						varVal->y = malloc (sizeof(double));
						fscanf (fileInput, "%lf", &varVal->x[0]);
						fscanf (fileInput, "%lf", &varVal->y[0]);
					}
					break;
			}
			turn (&qCalc1, varVal);
		}
		free (varVal);
		fclose (fileInput);
		
		while ((varVal = turnDel(&qCalc1)) != NULL) {
			switch (varVal->rezhime) {
				case 'V':
					switch (varVal->c) {
						case '+':
							result = malloc (varVal->size*sizeof(double));
							for (int i=0; i < varVal->size; i++) 
								result[i] = varVal->x[i] + varVal->y[i];
							varVal->res = result;
							break;
						case '-':
							for (int i=0; i < varVal->size; i++) 
								result[i] = varVal->x[i] - varVal->y[i];
							varVal->res = result;
							break;
						case '*':
							res = 0;
							for (int i=0; i < varVal->size; i++) {
								res += varVal->x[i] * varVal->y[i];
							}
							varVal->result = res;
							break;
					}
					break;
				case 'N':
					switch (varVal->c) {
						case '+': 
							varVal->result = varVal->x[0] + varVal->y[0];
							break;
						case '-': 
							varVal->result = varVal->x[0] - varVal->y[0];
							break;
						case '*': 
							varVal->result = varVal->x[0] * varVal->y[0];
							break;
						case '/': 
							varVal->result = varVal->x[0] / varVal->y[0];
							break;
						case '^': 
							d = varVal->x[0];
							for (int i=1; i < varVal->y[0]; i++) {
								d = d * varVal->x[0];
							}
							varVal->result = d;
							break;
						case '!':
							d = 1;
							if (varVal->x[0] >= 0) {
								for (int i=0; i<varVal->x[0]; i++) {
									d = d * (i+1);
								}
							}
							varVal->result = d;
							break;
					}
			}
			turn (&qCalc2, varVal);
		}
		if ((fileOut = fopen(outputFileName, "a")) == NULL) {
			fileOut = fopen(outputFileName, "w");
		}
		while ((varVal = turnDel(&qCalc2)) != NULL) {
			switch (varVal->rezhime) {
				case 'V':
					fprintf (fileOut, "( ");
					for (int i = 0; i < varVal->size; i++) {
						if (i == varVal->size-1) {
							fprintf (fileOut, "%lf", varVal->x[i]);
						} else 
							fprintf (fileOut, "%lf ", varVal->x[i]);
					}
					fprintf (fileOut, " ) %c ( ", varVal->c);
					for (int i = 0; i < varVal->size; i++) {
						if (i == varVal->size-1) {
							fprintf (fileOut, "%lf", varVal->y[i]);
						} else 
							fprintf (fileOut, "%lf ", varVal->y[i]);
					}
					if (varVal->c == '+' || varVal->c == '-') {
						fprintf (fileOut, " ) = ( ");

						for (int i = 0; i < varVal->size; i++) {
							if (i == varVal->size-1) {
								fprintf (fileOut, "%lf", varVal->res[i]);
							} else 
								fprintf (fileOut, "%lf ", varVal->res[i]);
						}
						fprintf (fileOut, " )\n");
					} else 
						fprintf (fileOut, " ) = %lf\n", varVal->result);
					break;
				case 'N':
					if (varVal->c == '!') {
						fprintf (fileOut, "%lf! = %lf\n", *varVal->x, varVal->result);
					} else 
						fprintf (fileOut, "%lf %c %lf = %lf\n", *varVal->x, varVal->c, *varVal->y, varVal->result);
					break;
			}
		}
		fclose (fileOut);
		puts ("\nДля продолжения введите y, n для выхода");
		scanf (" %c", &h);
	}
	while (h!='n');
	return 0;
}
