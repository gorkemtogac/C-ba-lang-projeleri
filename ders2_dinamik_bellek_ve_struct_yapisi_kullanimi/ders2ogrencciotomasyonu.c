#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

struct Ogrenci{
    char ad[20];
    char soyad[20];
    int numara;
    int vize;
    int final;
    int ortalama;
};
void yeni_kayit(int n, struct Ogrenci *ogrenciler[])

{
     system("clear");
    int i;
    for(i=0; i<n; i++)
    {
       printf("Ogrenci adini giriniz: ");
        scanf("%s", ogrenciler[i]->ad);
        printf("Ogrenci soyadini giriniz: ");
        scanf("%s", ogrenciler[i]->soyad);
        printf("Ogrenci numarasini giriniz: ");
        scanf("%d", &ogrenciler[i]->numara);
        printf("Ogrenci vize notunu giriniz: ");
        scanf("%d", &ogrenciler[i]->vize);
        printf("Ogrenci final notunu giriniz: ");
        scanf("%d", &ogrenciler[i]->final);
        if (ogrenciler[i]->vize < 0 || ogrenciler[i]->vize > 100 || ogrenciler[i]->final < 0 || ogrenciler[i]->final > 100)
        {
            printf("Hatali not girisi\n");
            continue;
        }
        ogrenciler[i]->ortalama = (ogrenciler[i]->vize + ogrenciler[i]->final) / 2;
        printf("Ogrenci eklendi\n");
        printf("**************************************************\n");
    }
        
}
void sil(int n, struct Ogrenci *ogrenciler[]) 
{
     system("clear");
    int i;
    int numara;
    printf("Silmek istediginiz ogrencinin numarasini giriniz: ");
    scanf("%d", &numara);
    for(i=0; i<n; i++)
    {
        if(numara == ogrenciler[i]->numara)
        {
            free(ogrenciler[i]);
            ogrenciler[i] = NULL;
            printf("Ogrenci silindi\n");
            break;
        }
    }
}
void guncelle(int n, struct Ogrenci *ogrenciler[])
{
     system("clear");
     int i;
    int numara;
    printf("Guncellemek istediginiz ogrencinin numarasini giriniz: ");
    scanf("%d", &numara);
    for(i=0; i<n; i++)
    {
        if(numara==ogrenciler[i]->numara)
        {
           printf("Ogrenci adini giriniz: ");
        scanf("%s", ogrenciler[i]->ad);
        printf("Ogrenci soyadini giriniz: ");
        scanf("%s", ogrenciler[i]->soyad);
        printf("Ogrenci numarasini giriniz: ");
        scanf("%d", &ogrenciler[i]->numara);
        printf("Ogrenci vize notunu giriniz: ");
        scanf("%d", &ogrenciler[i]->vize);
        printf("Ogrenci final notunu giriniz: ");
        scanf("%d", &ogrenciler[i]->final);
        ogrenciler[i]->ortalama = (ogrenciler[i]->vize + ogrenciler[i]->final) / 2;
        printf("Ogrenci guncellendi\n");
            break;
        }
    }
}
void listele(int n, struct Ogrenci *ogrenciler[])
{
    system("clear");
    int i=0;
    for(int i=0; i<n; i++)
    {
        if(ogrenciler[i] == NULL)
        {
            continue;
        }
        printf("Ogrenci adi: %s\n", ogrenciler[i]->ad);
        printf("Ogrenci soyadi: %s\n", ogrenciler[i]->soyad);
        printf("Ogrenci numarasi: %d\n", ogrenciler[i]->numara);
        printf("Ogrenci vize notu: %d\n", ogrenciler[i]->vize);
        printf("Ogrenci final notu: %d\n", ogrenciler[i]->final);
        printf("Ogrenci ortalama: %d\n", ogrenciler[i]->ortalama);
        printf("**************************************************\n");

    }
}
void ortalama(int n, struct Ogrenci *ogrenciler[])
{
    system("clear");
    int i;
    int toplam=0;
    for(i=0; i<n; i++)
    {   if(ogrenciler[i] == NULL)
        {
            continue;
        }
        toplam += ogrenciler[i]->ortalama;
    }
    printf("Sinifin ortalama notu: %d\n", toplam/n);
}
void en_basarili(int n, struct Ogrenci *ogrenciler[])
{
    system("clear");
    int i;
    int enBuyuk=0;
    for (i=0; i<n; i++)
    { 
        if (ogrenciler[i] != NULL && ogrenciler[i]->ortalama > enBuyuk)
        {
            enBuyuk = ogrenciler[i]->ortalama;
    
    printf("En basarili ogrencinin adi: %s\n", ogrenciler[i]->ad);
    printf("En basarili ogrencinin soyadi: %s\n", ogrenciler[i]->soyad);
    printf("En basarili ogrencinin numarasi: %d\n", ogrenciler[i]->numara);
    printf("En basarili ogrencinin vize notu: %d\n", ogrenciler[i]->vize);
    printf("En basarili ogrencinin final notu: %d\n", ogrenciler[i]->final);
    printf("En basarili ogrencinin ortalama: %d\n", ogrenciler[i]->ortalama);
     
        }
}
}
void cikis()
{ 
    system("clear");
    printf("Cikis yapiliyor\n");
    exit(0);
}
int menu()
         {
             int secim;
                printf("Seciminizi yapiniz:\n"); 
                printf("1. Ogrenci Ekle\n");
                printf("2. Ogrenci Sil\n");
                printf("3. Ogrenci Guncelle\n");
                printf("4. Ogrenci Listele\n");
                printf("5. Ortalama Hesapla\n");
                printf("6. En Basarili Ogrenci\n");
                printf("7. Cikis\n");
                scanf("%d", &secim);
                return secim;
                
    
    }
int main ()
{
    setlocale(LC_ALL, "Turkish");
    int n;
    int i;
     printf("Ogrenci takip programina hosgeldiniz\n");
     printf("Kayitli ogrenci sayisi =0\n");
     printf("Tek seferde kayit etmek istediginiz ogrenci sayisini giriniz:");
     scanf("%d", &n);
     struct Ogrenci *ogrenciler[n];
     
     for (int i=0; i<n; i++)
        {
            ogrenciler[i] = (struct Ogrenci*)malloc(sizeof(struct Ogrenci));
        }
 int secim;
   

   
 do
    {
        secim = menu();

        switch(secim)
        {
            case 1:
                yeni_kayit(n, ogrenciler);
                break;
            case 2:
                sil(n, ogrenciler);
                break;
            case 3:
                guncelle(n, ogrenciler);
                break;
            case 4:
                listele(n, ogrenciler);
                break;
            case 5:
                ortalama(n, ogrenciler);
                break;
            case 6:
                en_basarili(n, ogrenciler);
                break;
            case 7:
                cikis();
                break;
            default:
                printf("Hatali secim\n");
                break;
        }
    } while(secim != 7); 

    
    for(i=0; i<n; i++)
    {
        free(ogrenciler[i]);
    }
   
   return 0;
    }
 

