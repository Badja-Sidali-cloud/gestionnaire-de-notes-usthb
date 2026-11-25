#include "fonctions.h"

int main() {
    int choix;

    do {
        printf("\n=== Gestionnaire de Notes ===\n");
        printf("1. Ajouter un etudiant\n");
        printf("2. Afficher tous les etudiants\n");
        printf("3. Modifier les notes d'un etudiant\n");
        printf("4. Rechercher par statut\n");
        printf("5. Afficher le majore\n");
        printf("6. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        while (getchar() != '\n');

        switch (choix) {
            case 1: ajouterEtudiant();     break;
            case 2: afficherTous();        break;
            case 3: modifierNotes();       break;
            case 4: rechercherParStatut(); break;
            case 5: afficherMajore();      break;
            case 6: printf("Au revoir !\n"); break;
            default: printf("Choix invalide.\n");
        }

        if (choix != 6) {
            printf("\nAppuyez sur Entree pour continuer...");
            getchar();
        }

    } while (choix != 6);

    return 0;
}
