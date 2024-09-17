//envanterkontroluygulaması.c

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct Urun {
    char ad[50];
    char tur[50];
    int adet;
    float fiyat;
    int urunKodu;
    struct Urun *sonraki;

}
urun;


void urun_ekle (urun **head){ 
    system("clear");

    int adet;
    char ad[50];
    int i=0;
    printf("kac adet urun eklemek istiyorsunuz?\n");
    printf("Adet: ");
    scanf("%d",&adet);
    for (i=0;i<adet;i++)
    {
    urun *yeni_urun=(urun*)malloc(sizeof(urun));
    printf("Urun adini giriniz:");
    scanf("%s",yeni_urun->ad);
    strcpy(ad, yeni_urun->ad);
    urun *bakilan=*head;
    while (bakilan!=NULL && strcmp(bakilan->ad,ad)!=0)
    {
        bakilan=bakilan->sonraki;
    }
    if (bakilan!=NULL)
    {
        printf("Bu isimde bir urun zaten var\n");
        printf("\n====================================\n");
        return;
    }
    printf("Urun turunu giriniz:");
    scanf("%s",yeni_urun->tur);
    printf("Urun adetini giriniz:");
    scanf("%d",&yeni_urun->adet);
    printf("Urun fiyatini giriniz:");
    scanf("%f",&yeni_urun->fiyat);
    printf("Urun kodunu giriniz:");
    scanf("%d",&yeni_urun->urunKodu);
    printf("Urun eklendi\n");
    printf("\n====================================\n");
    yeni_urun->sonraki=NULL;
    if (*head==NULL)
    {
        *head=yeni_urun;
    }
    else 
    {
        urun *gecici=*head;
        while (gecici->sonraki!=NULL)
        {
            gecici=gecici->sonraki;
        }
        gecici->sonraki=yeni_urun;

        
    }   
    }
   
         
    
    

}


void urun_sil (urun **head){
    system("clear");

    int urunKodu;
    printf("Silmek istediginiz urunun kodunu giriniz\n");
    printf("Urun kodu: ");
    scanf("%d",&urunKodu);
    urun *bakilan=*head;
    urun *onceki=NULL;
    while (bakilan!=NULL && bakilan->urunKodu!=urunKodu)
    {
        onceki=bakilan;
        bakilan=bakilan->sonraki;
    }
    if(bakilan==NULL) {
        printf("Urun bulunamadi\n");
        printf("\n====================================\n");

        return;

    }
    if (onceki==NULL)
    {
        *head=bakilan->sonraki;
    }
    else
    {
        onceki->sonraki=bakilan->sonraki;
    }
    free(bakilan);
    printf("Urun silindi\n");
    printf("\n====================================\n");

}




void urun_guncelle (urun **head){
    system("clear");

    int urunKodu;
    char ad[50];
    printf("Guncellemek istediginiz urunun kodunu giriniz\n");
    printf("Urun kodu: ");
    scanf("%d",&urunKodu);
    urun *bakilan=*head;
    while (bakilan!=NULL && bakilan->urunKodu!=urunKodu)
    {
        bakilan=bakilan->sonraki;
    }
    if(bakilan==NULL) {
        printf("Urun bulunamadi\n");
        return;

    }
    printf("Yeni ad giriniz\n");
    scanf("%s",ad);
    bakilan=*head;
    while (bakilan!=NULL && strcmp(bakilan->ad,ad)!=0)
    {
        bakilan=bakilan->sonraki;
    }
    if (bakilan!=NULL)
    {
        printf("Bu isimde bir urun zaten var\n");
        printf("\n====================================\n");
        return;
    }
    printf("Yeni tur giriniz\n");
    scanf("%s",bakilan->tur);
    printf("Yeni adet giriniz\n");
    scanf("%d",&bakilan->adet);
    printf("Yeni fiyat giriniz\n");
    scanf("%f",&bakilan->fiyat);
    printf("Urun guncellendi\n");
    printf("\n====================================\n");
}




