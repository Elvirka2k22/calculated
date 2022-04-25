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
#include <math.h>
#include <locale.h>

int main() {

	char rezhim; // Для выборы режим (векторный/обычный)
    // установливаем буферизацию для записи в поток данных
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    double *x,*y; // для вычисления векторов
    double resultVector;

    float a,b; // Для стандартных действий

    double e,f; // Для использования в функции pow при возведении в степень, так как там требуется тип double для входящих параметров

    int d; // Для вычисления факториала
    unsigned long int fact;

    int lVector; // Для длины вектора
    char c,r; // Тип char для выбора действия и продолжения вычислений
    // Учитывая, что у нас есть действие по вычислению факториала, нужно сначала запрашивать действие - потом уже запрашивать числа
    // При этом, будем пользоваться функцией pow из math для возведения в степень, дабы учесть возможность использовать вещественные числа
    do{
        fact = 1;
        printf ("Ведите S для обычного режима или V для векторного: "); //выбираем режим работы
        scanf (" %c", &rezhim);
        switch (rezhim){
            case 'V':
                printf ("Укажите длину вектора:\n");
                scanf ("%i", &lVector); //считываем длину вектора
                x=malloc(lVector*sizeof(double)); // выделяем память для векторов
                y=malloc(lVector*sizeof(double));
                printf("\nВыбор векторного действия:\n'+' - сложение векторов\n'-' - вычитание векторов\n'*' - умножение векторов\n");
                scanf(" %c", &c);
                switch(c){
                    case'+':
                        printf ("Введите значение 1 вектора:\n");
                        for (int i=0;i<lVector;i++) //считываем вектор
                        {
                            scanf ("%lf", &x[i]);
                        }
                        printf ("\nВведите значение 2 вектора:\n");
                        for (int i=0;i<lVector;i++)
                        {
                            scanf ("%lf", &y[i]);
                        }
                        for (int i=0;i<lVector;i++)
                        {
                            printf ("\nРезультат сложения векторов: %lf ", x[i]+y[i]);
                        }
                        break;
                    case'-':
                        printf ("Введите значение 1 вектора:\n");
                        for (int i=0;i<lVector;i++) //считываем вектор
                        {
                            scanf ("%lf", &x[i]);
                        }
                        printf ("\nВведите значение 2 вектора:\n");
                        for (int i=0;i<lVector;i++)
                        {
                            scanf ("%lf", &y[i]);
                        }
                        for (int i=0;i<lVector;i++)
                        {
                            printf ("\nРезультат вычитания векторов: %lf ", x[i]-y[i]);
                        }
                        break;
                    case'*':
                        printf ("Введите значение 1 вектора:\n");
                         for (int i=0;i<lVector;i++) //считываем вектор
                        {
                            scanf ("%lf", &x[i]);
                        }
                        printf ("\nВведите значение 2 вектора:\n");
                        for (int i=0;i<lVector;i++)
                        {
                            scanf ("%lf", &y[i]);
                        }
                        for (int i=0;i<lVector;i++)
                        {
                            resultVector+=x[i]*y[i];
                        }
                        printf ("\nРезультат умножения векторов: %lf", resultVector);
                        break;
                    default:
                        printf("\nНеизвестное действие... Я ОТКАЗЫВАЮСЬ работать\n");
                }
                free (x);
			    free (y);
                break;
            case 'S':
                printf("Vibirite deystvie:\n'+' - slozhenie\n'-' - vichitanie\n'*' - umnozhenie\n'/' - delenie\n'!' - factorial\n'^' - vozvedenie v stepen\n");
                scanf(" %c", &c);
                switch(c){
                    case'+':
                        printf("Vvedite pervoe chislo:\n");
                        scanf("%f", &a);
                        printf("\nVvedite vtoroe chislo:\n");
                        scanf("%f", &b);
                        printf("Result: %.2f + %.2f = %.2lf \n", a, b, a+b);
                        break;
                    case'-':
                        printf("Vvedite pervoe chislo:\n");
                        scanf("%f", &a);
                        printf("\nVvedite vtoroe chislo:\n");
                        scanf("%f", &b);
                        printf("Result: %.2f - %.2f = %.2lf", a, b, a-b);
                        break;
                    case'*':
                        printf("Vvedite pervoe chislo:\n");
                        scanf("%f", &a);
                        printf("\nVvedite vtoroe chislo:\n");
                        scanf("%f", &b);
                        printf("Result: %.2f * %.2f = %.2lf", a, b, a*b);
                        break;
                    case'/':
                        printf("Vvedite pervoe chislo:\n");
                        scanf("%f", &a);
                        printf("\nVvedite vtoroe chislo:\n");
                        scanf("%f", &b);
                        if(b == 0){
                            printf("Na 0 delit nelzya...\n");
                        } else {
                            printf("Result: %.2f / %.2f = %.2lf", a, b, a/b);
                        }
                        break;
                    case'!':
                        printf("Vvedite naturalnoe chislo:\n");
                        scanf("%d", &d);
                        if(d<0){
                            printf("Ozhidalos naturalnoe chislo\n");
                        } else if (d==0){
                            printf("!0 = 1");
                        } else if(d>0){
                            // Классический способ получения факториала, который использовали в заданиях до этого
                            for(int i = 1; i<=d; i++){
                                fact = fact * i;
                            }
                            printf("!%d = %lu\n ", d, fact);
                        }
                            break;
                        case'^':
                            printf("Vvedite osnovanie:\n");
                            scanf("%lf", &e);
                            printf("\nVvedite pokazatel stepeni:\n");
                            scanf("%lf", &f);
                            printf("%.2lf ^ %.2lf = %.2lf\n", e, f, pow(e,f));
                            break;
                    default:
                        printf("Neizvestnoe deystvie... Ya ne budu rabotat\n");
                }
                break;
        }
        printf("\nProdolzhaem? (y/n)");
        scanf(" %c", &r);
    } while(r=='y');
    return 0;
}
