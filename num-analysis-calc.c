// a numerical analysis calculator.

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define boyut 20

void Fonksiyon_Al(float k[boyut],float u[boyut],int *j);
void Matris_Al(float matrix[boyut][boyut], int *j);
void Bisection(void);
void Regula_Falsi(void);
void Newton_Raphson(void);
void Matris_Tersi(void);
void Gauss_Eliminasyon(void);
void Gauss_Seidel(void);
void Sayisal_Turev(void);
void Simpson(void);
void Trapez(void);
void Gregory_Newton(void);


int main()
{
menu();
return 0;
}

void menu(void)
{
int choice;

do
{
    printf("\n\nMenu\n\n");
    printf("1. Bisection Yontemi\n");
    printf("2. Regula Falsi Yontemi\n");
    printf("3. Newton-Raphson Yontemi\n");
    printf("4. NxN'lik bir matrisin tersini alma\n");
    printf("5. Gauss Eliminasyon Yontemi\n");
    printf("6. Gauss Seidel Yontemi\n");
    printf("7. Sayisal Turev\n");
    printf("8. Simpson Yontemi\n");
    printf("9. Trapez Yontemi\n");
    printf("10. Degisken donusumlu Gregory Newton Enterpolasyonu\n");
    printf("Cikis icin 0'a basiniz.\n");
    printf("Seciminiz: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1: Bisection();
        break;
    case 2: Regula_Falsi();
        break;
    case 3: Newton_Raphson();
        break;
    case 4: Matris_Tersi();
        break;
    case 5: Gauss_Eliminasyon();
        break;
    case 6: Gauss_Seidel();
        break;
    case 7: Sayisal_Turev();
        break;
    case 8: Simpson();
        break;
    case 9: Trapez();
        break;
    case 10: Gregory_Newton();
        break;
    case 0: printf("\nProgram sonlanmistir.");
        break;
    default: printf("\nLutfen yeniden giris yapiniz.\n");
        break;
    }

  } while (choice!=0);

}

void Fonksiyon_Al(float k[boyut],float u[boyut],int *j){
	
	int i,size;

	do{printf("\n\nProgram sadece polinom fonksiyonlari desteklemektedir.\nFonksiyonda bulunan terim sayisini giriniz: "); scanf("%d",&size);
	}while(size<=0);
	
	 *j=size;
	
		for(i=0;i<size;i++)
	{
		printf("\n%d. terimin katsayisini giriniz: ",i+1); scanf("%f",&k[i]);
		printf("%d. terimin ussunu giriniz: ",i+1); scanf("%f",&u[i]);
	} 
	
		printf("\n\nFonksiyon: ");
	for(i=0;i<size;i++)
	{
		printf("%f*x^%f",k[i],u[i]);
		if(i!=(size-1))
		{
			printf(" + ");
		}
	}
}


void Matris_Al(float matrix[boyut][boyut], int *x){
	
	int size,i,j;
	
	printf("\n\nMatrisin satir ve sutun degerini giriniz: "); scanf("%d",&size);
	
	*x=size;
	
	printf("\nMatrisin elemanlarini giriniz:\n");
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			printf("[%d][%d]: ",i+1,j+1); scanf("%f",&matrix[i][j]);
		}
	}
	
	printf("\nGirdiginiz matris:\n");
		for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			printf("%f ",matrix[i][j]); 
		}
		printf("\n");
	}
	
	
}

