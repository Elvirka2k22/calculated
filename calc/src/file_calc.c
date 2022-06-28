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

// основная структура данных
typedef struct calcEl
{
	char rezhim;
	char c;
	double result;
	double *x,*y;
	double *resultOperation;
	int size;
	struct calcEl *next;
} calcEl;

// Структура для хранения текущему и главного значения
typedef struct listCalcEl
{
	calcEl *headValue;
	calcEl *currentValue;
} listCalcEl;

// Стартовая функция инициализации значений
void initListCalc (listCalcEl *val)
{
	val->headValue = NULL;
	val->currentValue = NULL;
}

void pushCalc (listCalcEl *val, calcEl *dataCalc)
{
	calcEl* tempInfo = malloc (sizeof(calcEl));
	calcEl *last = val->headValue;
	tempInfo->x = dataCalc->x;
	tempInfo->y = dataCalc->y;
	tempInfo->c = dataCalc->c;
	tempInfo->rezhim = dataCalc->rezhim;
	tempInfo->size = dataCalc->size;
	tempInfo->resultOperation = dataCalc->resultOperation;
	tempInfo->next = NULL;
	tempInfo->result = dataCalc->result;
	
	if (val->headValue == NULL)
	{
		val->headValue = tempInfo;
		return;
	}
	
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = tempInfo;
	return;
}



calcEl* nextCalcValue (listCalcEl *l)
{
	l->currentValue = l->currentValue->next;
	return l->currentValue;
}

void deleteCalc (listCalcEl *l)
{
	calcEl *temp;
	if (&l->headValue == NULL) return;
	temp = l->headValue;
	l->headValue = l->headValue->next;
	free (temp);
}

