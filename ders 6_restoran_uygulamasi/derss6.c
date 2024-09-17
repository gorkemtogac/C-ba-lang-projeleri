#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>    
#include <stdbool.h>
//bagli listeleri ikili dosya kullanarak restoran urun stok, musteri cari hesaplarini ve satis islemlerini tutan program


#if __has_include ("urun.bin")
#define URUN_MEVCUT 1
#else
#define URUN_MEVCUT 0
#endif
#if __has_include ("musteri.bin")
#define MUSTERI_MEVCUT 1
#else
#define MUSTERI_MEVCUT 0
#endif
#if __has_include ("satis.bin")
#define SATIS_MEVCUT 1
#else
#define SATIS_MEVCUT 0
#endif

struct aranacak {
        char ad[50];
        char soyad[50];
        char kategori[50];
};
typedef struct Musteri {
    char ad[50];
    char soyad[50];
    char telefon[50];
    float cari;
    struct Musteri *sonraki;
    struct Musteri *onceki;
} musteri;
pthread_mutex_t lock;   
musteri *musteri_head=NULL;
musteri *musteri_tail=NULL;
musteri *sonucmusteri=NULL;
musteri *musterikontrolbas=NULL;
musteri *musterikontrolson=NULL;
bool kontrolmusteri=false;


typedef struct Urun {
    char ad[50];
    char kategori[50];
    int stok;
    float fiyat;
    int urunKodu;
    struct Urun *sonraki;
    struct Urun *onceki;
    

}urun;
pthread_mutex_t lock;
urun *urun_head=NULL;
urun *urun_tail=NULL;
urun *sonucurun=NULL;
bool kontrolurun=false;
urun *urunkontrolbas=NULL;
urun *urunkontrolson=NULL;
typedef struct Satis {
    int zaman;
    char urunAd[50];
    char adet;
    float toplam;
    struct Satis *sonraki;
    struct Satis *onceki;
} satis;

satis *satis_head=NULL;
satis *satis_tail=NULL;
satis *satiskontrolbas=NULL;
satis *satiskontrolson=NULL;

//kayit ve okuma islemleri
void satis_kayit(){
printf("==================================================\n");
printf("Yaptiginiz degisiklikler kaydetmek istiyor musunuz?\n");
printf("1-Evet\n");
printf("2-Hayir\n");
printf("\tSeciminizi yapiniz:");
int secim;
scanf("%d", &secim);
printf("==================================================\n");
satis *gecici=satis_head;
satis *yazdir=(satis*)malloc(sizeof(satis));
switch(secim)
{
   
    case 1:
    if (SATIS_MEVCUT!=0)
    {   
     
        FILE *dosya=fopen("satisgecici.bin","wb");
            if (dosya==NULL)
            {
                printf("Dosya acilamadi\n");
                return;
            }
        while (gecici!=NULL)
        {
            
            yazdir->zaman=gecici->zaman;
            strcpy(yazdir->urunAd,gecici->urunAd);
            yazdir->adet=gecici->adet;
            yazdir->toplam=gecici->toplam;
            yazdir->sonraki=NULL;
            yazdir->onceki=NULL;
            if(fwrite(yazdir,sizeof(satis),1,dosya)!=1)
            {
                printf("Dosyaya yazilamadi\n");
                fclose(dosya);
                return;
            }
            printf("Satis bilgileri dosyaya basariyla yazildi\n");
            gecici=gecici->sonraki;
           }
            fclose(dosya);
            if(remove("satis.bin")!=0)
                {
                printf("Dosya silinemedi\n");
                  return;
                  }
             if (rename("satisgecici.bin","satis.bin")!=0)
               {
                    printf("Dosya adi degistirilemedi\n");
                    return;
                }
     }
    else 
    {
        FILE *dosya=fopen("satis.bin","wb");
        if (dosya==NULL)
        {
            printf("Dosya acilamadi\n");
            return;
        }
        while (gecici!=NULL)
        {
           
            yazdir->zaman=gecici->zaman;
            strcpy(yazdir->urunAd,gecici->urunAd);
            yazdir->adet=gecici->adet;
            yazdir->toplam=gecici->toplam;
            yazdir->sonraki=NULL;
            yazdir->onceki=NULL;
            if(fwrite(yazdir,sizeof(satis),1,dosya)!=1){
                printf("Dosyaya yazilamadi\n");
                fclose(dosya);
                return;
            }
            gecici=gecici->sonraki;
        }
            fclose(dosya);
    }
    break;
    case 2:
    printf("Kayit yapilmadi\n");
    break;
    default:
    printf("Hatali secim yaptiniz\n");
    break;
}
printf("==================================================\n");
};
void musteri_kayit(){
printf("==================================================\n");
printf("Yaptiginiz degisiklikler kaydetmek istiyor musunuz?\n");
printf("1-Evet\n");
printf("2-Hayir\n");
printf("\tSeciminizi yapiniz:");
int secim;
scanf("%d", &secim);
printf("==================================================\n");
musteri *gecici=musteri_head;
musteri *yazdir=(musteri*)malloc(sizeof(musteri));
switch(secim)
{
   
    case 1:
    if (MUSTERI_MEVCUT!=0)
    {   
     
        FILE *dosya=fopen("musterigecici.bin","wb");
            if (dosya==NULL)
            {
                printf("Dosya acilamadi\n");
                return;
            }
        while (gecici!=NULL)
        {
            
            strcpy(yazdir->ad,gecici->ad);
            strcpy(yazdir->soyad,gecici->soyad);
            strcpy(yazdir->telefon,gecici->telefon);
            yazdir->cari=gecici->cari;
            yazdir->sonraki=NULL;
            yazdir->onceki=NULL;
            if(fwrite(yazdir,sizeof(musteri),1,dosya)!=1)
            {
                printf("Dosyaya yazilamadi\n");
                fclose(dosya);
                return;
            }
            printf("Musteri bilgileri dosyaya basariyla yazildi\n");
            gecici=gecici->sonraki;
           }
            fclose(dosya);
            if(remove("musteri.bin")!=0)
                {
                printf("Dosya silinemedi\n");
                  return;
                  }
             if (rename("musterigecici.bin","musteri.bin")!=0)
               {
                    printf("Dosya adi degistirilemedi\n");
                    return;
                }
     }
    else 
    {
        FILE *dosya=fopen("musteri.bin","wb");
        if (dosya==NULL)
        {
            printf("Dosya acilamadi\n");
            return;
        }
        while (gecici!=NULL)
        {
           
            strcpy(yazdir->ad,gecici->ad);
            strcpy(yazdir->soyad,gecici->soyad);
            strcpy(yazdir->telefon,gecici->telefon);
            yazdir->cari=gecici->cari;
            yazdir->sonraki=NULL;
            yazdir->onceki=NULL;
            if(fwrite(yazdir,sizeof(musteri),1,dosya)!=1){
                printf("Dosyaya yazilamadi\n");
                fclose(dosya);
                return;
            }
            gecici=gecici->sonraki;
            
        }
         fclose(dosya);
    }
   
    break;
    case 2:
    printf("Kayit yapilmadi\n");
    break;
    default:
    printf("Hatali secim yaptiniz\n");
    break;
}

printf("==================================================\n");

};

 int musteri_kontrol(){
    if (musterikontrolbas!=musterikontrolson)
    {
        return 1;
    }
    else
    {
        return 0;
    }   
};
int urun_kontrol(){
    if (urunkontrolbas!=urunkontrolson)
    {
        return 1;
    }
    else
    {
        return 0;
    }   
};
int satis_kontrol(){
    if (satis_head!=NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }   
};
void urun_kayit(){
printf("==================================================\n");
printf("Yaptiginiz degisiklikler kaydetmek istiyor musunuz?\n");
printf("1-Evet\n");
printf("2-Hayir\n");
printf("\tSeciminizi yapiniz:");
int secim;
scanf("%d", &secim);
printf("==================================================\n");
urun *gecici=urun_head;
urun *yazdir=(urun*)malloc(sizeof(urun));
switch(secim)
{
   
    case 1:
    if (URUN_MEVCUT!=0)
    {   
     
        FILE *dosya=fopen("urungecici.bin","wb");
            if (dosya==NULL)
            {
                printf("Dosya acilamadi\n");
                return;
            }
        while (gecici!=NULL)
        {
            
            strcpy(yazdir->ad,gecici->ad);
            strcpy(yazdir->kategori,gecici->kategori);
            yazdir->stok=gecici->stok;
            yazdir->fiyat=gecici->fiyat;
            yazdir->urunKodu=gecici->urunKodu;
            yazdir->sonraki=NULL;
            yazdir->onceki=NULL;
            if(fwrite(yazdir,sizeof(urun),1,dosya)!=1)
            {
                printf("Dosyaya yazilamadi\n");
                fclose(dosya);
                return;
            }
            printf("Urun bilgileri dosyaya basariyla yazildi\n");
            gecici=gecici->sonraki;
           }
            fclose(dosya);
            if(remove("urun.bin")!=0)
                {
                printf("Dosya silinemedi\n");
                  return;
                  }
             if (rename("urungecici.bin","urun.bin")!=0)
               {
                    printf("Dosya adi degistirilemedi\n");
                    return;
                }
     }
    else 
    {
        FILE *dosya=fopen("urun.bin","wb");
        if (dosya==NULL)
        {
            printf("Dosya acilamadi\n");
            return;
        }
        while (gecici!=NULL)
        {
           
            strcpy(yazdir->ad,gecici->ad);
            strcpy(yazdir->kategori,gecici->kategori);
            yazdir->stok=gecici->stok;
            yazdir->fiyat=gecici->fiyat;
            yazdir->urunKodu=gecici->urunKodu;
            yazdir->sonraki=NULL;
            yazdir->onceki=NULL;
            if(fwrite(yazdir,sizeof(urun),1,dosya)!=1){
                printf("Dosyaya yazilamadi\n");
                fclose(dosya);
                return;
            }
            gecici=gecici->sonraki; 
        }
            fclose(dosya);
    }

    break;
    case 2:
    printf("Kayit yapilmadi\n");
    break;
    default:
    printf("Hatali secim yaptiniz\n");
    break;
}
  
};
void dosyadan_urun_ekle(urun** urun_head,urun** urun_tail,int urunKodu, const char* ad, const char* kategori, int stok, float fiyat)
{   

pthread_mutex_lock(&lock);
    urun *yeni_urun=(urun*)malloc(sizeof(urun));
    if (yeni_urun==NULL)
    {
        printf("Bellek tahsis edilemedi\n");
        return;
    }
    strcpy(yeni_urun->ad,ad);
    strcpy(yeni_urun->kategori,kategori);
    yeni_urun->stok=stok;
    yeni_urun->fiyat=fiyat;
    yeni_urun->urunKodu=urunKodu;
    yeni_urun->sonraki=NULL;
    yeni_urun->onceki=*urun_tail;

    if (*urun_tail!=NULL)
    {
        (*urun_tail)->sonraki=yeni_urun;
    }
    else
    {
        *urun_head=yeni_urun;
    }
   *urun_tail=yeni_urun;
    pthread_mutex_unlock(&lock);
}
void dosyadan_musteri_ekle(musteri** musteri_head,musteri** musteri_tail, const char* ad, const char* soyad, const char* telefon, float cari)
{  
pthread_mutex_lock(&lock);
    musteri *yeni_musteri=(musteri*)malloc(sizeof(musteri));
    if (yeni_musteri==NULL)
    {
        printf("Bellek tahsis edilemedi\n");
        return;
    }
    strcpy(yeni_musteri->ad,ad);
    strcpy(yeni_musteri->soyad,soyad);
    strcpy(yeni_musteri->telefon,telefon);
    yeni_musteri->cari=cari;
    yeni_musteri->sonraki=NULL;
    yeni_musteri->onceki=*musteri_tail;

    if (*musteri_tail!=NULL)
    {
        (*musteri_tail)->sonraki=yeni_musteri;
    }
    else
    {
        *musteri_head=yeni_musteri;
    }
   *musteri_tail=yeni_musteri;
    pthread_mutex_unlock(&lock); 
}
void dosyadan_satis_ekle(satis** satis_head,satis** satis_tail,int zaman, const char* urunAd, int adet, float toplam)
{pthread_mutex_lock(&lock);
    satis *yeni_satis=(satis*)malloc(sizeof(satis));
    if (yeni_satis==NULL)
    {
        printf("Bellek tahsis edilemedi\n");
        return;
    }
    yeni_satis->zaman=zaman;
    strcpy(yeni_satis->urunAd,urunAd);
    yeni_satis->adet=adet;
    yeni_satis->toplam=toplam;
    yeni_satis->sonraki=NULL;
    yeni_satis->onceki=*satis_tail;

    if (*satis_tail!=NULL)
    {
        (*satis_tail)->sonraki=yeni_satis;
    }
    else
    {
        *satis_head=yeni_satis;
    }
   *satis_tail=yeni_satis;
    pthread_mutex_unlock(&lock);

}

