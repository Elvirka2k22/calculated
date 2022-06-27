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
char regul;
char inputFileName[259], outputFileName[259];
char h;
FILE *fileInput,*fileOut;
int main(int argc, char *argv[])
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	do
	{
		puts ("Имя входного файла");
		scanf ("%s", inputFileName);

		puts ("Имя выходного файла");
		scanf ("%s", outputFileName);
        // Открываем файл на чтение и собираем данные
		fileInput = fopen (inputFileName, "r");
		if ((fileOut=fopen(outputFileName, "a"))==NULL)
			{
                // В случае отсутствия файла для записи - создаем, открыв на запись
				fileOut=fopen(outputFileName, "w");
			}
		while (feof(fileInput) == 0)
		{
            // Идем через весь входящий файл
			double a, b, d; // задаем переменные типа double
			char c; // задаем переменную типа char
			char rezhime;
            // Определяем режим работы калькулятора (векторный, обычный)
			fscanf (fileInput, " %c %c", &c, &rezhime);
			switch (rezhime)
			{
                case 'V':
                {
                    int lVector; // длина вектора
                    fscanf (fileInput, "%i", &lVector); //считываем длину вектора
                    switch (c){
                        case '+':
                        {
                            double *f,*g;
                            f = malloc(lVector*sizeof(double)); // память для хранения вектора
                            g = malloc(lVector*sizeof(double));
                            fprintf (fileOut, "(");
                            for (int i = 0; i < lVector; i++) //считываем вектор
                            {
                                fscanf (fileInput, "%lf", &f[i]);
                                fprintf (fileOut, "%lf ", f[i]);
                            }
                            fprintf (fileOut, ") + (");
                            for (int i = 0; i<lVector; i++)
                            {
                                fscanf (fileInput, "%lf", &g[i]);
                                fprintf (fileOut, "%lf ", g[i]);
                            }
                            fprintf (fileOut, ") = (");
                            for (int i = 0; i<lVector; i++)
                            {
                                fprintf (fileOut, "%lf ", f[i]+g[i]);
                            }
                            fprintf (fileOut, ")\n");
                            free (f);
                            free (g);
                            break;
                        }
                        case '-':
                        {
                            double *f,*g;
                            f=malloc(lVector*sizeof(double));
                            g=malloc(lVector*sizeof(double));
                            fprintf (fileOut, "(");
                            for (int i = 0; i<lVector; i++) //считываем вектор
                            {
                                fscanf (fileInput, "%lf", &f[i]);
                                fprintf (fileOut, "%lf ", f[i]);
                            }
                            fprintf (fileOut, ") - (");
                            for (int i = 0; i<lVector; i++)
                            {
                                fscanf (fileInput, "%lf", &g[i]);
                                fprintf (fileOut, "%lf ", g[i]);
                            }
                            fprintf (fileOut, ") = (");
                            for (int i = 0; i<lVector; i++)
                            {
                                fprintf (fileOut, "%lf ", f[i]-g[i]);
                            }
                            fprintf (fileOut, ")\n");
                            free (f);
                            free (g);
                            break;
                        }
                        case '*':
                        {
                            double *f,*g;
                            f=malloc(lVector*sizeof(double));
                            g=malloc(lVector*sizeof(double));
                            fprintf (fileOut, "(");
                            for (int i=0; i<lVector; i++) //считываем вектор
                            {
                                fscanf (fileInput, "%lf", &f[i]);
                                fprintf (fileOut, "%lf ", f[i]);
                            }
                            fprintf (fileOut, ") * (");
                            for (int i=0; i<lVector; i++)
                            {
                                fscanf (fileInput, "%lf", &g[i]);
                                fprintf (fileOut, "%lf ", g[i]);
                            }
                            fprintf (fileOut, ") = ");
                            double resultVec; //задаем переменную для хранения результата
                            for (int i=0; i<lVector; i++)
                            {
                                resultVec += f[i] * g[i];
                            }
                            fprintf (fileOut, "%lf\n", resultVec);
                            resultVec = 0;
                            free (f);
                            free (g);
                            break;
                        }
                    }
                    break;
                }
                case 'N':
                {
                    switch (c) //блок функций
                    {
                        case '+': // Если ищем сумму
                            fscanf (fileInput, "%lg %lg", &a, &b);
                            fprintf (fileOut, "%lg + %lg = %lg\n", a,b,a+b);
                            break;
                        case '-': // Если ищем разность
                            fscanf (fileInput, "%lg %lg", &a, &b);
                            fprintf (fileOut, "%lg - %lg = %lg\n", a,b,a-b);
                            break;
                        case '*': // Если умножаем
                            fscanf (fileInput, "%lg %lg", &a, &b);
                            fprintf (fileOut, "%lg * %lg = %lg\n", a,b,a*b);
                            break;
                        case '/': // Делим
                            fscanf (fileInput, "%lg %lg", &a, &b);
                            fprintf (fileOut, "%lg / %lg = %lg\n", a,b,a/b);
                            break;
                        case '^': // Степень
                            fscanf (fileInput, "%lg %lg", &a, &b);
                            d = a; // временное хранение
                            for (int i = 1; i < b; i++)
                            {
                                d = d * a;
                            }
                            fprintf (fileOut, "%lg ^ %lg = %lg\n", a, b, d);
                            break;
                        case '!': // блок факториала
                            d = 1; // приравниваем, чтобы посчитать факториал
                            fscanf (fileInput, "%lg", &a);
                            if (a >= 0) // так как факториал 0=1, сделаем такой цикл
                            {
                                for (int i = 0; i<a; i++)
                                {
                                    d = d * (i + 1);
                                }
                                fprintf (fileOut, "%lg! = %lg\n", a,d);
                            }
                            break;
                    }
                    break;
			    }
			}
		}
		fclose (fileInput);
		fclose (fileOut);
		puts ("\nДля продолжения введите y, n для выхода");
		scanf (" %c", &h);
	}
	while (h!='n');
	return 0;
}
