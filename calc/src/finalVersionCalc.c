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
#include "turnModule.h"
#include "listModule.h"
#include "structsCalc.h"
#include "stackModule.h"

FILE *fileInput,*fileOut;

int main(int argc, char *argv[]) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	char in[256], inputFileName[259], outputFileName[259];

	char h, rezhime, sign, r;
	double d, num;
	double *result;
	double res; 

	calcEl *var;
	
	stack s;
	
	turn tCalc1,tCalc2;
	
	list lCalc1,lCalc2;
	do {
		puts ("b - Обратная польская, n - обычная");
		scanf (" %c", &rezhime);

		puts ("Имя входного файла");
		scanf ("%s", inputFileName);

		puts ("Имя выходного файла");
		scanf ("%s", outputFileName);

		// Считали данные из файла
		fileInput = fopen (inputFileName, "r");
		// Выбрали режим польской обратной или стандарт
		switch (rezhime) {
			case 'b':
				// Обратная польская
				initialStack (&s);
				// При необходимости - создали файл выхода
				if ((fileOut=fopen(outputFileName, "a")) == NULL) {
					fileOut=fopen(outputFileName, "w");
				}
				// Идем по всему файлу
				while (feof (fileInput) == 0) {
					fscanf (fileInput, "%s", in);
					if (atof(in) == 0) {
						sign = in[0];
						// Отделяем знаки операций и проводим действия
						switch (sign) {
							case '+':
								pushStack (&s, popStack (&s) + popStack(&s));
								break;
							case '-':
								pushStack (&s, popStack (&s) - popStack(&s));
								break;
							case '*':
								pushStack (&s, popStack (&s) * popStack(&s));
								break;
							case '/':
								pushStack (&s, popStack (&s) / popStack(&s));
								break;
							case '!':
								d = 1; 
								num = popStack (&s);
								if (num >= 0) {
									for (int i = 0; i < num; i++) {
										d = d * (i + 1);
									}
								}
								pushStack (&s, d);
								break;
							case '^':
								num = popStack (&s);
								d = num; 
								for (int i = 1; i < popStack (&s); i++) {
									d = d * num;
								}
								pushStack (&s, d);
								break;
							case '=':
								fprintf (fileOut, "%lf\n", popStack (&s));
								break;
						}
					} else {
						num = atof (in);
						pushStack (&s, num);
					}
				}
				fclose (fileInput);
				break;
			case 'n':
				// Стандартный режим
				puts ("s - работаем со списком, t - работаем с очередями");
				scanf (" %c", &r);
				switch(r) {
					case 't':
						// Работаем с очередями
						// Инициализируем
						initialTurn (&tCalc1);
						initialTurn (&tCalc2);
						var = malloc (sizeof (calcEl));
						// Идем по всему файлу
						while (feof(fileInput) == 0) {
							fscanf (fileInput, " %c %c", &var->c, &var->rezhime);
							// Определяемся с режимом работы
							switch (var->rezhime) { // Выбор режима работы
								case 'V':
									// Работаем с векторами
									fscanf (fileInput, "%i", &var->size); // Длина вектора
									var->x = malloc (var->size*sizeof(double)); // Первый вектор
									var->y = malloc (var->size*sizeof(double)); // Второй вектор
									// Считываем вектор 1
									for (int i = 0; i < var->size; i++) 
										fscanf (fileInput, "%lf", &var->x[i]);
									// Считываем вектор 2
									for (int i = 0; i < var->size; i++) 
										fscanf (fileInput, "%lf", &var->y[i]);
									break;
								case 'N':
									// Работаем с числами
									var->size = 1;
									if (var->c == '!') {
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
							endTurn (&tCalc1, var);
						}
						free (var);
						fclose (fileInput);

						// Получив всю необходимую информацию, освободив память и закрыв файл, начинаем обработку данных
						while ((var = delTurn(&tCalc1)) != NULL) {
							switch (var->rezhime) {
								case 'V':
									// Стандартные операции с векторами 
									switch (var->c) {
										case '+':
											result = malloc (var->size*sizeof(double));
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
											res = 0;
											for (int i = 0; i < var->size; i++)
												res+=var->x[i] * var->y[i];
											var->result = res;
											break;
									}
									break;
								case 'N':
									// Стандартные операции с числами
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
											for (int i = 1; i < var->y[0]; i++)
												d = d * var->x[0];
											var->result = d;
											break;
										case '!':
											d = 1;
											if (var->x[0] >= 0)
												for (int i = 0; i < var->x[0]; i++)
													d = d * (i + 1);
											var->result = d;
											break;
									}
							}
							// Заканчиваем работу с очередями
							endTurn (&tCalc2, var);
						}

						// При необходимости пересоздаем файл выхода
						if ((fileOut=fopen(outputFileName, "a")) == NULL)
							fileOut=fopen(outputFileName, "w");

						// Закончив с очередями, пишем информацию в файл в соответствующем виде
						while ((var = delTurn(&tCalc2)) != NULL) {
							switch (var->rezhime) {
								case 'V':
									fprintf (fileOut, "( ");
									for (int i = 0; i < var->size; i++) {
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
						// Не забываем закрыть файл вывода
						fclose (fileOut);
						break;
					case 's':
						// Работаем со списком
						// Инициализируем их
						initialList (&lCalc1);
						initialList (&lCalc2);
						
						var = malloc (sizeof (calcEl));
						// Идем по входящему файлу
						while (feof(fileInput) == 0) {
							fscanf (fileInput, " %c %c", &var->c, &var->rezhime);
							switch (var->rezhime) {
								case 'V':
									// Считываем информацию по векторам, если режим векторный
									fscanf (fileInput, "%i", &var->size); 
									var->x = malloc (var->size * sizeof(double));
									var->y = malloc (var->size * sizeof(double));
									for (int i = 0; i < var->size; i++) 
										fscanf (fileInput, "%lf", &var->x[i]);
									for (int i = 0; i < var->size; i++) 
										fscanf (fileInput, "%lf", &var->y[i]);
									break;
								case 'N':
									// Информация по числам
									var->size = 1;
									if (var->c == '!') {
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
							// Добавили в список
							pushInList (&lCalc1, var);
						}
						// Закрыли файл
						fclose (fileInput);
						// Свапнули значения
						lCalc1.tlValue = lCalc1.headValue;
						// По списку двигаемся
						while (lCalc1.tlValue != NULL) {
							// Получаем нужную информацию и производим операции в зависимости от режима работы
							var->rezhime = lCalc1.tlValue->rezhime;
							var->c = lCalc1.tlValue->c;
							var->x = lCalc1.tlValue->x;
							var->y = lCalc1.tlValue->y;
							var->result = lCalc1.tlValue->result;
							var->res = lCalc1.tlValue->res;
							var->size = lCalc1.tlValue->size;
							switch (var->rezhime) {
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
											for (int i = 0; i < var->size; i++)
												res += var->x[i] * var->y[i];
											var->result = res;
											break;
									}
									break;
								case 'N':
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
											for (int i = 1; i < var->y[0]; i++)
												d = d * var->x[0];
											var->result = d;
											break;
										case '!':
											d = 1; 
											if (var->x[0] >= 0)
												for (int i = 0; i < var->x[0]; i++)
													d = d * (i + 1);
											var->result = d;
											break;
									}
							}
							// Добавили во второй список
							pushInList (&lCalc2, var);
							// Перешли дальше
							nextList (&lCalc1);
						}

						// При необходимости досоздаем файл выхода
						if ((fileOut=fopen(outputFileName, "a"))==NULL)
								fileOut=fopen(outputFileName, "w");
						// Освобождаем память
						free (var);
						// Свап значений
						lCalc1.tlValue = lCalc1.headValue;
						lCalc2.tlValue = lCalc2.headValue;

						// Идем по сформированному списку и пишем данные в файл
						while (lCalc2.tlValue != NULL) {
							switch (lCalc2.tlValue->rezhime) {
								case 'V':
									fprintf (fileOut, "( ");
									for (int i = 0; i < lCalc2.tlValue->size; i++) {
										if (i == lCalc2.tlValue->size-1) {
											fprintf (fileOut, "%lf", lCalc2.tlValue->x[i]);
										} else 
											fprintf (fileOut, "%lf ", lCalc2.tlValue->x[i]);
									}
									fprintf (fileOut, " ) %c ( ", lCalc2.tlValue->c);
									
									for (int i = 0; i < lCalc2.tlValue->size; i++) {
										if (i == lCalc2.tlValue->size-1) {
											fprintf (fileOut, "%lf", lCalc2.tlValue->y[i]);
										} else 
											fprintf (fileOut, "%lf ", lCalc2.tlValue->y[i]);
									}

									if (lCalc2.tlValue->c == '+' || lCalc2.tlValue->c == '-') {
										fprintf (fileOut, " ) = ( ");
										for (int i = 0; i < lCalc2.tlValue->size; i++) {
											if (i == lCalc2.tlValue->size-1) {
												fprintf (fileOut, "%lf", lCalc2.tlValue->res[i]);
											} else 
												fprintf (fileOut, "%lf ", lCalc2.tlValue->res[i]);
										}
										fprintf (fileOut, " )\n");
									} else 
										fprintf (fileOut, " ) = %lf\n", lCalc2.tlValue->result);
									break;
								case 'N':
									if (lCalc2.tlValue->c == '!') {
										fprintf (fileOut, "%lf! = %lf\n", *lCalc2.tlValue->x, lCalc2.tlValue->result);
									} else 
										fprintf (fileOut, "%lf %c %lf = %lf\n", *lCalc2.tlValue->x, lCalc2.tlValue->c, *lCalc2.tlValue->y, lCalc2.tlValue->result);
									break;
							}
							nextList (&lCalc2);
						}
						// Не забываем закрыл файл выхода
						fclose (fileOut);

						// Чистим списки 
						while (lCalc1.headValue != NULL) {
							deleteList (&lCalc1);
						}
						while (lCalc2.headValue != NULL) {
							deleteList (&lCalc2);
						}
						break;
				}
				break;
		}
		puts ("\nДля продолжения введите y, n для выхода");
		scanf (" %c", &h);
	}
	while (h!='n');
	return 0;
}