void *bastan_oku_musteri(void *arg)
{
    int kontrol;
    FILE *dosya = fopen("musteri.bin", "rb");
    if (dosya == NULL)
    {
        printf("Dosya acilamadi.\n");
        return NULL;
    }
    musterikontrolbas=NULL;
    musteri temp;
  
    while (fread(&temp, sizeof(musteri), 1, dosya)) 
    {
        dosyadan_musteri_ekle(&musteri_head, &musteri_tail, temp.ad, temp.soyad, temp.telefon, temp.cari);
         kontrol=musteri_kontrol();
    if (kontrol==0)
    {
        return NULL;
    }
        
        musterikontrolbas=musteri_tail;    }

    fclose(dosya);
    return NULL;
    
    }; 
void *sondan_oku_musteri(void *arg)
{
    int kontrol;
    FILE *dosya = fopen("musteri.bin", "rb");
    if (dosya == NULL)
    {
        printf("Dosya acilamadi.\n");
        return NULL;
    }
musterikontrolson=NULL;
    fseek(dosya, 0, SEEK_END);

    long pos = ftell(dosya);
    
    musteri temp;
   
    while (pos > 0)
    {
      
        pos -= sizeof(musteri); 
        fseek(dosya, pos, SEEK_SET);
        fread(&temp, sizeof(musteri), 1, dosya); 
        dosyadan_musteri_ekle(&musteri_head,&musteri_tail, temp.ad, temp.soyad, temp.telefon, temp.cari);
         kontrol=musteri_kontrol();
    if (kontrol==0)
    {
        return NULL;
    }
        musterikontrolson=musteri_tail;
    }

    fclose(dosya);
    return NULL;
};

void *bastan_oku_urun(void *arg)
{
    int kontrol;
    FILE *dosya = fopen("urun.bin", "rb");
    if (dosya == NULL)
    {
        printf("Dosya acilamadi.\n");
        return NULL;
    }
    urunkontrolbas=NULL;
    urun temp;
  
    while (fread(&temp, sizeof(urun), 1, dosya)) 
    {
        dosyadan_urun_ekle(&urun_head, &urun_tail, temp.urunKodu, temp.ad, temp.kategori, temp.stok, temp.fiyat);
         kontrol=urun_kontrol();
    if (kontrol==0)
    {
        return NULL;
    }
        
        urunkontrolbas=urun_tail;    }

    fclose(dosya);
    return NULL;
    
    };
