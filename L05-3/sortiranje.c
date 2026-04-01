#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        printf("Greska! Treba: %s <binarna_datoteka>\n", argv[0]);
        return 1;
    }

    int opcija;

    // Prikaz menija i odabir opcije
    printf("--- MENI ---\n");
    printf("1. Unos i sortiranje novih podataka\n");
    printf("2. Prikaz postojecih podataka\n");
    printf("Izaberite opciju (1 ili 2): ");
    scanf("%d", &opcija);

    if (opcija == 1) 
    {
        // OPCIJA 1: unos i sort
        int n;
        printf("Koliko brojeva zelite unijeti? ");
        do
        {
            scanf("%d", &n);
        } while (n < 1);
        
        int niz[n];
        // Unos brojeva
        printf("Unesite %d cjelobrojnih podataka:\n", n);
        for (int i = 0; i < n; i++) 
        {
            scanf("%d", &niz[i]);
        }

        // Sortiranje niza u opadajućem redoslijedu (bubble sort (bubble gum) algoritam)
        for (int i = 0; i < n - 1; i++) 
        {
            for (int j = 0; j < n - i - 1; j++) 
            {
                // Ako je trenutni broj manji od sljedećeg, mijenjamo im mjesta
                if (niz[j] < niz[j + 1]) 
                {
                    int privremena = niz[j];
                    niz[j] = niz[j + 1];
                    niz[j + 1] = privremena;
                }
            }
        }

        // upisujemo u datoteku u binarnom formatu
        FILE *datoteka = fopen(argv[1], "wb");
        if (datoteka == NULL) 
        {
            printf("Greska pri otvaranju datoteke za pisanje!\n");
            return 1;
        }

        // Upisuje redom vrijednosti
        fwrite(niz, sizeof(int), n, datoteka);

        fclose(datoteka);
        printf("Podaci su uspjesno sortirani i sacuvani u %s!\n", argv[1]);
    } 
    else if (opcija == 2) 
    {
        // OPCIJA 2: PRIKAZ POSTOJECIH PODATAKA
        
        char unos_naziva[100];
        char *ime_datoteke;

        printf("Unesite naziv datoteke za citanje (ili '#' za zadanu datoteku iz argumenta): ");
        scanf("%s", unos_naziva);

        // Provjeravamo da li je korisnik unio "#"
        if (strcmp(unos_naziva, "#") == 0) 
            ime_datoteke = argv[1];
        else 
            ime_datoteke = unos_naziva;

        // Otvaramo odgovarajuću datoteku u modu "rb" za čitanje
        FILE *datoteka = fopen(ime_datoteke, "rb");
        if (datoteka == NULL) 
        {
            printf("Datoteka '%s' je prazna ili ne postoji!\n", ime_datoteke);
            return 1;
        }

        int broj;
        printf("\n--- SORTIRANI BROJEVI (%s) ---\n", ime_datoteke);
        // Petlja se vrti sve dok fread uspijeva da procita po jedan cijeli broj (int)
        while (fread(&broj, sizeof(int), 1, datoteka) == 1) 
        {
            printf("%d ", broj);
        }
        printf("\n");

        fclose(datoteka);
    } 
    else 
    {
        printf("Nepostojeca opcija!\n");
    }

    return 0;
}