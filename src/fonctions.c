#include "fonctions.h"

/* ── helpers ─────────────────────────────────────────────────────────── */

static void lireChaine(char *dest, int taille, const char *invite) {
    do {
        printf("%s", invite);
        fflush(stdout);
        if (fgets(dest, taille, stdin) != NULL) {
            int len = (int)strcspn(dest, "\r\n");
            dest[len] = '\0';
            if (len == taille - 1)
                while (getchar() != '\n');
        }
        if (dest[0] == '\0')
            printf("Saisie vide. Reessayez.\n");
    } while (dest[0] == '\0');
}

static float lireNote(const char *invite) {
    float note;
    int ok;
    do {
        printf("%s", invite);
        ok = scanf("%f", &note);
        while (getchar() != '\n');
        if (!ok || note < 0.0f || note > 20.0f) {
            printf("Note invalide (0 - 20). Reessayez.\n");
            ok = 0;
        }
    } while (!ok);
    return note;
}

/* ── affichage ───────────────────────────────────────────────────────── */

void afficherEtudiant(Etudiant e) {
    printf("  Nom        : %s\n",   e.nom);
    printf("  Prenom     : %s\n",   e.prenom);
    printf("  Matricule  : %s\n",   e.matricule);
    printf("  Note 1     : %.2f\n", e.note1);
    printf("  Note 2     : %.2f\n", e.note2);
    printf("  Note 3     : %.2f\n", e.note3);
    printf("  Moyenne    : %.2f\n", e.moyenne);
    printf("  Statut     : %s\n",   e.statut);
    printf("  ---\n");
}

void afficherTous(void) {
    Etudiant e;
    FILE *f = fopen(FICHIER, "rb");
    if (f == NULL) {
        printf("Aucun etudiant enregistre.\n");
        return;
    }
    printf("\n=== Liste de tous les etudiants ===\n");
    while (fread(&e, sizeof(Etudiant), 1, f) == 1)
        afficherEtudiant(e);
    fclose(f);
}

void afficherMajore(void) {
    Etudiant e;
    int trouve = 0;
    FILE *f = fopen(FICHIER, "rb");
    if (f == NULL) {
        printf("Aucun etudiant enregistre.\n");
        return;
    }
    printf("\n=== Major de promotion ===\n");
    while (fread(&e, sizeof(Etudiant), 1, f) == 1) {
        if (strcmp(e.statut, "Majore") == 0) {
            afficherEtudiant(e);
            trouve = 1;
            break;
        }
    }
    if (!trouve)
        printf("Aucun majore trouve.\n");
    fclose(f);
}

void rechercherParStatut(void) {
    Etudiant e;
    char statut[15];
    int trouve = 0;

    lireChaine(statut, sizeof(statut),
               "Entrer un statut (Admis / Redoublant / Majore) : ");

    FILE *f = fopen(FICHIER, "rb");
    if (f == NULL) {
        printf("Aucun etudiant enregistre.\n");
        return;
    }
    printf("\n=== Etudiants avec le statut \"%s\" ===\n", statut);
    while (fread(&e, sizeof(Etudiant), 1, f) == 1) {
        if (strcmp(statut, e.statut) == 0) {
            afficherEtudiant(e);
            trouve = 1;
        }
    }
    if (!trouve)
        printf("Aucun etudiant avec ce statut.\n");
    fclose(f);
}

/* ── logique metier ──────────────────────────────────────────────────── */

void recalculerMajore(void) {
    Etudiant tab[MAX];
    int n = 0;

    FILE *f = fopen(FICHIER, "rb");
    if (f == NULL) return;
    while (n < MAX && fread(&tab[n], sizeof(Etudiant), 1, f) == 1)
        n++;
    fclose(f);

    if (n == 0) return;

    int idx = 0;
    for (int i = 1; i < n; i++)
        if (tab[i].moyenne > tab[idx].moyenne)
            idx = i;

    for (int i = 0; i < n; i++) {
        if (i == idx)
            strcpy(tab[i].statut, "Majore");
        else if (tab[i].moyenne >= 10.0f)
            strcpy(tab[i].statut, "Admis");
        else
            strcpy(tab[i].statut, "Redoublant");
    }

    FILE *f2 = fopen(FICHIER, "wb");
    if (f2 == NULL) return;
    for (int i = 0; i < n; i++)
        fwrite(&tab[i], sizeof(Etudiant), 1, f2);
    fclose(f2);
}

void ajouterEtudiant(void) {
    Etudiant e;

    lireChaine(e.nom,       sizeof(e.nom),       "Nom       : ");
    lireChaine(e.prenom,    sizeof(e.prenom),     "Prenom    : ");
    lireChaine(e.matricule, sizeof(e.matricule),  "Matricule : ");
    e.note1 = lireNote("Note 1    : ");
    e.note2 = lireNote("Note 2    : ");
    e.note3 = lireNote("Note 3    : ");

    FILE *f = fopen(FICHIER, "rb");
    if (f != NULL) {
        Etudiant tmp;
        while (fread(&tmp, sizeof(Etudiant), 1, f) == 1) {
            if (strcmp(e.matricule, tmp.matricule) == 0) {
                printf("Matricule deja existant.\n");
                fclose(f);
                return;
            }
        }
        fclose(f);
    }

    e.moyenne = (e.note1 + e.note2 + e.note3) / 3.0f;
    strcpy(e.statut, e.moyenne >= 10.0f ? "Admis" : "Redoublant");

    FILE *fw = fopen(FICHIER, "ab");
    if (fw == NULL) return;
    fwrite(&e, sizeof(Etudiant), 1, fw);
    fclose(fw);

    recalculerMajore();
    printf("Etudiant ajoute avec succes.\n");
}

void modifierNotes(void) {
    Etudiant tab[MAX];
    int n = 0;

    FILE *f = fopen(FICHIER, "rb");
    if (f == NULL) {
        printf("Aucun etudiant enregistre.\n");
        return;
    }
    while (n < MAX && fread(&tab[n], sizeof(Etudiant), 1, f) == 1)
        n++;
    fclose(f);

    if (n == 0) {
        printf("Aucun etudiant enregistre.\n");
        return;
    }

    char mat[13];
    lireChaine(mat, sizeof(mat), "Matricule de l'etudiant a modifier : ");

    int idx = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(tab[i].matricule, mat) == 0) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        printf("Matricule non trouve.\n");
        return;
    }

    printf("\nNotes actuelles :\n");
    printf("  Note 1  : %.2f\n", tab[idx].note1);
    printf("  Note 2  : %.2f\n", tab[idx].note2);
    printf("  Note 3  : %.2f\n", tab[idx].note3);
    printf("  Moyenne : %.2f\n", tab[idx].moyenne);

    tab[idx].note1 = lireNote("Nouvelle Note 1 : ");
    tab[idx].note2 = lireNote("Nouvelle Note 2 : ");
    tab[idx].note3 = lireNote("Nouvelle Note 3 : ");

    tab[idx].moyenne = (tab[idx].note1 + tab[idx].note2 + tab[idx].note3) / 3.0f;
    strcpy(tab[idx].statut, tab[idx].moyenne >= 10.0f ? "Admis" : "Redoublant");

    FILE *f2 = fopen(FICHIER, "wb");
    if (f2 == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }
    for (int i = 0; i < n; i++)
        fwrite(&tab[i], sizeof(Etudiant), 1, f2);
    fclose(f2);

    recalculerMajore();
    printf("Notes modifiees avec succes.\n");
}