FILE *fileInput,*fileOut;
int main(int argc, char *argv[])
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	
	char inputFileName[259], outputFileName[259];
	char h; double d, resultValueCalc;
	double *result;

	calcEl *var;
	listCalcEl lCalc1,lCalc2;
	
	do
	{
		// Инициализуем 
		initListCalc (&lCalc1);
		initListCalc (&lCalc2);
		puts ("Имя входного файла");
		scanf ("%s", inputFileName);

		puts ("Имя выходного файла");
		scanf ("%s", outputFileName);

		fileInput = fopen (inputFileName, "r");
		var = malloc (sizeof (calcEl));
		while (feof(fileInput) == 0) {
			fscanf (fileInput, " %c %c", &var->c, &var->rezhim);
			switch (var->rezhim) { // Режим работы (векторный, стандартный)
				case 'V':
					fscanf (fileInput, "%i", &var->size); // Вытаскиваем длину вектора
					// Выделили
					var->x = malloc (var->size*sizeof(double));
					var->y = malloc (var->size*sizeof(double));
					// Считали информацию по векторам
					for (int i=0; i < var->size; i++) 
						fscanf (fileInput, "%lf", &var->x[i]);
					for (int i=0; i < var->size; i++) 
						fscanf (fileInput, "%lf", &var->y[i]);
					break;
				case 'N':
					var->size = 1;
					if (var->c == '!')
					{
						var->x = malloc (sizeof (double));
						fscanf (fileInput, "%lf", &var->x[0]);
						var->y = NULL;
					} else {
						var->x = malloc (sizeof(double));
						var->y = malloc (sizeof(double));
						fscanf (fileInput, "%lf", &var->x[0]);
						fscanf (fileInput, "%lf", &var->y[0]);
					}
					break;
			}
			pushCalc (&lCalc1, var);
		}
		fclose (fileInput);
		lCalc1.currentValue = lCalc1.headValue;
		while (lCalc1.currentValue != NULL) {
			var->rezhim = lCalc1.currentValue->rezhim;
			
			var->x = lCalc1.currentValue->x;
			var->y = lCalc1.currentValue->y;
			var->c = lCalc1.currentValue->c;
			var->result = lCalc1.currentValue->result;
			var->resultOperation = lCalc1.currentValue->resultOperation;
			var->size = lCalc1.currentValue->size;
			switch (var->rezhim) {
				case 'V':
					switch (var->c) {
						case '+':
							result = malloc (var->size*sizeof(double));
							for (int i=0; i<var->size; i++) 
								result[i] = var->x[i]+var->y[i];
							var->resultOperation = result;
							break;
						case '-':
							for (int i=0; i<var->size; i++) 
								result[i] = var->x[i]-var->y[i];
							var->resultOperation = result;
							break;
						case '*':
							for (int i=0; i<var->size; i++) {
								resultValueCalc += var->x[i] * var->y[i];
							}
							var->result = resultValueCalc;
							break;
					}
					break;
				case 'N':
					switch (var->c) {
						case '+': // блок суммы
							var->result = var->x[0] + var->y[0];
							break;
						case '-': // блок разности
							var->result = var->x[0] - var->y[0];
							break;
						case '*': // блок умножения
							var->result = var->x[0] * var->y[0];
							break;
						case '/': // блок деления
							var->result = var->x[0] / var->y[0];
							break;
						case '^': // блок возведения в степень
							d=var->x[0]; // приравниваем, чтобы посчитать степень
							for (int i=1; i < var->y[0]; i++)
							{
								d = d * var->x[0];
							}
							var->result = d;
							break;
						case '!': // блок факториала
							d=1; // приравниваем, чтобы посчитать факториал
							if (var->x[0] >= 0) // так как факториал 0=1, сделаем такой цикл
							{
								for (int i=0; i < var->x[0]; i++)
								{
									d = d * (i+1);
								}
							}
							var->result = d;
							break;
					}
					break;
			}
			pushCalc (&lCalc2, var);
			nextCalcValue (&lCalc1);
		}
		if ((fileOut = fopen(outputFileName, "a")) == NULL) {
			fileOut = fopen(outputFileName, "w");
		}
		free (var);

		lCalc1.currentValue = lCalc1.headValue;
		lCalc2.currentValue = lCalc2.headValue;
		
		while (lCalc2.currentValue != NULL) {
			switch (lCalc2.currentValue->rezhim) {
				case 'V':
					fprintf (fileOut, "( ");
					for (int i = 0; i < lCalc2.currentValue->size; i++) {
						if (i == lCalc2.currentValue->size-1) {
							fprintf (fileOut, "%lf", lCalc2.currentValue->x[i]);
						}
						else 
							fprintf (fileOut, "%lf ", lCalc2.currentValue->x[i]);
					}
					fprintf (fileOut, " ) %c ( ", lCalc2.currentValue->c);
					for (int i = 0; i < lCalc2.currentValue->size; i++) {
						if (i == lCalc2.currentValue->size-1) {
							fprintf (fileOut, "%lf", lCalc2.currentValue->y[i]);
						}
						else 
							fprintf (fileOut, "%lf ", lCalc2.currentValue->y[i]);
					}
					if (lCalc2.currentValue->c == '+' || lCalc2.currentValue->c == '-') {
						fprintf (fileOut, " ) = ( ");
						for (int i=0; i < lCalc2.currentValue->size; i++) {
							if (i == lCalc2.currentValue->size-1) {
								fprintf (fileOut, "%lf", lCalc2.currentValue->resultOperation[i]);
							}
							else 
								fprintf (fileOut, "%lf ", lCalc2.currentValue->resultOperation[i]);
						}
						fprintf (fileOut, " )\n");
					}
					else 
						fprintf (fileOut, " ) = %lf\n", lCalc2.currentValue->result);
					break;
				case 'N':
					if (lCalc2.currentValue->c == '!') {
						fprintf (fileOut, "%lf! = %lf\n", *lCalc2.currentValue->x, lCalc2.currentValue->result);
					}
					else 
						fprintf (fileOut, "%lf %c %lf = %lf\n", *lCalc2.currentValue->x, lCalc2.currentValue->c, *lCalc2.currentValue->y, lCalc2.currentValue->result);
					break;
				}
			nextCalcValue (&lCalc2);
		}
		fclose (fileOut);
		while (lCalc1.headValue != NULL) {
			deleteCalc (&lCalc1);
		}

		while (lCalc2.headValue != NULL) {
			deleteCalc (&lCalc2);
		}

		puts ("\nДля продолжения введите y, n для выхода");
		scanf (" %c", &h);
	}
	while (h!='n');
	return 0;
}
