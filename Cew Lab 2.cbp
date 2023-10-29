QS.01:
#include <stdio.h>

FOR LOOP:
int main(){
    int n,i=1, sum = 0;

    printf("Enter the value of n: ");
    scanf("%d", &n);

    printf("First %d odd natural numbers: ", n);

    for (int j=1; j<= n; j++) {
        printf("%d ", i);
        sum += i;
        i += 2;
    }

    printf("\nSum of the first %d odd natural numbers: %d\n", n, sum);

return 0;
}



WHILE LOOP:
#include <stdio.h>

int main(){
    int n,i=1,j=1, sum = 0;

    printf("Enter the value of n: ");
    scanf("%d", &n);

    printf("First %d odd natural numbers: ", n);

    while (j<=n){
        printf("%d ", i);
        sum += i;
        i += 2;
        j+=1;
    }

    printf("\nSum of the first %d odd natural numbers: %d\n", n, sum);

return 0;
}


DO WHILE LOOP:
#include <stdio.h>

int main(){
    int n,i=1,j=1, sum = 0;

    printf("Enter the value of n: ");
    scanf("%d", &n);

    printf("First %d odd natural numbers: ", n);

    do{
        printf("%d ", i);
        sum += i;
        i += 2;
        j+=1;
    }while (j<=n);

    printf("\nSum of the first %d odd natural numbers: %d\n", n, sum);

return 0;
}

QS.02:
#include <stdio.h>

int main() {
    int rows;

    printf("Enter the number of rows for the pyramid: ");
    scanf("%d", &rows);

    for (int i = 1; i <= rows; i++) {
        // Print spaces for alignment
        for (int j = 1; j <= rows - i; j++) {
            printf(" ");
        }

        // Print asterisks
        for (int j = 1; j <= i; j++) {
            printf("* ");
        }

        printf("\n");
    }

    return 0;
}

QS.03:
#include <stdio.h>

int main() {
    char str1[100], str2[100];
    int i, isEqual = 1;

    printf("Enter the first string: ");
    scanf("%s", str1);

    printf("Enter the second string: ");
    scanf("%s", str2);

    for (i = 0; str1[i] != '\0' || str2[i] != '\0'; i++) {
        if (str1[i] != str2[i]) {
            isEqual = 0;
            break;
        }
    }

    if (isEqual) {
        printf("The strings are equal.\n");
    } else {
        printf("The strings are not equal.\n");
    }

    return 0;
}

QS.04:
#include <stdio.h>

int main(){
   char letter[20];
   printf("Enter a string:");
   scanf("s%",letter);

   int i,length;
   length=strlen(letter);

   for (i=0,i<length,i+=1){
    if(isupper(letter[i])){
         letter[i]=tolower(letter[i]);
    }
    else if(islower(letter[i])){
        letter[i]=toupper(letter[i]));
    }
    printf("The converted string:%s\n",letter[i]);
    }
    return 0
   }

QS.05:

#include <stdio.h>

int main(){
   int letter[]={1,2,4,5,6,7,56,20,80};

   for (int i=0;i<10;i+=1){
    int isunique=1;
    for (int j=0;j<10;j+=1){

         if(i!=j &&letter[i]==letter[j]){
            isunique=0;
            break;

    if (isunique==1){
        printf("%d",&letter[i]);

    }
         }
    }
   }

  return 0
}

QS.06:
#include <stdio.h>

struct Distance {
    int feet;
    float inches;
};

int main() {
    struct Distance distance1, distance2, sum;

    printf("Enter the first distance (feet inches): ");
    scanf("%d %f", &distance1.feet, &distance1.inches);

    printf("Enter the second distance (feet inches): ");
    scanf("%d %f", &distance2.feet, &distance2.inches);

    sum.feet = distance1.feet + distance2.feet;
    sum.inches = distance1.inches + distance2.inches;

    if (sum.inches >= 12.0) {
        sum.inches -= 12.0;
        sum.feet++;
    }

    printf("Sum of distances: %d feet %.2f inches\n", sum.feet, sum.inches);

    return 0;
}
