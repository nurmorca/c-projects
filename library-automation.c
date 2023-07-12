/* a library automation that basically handles most of the operations at a library
such as adding/deleting books, writers, students; keeping records of students borrowing/returning books etc. also  reads/writes these infos
to separate files. the speaking language used in the automation is turkish.
coded roughly in one week. */ 


#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Ogrenci {
    char ogrID[9];
    char ad[30];
    char soyad[30];
    int puan;
    struct Ogrenci *next;
    struct Ogrenci *prev;
}OGRENCI;

typedef struct Yazar {
    int  yazarID;
    char yazarAd[30];
    char yazarSoyad[30];
    struct Yazar *next;
}YAZAR;

typedef struct KitapOrnek {
    char etiketNo[20];
    char durum[9];
    struct KitapOrnek *next;
} KITAPORNEK;

typedef struct Kitap {
    char kitapAdi[30];
    char ISBN[13];
    int kitapSayisi;
    struct Kitap *next;
    struct KitapOrnek *head;
}KITAP;

typedef struct kitapYazar{
    char ISBN[13];
    int yazarID;
    struct kitapYazar *next;
}KITAPYAZAR;

typedef struct Tarih{
   unsigned int gun:5;
   unsigned int ay:4;
   unsigned int yil:12;
}TARIH;

typedef struct kitapOdunc{
    char etiketNo[20];
    char ogrID[9];
    unsigned int islemTipi:1;
    struct Tarih islemTarihi;
    struct kitapOdunc *next;
}KITAPODUNC;

// fonksiyonlar

void ogrenciDosyaOku(OGRENCI **head, OGRENCI **tail);
void ogrenciDosyaYaz(OGRENCI *head);
int ogrenciEkle(OGRENCI **head,OGRENCI **tail);
int ogrenciSil(OGRENCI **head, OGRENCI **tail);
int ogrenciGuncelle(OGRENCI **head);
void ogrenciListele(OGRENCI *head);
void ogrenciGoruntule(OGRENCI *head);
void cezaliListele(OGRENCI *head);
OGRENCI* ogrenciAra(OGRENCI *head, char *a);

KITAP* kitapISBNAra(KITAP *head, char *a);
void kitapDosyaOku(KITAP **head);
void kitapDosyaYaz(KITAP *head);
int kitapEkle(KITAP **kitapHead);
int kitapSil(KITAP **head);
int kitapGuncelle(KITAP **head);
void kitapGoruntule(KITAP *head, char *data, KITAP* (*fptr)(KITAP*,char *));
void raftakileriListele(KITAP* kitapHead);
KITAP* kitapAdiAra(KITAP *kitapHead, char *a);

void yazarDosyaOku(YAZAR** head);
void yazarDosyaYaz(YAZAR **head);
int yazarEkle(YAZAR** head);
int yazarSil(YAZAR** head, KITAPYAZAR *kitapYazarHead);
int yazarGuncelle(YAZAR **head);
void yazarGoruntule(YAZAR* head, KITAPYAZAR* kyHead, KITAP* kHead);
YAZAR* yazarAra(YAZAR* tmp, char* a);

int kitapYazarEslestir(KITAPYAZAR** head, KITAP* kitapHead, YAZAR* yazarHead);
void kitapYazarSil(KITAPYAZAR* head, int data);
void kitapYazarDosyaOku(KITAPYAZAR** head);
void kitapYazarDosyaYaz(KITAPYAZAR *head);
int kitapYazarGuncelle(KITAPYAZAR **kHead,YAZAR* yHead);

void kitapOduncDosyaOku(KITAPODUNC** head,KITAP** kHead);
void kitapOduncDosyaYaz(KITAPODUNC *head);
int kitapOduncTeslim(KITAPODUNC** kOHead, KITAP* kHead, OGRENCI** oHead);
KITAPODUNC* kitapOduncAra(KITAPODUNC* head, char *data1, char *data2);
int cezaDurumu(KITAPODUNC *data1, TARIH *data2);
void teslimsizListele(KITAP* head,OGRENCI *oHead);
void zamanListele(KITAPODUNC* kOHead,KITAP* kHead);

