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
        FILE *datoteka = fopen(argv[1], "ab");
        if (datoteka == NULL) 
        {
            printf("Greska pri otvaranju datoteke za pisanje!\n");
            return 1;
        }

        int n;
        printf("Koliko brojeva zelite unijeti? ");
        do
        {
            scanf("%d", &n);
        } while (n < 1);
        
        char telefonski_brojevi[n][30];
        for (int i = 0; i < n; i++) 
        {
            printf("Unesite %d. broj telefona: ", i+1);    
            scanf("%s", telefonski_brojevi[i]);
        }
        
        // Sortiranje niza u opadajućem redoslijedu (bubble sort (bubble gum) algoritam)
        for (int i = 0; i < n - 1; i++) 
        {
            for (int j = 0; j < n - i - 1; j++) 
            {
                // strcmp vraca < 0 ako je prvi string "manji" (po abecedi/brojevima) od drugog.
                // Ako zelimo opadajuci redoslijed, mijenjamo mjesta ako je prvi manji od drugog.
                // (Ako zelis rastuci redoslijed, samo promijeni < 0 u > 0)
                if (strcmp(telefonski_brojevi[j], telefonski_brojevi[j + 1]) < 0) 
                {
                    char privremena[30];
                    // Swap za stringove se radi preko strcpy funkcije
                    strcpy(privremena, telefonski_brojevi[j]);
                    strcpy(telefonski_brojevi[j], telefonski_brojevi[j + 1]);
                    strcpy(telefonski_brojevi[j + 1], privremena);
                }
            }
        }

        // Upisuje redom vrijednosti
        fwrite(telefonski_brojevi, sizeof(char) * 30, n, datoteka);

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

        char telefonski_broj[30];
        int rb = 1;
        printf("\n--- SORTIRANI BROJEVI (%s) ---\n", ime_datoteke);
        // Petlja se vrti sve dok fread uspijeva da procita po jedan cijeli broj (int)
        while (fread(telefonski_broj, sizeof(char)*30, 1, datoteka) == 1) 
        {
            printf("%d. %s\n", rb++, telefonski_broj);
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
