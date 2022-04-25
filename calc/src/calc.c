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
	setlocale(LC_ALL,"Russian");


    float a,b; // Для стандартных действий

    double e,f; // Для использования в функции pow при возведении в степень, так как там требуется тип double для входящих параметров

    int d; // Для вычисления факториала
    unsigned long int fact;

    char c,r; // Тип char для выбора действия и продолжения вычислений
    // Учитывая, что у нас есть действие по вычислению факториала, нужно сначала запрашивать действие - потом уже запрашивать числа
    // При этом, будем пользоваться функцией pow из math для возведения в степень, дабы учесть возможность использовать вещественные числа
    do{
        fact = 1;
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
        printf("\nProdolzhaem? (y/n)");
        scanf(" %c", &r);
    } while(r=='y');
    return 0;
}