int main() {
      int run = 1, opt;
      OGRENCI *ogrenciHead=NULL;
      OGRENCI *tail=NULL;
      KITAP *kitapHead=NULL;
      YAZAR *yazarHead=NULL;
      KITAPYAZAR* kitapYazarHead=NULL;
      KITAPODUNC* kitapOduncHead=NULL;
      int res;

    ogrenciDosyaOku(&ogrenciHead,&tail);
    kitapDosyaOku(&kitapHead);
    yazarDosyaOku(&yazarHead);
    kitapYazarDosyaOku(&kitapYazarHead);
    kitapOduncDosyaOku(&kitapOduncHead,&kitapHead);

    while(run)
      {
          printf("OGRENCI ISLEMLERI\n"
                 "1-Ogrenci Ekle/Sil/Guncelle\n"
                 "2-Ogrenci Bilgisi Goruntule\n"
                 "3-Kitap Teslim Etmemis Ogrencileri Listele\n"
                 "4-Cezali Ogrencileri Listele\n"
                 "5-Tum ogrencileri Listele\n"
                 "6- Kitap Odunc Al/Teslim Et\n\n"
                 "KITAP ISLEMLERI\n"
                 "7- Kitap Ekle/Sil/Guncelle\n"
                 "8 Kitap Bilgisi Goruntuleme\n"
                 "9- Raftaki Kitaplari Listele\n"
                 "10- Zamaninda Teslim Edilmeyen Kitaplari Listele\n"
                 "11- Kitap-Yazar Eslestir\n"
                 "12- Kitabin Yazarini Guncelle\n\n"
                 "YAZAR ISLEMLERI\n"
                 "13- Yazar /Ekle/Sil/Guncelle\n"
                 "14- Yazar Bilgisi Goruntuleme\n\n"
                 "15-CIKIS\n\n");
          printf("Secim: "); scanf("%d",&opt);

          switch(opt)
          {
              case 1:  
            
                  printf("Yapilacak islem:\n1-Ekleme\n2-Cikarma\n3-Guncelleme\n");
                  printf("Giris:"); scanf("%d",&opt);
                  if(opt==1) // ogrenci ekleme
                  {
                      res=ogrenciEkle(&ogrenciHead,&tail);
                      if(res==0)
                      {
                          printf("\nIslem basariyla gerceklestirildi.\n");
                      }

                  } else if(opt==2) // ogrenci silme
                  {
                      res=ogrenciSil(&ogrenciHead, &tail);
                      if(res==0)
                      {
                          printf("\nIslem basariyla gerceklestirildi.\n");
                      }
                  } else{
                      res=ogrenciGuncelle(&ogrenciHead); // ogrenci guncelleme
                      if(res==0)
                      {
                          printf("\nIslem basariyla gerceklestirildi.\n");
                      }

                  }
                  break;
              case 2:
                     ogrenciGoruntule(ogrenciHead);
                  break;
              case 3:
                      teslimsizListele(kitapHead, ogrenciHead);
                  break;
              case 4: cezaliListele(ogrenciHead);
                  break;
              case 5:
                  printf("\n");
                  printf("\n\n---Ogrenci Listesi--\n\n");
                  ogrenciListele(ogrenciHead); // ogrenci listelenmesi
                  printf("\n\n");
                  break;
              case 6:
                  res=kitapOduncTeslim(&kitapOduncHead,kitapHead,&ogrenciHead);
                  if(res==0){
                      printf("\nIslem basariyla gerceklestirildi.\n");
                  }
                  break;
              case 7:
                  printf("Yapilacak islem:\n1-Ekleme\n2-Cikarma\n3-Guncelleme\n");
                  printf("Giris:"); scanf("%d",&opt);
                  if(opt==1) //kitap ekleme
                  {
                      res=kitapEkle(&kitapHead);
                      if(res==0)
                      {
                          printf("\nIslem basariyla gerceklestirildi.\n");
                      }
                  }
                  else if(opt==2) //kitap silme
                  {
                      res=kitapSil(&kitapHead);
                      if(res==0)
                      {
                          printf("\nIslem basariyla gerceklestirildi.\n");
                      }
                  } else{
                      res=kitapGuncelle(&kitapHead); //kitap guncelleme
                      if(res==0)
                      {
                          printf("\nIslem basariyla gerceklestirildi.\n");
                      }

                  }
                  break;
              case 8:
                  printf("\n1-Isme gore arama\n2-ISBN'e gore arama\nSecim: "); scanf("%d",&opt);
                  char tmp;
                  scanf("%c",&tmp);
                  char bilgi[60];
                  printf("\nBilgi giriniz: "); gets(bilgi);
                  if(opt==1){

                      kitapGoruntule(kitapHead,bilgi,kitapAdiAra);
                  } else if(opt==2){
                      kitapGoruntule(kitapHead,bilgi,kitapISBNAra);
                  }

                  break;
              case 9:
                  raftakileriListele(kitapHead);
                  break;
              case 10:
                  zamanListele(kitapOduncHead,kitapHead);
                  break;
              case 11:
                  res=kitapYazarEslestir(&kitapYazarHead,kitapHead,yazarHead);
                  if(res==0){
                      printf("\nIslem basariyla gerceklestirildi.\n");
                  }
                  break;
              case 12:
                  res=kitapYazarGuncelle(&kitapYazarHead,yazarHead);
                  if(res==0){
                      printf("\nIslem basariyla gerceklestirildi.\n");
                  }
                  break;
              case 13:
                  printf("Yapilacak islem:\n1-Ekleme\n2-Cikarma\n3-Guncelleme\n");
                  printf("Giris:"); scanf("%d",&opt);
                  if(opt==1) // yazar ekleme
                  {
                      res=yazarEkle(&yazarHead);
                      if(res==0)
                      {
                          printf("\nIslem basariyla gerceklestirildi.\n");
                      }

                  } else if(opt==2) // ogrenci silme
                  {
                      res=yazarSil(&yazarHead,kitapYazarHead);
                      if(res==0)
                      {
                          printf("\nIslem basariyla gerceklestirildi.\n");
                      }
                  } else if(opt==3){
                      res=yazarGuncelle(&yazarHead); // ogrenci guncelleme
                      if(res==0)
                      {
                       printf("\nIslem basariyla gerceklestirildi.\n");
                      }
                  }
                  yazarDosyaYaz(&yazarHead);
                  break;
              case 14:
                  yazarGoruntule(yazarHead,kitapYazarHead,kitapHead);
                  break;
              case 15:
                  printf("Program sonu.\n");
                  OGRENCI *sil1;
                  while(ogrenciHead!=NULL) {
                      sil1=ogrenciHead;
                      ogrenciHead=ogrenciHead->next;
                      free(sil1);
                  }
                  YAZAR *sil2;
                  while(yazarHead!=NULL){
                      sil2=yazarHead;
                      yazarHead=yazarHead->next;
                      free(sil2);
                  }
                  KITAPODUNC *sil3;
                  while(kitapOduncHead!=NULL){
                      sil3=kitapOduncHead;
                      kitapOduncHead=kitapOduncHead->next;
                      free(sil3);
                  }
                  KITAPYAZAR *sil4;
                  while(kitapYazarHead!=NULL){
                      sil4=kitapYazarHead;
                      kitapYazarHead=kitapYazarHead->next;
                      free(sil4);
                  }

                  KITAP* sil5;
                  while(kitapHead!=NULL){
                      sil5=kitapHead;
                      KITAPORNEK* sil6;
                      while(kitapHead->head!=NULL){
                          sil6=kitapHead->head;
                          kitapHead->head=kitapHead->head->next;
                          free(sil6);
                      }
                      kitapHead=kitapHead->next;
                      free(sil5);
                  }
                  run=0;
                  break;
              default:
                  printf("Yeniden giris yapiniz.\n\n");

          }
      }

    return 0;
}

// fonksiyon tanimlama
void ogrenciListele(OGRENCI *head){
    OGRENCI *tmp = head;
    while(tmp != NULL){ //tmp NULL olmayana dek id,ad,soyad ve puan bilgilerini ekrana bas.
        printf("%s %s %s %d\n",tmp->ogrID,tmp->ad,tmp->soyad,tmp->puan);
        tmp = tmp->next; // tmp'yi guncelle.
    }
}

OGRENCI* ogrenciAra(OGRENCI *head, char *a)
{
    OGRENCI *index=head;
    while(index!=NULL){
        if(strcmp(index->ogrID,a)==0){ // girilen id linkli listede var mi diye arastir.
            return index; // varsa o node'u dondur.
        }
        index=index->next;
    }
    return NULL; // yoksa null dondur.
}