void Bisection(void){
	
	// pol: polinom fonksiyondaki terim sayisi.
	// sayac: kacinci iterasyonda olundugunu gosteren parametre.
	// max: maksimum iterasyon sayisi.
	// katsayi,us: islem yapilacak polinomun katsayi ve ussunu tutan matrisler.
	// alt,ust: sirasiyla alt ve ust sinir degerleri.
	// yeni_deger: belirlenen yeni x degerinin atandigi parametre.
	// deger: verilen aralikta kok olup olmadiginin kontrolu icin kullanilan bir parametre.
	// epsilon: hata miktari. // sonuc: yeni x degerinin fonksiyondaki sonucu.
	// durma_kosulu: durma kosulunun kontrol edilip atandigi parametre. algoritmanin gerekliliginden dolayi ilk degeri 6 olarak belirlendi.
	
	int pol,sayac=1,max,i;
	float katsayi[boyut],us[boyut];
	float alt,ust;
	float yeni_deger=0.0,deger=0.0,epsilon,sonuc=0.0,durma_kosulu=6;
	
	Fonksiyon_Al(katsayi,us,&pol);
	printf("\n\nAlt sinir degerini giriniz: "); scanf("%f",&alt);
	printf("Ust sinir degerini giriniz: "); scanf("%f",&ust);
	printf("Epsilon degerini giriniz: "); scanf("%f",&epsilon);
	printf("Maksimum iterasyon sayisini giriniz: "); scanf("%d",&max);
	
	
		for(i=0;i<pol;i++)
	{
		yeni_deger+=pow(ust,us[i])*katsayi[i];
		deger+=pow(alt,us[i])*katsayi[i];
    }
    
    if(yeni_deger*deger>0) 
    {
    	printf("Girilen aralikta kok bulunmamaktadir.");
	}
	else {
		while(durma_kosulu>epsilon && sayac!=max+1) 
		{
			printf("\n\n%d. Iterasyon",sayac);
			yeni_deger=(alt+ust)/2;  
			sonuc=0.0;  
			printf("\nUst sinir: %f",ust);
			printf("\nAlt sinir: %f",alt);
			printf("\nOrta nokta: %f",yeni_deger); 
			for(i=0;i<pol;i++)
	        {
		     sonuc+=pow(yeni_deger,us[i])*katsayi[i]; 
            }
            
			printf("\nF(%f)=%f",yeni_deger,sonuc);
            
            durma_kosulu=(ust-alt)/pow(2,sayac); 
		
            
            if(sonuc<0 && deger<0)
            {
            	alt=yeni_deger;
			}
			else
			{
				ust=yeni_deger;
			}
			deger=sonuc;
			sayac++;
		}
	    printf("\n\nSonuc: %f",yeni_deger);
	}
}

void Regula_Falsi(void){
	
	// pol: polinom fonksiyondaki terim sayisi.
	// sayac: kacinci iterasyonda olundugunu gosteren parametre.
	// max: maksimum iterasyon sayisi.
	// katsayi,us: islem yapilacak polinomun katsayi ve ussunu tutan matrisler.
	// alt,ust: sirasiyla alt ve ust sinir degerleri. // f_alt,f_ust: belirlenen alt,ust degerlerinin fonksiyondaki sonuclari.
	// yeni_deger: belirlenen yeni x degerinin atandigi parametre.
	// deger: verilen aralikta kok olup olmadiginin kontrolu icin kullanilan bir parametre.
	// epsilon: hata miktari. // sonuc: yeni x degerinin fonksiyondaki sonucu.
	// durma_kosulu: durma kosulunun kontrol edilip atandigi parametre. algoritmanin gerekliliginden dolayi ilk degeri 6 olarak belirlendi.
	
	
	int pol,sayac=1,max,i;
	float katsayi[boyut],us[boyut];
	float alt,ust;
	float yeni_deger=0,deger=0,epsilon,sonuc=0,durma_kosulu=6;
	float f_alt,f_ust;
	
	Fonksiyon_Al(katsayi,us,&pol);
	printf("\n\nAlt sinir degerini giriniz: "); scanf("%f",&alt);
	printf("Ust sinir degerini giriniz: "); scanf("%f",&ust);
	printf("Epsilon degerini giriniz: "); scanf("%f",&epsilon);
	printf("Maksimum iterasyon sayisini giriniz: "); scanf("%d",&max);
	
		for(i=0;i<pol;i++)
	{
		yeni_deger+=pow(ust,us[i])*katsayi[i];
		deger+=pow(alt,us[i])*katsayi[i];
    }
    
    if(yeni_deger*deger>0)
    {
    	printf("Girilen aralikta kok bulunmamaktadir.");
	} 
	else {
		
		while(sayac!=max && durma_kosulu>=epsilon)
		{
		printf("\n\n%d. Iterasyon:",sayac);
		sonuc=0.0;
		f_ust=0.0;
		f_alt=0.0;
		for(i=0;i<pol;i++)
		{
			f_ust+=pow(ust,us[i])*katsayi[i];
			f_alt+=pow(alt,us[i])*katsayi[i];
		}
		yeni_deger=((alt*f_ust)-(ust*f_alt))/(f_ust-f_alt);
		printf("\nUst sinir: %f",ust);
		printf("\nAlt sinir: %f",alt);
		printf("\nYeni nokta: %f",yeni_deger);
		printf("\nF(ust)=%f",f_ust);
		printf("\nF(alt)=%f",f_alt);
		for(i=0;i<pol;i++)
		{
			sonuc+=pow(yeni_deger,us[i])*katsayi[i];
		}
		printf("\nF(%f)=%f",yeni_deger,sonuc);
		
		durma_kosulu=(ust-alt)/pow(2,sayac);
		
		if(sonuc>0 && f_alt<0)
		{
			ust=yeni_deger;
		}
		else{
			alt=yeni_deger;
		}
		sayac++;
			
		}
		printf("\n\nSonuc: %f",yeni_deger);
		
	}
	
	
}