void *sondan_oku_urun(void *arg)
{
    int kontrol;
    FILE *dosya = fopen("urun.bin", "rb");
    if (dosya == NULL)
    {
        printf("Dosya acilamadi.\n");
        return NULL;
    }
urunkontrolson=NULL;
    fseek(dosya, 0, SEEK_END);

    long pos = ftell(dosya);
    
    urun temp;
   
    while (pos > 0)
    {
      
        pos -= sizeof(urun); 
        fseek(dosya, pos, SEEK_SET);
        fread(&temp, sizeof(urun), 1, dosya); 
        dosyadan_urun_ekle(&urun_head,&urun_tail, temp.urunKodu, temp.ad, temp.kategori, temp.stok, temp.fiyat);
         kontrol=urun_kontrol();
    if (kontrol==0)
    {
        return NULL;
    }
        urunkontrolson=urun_tail;
    }

    fclose(dosya);
    return NULL;
};

void *bastan_oku_satis(void *arg)
{
    int kontrol;
    FILE *dosya = fopen("satis.bin", "rb");
    if (dosya == NULL)
    {
        printf("Dosya acilamadi.\n");
        return NULL;
    }
    satiskontrolbas=NULL;
    satis temp;
  
    while (fread(&temp, sizeof(satis), 1, dosya)) 
    {
        dosyadan_satis_ekle(&satis_head, &satis_tail, temp.zaman, temp.urunAd, temp.adet, temp.toplam);
         kontrol=satis_kontrol();
    if (kontrol==0)
    {
        return NULL;
    }
        
        satiskontrolbas=satis_tail;    }

    fclose(dosya);
    return NULL;
    
    };
void *sondan_oku_satis(void *arg)
{
    int kontrol;
    FILE *dosya = fopen("satis.bin", "rb");
    if (dosya == NULL)
    {
        printf("Dosya acilamadi.\n");
        return NULL;
    }
satiskontrolson=NULL;
    fseek(dosya, 0, SEEK_END);

    long pos = ftell(dosya);
    
    satis temp;
   
    while (pos > 0)
    {
      
        pos -= sizeof(satis); 
        fseek(dosya, pos, SEEK_SET);
        fread(&temp, sizeof(satis), 1, dosya); 
        dosyadan_satis_ekle(&satis_head,&satis_tail, temp.zaman, temp.urunAd, temp.adet, temp.toplam);
         kontrol=satis_kontrol();
    if (kontrol==0)
    {
        return NULL;
    }
        satiskontrolson=satis_tail;
    }

    fclose(dosya);
    return NULL;
};



//urun islemleri
void *bastan_ara_urun(void *arg)
{
    struct aranacak *hedef = (struct aranacak *)arg;
    urun *gecici = urun_head;
    while (gecici != NULL)
    {
         pthread_mutex_lock(&lock); 
         if (kontrolurun==true)
         {
             pthread_mutex_unlock(&lock);
             return NULL;
         }
        if (strcmp(gecici->ad, hedef->ad) == 0)
        {
            kontrolurun=true;
            sonucurun = gecici;
            pthread_mutex_unlock(&lock);  
            return NULL;
        }
        gecici = gecici->sonraki;
        pthread_mutex_unlock(&lock);
    }
};
void *sondan_ara_urun(void *arg){
    struct aranacak *hedef = (struct aranacak *)arg;
    urun *gecici = urun_tail;

    while (gecici != NULL)
    {
        pthread_mutex_lock(&lock);
        if (kontrolurun==true)
        {
            pthread_mutex_unlock(&lock);
            return NULL;
        }
        if (strcmp(gecici->ad, hedef->ad) == 0)
        {
            kontrolurun=true;
            sonucurun = gecici;
            gecici=NULL;
            pthread_mutex_unlock(&lock);
            return NULL;
        }
        gecici = gecici->onceki;
        pthread_mutex_unlock(&lock);
    }   
};
void urun_ara(char ad[50]){
    sonucurun=NULL;
    kontrolurun=false;

    struct aranacak hedef;
    strcpy(hedef.ad, ad);
        pthread_t thread1, thread2;
    pthread_mutex_init(&lock,NULL);
    pthread_create(&thread1, NULL, bastan_ara_urun, &hedef);
    pthread_create(&thread2, NULL, sondan_ara_urun, &hedef);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&lock);

    return;
};
void urun_ara_menu(){
    char ad[50];
    
    printf("\n==============================================================\n");
    printf("\t\tUrun arama islemi\n");
    printf("\n==============================================================\n");
    printf("Urun adini giriniz:");
    scanf("%s", ad);
    printf("\n==============================================================\n");
    urun_ara(ad);
    sleep(2);
    if (sonucurun!=NULL)
    {
        system("clear");
        printf("\n==============================================================\n");
        printf("\tUrun bulundu!\n");
        printf("\n==============================================================\n");
        printf("Ad: %s\n", sonucurun->ad);
        printf("Kategori: %s\n", sonucurun->kategori);
        printf("Stok: %d\n", sonucurun->stok);
        printf("Fiyat: %f\n", sonucurun->fiyat);
        printf("Urun kodu: %d\n", sonucurun->urunKodu);
        printf("\n==============================================================\n");
        printf("Devam etmek icin entera basiniz\n");
        printf("\n==============================================================\n");
        getchar();
        getchar();
    }
    else
    {
        printf("\n==============================================================\n");
        printf("Urun bulunamadi\n");
        printf("\n==============================================================\n");
        sleep(1);
    }


    
};

void urun_sil(){
printf("\n==============================================================\n");
printf("silmek istediginiz urunun adini giriniz:");
char ad[50];
  int secim;
scanf("%s", ad);
urun_ara(ad);
if (sonucurun!=NULL){
    system("clear");
    printf("\n==============================================================\n");
    printf("\tUrun bulundu\n");
    printf("\n==============================================================\n");
    printf("Ad: %s\n", sonucurun->ad);
    printf("Kategori: %s\n", sonucurun->kategori);
    printf("Stok: %d\n", sonucurun->stok);
    printf("Fiyat: %f\n", sonucurun->fiyat);
    printf("Urun kodu: %d\n", sonucurun->urunKodu);
    printf("\n==============================================================\n");
    printf("Silmek istediginiz urun bu mu?\n");
    printf("1-Evet\n");
    printf("2-Hayir\n");
    printf("\n==============================================================\n");
  
    do {
         printf("\tSeciminizi yapiniz:");
         scanf("%d", &secim);
        switch(secim)
        {
            case 1:
            if (sonucurun->onceki==NULL&&sonucurun->sonraki==NULL)
            {
                urun_head=NULL;
                urun_tail=NULL;
                sonucurun=NULL;
            }
            else if (sonucurun->onceki==NULL&&sonucurun->sonraki!=NULL)
            {
                urun_head=sonucurun->sonraki;
                sonucurun->sonraki->onceki=NULL;
                if (sonucurun->sonraki==NULL)
                {
                    urun_tail=NULL;
                }
                sonucurun=NULL;
            }
            else if (sonucurun->onceki!=NULL&&sonucurun->sonraki==NULL)
            {
                urun_tail=sonucurun->onceki;
                sonucurun->onceki->sonraki=NULL;
                sonucurun=NULL;
            }
            else
            {
                sonucurun->onceki->sonraki=sonucurun->sonraki;
                sonucurun->sonraki->onceki=sonucurun->onceki;
                sonucurun=NULL;
            }
            printf("Urun silindi\n");
            printf("\n==============================================================\n");
            break;
            case 2:
            printf("Urun silinmedi\n");
            break;
            default:
            printf("Hatali secim yaptiniz\n");
            break;
            printf("\n==============================================================\n");
            sleep(2);
        }
        break;
    }

    while(secim!=2&&secim!=1);
}
else
{
    printf("Urun bulunamadi\n");
    sleep(1);
    printf("\n==============================================================\n");
}

            return;


};
  
