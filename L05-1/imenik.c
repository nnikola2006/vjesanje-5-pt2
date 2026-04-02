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

































/*
void selectionSort(int niz[], int n) 
{
    int i, j, min_indeks, privremena;
    
    for (i = 0; i < n - 1; i++) 
    {
        // Pretpostavljamo da je trenutni element najmanji
        min_indeks = i;
        
        // Trazimo stvarni najmanji element u ostatku niza
        for (j = i + 1; j < n; j++) 
        {
            if (niz[j] < niz[min_indeks]) 
            {
                min_indeks = j;
            }
        }
        
        // Mijenjamo mjesta trenutnom i najmanjem elementu
        privremena = niz[min_indeks];
        niz[min_indeks] = niz[i];
        niz[i] = privremena;
    }
}



void insertionSort(int niz[], int n) 
{
    int i, kljuc, j;
    
    for (i = 1; i < n; i++) 
    {
        kljuc = niz[i];
        j = i - 1;
        
        // Pomjeramo elemente koji su veci od kljuca za jedno mjesto udesno
        while (j >= 0 && niz[j] > kljuc) 
        {
            niz[j + 1] = niz[j];
            j = j - 1;
        }
        // Ubacujemo kljuc na njegovo pravo mjesto
        niz[j + 1] = kljuc;
    }
}



void shellSort(int niz[], int n) 
{
    // Krecemo sa velikim razmakom i prepolovljujemo ga u svakom koraku
    for (int razmak = n / 2; razmak > 0; razmak /= 2) 
    {
        // Radimo modifikovani Insertion sort za dati razmak
        for (int i = razmak; i < n; i++) 
        {
            int privremena = niz[i];
            int j;
            
            for (j = i; j >= razmak && niz[j - razmak] > privremena; j -= razmak) 
            {
                niz[j] = niz[j - razmak];
            }
            niz[j] = privremena;
        }
    }
}

void bubbleSort(int niz[], int n) 
{
    int i, j, privremena;
    
    for (i = 0; i < n - 1; i++) 
    {
        // Posljednjih 'i' elemenata su vec na svom mjestu
        for (j = 0; j < n - i - 1; j++) 
        {
            // Ako je lijevi veci od desnog, mijenjamo ih
            if (niz[j] > niz[j + 1]) 
            {
                privremena = niz[j];
                niz[j] = niz[j + 1];
                niz[j + 1] = privremena;
            }
        }
    }
}



// quick sort
int particija(int niz[], int niski, int visoki) 
{
    int pivot = niz[visoki]; // Uzimamo zadnji element kao pivot
    int i = (niski - 1);     // Indeks manjeg elementa
    int privremena;

    for (int j = niski; j <= visoki - 1; j++) 
    {
        // Ako je trenutni element manji od pivota
        if (niz[j] < pivot) 
        {
            i++;
            // Mijenjamo niz[i] i niz[j]
            privremena = niz[i];
            niz[i] = niz[j];
            niz[j] = privremena;
        }
    }
    // Stavljamo pivot na njegovu konacnu poziciju
    privremena = niz[i + 1];
    niz[i + 1] = niz[visoki];
    niz[visoki] = privremena;
    
    return (i + 1);
}

void quickSort(int niz[], int niski, int visoki) 
{
    if (niski < visoki) 
    {
        int pi = particija(niz, niski, visoki);

        // Rekurzivno sortiramo elemente prije i poslije particije
        quickSort(niz, niski, pi - 1);
        quickSort(niz, pi + 1, visoki);
    }
}


// merge
void spoji(int niz[], int lijevo, int sredina, int desno) 
{
    int i, j, k;
    int n1 = sredina - lijevo + 1;
    int n2 = desno - sredina;

    // Kreiranje privremenih nizova
    int L[n1], D[n2];

    // Kopiranje podataka u privremene nizove
    for (i = 0; i < n1; i++) 
    {
        L[i] = niz[lijevo + i];
    }
    for (j = 0; j < n2; j++) 
    {
        D[j] = niz[sredina + 1 + j];
    }

    // Spajanje privremenih nizova nazad u glavni niz
    i = 0; // Pocetni indeks prvog podniza
    j = 0; // Pocetni indeks drugog podniza
    k = lijevo; // Pocetni indeks spojenog niza
    
    while (i < n1 && j < n2) 
    {
        if (L[i] <= D[j]) 
        {
            niz[k] = L[i];
            i++;
        } 
        else 
        {
            niz[k] = D[j];
            j++;
        }
        k++;
    }

    // Kopiranje preostalih elemenata iz L[], ako ih ima
    while (i < n1) 
    {
        niz[k] = L[i];
        i++;
        k++;
    }

    // Kopiranje preostalih elemenata iz D[], ako ih ima
    while (j < n2) 
    {
        niz[k] = D[j];
        j++;
        k++;
    }
}

void mergeSort(int niz[], int lijevo, int desno) 
{
    if (lijevo < desno) 
    {
        // Nalazenje sredine (ovako se izbjegava overflow za velike brojeve)
        int sredina = lijevo + (desno - lijevo) / 2;

        // Sortiranje prve i druge polovine
        mergeSort(niz, lijevo, sredina);
        mergeSort(niz, sredina + 1, desno);

        // Spajanje sortiranih polovina
        spoji(niz, lijevo, sredina, desno);
    }
}
*/
