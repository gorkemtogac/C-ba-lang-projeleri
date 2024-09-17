#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>




int bakiye;
int menu()
{
system("cls");
int secim;

printf("MarmaraBank'a Hosgeldiniz\n");
printf("Bakiyeniz: %d\n",bakiye);
printf("Lutfen yapmak istediginiz islemi seciniz\n");
printf("1-Para Yatirma\n");
printf("2-Para Cekme\n");
printf("3-Havale Yapma\n");
printf("4-Borc Odeme\n");
printf("5-cikis\n");
scanf("%d",&secim);
return secim;
}
int paraYatirma()
{
    int yatirilacak;
    printf("Yatirmak istediginiz miktari giriniz\n");
    scanf("%d",&yatirilacak);
    bakiye+=yatirilacak;
    printf("Islem basarili, yeni bakiyeniz: %d\n",bakiye);
    printf("Ana menuye yonlendiriliyorsunuz\n");
    sleep(2);
    
}
int paraCekme()
{
    int cekilecek;
    printf("Cekmek istediginiz miktari giriniz\n");
    scanf("%d",&cekilecek);
    if(cekilecek>bakiye)
    {
        printf("Bakiyeniz yetersiz\n");
        sleep(2);
        return 0;
    }
    bakiye-=cekilecek;
    printf("Islem basarili, yeni bakiyeniz: %d\n",bakiye);
    sleep(2);
    printf("Ana menuye yonlendiriliyorsunuz\n");
}
int havaleYapma()
{
    int IBAN;
    int miktar;
    printf("Havale yapacaginiz IBAN numarasini giriniz\n");
    scanf("%d",&IBAN);
    printf("Havale yapacaginiz miktari giriniz\n");
    scanf("%d",&miktar);
    if(miktar>bakiye)
    {
        printf("Bakiyeniz yetersiz\n");
        sleep(2);
    }
    else
    {
        bakiye-=miktar;
        printf("Islem basarili, yeni bakiyeniz: %d\n",bakiye);
        sleep(2);
        printf("Ana menuye yonlendiriliyorsunuz\n");
    }
}

int borcOdeme()
{
    int secim2;
    printf("lutfen odemek istediginiz borcunuzu seciniz:\n");
    printf("1-Yemekhane Ucreti\n");
    printf("2- Yurt Odemesi\n");
    printf("3- Belge Ucreti\n");
    scanf("%d",&secim2);
    if (secim2<1 || secim2>3)
    {
        printf("Hatali secim yaptiniz, lutfen tekrar deneyiniz\n");
        sleep(2);
    }
    else
    {
        int odenecek;
        printf("Odemek istediginiz miktari giriniz\n");
        scanf("%d",&odenecek);
        if(odenecek>bakiye)
        {
            printf("Bakiyeniz yetersiz\n");
            sleep(2);
        }
        else
        {
            int fatura_numarasi;
            fatura_numarasi= rand()%10000;
            bakiye-=odenecek;
            printf("Islem basarili, yeni bakiyeniz: %d\n",bakiye);
            printf("Fatura numaraniz: %d\n",fatura_numarasi);
            sleep(2);
            printf("Ana menuye yonlendiriliyorsunuz\n");
        }
    } 
}    

int main ()

{
    int secim;
    bakiye= rand()%100000;
      while(1)
    {
        secim=menu();
            switch(secim)
            {
                case 1:
                    paraYatirma();
                    break;
                case 2:
                    paraCekme();
                    break;
                case 3:
                    havaleYapma();
                    break;
                case 4:
                    borcOdeme();
                    break;
                case 5:
                    printf("Cikis yapiliyor, kartinizi almayi unutmayiniz\n");
                    return 0;
                default:
                    printf("Hatali secim yaptiniz, lutfen tekrar deneyiniz\n");
            }

    }
        


    
}