void urun_guncelle(){
    printf("\n==============================================================\n");
    printf("Guncellemek istediginiz urun adini giriniz:"); 
    char ad[50];
    scanf("%s", ad);
    urun_ara(ad);
    if (sonucurun!=NULL)
    {
        printf("\n==============================================================\n");
        printf("\tUrun bulundu\n");
        printf("\n==============================================================\n");
        printf("Ad: %s\n", sonucurun->ad);
        printf("Kategori: %s\n", sonucurun->kategori);
        printf("Stok: %d\n", sonucurun->stok);
        printf("Fiyat: %f\n", sonucurun->fiyat);
        printf("Urun kodu: %d\n", sonucurun->urunKodu);
        printf("\n==============================================================\n");
        printf("Guncellemek istediginiz urun bu mu?\n");
        printf("1-Evet\n");
        printf("2-Hayir\n");
        printf("\tSeciminizi yapiniz:");
        int secim;
        scanf("%d", &secim);
        printf("\n==============================================================\n");
        do {
        switch(secim)
        {
            case 1:
            printf("Yeni urun adini giriniz:");
            scanf("%s", sonucurun->ad);
            printf("Yeni urun kategorisini giriniz:");
            scanf("%s", sonucurun->kategori);
            printf("Yeni urun stok miktarini giriniz:");
            scanf("%d", &sonucurun->stok);
            printf("Yeni urun fiyatini giriniz:");
            scanf("%f", &sonucurun->fiyat);
            printf("\n==============================================================\n");
            printf("Urun guncellendi\n");
            printf("\n==============================================================\n");
          sleep(1);
            break;
            case 2:
            printf("\n==============================================================\n");
            printf("Urun guncellenmedi\n");
            printf("\n==============================================================\n");
           sleep(1);
            break;
            default:
            printf("Hatali secim yaptiniz\n");
            break;
            printf("\n==============================================================\n");
            sleep(2);
        }
        }
        while(secim!=2&&secim!=1);
        return;
    }
    else
    {
        printf("\n==============================================================\n");
        printf("Urun bulunamadi\n");
        printf("\n==============================================================\n");
   sleep(1);
    }

    
};

void tumurunler(){
    urun *gecici=urun_head;
    if (gecici==NULL)
    {
        printf("Listede urun bulunmamaktadir\n");
        return;
    }
    while (gecici!=NULL)
    {
        printf("--------------------------------\n");
        printf("AD:%s\n",gecici->ad);
        printf("Kategori:%s\n",gecici->kategori);
        printf("Stok:%d\n",gecici->stok);
        printf("Fiyat:%f\n",gecici->fiyat);
        printf("Kod:%d\n",gecici->urunKodu);
        printf("--------------------------------\n");
        gecici=gecici->sonraki;
    }   
};


void* belirlikategoribastan(void *arg){
    struct aranacak *hedef = (struct aranacak *)arg;
    int kontrol;
    urun *gecici=urun_head;
    urunkontrolbas=NULL;
    if (gecici==NULL)
    {
        printf("Listede urun bulunmamaktadir\n");
        return NULL;
    }
    while (gecici!=NULL)
    {
        pthread_mutex_lock(&lock);
         if (urunkontrolbas==urunkontrolson){

        pthread_mutex_unlock(&lock);
        return NULL;
         }

            if (strcmp(gecici->kategori,hedef->kategori)==0)
            {
                printf("--------------------------------\n");
                printf("AD:%s\n",gecici->ad);
                printf("Kategori:%s\n",gecici->kategori);
                printf("Stok:%d\n",gecici->stok);
                printf("Fiyat:%f\n",gecici->fiyat);
                printf("Kod:%d\n",gecici->urunKodu);
                  urunkontrolbas=gecici;
            }
        
            gecici=gecici->sonraki;
          
            pthread_mutex_unlock(&lock);
    }
    
       
    };
void* belirlikategorisondan(void *arg){
    int kontrol;
    struct aranacak *hedef = (struct aranacak *)arg;
    urun *gecici=urun_tail;
    

    while (gecici!=NULL)
    {
          pthread_mutex_lock(&lock);
         if (urunkontrolbas==urunkontrolson){
        pthread_mutex_unlock(&lock);
        return NULL;
       
         }
       
        
        if (strcmp(gecici->kategori,hedef->kategori)==0)
        {

            printf("--------------------------------\n");
            printf("AD:%s\n",gecici->ad);
            printf("Kategori:%s\n",gecici->kategori);
            printf("Stok:%d\n",gecici->stok);
            printf("Fiyat:%f\n",gecici->fiyat);
            printf("Kod:%d\n",gecici->urunKodu);
              urunkontrolson=gecici;
        }
    
        gecici=gecici->onceki;
      

        pthread_mutex_unlock(&lock);
       
   
    }
};
void belirlikategori(char kategori[50]){
    struct aranacak hedef;
    strcpy(hedef.kategori, kategori);
    pthread_t thread1, thread2;
    pthread_mutex_init(&lock,NULL);
    pthread_create(&thread1, NULL, belirlikategorisondan, &hedef);
    pthread_create(&thread2, NULL, belirlikategoribastan, &hedef);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&lock);
    return;
};
void urun_son_oku(){
    urun *gecici=urun_tail;
    if (gecici==NULL)
    {
        printf("Listede urun bulunmamaktadir\n");
        return;
    }
    while (gecici!=NULL)
    {
        printf("%s\n",gecici->ad);
        printf("%s\n",gecici->kategori);
        printf("%d\n",gecici->stok);
        printf("%f\n",gecici->fiyat);
        printf("%d\n",gecici->urunKodu);
        gecici=gecici->onceki;
    }   

};
void urun_bas_oku(){
    urun *gecici=urun_head;
    if (gecici==NULL)
    {
        printf("Listede urun bulunmamaktadir\n");
        return;
    }
    while (gecici!=NULL)
    {
        printf("%s\n",gecici->ad);
        printf("%s\n",gecici->kategori);
        printf("%d\n",gecici->stok);
        printf("%f\n",gecici->fiyat);
        printf("%d\n",gecici->urunKodu);
        gecici=gecici->sonraki;
    }   
      
};
void *liste_turunu_bastan_oku(){

urun* gecici=urun_head;
urunkontrolbas=urun_head;
while (gecici!=NULL)
{
    pthread_mutex_lock(&lock);
    if(urunkontrolbas!=urunkontrolson){

        if (gecici->onceki!=NULL&& strcmp(gecici->kategori,gecici->onceki->kategori)!=0)
        {
            printf("%s\n",gecici->kategori);
            printf("--------------------------------\n");
            urunkontrolbas=gecici;
        }
        else if (gecici->onceki==NULL)
        {
            printf("%s\n",gecici->kategori);
            printf("--------------------------------\n");
            urunkontrolbas=gecici;
        }
       
    }
    gecici=gecici->sonraki;
    pthread_mutex_unlock(&lock);

}
};
void *liste_turunu_sondan_oku(){
   urun* gecici=urun_tail;
   urunkontrolson=urun_tail;

while (gecici!=NULL)
{
    pthread_mutex_lock(&lock);
    
    if(urunkontrolbas!=urunkontrolson){

        if (gecici->sonraki!=NULL&& strcmp(gecici->kategori,gecici->sonraki->kategori)!=0)
        {
            printf("%s\n",gecici->kategori);
            printf("--------------------------------\n");
            urunkontrolson=gecici;
        }
        else if (gecici->sonraki==NULL)
        {
            printf("%s\n",gecici->kategori);
            printf("--------------------------------\n");
            urunkontrolson=gecici;
        }
       
    }
    gecici=gecici->onceki;
    pthread_mutex_unlock(&lock);
}
};
void kategori_listele(){
    pthread_t thread1, thread2;
    pthread_mutex_init(&lock,NULL);
    pthread_create(&thread1, NULL, liste_turunu_sondan_oku, NULL);
    pthread_create(&thread2, NULL, liste_turunu_bastan_oku, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&lock);
    return;
};