int ogrenciEkle(OGRENCI **head,OGRENCI **tail) {
    OGRENCI *isFound;
    int control = 1;
    int flag = 1;
    char ad[30];
    char tmp;
    OGRENCI *temp = (OGRENCI *) malloc(sizeof(OGRENCI)); // yeni node olustur.
    if (temp == NULL) { // alan ayrildi mi diye kontrol et.
        printf("Bellek ayrilamadi.");
        return -1;
    }
    while (control) { // girilecek id daha once girilmis mi diye kontrol dongusu baslat.
        printf("\nOgrenci numarasini giriniz: ");
        scanf("%s", temp->ogrID);
        isFound=ogrenciAra(*head,temp->ogrID); // linkli listede id'yi ara.
        if(isFound!=NULL) // arama sonucu NULL gelmezse, id listede bulunmustur.
        {
            printf("\nAyni numarada ogrenci bulunmaktadir. ");
            flag=0; //id listede zaten varsa kontrol dongusunu devam ettirmek icin flag degiskenini 0'la.
        }
        if (flag == 1) { // id listede yoksa ve flag=1 ise donguyu sonlandir.
            control = 0;
        }
       flag=1; // flag 0'lanmissa dongu yeniden doneceginden saglikli calismasi icin flag=1 yap.
    }

    scanf("%c",&tmp);
    printf("\nOgrencinin adini giriniz:");
    gets(ad);
    strcpy(temp->ad,ad);
    printf("Ogrencinin soyadini giriniz: ");
    scanf("%s", temp->soyad);
    printf("Ogrencinin puani 100 olarak atanmistir.\n");
    temp->puan = 100;

    (*tail)->next = temp; // node'u linkli listeye ekle.
    temp->prev = (*tail);
    *tail = temp;
    (*tail)->next = NULL;
    ogrenciDosyaYaz(*head); // yeni ogrenciyi dosyaya yaz.
    return 0;
}

    int ogrenciSil(OGRENCI **head, OGRENCI **tail) {
        OGRENCI *isFound;
        char data[9];
        int control=1,flag=1;

        while (control) { // girilecek id listede var mi diye kontrol dongusu baslat.
            printf("Silinecek ogrencinin ID'sini giriniz: ");
            scanf("%s", data);
            isFound=ogrenciAra(*head,data); // girilen id'ye sahip ogrenci var mi diye kontrol et.
            if(isFound==NULL) {
                printf("\nGirilen ID'ye sahip bir ogrenci bulunamadi."); //yoksa yeni numara istemek icin flag=0 yap.
                flag=0;
            }
            if (flag == 1) { // id listede varsa ve flag=1 ise donguyu sonlandir.
                control = 0;
            }
            flag=1; // flag 0'lanmissa dongu yeniden doneceginden saglikli calismasi icin flag=1 yap.
        }

            if(isFound==(*tail))  // bulunan deger tail ise asagidaki sekilde sil.
            {
                OGRENCI *prev;

                prev=isFound->prev;
                prev->next=NULL;
                (*tail)=prev;
            } else { // ortadan bir degerse asagidaki sekilse sil.

                OGRENCI *prev;
                OGRENCI *next;

                prev = isFound->prev;
                prev->next = isFound->next;
                next = isFound->next;
                next->prev = prev;
            }
            free(isFound);
            ogrenciDosyaYaz(*head); // dosyayi guncelle.
        return 0;
    }


int ogrenciGuncelle(OGRENCI **head)
{
    OGRENCI *index;
    int secim;
    char data[9];

    printf("Guncellenecek ogrencinin numarasini giriniz: "); scanf("%s",data);
    index=ogrenciAra(*head,data);
    if(index==NULL)
    {
        printf("Girilen ID'ye sahip bir ogrenci bulunamadi.");
        return 1;
    }

    printf("Guncellenecek bilgiyi giriniz:\n"
           "1-Ad\n"
           "2-Soyad\n"
           "3-Puan\n"
           "Girisiniz: "); scanf("%d",&secim);

           if(secim==1)
           {
               printf("Ad:"); scanf("%s",index->ad);
           } else if(secim==2)
           {
               printf("Soyad: "); scanf("%s",index->soyad);
           } else{
               printf("Puan: "); scanf("%d",&index->puan);
           }

    ogrenciDosyaYaz(*head);
           return 0;
}

void ogrenciGoruntule(OGRENCI *head)
{
     char data[59];
     int secim;
     OGRENCI *index;
     int flag=1;

     printf("\nGireceginiz bilgi turunu seciniz:"
            "\n1-ID "
            "\n2-Ad Soyad "
            "\nSecim: "); scanf("%d",&secim);

            if(secim==1) {
                printf("ID giriniz: "); scanf("%s",data);
                index=ogrenciAra(head,data);
                if(index==NULL)
                {
                    printf("\nGirilen ID'ye sahip bir ogrenci bulunamamistir.\n");
                    return;
                }
            } else {
                char ad[30];
                char soyad[30];
                index=head;
                printf("\nAd: "); scanf("%s",ad);
                printf("Soyad: "); scanf("%s",soyad);
                while(index!=NULL && flag)
                {
                    if(strcmp(strupr(ad),strupr(index->ad))==0 && strcmp(strupr(index->soyad),strupr(soyad))==0)
                    {
                        flag=0;
                    }
                    index=index->next;
                }
                if(index==NULL)
                {
                    printf("\nGirilen ad soyad bilgisine sahip ogrenci bulunamamistir.\n");
                    return;
                }
                index=index->prev;
            }
            printf("\nAd: %s"
           "\nSoyad: %s"
           "\nID: %s"
           "\nPuan: %d\n",index->ad,index->soyad,index->ogrID,index->puan);
}

void cezaliListele(OGRENCI *head){

    OGRENCI *index=head;
    printf("\n----Cezali Ogrenciler----\n");
    while(index!=NULL){
        if(index->puan<0){
            printf("Ad: %s Soyad: %s Puan: %d\n",index->ad,index->soyad,index->puan);
        }
        index=index->next;
    }
}