void urun_listele (urun**head){
    system("clear");

printf ("Hangi turdeki urunleri listelemek istiyorsunuz\n");
printf ("Kayitli turler: \n");
urun *gecici=*head;
urun *onceki;
if (gecici==NULL)
{
    printf("Envanter bos! Lutfen urun ekleyiniz\n");
    printf("\n====================================\n");

    return;
}
while (gecici!=NULL)
{
    if (strcmp(gecici->tur,onceki->tur)!=0)
    {
        printf("%s\n",gecici->tur);
    }
    onceki=gecici;
    gecici=gecici->sonraki;
}
printf("Hepsini listelemek icin 'hepsi' yaziniz\n");
printf("Tur: ");

char tur[50];
scanf("%s",tur);
system("clear");
if (strcmp(tur,"hepsi")==0)
{
    urun *gecici2=*head;
    while (gecici2!=NULL)
    {
        printf("Urun adi: %s\n",gecici2->ad);
        printf("Urun turu: %s\n",gecici2->tur);
        printf("Urun adeti: %d\n",gecici2->adet);
        printf("Urun fiyati: %.2f\n",gecici2->fiyat);
        printf("Urun kodu: %d\n",gecici2->urunKodu);
        gecici2=gecici2->sonraki;
        printf("\n====================================\n");
    }
    return;
}
urun *gecici2=*head;
while (gecici2!=NULL)
{
    if (strcmp(gecici2->tur,tur)==0)
    {
        printf("Urun adi: %s\n",gecici2->ad);
        printf("Urun turu: %s\n",gecici2->tur);
        printf("Urun adeti: %d\n",gecici2->adet);
        printf("Urun fiyati: %.2f\n",gecici2->fiyat);
        printf("Urun kodu: %d\n",gecici2->urunKodu);
        printf("\n====================================\n");

    }
    gecici2=gecici2->sonraki;
}
}



void urun_ara (urun**head)
{
    printf("Hangi yontemle aramak istiyorsunuz?\n");
    printf("1- Urun koduna gore\n");
    printf("2- Urun adina gore\n");
    printf("Secim: ");
    int secim1;
    scanf("%d",&secim1);
                urun *bakilan=*head;

            switch(secim1)

            {
                case 1:
                    system("clear");

                    int urunKodu;
                    printf("Aramak istediginiz urunun kodunu giriniz\n");
                    printf("Urun kodu: ");
                    scanf("%d",&urunKodu);
                    system("clear");
                    bakilan=*head;
                    while (bakilan!=NULL && bakilan->urunKodu!=urunKodu)
                    {
                    bakilan=bakilan->sonraki;
                    }
                            if(bakilan==NULL)
                            {
                            printf("Urun bulunamadi\n");
                            printf("\n====================================\n");
                            return;
                            }  
                   
                       printf("Urun adi: %s\n",bakilan->ad);
                       printf("Urun turu: %s\n",bakilan->tur);
                       printf("Urun adeti: %d\n",bakilan->adet);
                       printf("Urun fiyati: %.2f\n",bakilan->fiyat);
                       printf("Urun kodu: %d\n",bakilan->urunKodu);
                       printf("\n====================================\n");
                          break;  
  
  
                  case 2:
                    system("clear");

                   char ad[50];
                   printf("Aramak istediginiz urunun adini giriniz\n");
                   printf("Urun adi: ");
                   scanf("%s",ad);
                   system("clear");
                   bakilan=*head;
                   while (bakilan!=NULL && strcmp(bakilan->ad,ad)!=0)
                    {
                        bakilan=bakilan->sonraki;
                     }
                        if(bakilan==NULL) {
                         printf("Urun bulunamadi\n");
                        printf("\n====================================\n");
                    
                        return;
         
                    }
    printf("Urun adi: %s\n",bakilan->ad);
    printf("Urun turu: %s\n",bakilan->tur);
    printf("Urun adeti: %d\n",bakilan->adet);
    printf("Urun fiyati: %.2f\n",bakilan->fiyat);
    printf("Urun kodu: %d\n",bakilan->urunKodu);
    printf("\n====================================\n");
}    
    }

            
  

int menu(){
    int secim;
    
    printf("Lutfen yapmak istediginiz islemi seciniz\n");
    printf("1-Urun Ekle\n");
    printf("2-Urun Sil\n");
    printf("3-Urun Guncelle\n");
    printf("4-Urun Listele\n");
    printf("5-Urun Ara\n");
    printf("6-Cikis\n");
    printf("Secim: ");
    scanf("%d",&secim);
    return secim;
}


int main(){

    int secim;

    urun *head=NULL;
     do {
        secim=menu();
        switch (secim){
            case 1:
                urun_ekle(&head);
                break;
            case 2:
                urun_sil(&head);
                break;
            case 3:
                urun_guncelle(&head);
                break;
            case 4:
                urun_listele(&head);
                break;
            case 5:
                urun_ara(&head);
                break;
            case 6:
                printf("Cikis yapiliyor\n");
                break;
            default:
                printf("Hatali secim yaptiniz\n");
                break;
        }
    
       }
       while (secim!=6);
    return 0;
    }
   






 