void Newton_Raphson(void){
	
	// pol: polinom fonksiyondaki terim sayisi.
	// sayac: kacinci iterasyonda olundugunu gosteren parametre.
	// max: maksimum iterasyon sayisi.
	// katsayi,us: islem yapilacak polinomun katsayi ve ussunu tutan matrisler.
	// fonk,turev: kok adaylarinin sirasiyla fonksiyonda ve fonksiyonun turevindeki goruntusu.
	// baslangic_degeri: basta kullanicidan alinan baslangic degeri, ardindan kok adaylarinin atanmasi icin kullanildi.
	// epsilon: hata miktari. // sonuc: kok adaylarinin fonksiyondaki sonucu.
	// durma_kosulu: durma kosulunun kontrol edilip atandigi parametre. algoritmanin gerekliliginden dolayi ilk degeri 6 olarak belirlendi.
	
	int pol,i,sayac=1,max;
	float katsayi[boyut],us[boyut],turev,fonk;
	float sonuc,durma_kosulu=6,baslangic_degeri,epsilon;
	
	Fonksiyon_Al(katsayi,us,&pol);
    printf("\nBaslangic degerini giriniz: "); scanf("%f",&baslangic_degeri);
	printf("\nEpsilon degerini giriniz: "); scanf("%f",&epsilon);
	printf("\nMaksimum iterasyon sayisini giriniz: "); scanf("%d",&max);

	while(durma_kosulu>epsilon && sayac!=max)
	{
		printf("\n\n%d. Iterasyon: ",sayac);
		fonk=0.0;
		turev=0.0;
	    i=0;
	   	while(i<pol)
		{
			if(us[i]==0)
			{
			fonk+=pow(baslangic_degeri,us[i])*katsayi[i];
			} 
			else{
			fonk+=pow(baslangic_degeri,us[i])*katsayi[i];
			turev+=pow(baslangic_degeri,(us[i]-1))*katsayi[i]*us[i];
			}
			i++;
		}
		   
		printf("\nF(%f)=%f",baslangic_degeri,fonk);
		printf("\nF'(%f)=%f",baslangic_degeri,turev);
		sonuc=baslangic_degeri-(fonk/turev);
		printf("\nYeni x degeri: %f",sonuc);
	    durma_kosulu=sonuc-baslangic_degeri;
	    if(durma_kosulu<0)
	    {
	    	durma_kosulu*-1;
		}
		baslangic_degeri=sonuc;
		sayac++;
	}
	
	printf("\n\nSonuc: %f",sonuc);
}

