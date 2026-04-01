#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definisanje strukture za osobu u imeniku
typedef struct 
{
    char ime[50];
    char prezime[50];
    char telefon[30];
} Osoba;

int main(int argc, char *argv[]) 
{
    // Osto sam bez fori
    if (argc != 2) 
    {
        printf("Greska! Treba: %s <binarna_datoteka>\n", argv[0]);
        return 1;
    }

    int opcija;
    // Prikaz menija i odabir opcije (MTEL IMATE NERPIJATELJE)
    printf("--- MENI ---\n");
    printf("1. Unos novih podataka\n");
    printf("2. Prikaz postojecih podataka\n");
    printf("Izaberite opciju (1 ili 2): ");
    scanf("%d", &opcija);

    if (opcija == 1) 
    {
        // OPCIJA 1: UNOS NOVIH PODATAKA

        // hello i am calling from softmicro, you have binary on your computer
        FILE *datoteka = fopen(argv[1], "ab");
        if (datoteka == NULL) 
        {
            printf("Greska pri otvaranju datoteke za pisanje!\n");
            return 1;
        }

        int broj_osoba;
        printf("Koliko osoba zelite unijeti? "); // 0 jer je mtel
        scanf("%d", &broj_osoba);

        Osoba o;
        for (int i = 0; i < broj_osoba; i++) 
        {
            printf("Unesite podatke %d. osobe (ime prezime broj_telefona):\n", i + 1);
            scanf("%s %s %s", o.ime, o.prezime, o.telefon);

            // Zapisujemo cijelu strukturu direktno u binarnu datoteku
            fwrite(&o, sizeof(Osoba), 1, datoteka);
        }

        fclose(datoteka);
        printf("Podaci su uspjesno sacuvani u datoteku %s!\n", argv[1]);
    } 
    else if (opcija == 2) 
    {
        // OPCIJA 2: PRIKAZ POSTOJECIH PODATAKA
        
        char unos_naziva[100];
        char *ime_datoteke_za_citanje = "";

        printf("Unesite naziv datoteke za citanje (ili '#' za zadanu datoteku iz argumenta): ");
        scanf("%s", unos_naziva);

        // Provjeravamo da li je korisnik unio "#"
        if (strcmp(unos_naziva, "#") == 0) 
            ime_datoteke_za_citanje = argv[1];
        else 
            ime_datoteke_za_citanje = unos_naziva;

        // read nigga read
        FILE *datoteka = fopen(ime_datoteke_za_citanje, "rb");
        if (datoteka == NULL) 
        {
            printf("Datoteka '%s' je prazna ili ne postoji!\n", ime_datoteke_za_citanje);
            return 1;
        }

        Osoba o;
        int redni_broj = 1;
        printf("\n--- IMENIK (%s) ---\n", ime_datoteke_za_citanje);
        // Petlja se vrti sve dok fread uspijeva da procita po jednu strukturu
        while (fread(&o, sizeof(Osoba), 1, datoteka) == 1) 
        {
            printf("%d. %s %s %s\n", redni_broj++, o.ime, o.prezime, o.telefon);
        }

        fclose(datoteka);
    } 
    else 
    {
        printf("Nepostojeca opcija!\n"); // idiote imas 1. i 2. nema vise
    }

    return 0;
}