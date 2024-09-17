#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct urun {
    int urunKodu;
    char ad[30];
    char tur[30];
    int adet;
    float fiyat;
    struct urun* sonraki;
    struct urun* onceki;
} urun;

// Dosyadan baştan ve sondan veri okuma fonksiyonu
void dosyadan_bagli_liste_al_optimize() {
    FILE *dosya = fopen("envanter.bin", "rb");
    if (dosya == NULL) {
        printf("Dosya açılmadı\n");
        return;
    }

    // Dosya boyutunu bulmak için dosyanın sonuna git
    fseek(dosya, 0, SEEK_END);
    long dosya_boyutu = ftell(dosya);

    // Her iki uçtan aynı anda okuma için baştan ve sondan okumak üzere işaretçiler
    long orta_nokta = dosya_boyutu / 2;
    urun *head = NULL, *tail = NULL;

    urun temp;
    long pos = 0;

    // Baştan okuma: ilk yarıdan okur
    fseek(dosya, 0, SEEK_SET);  // Dosyanın başına git
    while (ftell(dosya) < orta_nokta && fread(&temp, sizeof(urun) - sizeof(urun*), 1, dosya)) {
        urun *yeni_urun = (urun*)malloc(sizeof(urun));
        if (yeni_urun == NULL) {
            printf("Bellek tahsis edilemedi.\n");
            fclose(dosya);
            return;
        }
        // Verileri yeni ürüne kopyala
        strcpy(yeni_urun->ad, temp.ad);
        strcpy(yeni_urun->tur, temp.tur);
        yeni_urun->adet = temp.adet;
        yeni_urun->fiyat = temp.fiyat;
        yeni_urun->urunKodu = temp.urunKodu;
        yeni_urun->sonraki = NULL;
        yeni_urun->onceki = tail;

        // Listeye ekleme işlemi
        if (tail != NULL) {
            tail->sonraki = yeni_urun;
        } else {
            head = yeni_urun;
        }
        tail = yeni_urun;
    }

    // Sondan okuma: ikinci yarıdan okur
    pos = sizeof(urun);  // Ürün boyutu kadar geri gitme
    while (ftell(dosya) > orta_nokta && pos <= dosya_boyutu) {
        fseek(dosya, -pos, SEEK_END);  // Dosyanın sonundan başla
        fread(&temp, sizeof(urun) - sizeof(urun*), 1, dosya);
        urun *yeni_urun = (urun*)malloc(sizeof(urun));
        if (yeni_urun == NULL) {
            printf("Bellek tahsis edilemedi.\n");
          
            fclose(dosya);
            return;
        }
        // Verileri yeni ürüne kopyala
        strcpy(yeni_urun->ad, temp.ad);
        strcpy(yeni_urun->tur, temp.tur);
        yeni_urun->adet = temp.adet;
        yeni_urun->fiyat = temp.fiyat;
        yeni_urun->urunKodu = temp.urunKodu;
        yeni_urun->onceki = NULL;
        yeni_urun->sonraki = head;

        // Baş listeye ekleme işlemi
        if (head != NULL) {
            head->onceki = yeni_urun;
        }
        head = yeni_urun;
        pos += sizeof(urun);
    }

    fclose(dosya);
    printf("Dosya baştan ve sondan başarıyla okundu.\n");
}

// Ana fonksiyon
int main() {
    dosyadan_bagli_liste_al_optimize();
    return 0;
}