void ogrenciDosyaOku(OGRENCI **head, OGRENCI **tail)
{

    FILE *ogrenci;
    int read=0;

    ogrenci=fopen("C:\\Users\\nur\\OneDrive\\Desktop\\Ogrenciler.csv","r"); // ACILACAK DOSYANIN ADRESI.
    if(ogrenci==NULL) // dosya acilamadiysa hata ver.
    {
        printf("Dosya acma hatasi.\n");
    }

    do{
        OGRENCI *yeni=(OGRENCI*)malloc(sizeof(OGRENCI)); // yeni dugum olustur.
        if(yeni==NULL) // alan ayrilamadiysa hata ver.
        {
            printf("Bellek ayrilamadi.\n");
        }
        read = fscanf(ogrenci,"%8[^,],%29[^,],%29[^,],%d\n", // belgeden bilgileri oku.
                      yeni->ogrID,
                      yeni->ad,
                      yeni->soyad,
                      &yeni->puan);
        if(read!=4 && !feof(ogrenci)) // okuma yapilamadiysa hatayi belirt, programdan cik.
        {
            printf("Format hatasi.\n");
            return;
        }
        if(ferror(ogrenci)) // dosya okuma hatasi varsa belirt.
        {
            printf("Dosya okuma hatasi.\n");
        }
        if(*head==NULL) // head bos ise yeni node'u head'e ata.
        {
            yeni->next=NULL;
            yeni->prev=NULL;
            (*head)=(*tail)=yeni;
        } else{ // head bos degilse yeni node'u tail'e gore ekle.
            (*tail)->next=yeni;
            yeni->prev=(*tail);
            (*tail)=yeni;
            (*tail)->next=NULL; // bilgisayarda yeni tail'in next adresi erisilemeyen bir adrese isaret ettigi icin hata verdigi icin NULL'la.
        }

    } while(!feof(ogrenci)); // donguyu dosyanin sonuna gelene kadar devam ettir

}

void ogrenciDosyaYaz(OGRENCI *head){

    OGRENCI *index;
    FILE *ogrenci;

    index=head;

    ogrenci=fopen("C:\\Users\\nur\\OneDrive\\Desktop\\Ogrenciler.csv","w"); // ACILACAK DOSYANIN ADRESI.
    if(index==NULL) // dosya acilamadiysa hata ver.
    {
        printf("Dosya acma hatasi.\n");
    }

    while(index!=NULL)
    {
        fprintf(ogrenci,"%s,%s,%s,%d",
                index->ogrID,
                index->ad,
                index->soyad,
                index->puan);
        index=index->next;
        if(index!=NULL){
            fprintf(ogrenci,"\n");
        }
    }
    fclose(ogrenci);
}

void kitapDosyaYaz(KITAP *head){
    KITAP* index;
    FILE* kitap;

    index=head;
    kitap=fopen("C:\\Users\\nur\\OneDrive\\Desktop\\Kitaplar.csv","w");
    if(kitap==NULL){
        printf("\nDosya acma hatasi.");
    }

    while(index!=NULL)
    {
        fprintf(kitap,"%s,%s,%d",index->kitapAdi,index->ISBN,index->kitapSayisi);
        index=index->next;
        if(index!=NULL)
        {
            fprintf(kitap,"\n");
        }
    }
    fclose(kitap);
}

void kitapDosyaOku(KITAP **kitapHead){

    FILE *kitap;
    int read=0;

    kitap=fopen("C:\\Users\\nur\\OneDrive\\Desktop\\Kitaplar.csv","r"); // ACILACAK DOSYANIN ADRESI.
    if(kitap==NULL) // dosya acilamadiysa hata ver.
    {
        printf("Dosya acma hatasi.\n");
    }

    do{
        KITAP *yeni=(KITAP *)malloc(sizeof(KITAP)); // yeni dugum olustur.

        if(yeni==NULL) // alan ayrilamadiysa hata ver.
        {
            printf("Bellek ayrilamadi.\n");
        }
        read = fscanf(kitap,"%[^,],%[^,],%d\n", // belgeden bilgileri oku.
                      yeni->kitapAdi,
                      yeni->ISBN,
                      &yeni->kitapSayisi);
        if(read!=3 && !feof(kitap)) // okuma yapilamadiysa hatayi belirt, programdan cik.
        {
            printf("Format hatasi.\n");
            return;
        }
        if(ferror(kitap)) // dosya okuma hatasi varsa belirt.
        {
            printf("Dosya okuma hatasi.\n");
        }
        int i;
        yeni->head=NULL;
        for(i=1;i<=(yeni->kitapSayisi);i++){
            KITAPORNEK *ornek=(KITAPORNEK*)malloc(sizeof(KITAPORNEK));
            char sayi[3];
            char durum[8]="Rafta";
            sprintf(sayi, "_%d",i);
            strcpy(ornek->etiketNo,yeni->ISBN);
            strcat(ornek->etiketNo,sayi);
            strcpy(ornek->durum,durum);
            if(yeni->head==NULL){
            yeni->head=ornek;
            ornek->next=NULL;
            }else{
                ornek->next=yeni->head;
                yeni->head=ornek;
            }
        }

        if(*kitapHead==NULL) // head bos ise yeni node'u head'e ata.
        {
            (*kitapHead)=yeni;
            (*kitapHead)->next=NULL;
        } else{ // head bos degilse yeni node'u tail'e gore ekle.
            yeni->next=(*kitapHead);
            (*kitapHead)=yeni;
		// bilgisayarda yeni head'in next adresi erisilemeyen bir adrese isaret ettigi icin hata verdigi icin NULL'ladim.
        }

    } while(!feof(kitap)); // donguyu dosyanin sonuna gelene kadar devam ettir.

    fclose(kitap);
}

int kitapEkle(KITAP **kitapHead) {

    char ad[60];
    char tmp;
    KITAP *yeni=(KITAP *)malloc(sizeof(KITAP)); // yeni dugum olustur.
    KITAP *isFound;
    int control=1,flag=1;
    if(yeni==NULL) // alan ayrilamadiysa hata ver.
    {
        printf("Bellek ayrilamadi.\n");
        return 1;
    }

    while (control) {
        if(flag==0)
        {
            flag=1;
        }
         printf("\nKitabin ISBN numarasini giriniz: "); scanf("%s",yeni->ISBN); scanf("%c",&tmp);
           isFound=kitapISBNAra(*kitapHead,yeni->ISBN);
           if(isFound!=NULL) {
              printf("\nAyni ISBN numarasina sahip bir kitap bulunmaktadir.\n");
              flag=0;
           }
        if (flag == 1) {
            control = 0;
        }
    }
    
    printf("Kitabin adini giriniz: "); gets(ad);
    strcpy(yeni->kitapAdi,ad);
    printf("Kitap sayisini giriniz: "); scanf("%d",&yeni->kitapSayisi);
    int i;
    yeni->head=NULL;
    for(i=1;i<=(yeni->kitapSayisi);i++){
        KITAPORNEK *ornek=(KITAPORNEK*)malloc(sizeof(KITAPORNEK));
        char sayi[3];
        char durum[8]="Rafta";
        sprintf(sayi, "_%d",i);
        strcpy(ornek->etiketNo,yeni->ISBN);
        strcat(ornek->etiketNo,sayi);
        strcpy(ornek->durum,durum);
        if(yeni->head==NULL){
            yeni->head=ornek;
            ornek->next=NULL;
        }else{
            ornek->next=yeni->head;
            yeni->head=ornek;
        }
    }

    if(*kitapHead==NULL) // head bos ise yeni node'u head'e ata.
    {
        yeni->next=NULL;
        (*kitapHead)=yeni;
    } else{ // head bos degilse yeni node'u tail'e gore ekle.
        yeni->next=(*kitapHead);
        (*kitapHead)=yeni;// bilgisayarda yeni head'in next adresi erisilemeyen bir adrese isaret ettigi icin hata verdigi icin NULL'ladim.
    }
    kitapDosyaYaz(*kitapHead);
    return 0;
}