void urun_listele_menu(){
   char kategori[50];
   system("clear");
    printf("\n==============================================================\n");
    printf("\tUrun listeleme islemi\n");
    printf("\n==============================================================\n");
    printf("Kayitli kategoriler:\n");
    printf("\n==============================================================\n");
    if(urun_head!=NULL){
        kategori_listele();
    printf("\n==============================================================\n");
    printf("Tum urunleri listelemek isterseniz 'hepsi' yaziniz\n");
    printf("Kategori seciniz:");
    scanf("%s", kategori);
    printf("\n==============================================================\n");
   if (strcmp(kategori,"hepsi")==0){
   tumurunler();
   printf("\n==============================================================\n");
   printf("Devam etmek icin entera basiniz\n");
    printf("\n==============================================================\n");
    getchar();
    getchar();
   }
   else
   {
       belirlikategori(kategori);
         printf("\n==============================================================\n");
    printf("Devam etmek icin entera basiniz\n");
    printf("\n==============================================================\n");
    getchar();
    getchar();
   }
    }
    else
    {
        printf("\n==============================================================\n");
        printf("Listede urun bulunmamaktadir\n");
        printf("Lutfen urun ekleyiniz\n");
        printf("\n==============================================================\n");
        printf("Devam etmek icin entera basiniz\n");
        printf("\n==============================================================\n");
        getchar();
        getchar();
    }
};
void urun_ekle(){
    printf("\n==============================================================\n");
    printf("\tKac adet urun eklemek istiyorsunuz?\n");
    int adet;
    char ad[50];
    char kategori[50];
    printf("\tAdet giriniz:");
    scanf("%d", &adet);
    printf("\n==============================================================\n");
    for (int i = 0; i < adet; i++)
    {
         urun *yeni_urun = (urun *)malloc(sizeof(urun));
            if (yeni_urun==NULL)
            {
                printf("Bellek tahsis edilemedi\n");
                return;
            }
            printf("Urun adini giriniz:");
            scanf("%s", yeni_urun->ad);
            strcpy(ad,yeni_urun->ad);
            urun_ara(ad);
            if (sonucurun!=NULL)
            {
                printf("\n==============================================================\n");
                printf("Bu isimde bir urun zaten var\n");
                printf("\n==============================================================\n");
                i--;
                sleep(1);
                return;
            }
            printf("Urun kategorisini giriniz:");
            scanf("%s", yeni_urun->kategori);
            printf("Urun stok miktarini giriniz:");
            scanf("%d", &yeni_urun->stok);
            printf("Urun fiyatini giriniz:");
            scanf("%f", &yeni_urun->fiyat);
            printf("Urun kodunu giriniz:");
            scanf("%d", &yeni_urun->urunKodu);
            printf("Urun eklendi\n");
            printf("\n====================================\n");
            yeni_urun->sonraki=NULL;
            yeni_urun->onceki=urun_tail;
            if (urun_tail!=NULL)
            {
                urun_tail->sonraki=yeni_urun;
            }
            else
            {
                urun_head=yeni_urun;
            }
            urun_tail=yeni_urun;
            printf("\n==============================================================\n");
            printf("Urun eklendi\n");
            printf("\n==============================================================\n");
            sleep(1);
            system("clear");
            printf("\n==============================================================\n");
    }
};

//musteri islemleri

void *bastan_ara_musteri(void *arg)
{
    struct aranacak *hedef = (struct aranacak *)arg;
    musteri *gecici = musteri_head;

    if (gecici == NULL)
    {
      
        return NULL;
    }

    while (gecici != NULL)
    {
         pthread_mutex_lock(&lock); 
         if (kontrolmusteri==true)
         {
             pthread_mutex_unlock(&lock);
             return NULL;
         }
        if (strcmp(gecici->ad, hedef->ad) == 0 && strcmp(gecici->soyad, hedef->soyad) == 0)
        {
            kontrolmusteri=true;
            sonucmusteri = gecici;
            pthread_mutex_unlock(&lock);  
            return NULL;
        }
        gecici = gecici->sonraki;
        pthread_mutex_unlock(&lock);
    }
}
 
void *sondan_ara_musteri(void *arg)
{
    struct aranacak *hedef = (struct aranacak *)arg;
    musteri *gecici = musteri_tail;

    if (gecici == NULL)
    {
       
        return NULL;
    }

    while (gecici != NULL)
    {
        pthread_mutex_lock(&lock);
        if (kontrolmusteri==true)
        {
            pthread_mutex_unlock(&lock);
            return NULL;
        }
        if (strcmp(gecici->ad, hedef->ad) == 0 && strcmp(gecici->soyad, hedef->soyad) == 0)
        {
            kontrolmusteri=true;
            sonucmusteri = gecici;
            gecici=NULL;
            pthread_mutex_unlock(&lock);
            return NULL;
        }
        gecici = gecici->onceki;
        pthread_mutex_unlock(&lock);
    }   
}
            
void musteri_ara(char ad[50], char soyad[50]){
   


    sonucmusteri=NULL;
    kontrolmusteri=false;

    struct aranacak hedef;
    strcpy(hedef.ad, ad);
    strcpy(hedef.soyad, soyad);

        pthread_t thread1, thread2;
    pthread_mutex_init(&lock,NULL);
    pthread_create(&thread1, NULL, bastan_ara_musteri, &hedef);
    pthread_create(&thread2, NULL, sondan_ara_musteri, &hedef);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&lock);

    return;


    
}

void musteri_ara_menu(){
    char ad[50];
    char soyad[50];
    system("clear");
    printf("\n==============================================================\n");
    printf("\tMusteri arama islemi\n");
    printf("\n==============================================================\n");
    printf("Musteri adini giriniz:");
    scanf("%s", ad);
    printf("Musteri soyadini giriniz:");
    scanf("%s", soyad);
    printf("\n==============================================================\n");
    musteri_ara(ad,soyad);
    sleep(2);
    if (sonucmusteri!=NULL)
    {
        system("clear");
        printf("\n==============================================================\n");
        printf("\tMusteri bulundu!\n");
        printf("\n==============================================================\n");
        printf("Ad: %s\n", sonucmusteri->ad);
        printf("Soyad: %s\n", sonucmusteri->soyad);
        printf("Telefon: %s\n", sonucmusteri->telefon);
        printf("Cari: %f\n", sonucmusteri->cari);
        printf("\n==============================================================\n");
        printf("\tDevam etmek icin entera basiniz\n");
        printf("\n==============================================================\n");
        getchar();
        getchar();
    }
    else
    {
        printf("Musteri bulunamadi\n");
        printf("\n==============================================================\n");
        sleep(2);
    }


    
};



