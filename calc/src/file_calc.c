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
// Основная структура
typedef struct calcEl {
	char rezhim;
	double result;
	double *x,*y;
	char c;
	double *res;
	int size;
	struct calcEl *next;
} calcEl;

typedef struct turn {
	calcEl *headValue;
	calcEl *tlValue;
} turn;

void initialTurn (turn *Z) {
	Z->headValue = NULL;
	Z->tlValue = NULL;
}

void editTurn (turn *W, calcEl *dataCalc) {
	calcEl* temp = malloc (sizeof(calcEl));
	temp->c = dataCalc->c;
	temp->x = dataCalc->x;
	temp->y = dataCalc->y;
	temp->rezhim = dataCalc->rezhim;
	temp->res = dataCalc->res;
	temp->size = dataCalc->size;
	temp->next = NULL;
	temp->result = dataCalc->result;
	if (W->tlValue != NULL) {
		W->tlValue->next = temp;
	}
	W->tlValue = temp;
	if (W->headValue == NULL) {
		W->headValue = temp;
	}
}

calcEl* delTurn (turn *J) {
	calcEl *outRes;
	outRes = malloc (sizeof (calcEl));
	if (J->headValue == NULL) {
		outRes = NULL;
		return outRes;
	}
	calcEl *temp = J->headValue;
	outRes->c = temp->c;
	outRes->res = temp->res;
	outRes->result = temp->result;
	outRes->x = temp->x;
	outRes->y = temp->y;
	outRes->size = temp->size;
	outRes->rezhim = temp->rezhim;
	J->headValue = J->headValue->next;
	if (J->headValue == NULL) {
		J->tlValue = NULL;
	}
	free (temp);
	return outRes;
}

typedef struct node {
	double x;
	struct node *next;
} node;

typedef struct stack {
	node *headValue;
} stack;

void init_stack (stack *X) {
	X->headValue = NULL;
}

void push (stack *X, double num) {
	node * temp = malloc (sizeof (node));
	temp->x = num;
	temp->next = X->headValue;
	X->headValue = temp;
}

double pop (stack *Z) {
	node *temp;
	temp = malloc (sizeof (node));
	temp = Z->headValue;
	Z->headValue = Z->headValue->next;
	return temp->x;
}

FILE *fileInput, *fileOut;