int kitapSil(KITAP **head) {
    KITAP *isFound;
    char data[13];

    printf("Silinecek kitabin ISBN'ini giriniz: ");
    scanf("%s", data);
    isFound=kitapISBNAra(*head,data);
    if(isFound==NULL) {
        printf("\nGirilen ISBN'e sahip bir kitap bulunamadi.");
        return 1;

    }

        KITAPORNEK* sil=isFound->head;
        while(isFound->head!=NULL) {
            free(sil);
            isFound->head=isFound->head->next;
            sil=isFound->head;
        }

        KITAP *prev=*head;
        int found=0;
        while(prev!=NULL && !found)
        {
            if(prev->next!=isFound){
                prev=prev->next;
            } else
            {
                found=1;
            }
        }
        if(prev==NULL){
            *head=isFound->next;
        }else{
            prev->next=isFound->next;
        }
        free(isFound);

    kitapDosyaYaz(*head);
    return 0;

    }

int kitapGuncelle(KITAP **head) {
    KITAP *isFound;
    char data[13];

    printf("Guncellenecek kitabin ISBN'ini giriniz: ");
    scanf("%s", data);
    isFound=kitapISBNAra(*head,data);
    if(isFound==NULL)
    {
        printf("\nGirilen ISBN'e sahip bir kitap bulunamadi.");
        return 1;

    }
    int secim;
    char temp;
    printf("\nYapilacak islemi giriniz:\n"
           "1-Isim Guncelleme\n"
           "2-ISBN Guncelleme\n"
           "3-Adet Sayisi Guncelleme\n"
           "Girisiniz:"); scanf("%d",&secim);
           scanf("%c",&temp);

           if(secim==1) {
               char guncel[30];
               printf("\nYeni ismi giriniz: ");
                gets(guncel);
               strcpy(isFound->kitapAdi,guncel);
               printf("Kitabin yeni adi: %s",isFound->kitapAdi);
           } else if(secim==2) {
               char guncel[13];
               KITAP *index;
               printf("\nYeni ISBN'i giriniz: ");
               gets(guncel);
               index = kitapISBNAra(*head, guncel);
               if (index == NULL) {
                   strcpy(isFound->ISBN, guncel);
                   printf("\nKitabin yeni ISBN'i: %s", isFound->ISBN);
                   int i;
                   KITAPORNEK *ornek;
                   ornek=isFound->head;
                   for(i=1;i<=isFound->kitapSayisi;i++){
                       char sayi[3];
                       sprintf(sayi, "_%d",i);
                       strcpy(ornek->etiketNo,isFound->ISBN);
                       strcat(ornek->etiketNo,sayi);
                       ornek=ornek->next;
                   }

               } else {
                   printf("\nGirilen ISBN'e ait kitap bulunmaktadir.");
               }
           } else {
               int sayi;
               do{
                   printf("\nGirilen kitaptan %d kadar mevcuttur.",isFound->kitapSayisi);
                   printf("\nSilinecek kitap sayisini giriniz: ");
                   scanf("%d",&sayi);
               }while(sayi>isFound->kitapSayisi);
                   int i;
               for(i=0;i<sayi;i++){
                   KITAPORNEK* sil=isFound->head;
                 isFound->head=isFound->head->next;
                   free(sil);
               }
               isFound->kitapSayisi-=sayi;
           }
    kitapDosyaYaz(*head);

    return 0;
}

KITAP* kitapISBNAra(KITAP *kitapHead, char *a){
    KITAP *index=kitapHead;
    while(index!=NULL){
        if(strcmp(index->ISBN,a)==0){
            return index;
        }
        index=index->next;
    }
    return NULL;
	}

void kitapGoruntule(KITAP *head, char* data, KITAP* (*fptr)(KITAP*,char *)){

    KITAP *isFound;
    isFound=fptr(head,data);
    if(isFound==NULL){
        printf("\nGirilen isimde kitap bulunamamistir.");
        return;
    }else{
        KITAPORNEK *index=isFound->head;
        printf("\nIsim: %s\nISBN: %s\nSayi: %d\n",isFound->kitapAdi,isFound->ISBN,isFound->kitapSayisi);
        while(index!=NULL){
            printf("Ornek: %s\nDurum: %s\n",index->etiketNo,index->durum);
            index=index->next;
        }
    }
}

void raftakileriListele(KITAP* kitapHead){

    KITAP* index=kitapHead;
    KITAPORNEK *index2;
    while(index!=NULL){
        index2=index->head;
      while(index2!=NULL){
          if(strcmp(index2->durum,"Rafta")==0){
              printf("Kitap Adi: %s ISBN: %s\n",index->kitapAdi,index2->etiketNo);
          }
          index2=index2->next;
      }
      index=index->next;
    }


}

KITAP* kitapAdiAra(KITAP *kitapHead, char *a){
    KITAP *index=kitapHead;
    char ad[30];
    while(index!=NULL){
        strcpy(ad,index->kitapAdi);
        if(strcmp(strupr(ad),strupr(a))==0){
            return index;
        }
        index=index->next;
    }
    return NULL;
}