void Matris_Tersi(void)
{     
     // n: matrisin boyutu.
     // matris: kullanicidan alinan matris.
     // ters: olusturulacak olan ters matris.
     // cikarim: gauss-jordan eliminasyonu icin matrisin elemanlarindan cikarilacak degerlerin bulunmasi adina kullanilacak carpim orani.
	
	float matris[boyut][boyut],ters[boyut][boyut];
	float cikarim;
	int n;
	int i,j,k,x;
	
	Matris_Al(matris,&n);
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i==j)
			{
				ters[i][j]=1;
			}
			else
			{
				ters[i][j]=0;
			}
		}
	}
	
	while (x<n)
	{
		if(matris[x][x]!=0)
		{   
		    for(j=0;j<n;j++)
	        {
	         if(x!=j)
	         {
		     cikarim=matris[j][x]/matris[x][x];	
	         }
		    for(k=0;k<n;k++)
		     {
		   matris[j][k]=matris[j][k]-cikarim*matris[x][k];
		   ters[j][k]=ters[j][k]-cikarim*ters[x][k];
		     }
	        }
	        x++;
		} else
		{
			printf("\nProgram tarafindan girilen matrisin tersi alinamaz.");
			x=n+5;
		}
	}
	
	while(x!=n+5)
	{
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			ters[i][j]=ters[i][j]/matris[i][i];
		}
	}
	
    printf("\nGirilen matrisin tersi:\n");
	for(i=0;i<n;i++)
	  {
	  for(j=0;j<n;j++)
	   {
	   printf("%f ",ters[i][j]);
	   }	 
	     printf("\n");
	   }
     x=n+5;	
	}

}



void Gauss_Eliminasyon(void)
{   
    // matris: kullanicidan alinan matris. // n: matrisin boyutu.
    // x: a.x=b formundan bulunacak olan x'lerin saklandigi matris. nx1 formatinda oldugundan direkt dizi olarak kodlandi.
	// b: a.x=b formundan sonuclarin yazildigi b matrisi. nx1 formatinda oldugundan direkt dizi olarak kodlandi.
	// cikarim: gauss eliminasyonunda matrisin elemanlarindan cikarilacak degerlerin bulunmasi adina kullanilacak carpim orani.
	
	float matris[boyut][boyut],b[boyut],x[boyut]={0};
	float cikarim;
	int n;
	int i,j,k,y=0;
	
	Matris_Al(matris,&n);
	printf("\nb matrisini giriniz:\n"); 
	for(k=0;k<n;k++)
	{
		printf("[%d][1]: ",k+1); scanf("%f",&b[k]);
	}
	
	   while(y<n)
	   {
	   	if(matris[y][y]==0)
		{
			printf("\nGirilen matrisin x degerleri program tarafindan bulunamaz.");
			y=n+5;
		}
		else
		{
		  for(j=y;j<n;j++)
	     {
	   	 if(y!=j)
	   	   {
	   	 	cikarim=matris[j][y]/matris[y][y];
		   }
		   b[j]=b[j]-(cikarim*b[y]);
		 for(k=0;k<n;k++)
		   {
		 	matris[j][k]=matris[j][k]-(cikarim*matris[y][k]);
		   }
	     }
	     y++;
		}
	}  
	   	
	while(y!=n+5)
	{
	x[n-1]=b[n-1]/matris[n-1][n-1];
    
    for(i=n-2;i>=0;i--)
    {
    	for(j=n-1;j>i;j--)
    	{
    		b[i]=b[i]-(matris[i][j]*x[j]);
		}
	   x[i]=b[i]/matris[i][i];
	}
	
	printf("\nx matrisi: ");
	for(i=0;i<n;i++)
	 {
	  printf("\nx%d: %f",i+1,x[i]);
     }
	 y=n+5;	
	}
}