void musteri_ekle(){
    int adet;
    char ad[50];
    char soyad[50];
    printf("\n==============================================================\n");
    printf("\tKac adet musteri eklemek istiyorsunuz?\n");
    printf("\tAdet:");
    scanf("%d", &adet);
    printf("\n==============================================================\n");
for (int i = 0; i < adet; i++)
 {
        musteri *yeni_musteri = (musteri *)malloc(sizeof(musteri));
        if (yeni_musteri == NULL)
        {
            printf("Bellek tahsis edilemedi\n");
            return;
        }

        printf("Musteri adini giriniz:");
        scanf("%s", yeni_musteri->ad);
        printf("Musteri soyadini giriniz:");
        scanf("%s", yeni_musteri->soyad);
        strcpy(ad,yeni_musteri->ad);    
        strcpy(soyad,yeni_musteri->soyad);
        musteri_ara(ad,soyad);
        if (sonucmusteri!=NULL)
        {
            system("clear");
            printf("\n==============================================================\n");
            printf("\tBu isimde bir musteri zaten var!\n");
            printf("\n==============================================================\n");
            i--;
            sleep(1);

            return;
        }
        printf("Musteri telefonunu giriniz:");
        scanf("%s", yeni_musteri->telefon);
        printf("Musteri cari hesabini giriniz:");
        scanf("%f", &yeni_musteri->cari);
      
        yeni_musteri->sonraki = NULL;
        yeni_musteri->onceki = musteri_tail;
        if (musteri_tail != NULL)
        {
            musteri_tail->sonraki = yeni_musteri;
            
        }
        else
        {
            musteri_head = yeni_musteri;
            
        }
        musteri_tail = yeni_musteri;
        printf("\n==============================================================\n");
        printf("\tMusteri eklendi\n");
        printf("\n==============================================================\n");
        sleep(1);
        system("clear");
        printf("\n==============================================================\n");
 }   
};
void musteri_listele(){

system("clear");
    printf("\n==============================================================\n");
    printf("\tMusteri listesi\n");
    printf("\n==============================================================\n");
    musteri *gecici=musteri_head;
    if (gecici==NULL)
    {
        printf("Listede musteri bulunmamaktadir\n");
        return;
    }
    while (gecici!=NULL)
    {
        printf("==================================================\n");
        printf("Ad: %s\n", gecici->ad);
        printf("Soyad: %s\n", gecici->soyad);
        printf("Telefon: %s\n", gecici->telefon);
        printf("Cari: %f\n", gecici->cari);
        printf("==================================================\n");
        gecici=gecici->sonraki;
    }
    printf("\n==============================================================\n");
    printf("\tDevam etmek icin entera basiniz\n");
    printf("\n==============================================================\n");
    getchar();
    getchar();
    
    return;

 
};
void musteri_sil(){
   int secim;
   printf("\n==============================================================\n");
   printf("Musteri adini giriniz:");
   char ad[50];
    scanf("%s", ad);
    printf("Musteri soyadini giriniz:");
    char soyad[50];
    scanf("%s", soyad);
    musteri_ara(ad,soyad);
    if (sonucmusteri!=NULL)
    {
    system("clear");
    printf("\n==============================================================\n");
    printf("Musteri bilgileri\n");
    printf("Ad: %s\n", sonucmusteri->ad);
    printf("Soyad: %s\n", sonucmusteri->soyad);
    printf("Telefon: %s\n", sonucmusteri->telefon);
    printf("Cari: %f\n", sonucmusteri->cari);
    printf("\n==============================================================\n");
    printf("Silmek istediğiniz musteri bu mu?\n");
    printf("1-Evet\n");
    printf("2-Hayir\n");
    printf("\n==============================================================\n");

    do {
    printf("\tSeciminizi yapiniz:");
    scanf("%d", &secim);
    printf("\n==============================================================\n");
        switch(secim)
        {
            case 1:
            if (sonucmusteri->onceki==NULL && sonucmusteri->sonraki==NULL)
            {
                musteri_head=NULL;
                musteri_tail=NULL;
                sonucmusteri=NULL;
            }
           else if (sonucmusteri->onceki==NULL && sonucmusteri->sonraki!=NULL)
            {
                musteri_head=sonucmusteri->sonraki;
                sonucmusteri->sonraki->onceki=NULL;
                if (sonucmusteri->sonraki==NULL)
                {
                    musteri_tail=NULL;
                }

                sonucmusteri=NULL;
            }
            else if (sonucmusteri->onceki!=NULL && sonucmusteri->sonraki==NULL)
            {
                musteri_tail=sonucmusteri->onceki;
                sonucmusteri->onceki->sonraki=NULL;
                sonucmusteri=NULL;
            }
            else
            {
                sonucmusteri->onceki->sonraki=sonucmusteri->sonraki;
                sonucmusteri->sonraki->onceki=sonucmusteri->onceki;
                sonucmusteri=NULL;
            }
            printf("Musteri silindi\n");
            break;;
            case 2:
            printf("Musteri silinmedi\n");
            break;
            default:
            printf("Hatali secim yaptiniz\n");
            break;
            printf("\n==============================================================\n");
          
        }
        break;
        
    }
    while (secim!=1 && secim!=2);
    }
    else
    {
        printf("Musteri bulunamadi\n");
        sleep(1);
        printf("\n==============================================================\n");
    }
    return;

};
void musteri_guncelle(){
    printf("\n==============================================================\n");
    printf("Musteri adini giriniz:");
    char ad[50];
    scanf("%s", ad);
    printf("Musteri soyadini giriniz:");
    char soyad[50];
    scanf("%s", soyad);
    musteri_ara(ad,soyad);
   if (sonucmusteri!=NULL)
    {
    printf("\n==============================================================\n");   
    printf("Musteri bilgileri\n");
    printf("Ad: %s\n", sonucmusteri->ad);
    printf("Soyad: %s\n", sonucmusteri->soyad);
    printf("Telefon: %s\n", sonucmusteri->telefon);
    printf("Cari: %f\n", sonucmusteri->cari);
    printf("Guncellemek istediginiz musteri bu mu?\n");
    printf("1-Evet\n");
    printf("2-Hayir\n");
    printf("\tSeciminizi yapiniz:");

    int secim;
    scanf("%d", &secim);
    printf("\n==============================================================\n");
    do {
    switch(secim)
    {
        case 1:
        printf("Musteri adini giriniz:");
        scanf("%s", sonucmusteri->ad);
        printf("Musteri soyadini giriniz:");
        scanf("%s", sonucmusteri->soyad);
        printf("Musteri telefonunu giriniz:");
        scanf("%s", sonucmusteri->telefon);
        printf("Musteri cari hesabini giriniz:");
        scanf("%f", &sonucmusteri->cari);
        printf("Musteri guncellendi\n");
        break;
        case 2:
                    printf("\n==============================================================\n");

        printf("Musteri guncellenmedi\n");
                   
                 printf("\n==============================================================\n");
sleep(1);
        break;

        default:
        printf("Hatali secim yaptiniz\n");
        break;
        printf("\n==============================================================\n");
        sleep(2);
    }
    }
    while (secim!=1 && secim!=2);
    return;
    }
    else

    {
        printf("\n==============================================================\n");
        printf("Musteri bulunamadi\n");
        printf("\n==============================================================\n");
   sleep(1);
    }

};
    
   
 