void yazarDosyaOku(YAZAR** head) {

    FILE *yazar;
    int read = 0;
    yazar = fopen("C:\\Users\\nur\\OneDrive\\Desktop\\Yazarlar.csv", "r"); // ACILACAK DOSYANIN ADRESI.
    if (yazar == NULL) // dosya acilamadiysa hata ver.
    {
        printf("Dosya acma hatasi.\n");
    }

    do {
        YAZAR *yeni = (YAZAR *) malloc(sizeof(YAZAR)); // yeni dugum olustur.

        if (yeni == NULL) // alan ayrilamadiysa hata ver.
        {
            printf("Bellek ayrilamadi.\n");
        }
        read = fscanf(yazar, "%d,%[^,],%[^\n]\n", // belgeden bilgileri oku.
                      &yeni->yazarID,
                      yeni->yazarAd,
                      yeni->yazarSoyad);
        if (read != 3 && !feof(yazar)) // okuma yapilamadiysa hatayi belirt, programdan cik.
        {
            printf("Format hatasi.\n");
            return;
        }
        if (ferror(yazar)) // dosya okuma hatasi varsa belirt.
        {
            printf("Dosya okuma hatasi.\n");
        }

        if (*head == NULL) // head bos ise yeni node'u head'e ata.
        {
            yeni->next = NULL;
            (*head) = yeni;
        } else { // head bos degilse yeni node'u tail'e gore ekle.
            yeni->next = (*head);
            (*head) = yeni;
        }
    } while (!feof(yazar));

    fclose(yazar);
}

void yazarDosyaYaz(YAZAR **head){
    YAZAR* index;
    FILE* yazar;

    index=*head;
    yazar=fopen("C:\\Users\\nur\\OneDrive\\Desktop\\Yazarlar.csv","w");
    if(yazar==NULL){
        printf("\nDosya acma hatasi.");
    }

    while(index!=NULL)
    {
        fprintf(yazar,"%d,%s,%s",index->yazarID,index->yazarAd,index->yazarSoyad);
        index=index->next;
        if(index!=NULL)
        {
            fprintf(yazar,"\n");
        }
    }
    fclose(yazar);
}

int yazarEkle(YAZAR** head){

    char tmp;
    int ID;
    ID=(*head)->yazarID;
    ID++;
    scanf("%c",&tmp);
    YAZAR *temp = (YAZAR *) malloc(sizeof(YAZAR)); // yeni node olustur.
    if (temp == NULL) { // alan ayrildi mi diye kontrol et.
        printf("Bellek ayrilamadi.");
        return -1;
    }
        temp->yazarID=ID;

    printf("\nYazar adi giriniz:");
    gets(temp->yazarAd);
    printf("Yazarin soyadini giriniz: ");
    gets(temp->yazarSoyad);

    temp->next=(*head);
    (*head)=temp;

    return 0;
}

int yazarSil(YAZAR** head, KITAPYAZAR* kitapYazarHead) {
    YAZAR *isFound;
    char data[60];
    char tmp;
    int control=1,flag=1;
    scanf("%c",&tmp);

    while (control) { // girilecek id listede var mi diye kontrol dongusu baslat.
        printf("Silinecek yazarin ad ve soyad bilgisini giriniz: ");
        gets(data);
        isFound=yazarAra(*head,data); // girilen id'ye sahip ogrenci var mi diye kontrol et.
        if(isFound==NULL) {
            printf("\nGirilen yazara ait bir kayit bulunamadi."); //yoksa yeni numara istemek icin flag=0 yap.
            flag=0;
        }
        if (flag == 1) { // id listede varsa ve flag=1 ise donguyu sonlandir.
            control = 0;
        }
        flag=1; // flag 0'lanmissa dongu yeniden doneceginden saglikli calismasi icin flag=1 yap.
    }

    kitapYazarSil(kitapYazarHead,isFound->yazarID);

    YAZAR *prev=*head;
    int found=0;
    while(prev!=NULL && !found)
    {
        if(prev->next!=isFound){
            prev=prev->next;
        } else
        {
            found=1;
        }
    }
    if(prev==NULL){
        *head=isFound->next;
    }else{
        prev->next=isFound->next;
    }
    free(isFound);

    return 0;
}


YAZAR* yazarAra(YAZAR* tmp, char* a){
    YAZAR* index=tmp;
    char adSoyad[60];
    while(index!=NULL){
        strcpy(adSoyad,index->yazarAd);
        strcat(adSoyad," ");
        strcat(adSoyad,index->yazarSoyad);
        if(strcmp(strupr(adSoyad), strupr(a))==0){
            return index;
        }
        index=index->next;
    }
    return NULL;
}


int yazarGuncelle(YAZAR **head)
{
    YAZAR *index;
    int secim;
    char data[60];
    char tmp;
    scanf("%c",&tmp);

    printf("Yazar ad ve soyadini giriniz: "); gets(data);
    index=yazarAra(*head,data);
    if(index==NULL)
    {
        printf("Girilen isme sahip bir yazar bulunamadi.");
        return 1;
    }

    printf("Guncellenecek bilgiyi giriniz:\n"
           "1-Ad\n"
           "2-Soyad\n"
           "Yazar ID'si degistirilememektedir." // degis
           "Girisiniz: "); scanf("%d",&secim);

    if(secim==1)
    {
        printf("Ad:"); scanf("%s",index->yazarAd);
    } else
    {
        printf("Soyad: "); scanf("%s",index->yazarSoyad);
    }

    return 0;
}

int kitapYazarEslestir(KITAPYAZAR** head, KITAP* kitapHead, YAZAR* yazarHead){

       KITAP *isFound;
       YAZAR *tmp;
       char isbn[13];
       char adSoyad[60];
       char temp;
       KITAPYAZAR* yeni=(KITAPYAZAR*)malloc(sizeof(KITAPYAZAR));
       if(yeni==NULL){
           printf("\nAlan ayrilamadi.");
           return 1;
       }

       printf("\nISBN giriniz: "); scanf("%s",isbn);
       scanf("%c",&temp);
       isFound=kitapISBNAra(kitapHead,isbn);
       if(isFound==NULL){
           printf("\nGirilen ISBN'e ait bir kitap bulunamamistir.");
           return 1;
       }

    printf("\nYazarin ad ve soyad bilgisini giriniz: "); gets(adSoyad);
       tmp=yazarAra(yazarHead,adSoyad);
       if(tmp==NULL){
           printf("\nGirilen ad soyada sahip bir yazar bulunamamistir.");
           return 1;
       }

       strcpy(yeni->ISBN,isFound->ISBN);
       yeni->yazarID=tmp->yazarID;
       yeni->next=(*head);
       (*head)=yeni;
    kitapYazarDosyaYaz(*head);
     return 0;
}

void kitapYazarSil(KITAPYAZAR* head, int data) {

    KITAPYAZAR *index=head;
    while(index!=NULL){
        if(index->yazarID==data){
            index->yazarID=-1;
        }
        index=index->next;
    }
    kitapYazarDosyaYaz(head);
}