void Sayisal_Turev(void){
	
	// katsayi,us: fonksiyonun katsayisi ve us degerlerinin tutuldugu matrisler.
	// x: kullanicidan alinacak x degeri. // h: kullanicidan alinacak h degeri.
	// pol: fonksiyondaki terim sayisi. // sonuc: islem sonuclarinin atandigi parametre.
	// secim: ileri,geri ve merkezi fark islemlerinden hangisinin gerceklestirilecegi bilgisini tutan parametre.
	
	
	float katsayi[boyut],us[boyut];
	float x,h,sonuc=0.0;
	int pol,secim,i;
	
	
	Fonksiyon_Al(katsayi,us,&pol);
	
	printf("\n\nYontem seciniz: ");
	printf("\n1. Ileri fark\n2. Geri fark\n3.Merkezi fark");
	printf("\nSeciminiz: "); scanf("%d",&secim);
	printf("x degerini giriniz: "); scanf("%f",&x);
	printf("h degerini giriniz: "); scanf("%f",&h);
	
	if(secim==1)
	{
	    
	    for(i=0;i<pol;i++){
	    	sonuc+=(pow((x+h),us[i])*katsayi[i]-pow(x,us[i])*katsayi[i])/h;
		}
		printf("\nSonuc: %f",sonuc);
	    	
	}
	else if(secim==2)
	{
		
		for(i=0;i<pol;i++)
		{
			sonuc+=(pow(x,us[i])*katsayi[i]-pow((x-h),us[i])*katsayi[i])/h;
		}
		printf("\nSonuc: %f",sonuc);
			
	} else
	{

		for(i=0;i<pol;i++)
		{
		   sonuc+=(pow((x+h),us[i])*katsayi[i]-pow((x-h),us[i])*katsayi[i])/(2*h);	
		}
		printf("\nSonuc: %f",sonuc);
		
	}
	
}


void Trapez(void)
{
	// katsayi,us: fonksiyonun katsayi ve us degerlerinin tutuldugu matrisler.
	// ust,alt: ust ve alt sinir degerleri. // f_alt,f_ust: alt ve ust degerlerinin fonksiyondaki sonuclari.
	// n_farki: sinir degerlerinin belirlenmesinde kullanilan bir parametre.
    // pol: fonksiyondaki terim sayisi.
	
	float katsayi[boyut],us[boyut];
	float ust,alt,f_ust,f_alt,n_farki;
	float sonuc=0.0;
	int n,i,j,pol;
	
	Fonksiyon_Al(katsayi,us,&pol);
	printf("\n\nUst siniri giriniz: "); scanf("%f",&ust);
	printf("Alt siniri giriniz: "); scanf("%f",&alt);
	printf("n degerini giriniz: "); scanf("%d",&n);
	
	n_farki=(ust-alt)/n;
	for(i=0;i<n;i++)
	{
	 f_ust=0.0;
	 f_alt=0.0;
	 ust=alt+n_farki;
	 for(j=0;j<pol;j++)
	 {
	 	f_ust+=pow(ust,us[j])*katsayi[j];
	 	f_alt+=pow(alt,us[j])*katsayi[j];
	 }
	 sonuc+=(ust-alt)*((f_ust+f_alt)/2);
	 alt=ust;
	}
	
	printf("\nSonuc: %f",sonuc);
		
}

		


void Simpson(void){
	
	// pol: alinan polinomun terim sayisi.
	// katsayi ve us: alinmis polinomun katsayi ve us degerlerini saklayan matrisler.
	// ust: ust sinir degeri. // alt: alt sinir degeri.
	// x1,x2: simpson kurallarinda sinir degerleri disinda fonksiyonda degerleri hesaplanan parametreler.
	// f_alt,f_ust,f_x1,f_x2: sirasiyla alt,ust,x1,x2 degerlerinin fonksiyondaki sonuclari.
	// n_farki: yapilacak hesaplamalarda sinir degerlerin belirlenmesi icin kullanilan deger.
	// sonuc1: 1/3 kurali icin sonuc. // sonuc2: 3/8 kurali icin sonuc.
	
	float katsayi[boyut],us[boyut];
	float ust,alt,f_alt,f_ust,f_x1,f_x2,tmp;
	float x1,x2,sonuc1=0.0,sonuc2=0.0;
	float n_farki;
	int i,j,n,pol;
	
	Fonksiyon_Al(katsayi,us,&pol);
	
	printf("\nUst siniri giriniz: "); scanf("%f",&ust);
	printf("Alt siniri giriniz: "); scanf("%f",&alt);
	printf("n degerini giriniz: "); scanf("%d",&n);
	
	tmp=alt;
	
	n_farki=(ust-alt)/n;
	for(i=0;i<n;i++)
	{
		f_alt=0.0;
		f_ust=0.0;
		f_x1=0.0;
	    ust=alt+n_farki;
	    x1=(alt+ust)/2;
		for(j=0;j<pol;j++)
		{
			f_ust+=pow(ust,us[j])*katsayi[j];
			f_alt+=pow(alt,us[j])*katsayi[j];
			f_x1+=pow(x1,us[j])*katsayi[j];
	    }
	 sonuc1+=(ust-alt)*((f_ust+(4*f_x1)+f_alt)/6);
	 alt=ust;
	 }
	 
	 alt=tmp;
	 
	 for(i=0;i<n;i++)
	 {
	 	f_alt=0.0;
		f_ust=0.0;
		f_x1=0.0;
		f_x2=0.0;
	    ust=alt+n_farki;
	    x1=((ust-alt)/3)+alt;
	    x2=(((ust-alt)/3)*2)+alt;
	    for(j=0;j<pol;j++)
	    {
	    	f_ust+=pow(ust,us[j])*katsayi[j];
	    	f_alt+=pow(alt,us[j])*katsayi[j];
	    	f_x1+=pow(x1,us[j])*katsayi[j];
	    	f_x2+=pow(x2,us[j])*katsayi[j];
		}
		sonuc2+=(ust-alt)*((f_ust+(3*f_x1)+(3*f_x2)+f_alt)/8);
		alt=ust;
	 }
	
	printf("\nSimpson 1/3 kurali icin sonuc: %f",sonuc1);
	printf("\nSimpson 3/8 kurali icin sonuc: %f",sonuc2);
	
}