int main(int argc, char *argv[]) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	char inputMass[256], inputFileName[259], outputFileName[259];
	char h, L, valSign;
	double d, num;
	double *result;
	double resultVal; 
	calcEl *var;
	turn cal1, cal2;
	stack s;
	
	do {
		puts ("b - обратная польская нотация, s - обычн");
		scanf (" %c", &L);

		puts ("Имя входного файла");
		scanf ("%s", inputFileName);

		puts ("Имя выходного файла");
		scanf ("%s", outputFileName);

		fileInput = fopen (inputFileName, "r");
		switch (L) {
			case 'b':
				init_stack (&s);

				if ((fileOut = fopen(outputFileName, "a")) == NULL) {
					fileOut = fopen(outputFileName, "w");
				}

				while (feof (fileInput) == 0) {
					fscanf (fileInput, "%s", inputMass);
					if (atof (inputMass) == 0) {
						valSign = inputMass[0];
						switch (valSign) {
							case '-':
								push (&s, pop (&s) - pop(&s));
								break;
							case '+':
								push (&s, pop (&s) + pop(&s));
								break;
							case '*':
								push (&s, pop (&s) * pop(&s));
								break;
							case '/':
								push (&s, pop (&s) / pop(&s));
								break;
							case '!':
								d = 1;
								num = pop (&s);
								if (num >= 0) {
									for (int i=0; i < num; i++) {
										d = d * (i + 1);
									}
								}
								push (&s, d);
								break;
							case '^':
								num = pop (&s);
								d = num;
								for (int i=1; i < pop (&s); i++) {
									d = d * num;
								}
								push (&s, d);
								break;
							case '=':
								fprintf (fileOut, "%lf\n", pop (&s));
								break;
						}
					} else {
						num = atof (inputMass);
						push (&s, num);
					}
				}
				fclose (fileInput);
				break;
			case 's':
				initialTurn (&cal1);
				initialTurn (&cal2);
				var = malloc (sizeof (calcEl));
				while (feof(fileInput) == 0) {
					fscanf (fileInput, " %c %c", &var->c, &var->rezhim);
					switch (var->rezhim) { // Режим работы (векторный или обычный)
						case 'V':
							fscanf (fileInput, "%i", &var->size); // Размерность вектора
							var->x = malloc (var->size * sizeof(double)); // Память на вектора
							var->y = malloc (var->size * sizeof(double));
							// Заполняем информацию о векторах
							for (int i = 0; i < var->size; i++) 
								fscanf (fileInput, "%lf", &var->x[i]);
							for (int i = 0; i < var->size; i++) 
								fscanf (fileInput, "%lf", &var->y[i]);
							break;
						case 'N':
							var->size = 1;
							if (var->c == '!') {
								var->x = malloc (sizeof (double));
								fscanf (fileInput, "%lf", &var->x[0]);
								var->y = NULL;
							}
							else {
								var->x = malloc (sizeof(double));
								var->y = malloc (sizeof(double));
								fscanf (fileInput, "%lf", &var->x[0]);
								fscanf (fileInput, "%lf", &var->y[0]);
							}
							break;
					}
					editTurn (&cal1, var);
				}
				free (var);
				fclose (fileInput);

				while ((var = delTurn(&cal1)) != NULL) {
					switch (var->rezhim) {
						// Векторный режим (суть работы такая же, как в предыдущих версиях, комментарии излишни)
						case 'V':
							switch (var->c) {
								case '+':
									result = malloc (var->size * sizeof(double));
									for (int i = 0; i < var->size; i++) 
										result[i] = var->x[i] + var->y[i];
									var->res = result;
									break;
								case '-':
									for (int i = 0; i < var->size; i++) 
										result[i] = var->x[i] - var->y[i];
									var->res = result;
									break;
								case '*':
									resultVal = 0;
									for (int i = 0; i<var -> size; i++) {
										resultVal += var->x[i] * var->y[i];
									}
									var->result = resultVal;
									break;
							}
							break;
						case 'N':
							// Скалярные операции. Принцип работы как в прошлых версиях
							switch (var->c) {
								case '+': 
									var->result = var->x[0] + var->y[0];
									break;
								case '-': 
									var->result = var->x[0] - var->y[0];
									break;
								case '*': 
									var->result = var->x[0] * var->y[0];
									break;
								case '/': 
									var->result = var->x[0] / var->y[0];
									break;
								case '^':
									d = var->x[0]; 
									for (int i=1; i < var->y[0]; i++) {
										d = d * var->x[0];
									}
									var->result = d;
									break;
								case '!': 
									d = 1; 
									if (var->x[0] >= 0) {
										for (int i = 0; i < var->x[0]; i++) {
											d = d * (i + 1);
										}
									}
									var->result = d;
									break;
							}
							break;
					}
					editTurn (&cal2, var);
				}
				// Открываем файл для записи, если нет его - создаем
				if ((fileOut = fopen(outputFileName, "a")) == NULL) {
					fileOut = fopen(outputFileName, "w");
				}
				while ((var = delTurn(&cal2)) != NULL) {
					// Заполняем его, в зависимости от выбранных операций и режима
					switch (var->rezhim) {
						case 'V':
							fprintf (fileOut, "( ");
							for (int i=0; i < var->size; i++) {
								if (i == var->size-1) {
									fprintf (fileOut, "%lf", var->x[i]);
								} else 
									fprintf (fileOut, "%lf ", var->x[i]);
							}
							fprintf (fileOut, " ) %c ( ", var->c);
							for (int i = 0; i < var->size; i++) {
								if (i == var->size-1) {
									fprintf (fileOut, "%lf", var->y[i]);
								} else 
									fprintf (fileOut, "%lf ", var->y[i]);
							}

							if (var->c == '+' || var->c == '-') {
								fprintf (fileOut, " ) = ( ");
								for (int i = 0; i < var->size; i++) {
									if (i == var->size-1) {
										fprintf (fileOut, "%lf", var->res[i]);
									} else 
										fprintf (fileOut, "%lf ", var->res[i]);
								}
								fprintf (fileOut, " )\n");
							} else 
								fprintf (fileOut, " ) = %lf\n", var->result);
							break;
						case 'N':
							if (var->c == '!') {
								fprintf (fileOut, "%lf! = %lf\n", *var->x, var->result);
							} else 
								fprintf (fileOut, "%lf %c %lf = %lf\n", *var->x, var->c, *var->y, var->result);
							break;
					}
				}
				break;
		}
		// Закрываем файл
		fclose (fileOut);
		puts ("\nДля продолжения введите y, n для выхода");
		scanf (" %c", &h);
	}
	while (h!='n');
	return 0;
}
