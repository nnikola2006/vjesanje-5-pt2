#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Funkcija koja vrsi sifrovanje teksta Cezarovom sifrom (pomjeraj za 3)
void sifruj(char *tekst);

int main(int argc, char *argv[]) 
{
    // provjera argumenata
    if (argc != 2) 
    {
        printf("Greska! Treba: %s <binarna_datoteka>\n", argv[0]);
        return 1;
    }

    int opcija;
    // Prikaz menija (gladan sam... ne stvarno sam bio gladan kad sam ovo pisao)
    printf("--- MENI ---\n");
    printf("1. Unos novog teksta\n");
    printf("2. Prikaz sifrovanog teksta\n");
    printf("Izaberite opciju (1 ili 2): ");
    scanf("%d", &opcija);

    // Ciscenje buffer-a nakon scanf-a kako bi fgets radio pravilno (zbog \n)
    getchar();
    if (opcija == 1)
    {
        // Otvaramo datoteku iz argumenta za pisanje u binarnom modu
        FILE *datoteka = fopen(argv[1], "wb");
        if (datoteka == NULL) 
        {
            printf("Greska pri otvaranju datoteke za pisanje!\n");
            return 1;
        }

        char tekst[4096]; // prvi mi broj pao na pamet
        printf("Unesite tekst za sifrovanje: ");
        // fgets cita cijelu liniju teksta ukljucujuci i razmake
        fgets(tekst, sizeof(tekst), stdin);

        sifruj(tekst);

        // Zapisujemo sifrovani tekst u binarnu datoteku
        fwrite(tekst, sizeof(char), strlen(tekst), datoteka);

        fclose(datoteka);
        printf("Tekst je uspjesno sifrovan i snimljen u %s!\n", argv[1]);
    } 
    else if (opcija == 2) 
    {
        char unos_naziva[100];
        char *ime_datoteke;

        // isto ko prosli
        printf("Unesite naziv datoteke za citanje (ili '#' za zadanu datoteku iz argumenta): ");
        scanf("%s", unos_naziva);

        // Postavljanje * na pravo ime datoteke (jel te radi strahinja)
        if (strcmp(unos_naziva, "#") == 0) 
            ime_datoteke = argv[1];
        else 
            ime_datoteke = unos_naziva;

        // Otvaranje binarne datoteke za citanje
        FILE *datoteka = fopen(ime_datoteke, "rb");
        if (datoteka == NULL) 
        {
            printf("Datoteka '%s' ne postoji ili se ne moze otvoriti!\n", ime_datoteke);
            return 1;
        }

        printf("\n--- SIFROVANI TEKST ---\n");
        char c;
        // Citamo datoteku znak po znak i ispisujemo na ekran
        while (fread(&c, sizeof(char), 1, datoteka) == 1) 
        {
            putchar(c);
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

void sifruj(char *tekst)
{
    for (int i = 0; tekst[i] != '\0'; i++) 
    {
        // Provjera za velika slova
        if (tekst[i] >= 'A' && tekst[i] <= 'Z') 
        {
            tekst[i] = (tekst[i] - 'A' + 3) % 26 + 'A'; // formula ne pitaj kako znam
        }
        // Provjera za mala slova
        else if (tekst[i] >= 'a' && tekst[i] <= 'z') 
        {
            tekst[i] = (tekst[i] - 'a' + 3) % 26 + 'a';
        }
        // Znakovi koji nisu slova ostaju nepromijenjeni
    }
}