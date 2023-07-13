/* a game coded only using stdio.h library, based on guessing if a word is in the given array. 
string array can be changed. the speaking language used in the game is turkish. */

#include <stdio.h>


int main() {

   char D[6] = {'u','e','l','m','i','k'};

char kelimeler[][6] = {"ilmek","imlek","melik","kule","ilke","ekim","mil","kem","kum","mil","kel","kil","ilk","ile","lim","el","il"};

    int n = 0, run = 1, flag;
    int i, j, puan = 0, count=0;
    int vis2[100] = {0};
    n=sizeof(D); // D dizisinin uzunlugunu n'de sakla.
    while(kelimeler[count][0]!='\0')
    {
    	count++;
	}
	printf("%d",count); // kelimeler dizisinin uzunlugunu count'da sakla.
    char girdi[20];

    while (run) { // oyunun devam edip etmedigini kontrol et.
        int temp = 0;
        int kosum;
        printf("kullanilabilecek harfler: "); // ekrana D dizisini bas.
        for (i = 0; i < n; i++) {
            printf("'%c'\t", D[i]);
        }
        printf("\ncikis icin 0\ngirisiniz: ");
        scanf("%s", girdi); // kullanici girdisini girdi'de sakla.
        while (girdi[temp] != '\0') {
            temp++;  // girdi'nin uzunlugunu temp'de sakla.
        }

        if (girdi[0] == '0') { // kullanici oyundan cikmak istiyorsa puani goruntule ve programi bitir.
            printf("program sonu. puan: %d", puan);
            run = 0;
            flag = 0;
        } else if (temp < 2) // kelime uzunlugunun 2'den buyuk olup olmadigini kontrol et. kucukse yeniden girdi al.
            {
                printf("girilen kelimenin uzunlugu 2'den buyuk olmalidir.\n");
                flag=0;
            } else { flag = 1; } // kullanici oyundan cikmak istemiyorsa girilen kelime icin kontrol dongusune gir


            while (flag) { // sartlar saglandigi surece kontrol dongusunu devam ettir.
            int vis1[50] = {0};

            int control = 0;

            for (i = 0; i < temp; i++) { // girdi'deki harfler ve dizideki harfler birbirine uyusuyor mu kontrol et.
                for (j = 0; j < n; j++) {
                    if (girdi[i] == D[j]) {
                        control++;
                        vis1[j]++;
                    }
                }
            }

            kosum=1;
             for(i=0;i<n;i++) // ayni harften 2 tane var mi diye kontrol et.
             {
                 if(vis1[i]>=2)
                 {
                     kosum=0;
                 }
             }

             if(kosum==0 && control==temp) // ayni harften iki tane varsa ekrana yazdir.
             {
                 printf("hatali giris. ");
                 control+=10;
             }

            if (control != temp) { // girdi'deki harfler ve dizideki harfler uyusmuyorsa puani guncelle, kontrol dongusunden cik.
                puan -= temp;
                printf("puaniniz: %d\n", puan);
                flag = 0;
            } else { // girdideki harf sayilari uyusuyorsa kelimeler dizisinde girdi'nin varligini arastir.
                i = 0;
                kosum=1;
                while(i < count && kosum) {
                    j=0;
                    while(kelimeler[i][j] != '\0') // kelimeler dizisindeki kelimelerin uzunlugunu bul.
                    {
                        j++;
                    }
                    if(j == temp) {
                        // kelime[i]'nin uzunlugu girdi ile ayni mi diye kontrol et.
                        control = 0;
                        for(j = 0; j < temp; j++)
                        {
                            if(girdi[j] == kelimeler[i][j]) // ayniysa kelime[i] ve girdi ayni kelime mi diye kontrol et
                            {
                                control++;
                            }
                        }
                        if(control == temp) {
                            vis2[i]++; // kelime[i] ve girdi ayniysa kelimenin visited degerini 1 arttir.
                            if(vis2[i] == 1) { // kelime ilk defa girilmisse puan ver, round'i sonlandir.
                                puan += temp;
                                printf("dogru giris. puan: %d\n",puan);
                                kosum = 0;
                            } else { // kelime ikinci defa girildiyse puan kir, round'i sonlandir.
                                puan -= temp;
                                kosum = 0;
                                printf("onceden giris yapilmis kelime. puan: %d\n",puan);
                            }
                        }
                    }
                    i++;
                }
                if(i == count && kosum == 1) // kelime listede bulunamadiysa puan kir, round'i sonlandir.
                {
                    puan -= temp;
                    printf("girdi listede yok. puan: %d\n",puan);
                }
                flag = 0;
            }
        }
    }
    return 0;
}