void yazarGoruntule(YAZAR* head, KITAPYAZAR* kyHead, KITAP* kHead){
    YAZAR *isFound;
    char data[60];
    char tmp;
    scanf("%c",&tmp);

    printf("Yazar ad ve soyadini giriniz: "); gets(data);
    isFound=yazarAra(head,data);
    if(isFound==NULL){
        printf("\nGirilen isme sahip bir yazar bulunamamistir.");
        return;
    }
    printf("\nYazar ID: %d",isFound->yazarID);
    printf("\nYazar adi: %s",isFound->yazarAd);
    printf("\nYazar Soyadi: %s",isFound->yazarSoyad);
    printf("\nYazarin kitaplari:");
    KITAPYAZAR *index=kyHead;
    while(index!=NULL){
        if(index->yazarID==isFound->yazarID){
           kitapGoruntule(kHead,index->ISBN,kitapISBNAra);
        }
        index=index->next;
    }

}

int kitapYazarGuncelle(KITAPYAZAR **kHead,YAZAR *yHead){

    char data[60];
    KITAPYAZAR* isFound=*kHead;
    YAZAR* index=yHead,*found;
    int flag=1;
    char tmp;

    printf("\nYazari guncellenecek kitabin ISBN'inini giriniz: "); scanf("%s",data);
    scanf("%c",&tmp);

    while(isFound!=NULL){
        if(strcmp(isFound->ISBN,data)==0){
           while(index!=NULL && flag){
               if(isFound->yazarID==index->yazarID){
                   printf("\nKitabin su an kayitli olan yazari: %s %s",index->yazarAd,index->yazarSoyad);
                   printf("\nYeni yazarin ismini giriniz: "); gets(data);
                   found=yazarAra(yHead,data);
                   if(found==NULL){
                       printf("Girilen isme sahip bir yazar bulunamadi.");
                       return 1;
                   } else{
                       isFound->yazarID=found->yazarID;
                       flag=0;
                   }
               }
               index=index->next;
           }
        }
       isFound=isFound->next;
    }

    kitapYazarDosyaYaz(*kHead);

    return 0;

}

void kitapYazarDosyaOku(KITAPYAZAR** head) {

    FILE *kitapYazar;
    int read=0;

    kitapYazar=fopen("C:\\Users\\nur\\OneDrive\\Desktop\\KitapYazar.csv","r"); // ACILACAK DOSYANIN ADRESI.
    if(kitapYazar==NULL) // dosya acilamadiysa hata ver.
    {
        printf("Dosya acma hatasi.\n");
    }

    do{
        KITAPYAZAR *yeni=(KITAPYAZAR*)malloc(sizeof(KITAPYAZAR)); // yeni dugum olustur.
        if(yeni==NULL) // alan ayrilamadiysa hata ver.
        {
            printf("Bellek ayrilamadi.\n");
        }
        read = fscanf(kitapYazar,"%[^,],%d\n", // belgeden bilgileri oku.
                      yeni->ISBN,
                      &yeni->yazarID);
        if(read!=2 && !feof(kitapYazar)) // okuma yapilamadiysa hatayi belirt, programdan cik.
        {
            printf("Format hatasi.\n");
            return;
        }
        if(ferror(kitapYazar)) // dosya okuma hatasi varsa belirt.
        {
            printf("Dosya okuma hatasi.\n");
        }
        if(*head==NULL) // head bos ise yeni node'u head'e ata.
        {
            yeni->next=NULL;
            (*head)=yeni;
        } else{ // head bos degilse yeni node'u tail'e gore ekle.
            yeni->next=(*head);
            (*head)=yeni;
        }

    } while(!feof(kitapYazar)); // donguyu dosyanin sonuna gelene kadar devam ettir
}

void kitapOduncDosyaOku(KITAPODUNC** head, KITAP** kHead) {

    FILE *kitapOdunc;
    int read=0;
    unsigned int val1,val2,val3,val4;

    kitapOdunc=fopen("C:\\Users\\nur\\OneDrive\\Desktop\\KitapOdunc.csv","r"); // ACILACAK DOSYANIN ADRESI.
    if(kitapOdunc==NULL) // dosya acilamadiysa hata ver.
    {
        printf("Dosya acma hatasi.\n");
    }

    do{
        KITAPODUNC *yeni=(KITAPODUNC*)malloc(sizeof(KITAPODUNC)); // yeni dugum olustur.
        if(yeni==NULL) // alan ayrilamadiysa hata ver.
        {
            printf("Bellek ayrilamadi.\n");
        }
        read = fscanf(kitapOdunc,"%15[^,],%8[^,],%d,%d.%d.%d\n", // belgeden bilgileri oku.
                      yeni->etiketNo,
                      yeni->ogrID,
                      &val1,
                      &val2,
                      &val3,
                      &val4);
        yeni->islemTipi=val1;
        yeni->islemTarihi.gun=val2;
        yeni->islemTarihi.ay=val3;
        yeni->islemTarihi.yil=val4;
        if(read!=6 && !feof(kitapOdunc)) // okuma yapilamadiysa hatayi belirt, programdan cik.
        {
            printf("Format hatasi.\n");
            return;
        }
        if(ferror(kitapOdunc)) // dosya okuma hatasi varsa belirt.
        {
            printf("Dosya okuma hatasi.\n");
        }
        if(*head==NULL) // head bos ise yeni node'u head'e ata.
        {
            yeni->next=NULL;
            (*head)=yeni;
        } else{ // head bos degilse yeni node'u tail'e gore ekle.
            yeni->next=(*head);
            (*head)=yeni;
        }

    } while(!feof(kitapOdunc)); // donguyu dosyanin sonuna gelene kadar devam ettir

    KITAPODUNC *index=(*head);
        while(index!=NULL){
           if(index->islemTipi==0){
               KITAP* index2=*kHead;
               while(index2!=NULL){
                   KITAPORNEK *index3=index2->head;
                  while(index3!=NULL){
                      if(strcmp(index->etiketNo,index3->etiketNo)==0){
                          strcpy(index3->durum,index->ogrID);
                      }
                      index3=index3->next;
                  }
                  index2=index2->next;
               }
           }
           index=index->next;
       }

}


