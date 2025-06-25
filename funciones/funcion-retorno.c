#include <stdio.h>

int suma(int num1, int num2)
{
   int suma = num1 + num2;
   return suma;
}
main()
{
   int num1, num2;
   printf("Ingresa el primer valor:\n");
   scanf("%i", &num1);
   printf("Ingresa el segundo valor:\n");
   scanf("%i", &num2);

   printf("%i + %i = %i\n", num1, num2, suma(num1, num2));
}

