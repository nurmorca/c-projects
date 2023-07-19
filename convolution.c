/*convolutes mxn matrix with an kxk filter, all variables entered by user. [k < m,n and also k%2 != 0]. */

#include <stdio.h>
#define max 50

int main() {


    int matris[max][max],filtre[max][max],n,m;
    int i,j;

    do{
        printf("m sayisi: "); scanf("%d",&m);
        printf("n sayisi: "); scanf("%d",&n);
    } while(m>=50 || n>=50);

    printf("matris:\n");
    for(i=0;i<m;i++) {
        for(j=0;j<n;j++) {
            printf("[%d][%d]:",i+1,j+1); scanf("%d",&matris[i][j]);
        }
    }

    int k;
    int filtreToplam=0;
    do{
        printf("k sayisi: "); scanf("%d",&k);
    }while(k>=50);

    printf("filtre:\n");
    for(i=0;i<k;i++) {
        for(j=0;j<k;j++) {
            printf("[%d][%d]: ",i+1,j+1); scanf("%d",&filtre[i][j]);
            filtreToplam+=filtre[i][j];
        }
    }

   int sonuc[max][max];
   int yatay,dikey=0;
   int carpim;

   while(dikey+k<=m){
       yatay=0;
       while(yatay+k<=n){
           carpim=0;
           for(i=0;i<k;i++){
               for(j=0;j<k;j++){
                   carpim+=(matris[dikey+i][yatay+j]*filtre[i][j]);
               }
           }
           carpim/=filtreToplam;
           sonuc[dikey][yatay]=carpim;
           yatay++;
       }
       dikey++;
   }

   for(i=0;i<(m-k+1);i++){
       for(j=0;j<(n-k+1);j++){

           printf("%d  ",sonuc[i][j]);
       }
       printf("\n");
   }



    return 0;
}
