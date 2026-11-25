# Gestionnaire de notes avec statut automatique

Projet réalisé dans le cadre du **Projet 2 de TP Algorithmique**  
**Université des Sciences et de la Technologie Houari Boumediene (USTHB)**  
Faculté d’Informatique — Licence 1 — Année universitaire 2025/2026

## Présentation

Ce projet consiste à développer une application console en langage C permettant de gérer les étudiants d’une promotion. Le programme enregistre les informations des étudiants dans un fichier binaire, calcule automatiquement leur moyenne et attribue un statut académique.

Une règle particulière concerne le statut **Majoré** : l’étudiant ayant la meilleure moyenne de la promotion reçoit ce statut. Il est recalculé après l’ajout d’un étudiant ou la modification de ses notes.

## Fonctionnalités

- Ajouter un étudiant (nom, prénom, matricule et trois notes).
- Vérifier l’unicité du matricule avant l’ajout.
- Valider les notes dans l’intervalle `[0, 20]`.
- Calculer automatiquement la moyenne des trois notes.
- Attribuer automatiquement le statut `Admis`, `Redoublant` ou `Majore`.
- Afficher la liste des étudiants enregistrés.
- Modifier les notes d’un étudiant à partir de son matricule.
- Rechercher les étudiants selon leur statut.
- Afficher le major de promotion.
- Conserver les enregistrements dans le fichier binaire `etudiants.dat`.

## Règles de calcul des statuts

- **Admis** : moyenne supérieure ou égale à 10.
- **Redoublant** : moyenne inférieure à 10.
- **Majoré** : étudiant ayant la meilleure moyenne de la promotion. Ce statut est prioritaire sur les deux autres.

La moyenne est calculée ainsi :

```text
moyenne = (note1 + note2 + note3) / 3
```

## Organisation du dépôt

```text
gestionnaire-de-notes-usthb/
├── src/
│   ├── main.c
│   ├── fonctions.c
│   └── fonctions.h
├── docs/
│   └── rapport-descriptif.pdf
├── .gitignore
└── README.md
```

- `src/main.c` : menu principal et boucle de navigation.
- `src/fonctions.c` : fonctions de gestion des étudiants et logique métier.
- `src/fonctions.h` : structure `Etudiant`, constantes et prototypes.
- `docs/rapport-descriptif.pdf` : rapport descriptif du projet.

## Compilation et exécution

Un compilateur C tel que GCC est nécessaire.

Depuis la racine du dépôt, exécuter :

```bash
gcc -Wall -Wextra -o programme src/main.c src/fonctions.c
```

Puis lancer le programme :

```bash
./programme
```

Sous Windows avec MinGW, la commande de lancement est :

```powershell
.\programme.exe
```

Le fichier `etudiants.dat` est créé automatiquement dans le répertoire courant lors du premier ajout d’un étudiant.

## Technologies et notions travaillées

- Langage C
- Structures (`struct`)
- Fonctions et modularité
- Tableaux et chaînes de caractères
- Manipulation de fichiers binaires (`fopen`, `fread`, `fwrite`, `fclose`)
- Validation des entrées
- Calcul de moyennes et gestion de statuts

## Membres du groupe

- Badja Sidali
- Khelifa Rym
- Aitbraham Ikram
- Ouziane Adel
- Hadadou Sydra

## Contexte académique

Projet 2 — Travaux pratiques d’Algorithmique  
Licence 1 Informatique — USTHB  
Année universitaire 2025/2026
