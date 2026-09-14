#include <stdio.h>

#define SIZE 256

int stack[SIZE];

int *sp = &stack[-1];

#define STACK_FULL()  (((sp-stack) + 1) >= SIZE)    // полный стек
#define STACK_EMPTY()  (((sp-stack) + 1) == 0)    // пустой стек
 
#define PUSH(n) (*++sp = (n))   // добавляем в стек
#define POP() (*sp--)       // получаем значение из стека


void operate(char c)
{ 
	// вычисляем два верхних значения на стеке st    
	double arg1=POP();
	double arg2=POP();    
	
	if (c=='+') 
		PUSH(arg2+arg1);    
	else if (c=='-') 
		PUSH(arg2-arg1);    
	else if (c=='*') 
		PUSH(arg2*arg1);    
	else if (c=='/') 
		PUSH(arg2/arg1); 
}

int main(int argc, char **argv)
{
	double number;
	char c;
	
	
	while ((c = getchar()) != EOF)
	{
    if (c == ' ' || c == '\n' || c == '\t')
        continue;

    if (c == '.')
        break;

    if (c >= '0' && c <= '9')
    {
        ungetc(c, stdin);
        scanf("%lf", &number);
        PUSH(number);
    }
    else
    {
        operate(c);
    }
	}
	printf("%d",POP());
	
	// 1)  взять очередной элемент
	
	// 2) если это не знак операции, добавить его в стек;
	
	// 3) если это знак операции, то
	//     *взять из стека два операнда
	//     *выполнить операция и записать результат в стек
	
	// 4) перейти к шагу 1

    return 0;
}