//satis islemleri
void satis_ekle()
{

      int defa;
    int secim;
   
    printf("\n==============================================================\n");   
    printf("Kac adet urun satisi yapmak istiyorsunuz?\n");
    printf("\tAdet:");
     scanf("%d", &defa);
    printf("\n==============================================================\n");
  
    for (int i = 0; i < defa; i++)
    {
        printf("Urun adini giriniz:");
        char ad[50];
        scanf("%s", ad);
        urun_ara(ad);

        if (sonucurun!=NULL){
            system("clear");
            printf("\n==============================================================\n");
            printf("\n--------------------------------------------------------------\n");
            printf("\tUrun bilgileri\n");
            printf("\n--------------------------------------------------------------\n");
            printf("Ad: %s\n", sonucurun->ad);
            printf("Kategori: %s\n", sonucurun->kategori);
            printf("Stok: %d\n", sonucurun->stok);
            printf("Fiyat: %f\n", sonucurun->fiyat);
            printf("Urun kodu: %d\n", sonucurun->urunKodu);
        printf("\n==============================================================\n");
        printf("Satis yapmak istediginiz urun bu mu?\n");
        printf("1-Evet\n");
        printf("2-Hayir\n");
        printf("\n==============================================================\n");
        printf("\tSeciminizi yapiniz:");
        scanf("%d", &secim);
        printf("\n==============================================================\n");
        switch(secim)
        {
            case 1:
            printf("Bu urunden kaç adet satmak istiyorsunuz?\n");
            printf("\tAdet:");
            int adet;
            scanf("%d", &adet);
            if (adet>sonucurun->stok)
            {
                system("clear");
                printf("\n==============================================================\n");
                printf("Stokta yeterli urun bulunmamaktadir\n");
                printf("\n==============================================================\n");
                sleep(1);
                return;
            }
           sonucurun->stok-=adet;
            satis *yeni_satis = (satis *)malloc(sizeof(satis));
            if (yeni_satis==NULL)
            {
                printf("Bellek tahsis edilemedi\n");
                return;
            }
            yeni_satis->zaman=time(NULL);
            strcpy(yeni_satis->urunAd, sonucurun->ad);
            yeni_satis->adet=adet;
            yeni_satis->toplam=adet*sonucurun->fiyat;
            yeni_satis->sonraki=NULL;
            yeni_satis->onceki=satis_tail;
            if (satis_tail!=NULL)
            {
                satis_tail->sonraki=yeni_satis;
            }
            else
            {
                satis_head=yeni_satis;
            }
            satis_tail=yeni_satis;
            printf("\n==============================================================\n");
            printf("Satis yapildi\n");
            printf("\n==============================================================\n");
            sleep(1);
            break;
            case 2:
            printf("\n==============================================================\n");
            printf("Satis yapilmadi\n");
            printf("\n==============================================================\n");
            break;
            default:
            printf("\n==============================================================\n");
            printf("Hatali secim yaptiniz\n");
            printf("\n==============================================================\n");
            break;
            printf("\n==============================================================\n");
            sleep(2);
        
           
           
        }
        
        }
        else
        {
            printf("Urun bulunamadi\n");
            printf("\n==============================================================\n");
            sleep(1);
        }
    }
};
void yazdir_tarih(time_t zaman) {
    struct tm *tm_info;
    char buffer[26];
    
    tm_info = localtime(&zaman);
    if (tm_info != NULL) {
        strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
        printf("%s", buffer);
    } else {
        printf("Geçersiz zaman verisi\n");
    }
};

void sondan_gunluk_rapor_yaz(){
time_t t = time(NULL);
    satis* gecici=satis_tail;
    if (gecici==NULL)
    {
        printf("Listede satis bulunmamaktadir\n");
        return;
    }
    while (gecici!=NULL)
    {
        if (t-gecici->zaman<=86400)
        {
            printf("--------------------------------\n");
            printf("Urun adi:%s\n",gecici->urunAd);
            printf("Adet:%d\n",gecici->adet);
            printf("Toplam:%f\n",gecici->toplam);
            printf("Zaman:");
            yazdir_tarih(gecici->zaman);
            printf("--------------------------------\n");
        }
        gecici=gecici->onceki;
    }
};
void gunluk_rapor(){
    printf("\n==============================================================\n");
    printf("\t\tGUNLUK RAPOR\n");
    printf("\n==============================================================\n");
    sondan_gunluk_rapor_yaz();
    printf("\n==============================================================\n");
    printf("Rapor basariyla olusturuldu\n");
    printf("\n==============================================================\n");
    sleep(2);
    printf("\n==============================================================\n");
    printf("Devam etmek icin entera basiniz\n");
    printf("\n==============================================================\n");
    getchar();
    getchar();


};



void ciro_rapor(){
    satis* gecici=satis_head;
    float ciro=0;
    if (gecici==NULL)
    {
        printf("Listede satis bulunmamaktadir\n");
        return;
    }
    while (gecici!=NULL)
    {
        ciro+=gecici->toplam;
        gecici=gecici->sonraki;
    }
    printf("Cironuz : %f\n",ciro);
    printf("\n==============================================================\n");
    printf("Devam etmek icin entera basiniz\n");
    printf("\n==============================================================\n");
    getchar();
    getchar();

    return;
};
void cari_rapor(){
    musteri* gecici=musteri_head;
    float cari=0;
    if (gecici==NULL)
    {
        printf("Listede musteri bulunmamaktadir\n");
        return;
    }
    while (gecici!=NULL)
    {
        printf("--------------------------------\n");
        printf("Ad:%s\n",gecici->ad);
        printf("Soyad:%s\n",gecici->soyad);
        printf("Cari hesap:%f\n",gecici->cari);
        printf("--------------------------------\n");
        cari+=gecici->cari;
        gecici=gecici->sonraki;
    }
    printf("Cari hesaplarinizin toplami : %f\n",cari);
    printf("\n==============================================================\n");
    printf("Devam etmek icin entera basiniz\n");
    printf("\n==============================================================\n");
    getchar();
    getchar();
    return;
};