int kitapOduncTeslim(KITAPODUNC** kOHead, KITAP* kHead, OGRENCI** oHead){

   KITAPODUNC* yeni=(KITAPODUNC*)malloc(sizeof(KITAPODUNC));

   KITAP *isFound=kHead;
   KITAPORNEK *index;
   OGRENCI *found;
   TARIH tarih;

   char data[60];
   int flag=0;
   int val;
   char tmp;
   scanf("%c",&tmp);

   printf("\nYapilacak islemi giriniz:\n1-Teslim Etme\n2-Odunc Alma\nGiris: "); scanf("%d",&val);
   scanf("%c",&tmp);
   printf("\nKitabin adini giriniz: "); gets(data);
   isFound=kitapAdiAra(kHead,data);
   if(isFound==NULL){
       printf("\nGirilen ada sahip bir kitap bulunamadi.");
       return 1;
   }
    printf("\nOgrencinin ID bilgisini giriniz: "); scanf("%s",data);
    found=ogrenciAra(*oHead,data);
    if(found==NULL){
        printf("\nGirilen numaraya ait ogrenci bulunamamistir.\n");
        return 1;
    }
    SYSTEMTIME t;
    GetLocalTime(&t);
    tarih.yil=t.wYear;
    tarih.ay=t.wMonth;
    tarih.gun=t.wDay;
    if(val==2){
        if(found->puan<0){
            printf("\nOgrencinin puani 0 alti oldugundan dolayi isleme devam edilememektedir.\n");
            return 1;
        }

        index=isFound->head;
        while(index!=NULL && flag==0){
            if(strcmp(index->durum,"Rafta")==0){
                strcpy(yeni->etiketNo,index->etiketNo);
                strcpy(index->durum,found->ogrID);
                strcpy(yeni->ogrID,found->ogrID);
                yeni->islemTipi=0;
                flag=1;
            }
            index=index->next;
        }

        if(flag==0){
            printf("\nKitabin tum ornekleri odunc verildigi icin isleme devam edilememektedir.\n");
            return 1;
        }

    } else if(val==1){
        KITAPODUNC* kontrol;
        index=isFound->head;
        while(index!=NULL && flag==0){
            if(strcmp(index->durum,found->ogrID)==0){
                kontrol=kitapOduncAra(*kOHead,index->etiketNo,index->durum);
                strcpy(yeni->etiketNo,index->etiketNo);
                strcpy(index->durum,"Rafta");
                strcpy(yeni->ogrID,found->ogrID);
                yeni->islemTipi=1;
                val=cezaDurumu(kontrol, &tarih);
                if(val==1){
                    found->puan-=10;
                    ogrenciDosyaYaz(*oHead);
                }
                flag=1;
            }
            index=index->next;
        }
    }
    yeni->islemTarihi=tarih;
    yeni->next=(*kOHead);
    (*kOHead)=yeni;
    kitapOduncDosyaYaz(*kOHead);
   return 0;
}

KITAPODUNC* kitapOduncAra(KITAPODUNC* head, char *data1, char *data2) {
    KITAPODUNC *index=head;
    while(index!=NULL){
        if(strcmp(data1,index->etiketNo)==0 && strcmp(data2,index->ogrID)==0){
            return index;
        }
        index=index->next;
    }
    return NULL;
}

int cezaDurumu(KITAPODUNC *data1, TARIH *data2){
    int val;

    if((data1->islemTarihi.ay)==(data2->ay) && (data1->islemTarihi.yil)==(data2->yil)){
        val=(data2->gun)-(data1->islemTarihi.gun);
        if(val>=15){
            return 1;
        }
    }else {
        val=((30-(data1->islemTarihi.gun))+(data2->gun));
        if(val>=15){
            return 1;
        }
    }
    return 0;
}

void teslimsizListele(KITAP *head, OGRENCI *oHead){

    int i;
    KITAP* index=head;
    KITAPORNEK* index2;
    OGRENCI* found;
    while(index!=NULL){
        index2=index->head;
         while(index2!=NULL){
            if(strcmp(index2->durum,"Rafta")!=0){
                    found=ogrenciAra(oHead,index2->durum);
                    printf("ID: %s Ad: %s Soyad: %s Teslim etmedigi kitap: %s\n",found->ogrID,found->ad,found->soyad,index->kitapAdi);
            }
            index2=index2->next;
        }
        index=index->next;
    }
}

void zamanListele(KITAPODUNC* kOHead,KITAP* kHead){

    KITAPODUNC* index1=kOHead;
    TARIH tarih;
    KITAPORNEK *index2;
    KITAP* index=kHead;
    int val;

    SYSTEMTIME t;
    GetLocalTime(&t);
    tarih.yil=t.wYear;
    tarih.ay=t.wMonth;
    tarih.gun=t.wDay;
    printf("\n--Zamaninda teslim edilmeyen kitaplar---\n");
    while(index1!=NULL){
        if(index1->islemTipi==0){
            val=cezaDurumu(index1,&tarih);
            if(val==1){
                index=kHead;
                while(index!=NULL){
                    index2=index->head;
                       while(index2!=NULL){
                        if(strcmp(index2->etiketNo,index1->etiketNo)==0){
                            printf("Kitap Adi: %s - Kitabi odunc alan ogrenci ID'si: %s\n",index->kitapAdi,index1->ogrID);
                        }
                        index2=index2->next;
                    }
                    index=index->next;
                }
            }
        }
        index1=index1->next;
    }
}

void kitapOduncDosyaYaz(KITAPODUNC *head){
    KITAPODUNC* index;
    FILE* kitapodunc;

    index=head;
    kitapodunc=fopen("C:\\Users\\nur\\OneDrive\\Desktop\\KitapOdunc.csv","w");
    if(kitapodunc==NULL){
        printf("\nDosya acma hatasi.");
    }

    while(index!=NULL)
    {
        fprintf(kitapodunc,"%s,%s,%d,%d.%d.%d",index->etiketNo,index->ogrID,index->islemTipi,index->islemTarihi.gun,index->islemTarihi.ay,index->islemTarihi.yil);
        index=index->next;
        if(index!=NULL)
        {
            fprintf(kitapodunc,"\n");
        }
    }
    fclose(kitapodunc);
}

void kitapYazarDosyaYaz(KITAPYAZAR *head){
    KITAPYAZAR* index;
    FILE* kitapYazar;

    index=head;
    kitapYazar=fopen("C:\\Users\\nur\\OneDrive\\Desktop\\KitapYazar.csv","w");
    if(kitapYazar==NULL){
        printf("\nDosya acma hatasi.");
    }

    while(index!=NULL)
    {
        fprintf(kitapYazar,"%s,%d",index->ISBN,index->yazarID);
        index=index->next;
        if(index!=NULL)
        {
            fprintf(kitapYazar,"\n");
        }
    }
    fclose(kitapYazar);
}