void Gauss_Seidel(void)
{   
	// matris: islem yapilacak matris.
	// n: matrisin boyutu. // secim: kosegensel baskin matris olusumu icin kullanicidan alinacak parametre.
	// c: kullanici tarafindan girilecek sonuclarin tutuldugu matris. nx1 formatinda oldugundan direkt dizi olarak kodlandi.
	// degerler: baslangic degerlerini tutan matris. nx1 formatinda oldugundan direkt dizi olarak kodlandi.
	// k_baskin: olusturulan kosegensel baskin matris.
	// max_it: maksimum iterasyon sayisi.
	// epsilon: hata degeri.
	
	/* fabs() kullanilmasi gerektigi icin float degerler alan matris_al fonksiyonu kullanilmadan direkt double olarak matris alinmistir.*/
	
	double k_baskin[boyut][boyut]={0.0},c[boyut]={0.0},deger[boyut]={0.0};
	double matris[boyut][boyut]={0.0},tmp;
	double epsilon,max,cikarim,durma_kosulu=6.0,temp;
	int n,max_it,i,j,k,secim,sayac=0;
	
	
	printf("\n\nMatrisin satir ve sutun degerini giriniz: "); scanf("%d",&n);
	
    printf("\nMatrisin elemanlarini giriniz:\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("[%d][%d]: ",i+1,j+1); scanf("%lf",&matris[i][j]);
		}
	}
	
	printf("\nGirdiginiz matris:\n");
		for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%lf ",matris[i][j]); 
		}
		printf("\n");
	}
	
	
	printf("\nC matrisini giriniz:\n");
	for(i=0;i<n;i++)
	{
		printf("[%d][1]: ",i+1); scanf("%lf",&c[i]);
	}
	printf("Baslangic degerlerini giriniz:\n");
	for(i=0;i<n;i++)
	{
		printf("[%d][1]: ",i+1); scanf("%lf",&deger[i]);
	}
	printf("Kosegensel baskin matris icin secenekler:\n0-Sadece girilen matris ile islem yapilmasi\n1-Satir degistirme islemleri ile bulunmasi");
	printf("\nSeciminiz: "); scanf("%d",&secim);
	printf("Epsilon degerini giriniz: "); scanf("%lf",&epsilon);
	printf("Maksimum iterasyon sayisini giriniz: "); scanf("%d",&max_it);

	
	if(secim==1)
	{
	for(i=0;i<n;i++)
	{
		for(j=i;j>=0;j--)
		{
			if(fabs(matris[k][j])<matris[j][i])
			{
				k=j;
			}
		}
		
		if(k!=i)
		{   
		    tmp=c[i];
		    c[i]=c[k];
		    c[k]=tmp;
			for(j=0;j<=n;j++)
			{
			 tmp=matris[i][j];
			 matris[i][j]=matris[k][j];
			 matris[k][j]=tmp;	
			}
		}
	}
	
	printf("\nKosegensel baskin matris:\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			
			printf("%lf ",matris[i][j]);
		}
		printf("\n");
    } 
}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			k_baskin[i][j]=matris[i][j];
		}
	}

	
  while (durma_kosulu>=epsilon && sayac!=max_it)
  {
  	for(k=0;k<n;k++)
	  {
  	 temp=deger[k];
  	 deger[k]=c[k];
  	for(j=0;j<n;j++)
  	{
  	if(j!=k)
  	 {
  	deger[k]-=k_baskin[k][j]*deger[j];
	 }
    }
    deger[k]=deger[k]/k_baskin[k][k];
    durma_kosulu=temp-deger[k];
    durma_kosulu=fabs(durma_kosulu);
    }
    printf("\n\n%d. iterasyon:",sayac+1);
    for(i=0;i<n;i++)
    {
    	printf("\nx%d degeri: %lf",i+1,deger[i]);
	}
	sayac++;
  }}