void sec_fonk() {
    int secim;
    while (1) {
        printf("\tBu islem veri kaybina sebep olabilir\n");
        printf("\tDevam etmek istiyor musunuz ?\n");
        printf("\t1-Evet\n");
        printf("\t2-Hayir\n");
        printf("\n==============================================================\n");
        printf("\tSeciminizi yapiniz : ");
        if (scanf("%d", &secim) != 1) {
          
            while (getchar() != '\n'); 
            printf("\n==============================================================\n");
            printf("\tGeçersiz giriş. Lütfen bir sayı girin.\n");
            printf("\n==============================================================\n");
            continue;
        }

        switch (secim) {
            case 1:
                return;  
            case 2:
            system("clear");
                printf("\n==============================================================\n");
                printf("\tProgram kapatiliyor...");
                printf("\n==============================================================\n");
                sleep(1);
                exit(0);
            default:
             system("clear");
                printf("\n==============================================================\n");
                printf("\tHatali secim yaptiniz !\n");
                printf("\n==============================================================\n");
                sleep(1);
                break;
        }
    }
};
void dosya_kontrol(){

   
    

if (URUN_MEVCUT!=1)
{
system("clear");    printf("\n==============================================================\n");
printf("\tUrun bilgi dosyasi bulunamadi !\n");    printf("\n==============================================================\n");
sleep(2);
    printf("\n==============================================================\n");
printf("\tProgram icerisinde urun bilgi dosyasi olusturulacaktir.\n");
sec_fonk();

}
else 
{
    pthread_t thread1, thread2;
    pthread_mutex_init(&lock, NULL);
    pthread_create(&thread1, NULL, bastan_oku_urun, NULL);
    pthread_create(&thread2, NULL, sondan_oku_urun, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_mutex_destroy(&lock);
    printf("\n==============================================================\n");
    printf("\tUrun bilgileri basariyla okundu\n");
    printf("\n==============================================================\n");
    sleep(1);

}










if (MUSTERI_MEVCUT!=1)
{
system("clear");    printf("\n==============================================================\n");
printf("\tMusteri bilgi dosyasi bulunamadi !\n");    printf("\n==============================================================\n");
sleep(2);    printf("\n==============================================================\n");
printf("\tProgram icerisinde musteri bilgi dosyasi olusturulacaktir.\n");
sec_fonk();
}
else
{
    pthread_t thread1, thread2;
    pthread_mutex_init(&lock, NULL);
    pthread_create(&thread1, NULL, bastan_oku_musteri, NULL);
    pthread_create(&thread2, NULL, sondan_oku_musteri, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_mutex_destroy(&lock);
    printf("\n==============================================================\n");
    printf("\tMusteri bilgileri basariyla okundu\n");
    printf("\n==============================================================\n");
    sleep(1);
}





if (SATIS_MEVCUT!=1)
{
system("clear");  
  printf("\n==============================================================\n");
printf("\t Satilan urun bilgi dosyasi bulunamadi !\n"); 
   printf("\n==============================================================\n");
sleep(2);   
 printf("\n==============================================================\n");
printf("\tProgram icerisinde satilan urun bilgi dosyasi olusturulacaktir.\n");
sec_fonk();
}
else
{
    pthread_t thread1, thread2;
    pthread_mutex_init(&lock, NULL);
    pthread_create(&thread1, NULL, bastan_oku_satis, NULL);
    pthread_create(&thread2, NULL, sondan_oku_satis, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_mutex_destroy(&lock);
    printf("\n==============================================================\n");
    printf("\tSatilan urun bilgileri basariyla okundu\n");
    printf("\n==============================================================\n");
    sleep(1);
}









};

//menu fonksiyonlari
void rapor_menu(){
     int secim;
    do{
        system("clear");
    printf("\n==============================================================\n");
    printf("\t\tRAPORLAR\n");
    printf("\n==============================================================\n");
    printf("\t1-Gunluk Rapor\n");
    printf("\t2-Ciro Rapor\n");
    printf("\t3-Cari Rapor\n");
    printf("\t4-Satis Kayit Kontrol\n");
    printf("\t5-Geri\n");
    printf("\n==============================================================\n");
    printf("\tSeciminizi yapiniz : ");
   
    scanf("%d",&secim);
   
    switch(secim)
    {
    case 1: gunluk_rapor(); break;
    case 2: ciro_rapor(); break;
    case 3: cari_rapor(); break;
    case 4: satis_kayit(&satis_head); break;
    case 5: printf("Geri donuluyor..."); break;
    default:
    //temizle
    printf("\n==============================================================\n");
    printf("\tHatali secim yaptiniz !\n");
    printf("\n==============================================================\n");
    sleep(1);
    break;
    }
    }
    while (secim!=5);
    return;
};
void musteri_menu(){

    int secim;
    do 
    {
    system("clear");
    printf("\n==============================================================\n");
    printf("\t\tMUSTERI MENU\n");
    printf("\n==============================================================\n");
    printf("\t1-Musteri Ekle\n");
    printf("\t2-Musteri Sil\n");
    printf("\t3-Musteri Guncelle\n");
    printf("\t4-Musteri Listele\n");
    printf("\t5-Musteri Ara\n");
    printf("\t6-Musteri Kayit Kontrol\n");
    printf("\t7-Geri\n");
    printf("\n==============================================================\n");
    printf("\tSeciminizi yapiniz : ");
    scanf("%d",&secim);
    switch(secim)
    {
    case 1: musteri_ekle(); break; 
    case 2: musteri_sil(); break; 
    case 3: musteri_guncelle(); break; 
    case 4: musteri_listele(); break; 
    case 5: musteri_ara_menu(); break;
    case 6: musteri_kayit(&musteri_head); break;
    case 7:
    printf("\n==============================================================\n");
    printf("\tGeri donuluyor...\n"); 
    printf("\n==============================================================\n");
    sleep(1);

    break;
    default:
    system("clear");
    printf("\n==============================================================\n");
    printf("\tHatali secim yaptiniz !\n");
    printf("\n==============================================================\n");
    sleep(1);
    break;
    }
    }
    while (secim!=7);
};
void satis_menu(){
    system("clear");
    char secim;
    printf("\n==============================================================\n");
    printf("\t\tSATIS MENU\n");
    printf("\n==============================================================\n");
    printf("\tUrunleri listelemek ister misiniz?\n");
    printf("\t\tE/H?\n");
    printf("\n==============================================================\n");
    printf("\n Seciminizi yapiniz : ");
    scanf("%s",&secim);
    if (strcmp(&secim,"E")==0 || strcmp(&secim,"e")==0)
    {
        urun_listele_menu();
    }
   satis_ekle();

    

    
    



};
void urun_menu(){ 
        int secim;
         do 
        {
        system("clear");
        printf("\n==============================================================\n");
        printf("\t\tURUN MENU\n");
        printf("\n==============================================================\n");
        printf("\t1-Urun Ekle\n");
        printf("\t2-Urun Sil\n");
        printf("\t3-Urun Guncelle\n");
        printf("\t4-Urun Listele\n");
        printf("\t5-Urun Ara\n");
        printf("\t6-Urun Kayit Kontrol\n");
        printf("\t7-Geri\n");
        printf("\n==============================================================\n");
        printf("\tSeciminizi yapiniz : ");
        scanf("%d",&secim);
       
        switch(secim)
        {
        case 1: urun_ekle(); break; 
        case 2: urun_sil(); break; 
        case 3: urun_guncelle(); break; 
        case 4: urun_listele_menu(); break; 
        case 5: urun_ara_menu(); break; 
        case 6: urun_kayit(&urun_head); break;
        case 7: 
        system("clear");
        printf("\n==============================================================\n");
        printf("\tGeri donuluyor..."); 
        printf("\n==============================================================\n");
        sleep(1);
        break;
        default:
        system("clear");
        printf("\n==============================================================\n");
        printf("\tHatali secim yaptiniz !\n");
        printf("\n==============================================================\n");
        sleep(1);
        break;
        }
        }
while (secim!=7);
        
};
int ana_menu(){
int secim;
do{
system("clear"); 
printf("\n==============================================================\n");
printf("\t\tANA MENU\n");
printf("\n==============================================================\n");
printf("\t1-Urun Islemleri\n");
printf("\t2-Musteri Islemleri\n");
printf("\t3-Satis Islemleri\n");
printf("\t4-Raporlar\n");
printf("\t5-Cikis\n");
printf("\n==============================================================\n");
printf("\tSeciminizi yapiniz : ");
scanf("%d",&secim);
}
while (secim!=5 && secim!=4 && secim!=3 && secim!=2 && secim!=1);
return secim;


};

void uyari_mesaji(){
    printf("\n==============================================================\n");
    printf("\t\tUYARI\n");
    printf("\n==============================================================\n");
    printf("\t Bu program halen prototip asamadadir!\n");
    printf("\t Programda hatalar olabilir.\n");
    printf("\t Programi kullanirken olusturdugunuz verileri menu seceneklerinden kaydetmeyi unutmayiniz.\n");
    printf("\t Programi kullanirken sizden istenen  turde(int,float,char) veri girmeniz gerekmektedir.\n");
    printf("\t Program ticari amaclar icin uygun degildir.\n");
    printf("\n==============================================================\n");
    printf("\tDevam etmek icin entera basiniz\n");
    printf("\n==============================================================\n");
    getchar();
    getchar();
    system("clear");
};
int main() 
{
int secim;

uyari_mesaji();
printf("\n==============================================================\n");
printf("\t\tRESTORAN OTOMASYONU\n");
printf("\t\t Hosgeldiniz\n"); 
printf("\n==============================================================\n");
sleep(1);   
printf("\n==============================================================\n");
printf("\tDosyalar Kontrol Ediliyor...\n");   
printf("\n==============================================================\n");
sleep(2);
dosya_kontrol();



do 
{
secim=ana_menu();
switch(secim)
{
case 1: urun_menu(); break;
case 2: musteri_menu(); break;
case 3: satis_menu(); break;
case 4: rapor_menu(); break;
case 5: printf ("\tDosya Kayitlari kontrol ediliyor.\n");
musteri_kayit(&musteri_head);
urun_kayit(&urun_head);
satis_kayit(&satis_head, &satis_tail);
printf("Programdan cikiliyor...");
sleep(1);
exit(0);
 break;
default:
//temizle  
printf("\n==============================================================\n");
printf("\tHatali secim yaptiniz !\n");           
printf("\n==============================================================\n");
sleep(1);
break;
}
}
while (secim!=5);


return 0;


};










