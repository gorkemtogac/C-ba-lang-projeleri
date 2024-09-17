#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Ürün yapısı (çift bağlı liste)
typedef struct Product {
    int id;                // Ürünün kimlik numarası
    char name[50];         // Ürünün adı
    int quantity;          // Ürünün miktarı
    float price;           // Ürünün fiyatı
    struct Product* next;  // Sonraki ürünü işaret eden işaretçi
    struct Product* prev;  // Önceki ürünü işaret eden işaretçi
} Product;

// Yeni bir ürün eklemek için kullanılan fonksiyon
void addProduct(Product** head, Product** tail, int id, const char* name, int quantity, float price) {
    Product* newProduct = (Product*)malloc(sizeof(Product)); // Yeni ürün için hafızada yer ayırıyoruz
    newProduct->id = id;                                     // Ürün ID'sini atıyoruz
    strcpy(newProduct->name, name);                          // Ürün adını kopyalıyoruz
    newProduct->quantity = quantity;                         // Ürün miktarını atıyoruz
    newProduct->price = price;                               // Ürün fiyatını atıyoruz
    newProduct->next = NULL;                                 // Yeni ürünün 'next' işaretçisini NULL yapıyoruz
    newProduct->prev = *tail;                                // Yeni ürünün 'prev' işaretçisini tail'e bağlıyoruz

    if (*tail != NULL) {
        (*tail)->next = newProduct; // Eğer tail varsa, eski tail'in next işaretçisini yeni ürüne bağlarız
    } else {
        *head = newProduct; // Eğer liste boşsa, yeni ürün liste başı olur
    }

    *tail = newProduct; // Yeni ürünü tail yapıyoruz
}

// Envanteri dosyadan yükleyen ve listeye ekleyen fonksiyon
Product* loadInventoryFromFile(const char* filename, Product** tail) {
    FILE *file = fopen(filename, "rb");  // Dosyayı okuma modunda açıyoruz
    if (file == NULL) {                  // Dosya açılamazsa hata mesajı veriyoruz
        printf("Dosya açılamadı.\n");
        return NULL;
    }

    Product* head = NULL;  // Yüklenecek listenin başını tutacak işaretçi
    Product temp;

    while (fread(&temp, sizeof(Product) - sizeof(Product*), 1, file)) { // Dosyadan ürün bilgilerini okuyup geçici ürüne kaydediyoruz
        addProduct(&head, tail, temp.id, temp.name, temp.quantity, temp.price); // Ürünü listeye ekliyoruz
    }

    fclose(file);  // Dosyayı kapatıyoruz
    return head;   // Listenin başını döndürüyoruz
}

// Ürün bilgilerini dosyaya kaydeden fonksiyon
void saveProductToFile(const char* filename, Product* product) {
    FILE* file = fopen(filename, "ab");  // Dosyayı ekleme modunda açıyoruz
    if (file == NULL) {
        printf("Dosya açılamadı.\n");
        return;
    }

    fwrite(product, sizeof(Product) - sizeof(Product*), 1, file);  // Ürün bilgilerini dosyaya yaz
    fclose(file);
}

// Envanteri ekrana yazdıran fonksiyon
void printInventory(Product* head) {
    Product* current = head;
    while (current != NULL) { // Listenin sonuna kadar ürün bilgilerini yazdırıyoruz
        printf("ID: %d, Ürün: %s, Miktar: %d, Fiyat: %.2f\n", current->id, current->name, current->quantity, current->price);
        current = current->next;  // Bir sonraki ürüne geçiyoruz
    }
}

// Ürünü listeden ve dosyadan silen fonksiyon
void deleteProduct(Product** head, Product** tail, int id) {
    Product* current = *head;  // Listenin başından başlayarak ürünü arıyoruz

    while (current != NULL) {
        if (current->id == id) {  // Ürün ID'si eşleşirse
            if (current->prev != NULL) {
                current->prev->next = current->next;  // Önceki düğümün 'next' işaretçisini, silinen düğümün sonrasına bağla
            } else {
                *head = current->next;  // Eğer silinecek düğüm liste başıysa, 'head' işaretçisini güncelle
            }

            if (current->next != NULL) {
                current->next->prev = current->prev;  // Sonraki düğümün 'prev' işaretçisini, silinen düğümün öncesine bağla
            } else {
                *tail = current->prev;  // Eğer silinecek düğüm liste sonuysa, 'tail' işaretçisini güncelle
            }

            free(current);  // Silinen düğüm için ayrılmış hafızayı serbest bırak
            printf("Ürün ID %d silindi.\n", id);

            removeProductFromFile("inventory.bin", id);  // Ürünü dosyadan sil
            return;
        }
        current = current->next;
    }

    printf("Ürün ID %d bulunamadı.\n", id);  // Ürün bulunamazsa mesaj veriyoruz
}

// Ürünü dosyadan silen fonksiyon
void removeProductFromFile(const char* filename, int id) {
    FILE* file = fopen(filename, "rb");
    FILE* tempFile = fopen("temp.bin", "wb");

    if (file == NULL || tempFile == NULL) {
        printf("Dosya açılamadı.\n");
        return;
    }

    Product temp;

    // Ürünü bulup atlayarak dosyanın geri kalanını geçici dosyaya kopyalıyoruz
    while (fread(&temp, sizeof(Product) - sizeof(Product*), 1, file)) {
        if (temp.id != id) {
            fwrite(&temp, sizeof(Product) - sizeof(Product*), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Orijinal dosyayı silip, geçici dosyayı yeniden adlandırıyoruz
    remove(filename);
    rename("temp.bin", filename);
}

// Programın ana fonksiyonu
int main() {
    Product* inventory = NULL;  // Envanter listesinin başını tutacak işaretçi
    Product* tail = NULL;       // Envanter listesinin sonunu tutacak işaretçi
    int choice, id, quantity;
    float price;
    char name[50];

    // Envanteri dosyadan yüklüyoruz
    inventory = loadInventoryFromFile("inventory.bin", &tail);

    do {
        printf("\n1. Ürün Ekle\n2. Ürün Sil\n3. Envanteri Görüntüle\n0. Çıkış\nSeçiminiz: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Ürün ID: ");
                scanf("%d", &id);
                printf("Ürün adı: ");
                scanf("%s", name);
                printf("Miktar: ");
                scanf("%d", &quantity);
                printf("Fiyat: ");
                scanf("%f", &price);

                addProduct(&inventory, &tail, id, name, quantity, price);
                saveProductToFile("inventory.bin", tail);  // Yeni ürünü dosyaya kaydediyoruz
                break;

            case 2:
                printf("Silinecek Ürün ID: ");
                scanf("%d", &id);
                deleteProduct(&inventory, &tail, id);  // Ürünü listeden ve dosyadan siliyoruz
                break;

            case 3:
                printInventory(inventory);  // Envanteri ekrana yazdırıyoruz
                break;

            case 0:
                printf("Çıkış yapılıyor...\n");
                break;

            default:
                printf("Geçersiz seçim.\n");
        }
    } while (choice != 0);

    return 0;
}
