#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <stdio.h>
#include <string.h>

#define FICHIER "etudiants.dat"
#define MAX 100

typedef struct {
    char nom[50];
    char prenom[50];
    char matricule[13];
    float note1, note2, note3;
    float moyenne;
    char statut[15];
} Etudiant;

void ajouterEtudiant(void);
void afficherTous(void);
void modifierNotes(void);
void rechercherParStatut(void);
void afficherMajore(void);
void recalculerMajore(void);
void afficherEtudiant(Etudiant e);

#endif