void Gregory_Newton(void) {
	
	// x_bas: x degerlerlerinin baslangic degeri.
	// x_istenen: olusturulan fonksiyonda hesaplanmasi istenen x degeri. 
	// h: x degerleri arasindaki fark.
	// y_deger: y degerlerinin tutuldugu dizi.
	// fonksiyon: fonskiyonun olusturulmasinda kullanilacak ileri fark degerlerinin tutuldugu matris.
	// sonuc: x_istenen degerinin fonksiyondaki degerini gosteren parametre.
	// n: deger sayisi. // fakt: faktoriyel.
	// kat: (x-x0).(x-x1)....(x-xn) ifadesinin acilimindaki katsayilari bulmak icin tutulan dizi.
	// x: enterpolasyon fonksiyonunun katsayilarinin belirlenip atandigi dizi.
	
	float x_bas, x_istenen,h;
	float y_deger[boyut]={0},fonksiyon[boyut]={0},x[boyut]={0};
	float sonuc=0,fakt=1;
	int n,i,c=0,j=0,k=0,tmp,kat[boyut]={0},a;
	
	printf("\nx degerlerinin baslangicini giriniz: "); scanf("%f",&x_bas);
	printf("\nx degerleri arasindaki farki giriniz: "); scanf("%f",&h);
	printf("\nDeger sayisini giriniz: "); scanf("%d",&n);
	
	printf("\nFonksiyon degerlerini giriniz:\n");
	for(i=0;i<n;i++)
	{
		printf("F(%f):",(x_bas+(i*h))); scanf("%f",&y_deger[i]);
	}
	
	while(y_deger[0]!=0)
	{	
	  fonksiyon[c]=y_deger[0];
	  c++;
 	for(i=0;i<(n-1-c);i++)
	 {
	  y_deger[i]=y_deger[i+1]-y_deger[i];
	 }	
	}
	
	for(i=1;i<c;i++)
	{
		fakt*=i;
		fonksiyon[i]/=(fakt*pow(h,i));
	}
	
       while(j<n)
      {
    	kat[j]=1;	
    	for(i=(j-1);i>=0;i--)
    	{	
    	    tmp=kat[i-1];
    		kat[i]*=-k;	
			if(i!=0)
			{
			  kat[i]=kat[i]+tmp;	
			}	
			}
		k+=h;
		for(a=0;a<=j;a++)
		{  
		  if(x_istenen==0){
		  	x[a+1]+=kat[a]*fonksiyon[j+1]; 
		  }
	    	else
		{   if(j>0)
		{
			x[a]+=kat[a]*fonksiyon[j]; 
		}
		}   

	}	
		j++;
	}
		
      
      x[0]+=fonksiyon[0];
      	
    printf("\nFonksiyon: ");
	for(i=c-1;i>=0;i--)
	{
	   printf("%f*x^%d",x[i],i);
	   if(i!=0)
	   {
	   	printf(" + ");
	   } 	
	}
	
	printf("\n\nIstenen x degerini giriniz: "); scanf("%f",&x_istenen);
	
	 for(i=(c-1);i>=0;i--)
   {
   	sonuc+=pow(x_istenen,i)*x[i];
   }
    
	printf("\nSonuc: %f",sonuc);
}
	



