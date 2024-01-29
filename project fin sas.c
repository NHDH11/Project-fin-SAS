#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TACHES 150

typedef struct {
    char description[100];
    char dateEcheance[20];
    int priorite;
    int statut; // 0 pour incomplete, 1 pour complete
} Tache;

void ajouterTache(Tache* taches, int* nombreTaches) {
    if (*nombreTaches < MAX_TACHES) {
        Tache nouvelleTache;
        printf("Description de la tache : ");
        scanf(" %[^\n]s", nouvelleTache.description);
        printf("Date d'echeance : ");
        scanf(" %s", nouvelleTache.dateEcheance);
        printf("Priorite (1 - Faible, 2 - Moyenne, 3 - Haute) : ");
        scanf("%d", &nouvelleTache.priorite);
        nouvelleTache.statut = 0; // Nouvelle tache est incomplete par defaut

        taches[*nombreTaches] = nouvelleTache;
        (*nombreTaches)++;
        printf("Tache ajoutee avec succes.\n");
    } else {
        printf("La liste des taches est pleine.\n");
    }
}

void afficherListeTaches(Tache* taches, int nombreTaches) {
    if (nombreTaches > 0) {
        printf("Liste des taches :\n");
        for (int i = 0; i < nombreTaches; i++) {
            printf("Tache %d :\n", i + 1);
            printf("Description : %s\n", taches[i].description);
            printf("Date d'echeance : %s\n", taches[i].dateEcheance);
            printf("Priorite : %d\n", taches[i].priorite);
            printf("Statut : %s\n", taches[i].statut == 0 ? "Incomplet" : "Complet");
            printf("\n");
        }
    } else {
        printf("Aucune tache disponible.\n");
    }
}

void modifierTache(Tache* taches, int nombreTaches) {
    int choix;
    afficherListeTaches(taches, nombreTaches);
    printf("Entrez le numero de la tache a modifier : ");
    scanf("%d", &choix);
    if (choix > 0 && choix <= nombreTaches) {
        printf("Nouvelle description : ");
        scanf(" %[^\n]s", taches[choix - 1].description);
        printf("Nouvelle date d'echeance : ");
        scanf(" %s", taches[choix - 1].dateEcheance);
        printf("Nouvelle priorite (1 - Faible, 2 - Moyenne, 3 - Haute) : ");
        scanf("%d", &taches[choix - 1].priorite);
        printf("Nouveau statut ( 1 - Complet, 0 - Incomplet) : ");
        scanf("%d", &taches[choix - 1].statut);
        printf("Tache modifiee avec succes.\n");
    } else {
        printf("Numero de tache invalide.\n");
    }
}

void supprimerTache(Tache* taches, int* nombreTaches) {
    int choix;
    afficherListeTaches(taches, *nombreTaches);
    printf("Entrez le numero de la tache a supprimer : ");
    scanf("%d", &choix);
    if (choix > 0 && choix <= *nombreTaches) {
        for (int i = choix - 1; i < *nombreTaches - 1; i++) {
            taches[i] = taches[i + 1];
        }
        (*nombreTaches)--;
        printf("Tache supprimee avec succes.\n");
    } else {
        printf("Numero de tache invalide.\n");
    }
}

void trierTachesParDate(Tache* taches, int nombreTaches) {
    int i, j;
    Tache temp;

    for (i = 0; i < nombreTaches - 1; i++) {
        for (j = 0; j < nombreTaches - i - 1; j++) {
            // Comparaison des dates d'echeance
            int annee1, mois1, jour1;
            int annee2, mois2, jour2;

            sscanf(taches[j].dateEcheance, "%d-%d-%d", &annee1, &mois1, &jour1);
            sscanf(taches[j + 1].dateEcheance, "%d-%d-%d", &annee2, &mois2, &jour2);

            // Comparaison des composantes des dates
            if (annee1 > annee2 || (annee1 == annee2 && mois1 > mois2) || (annee1 == annee2 && mois1 == mois2 && jour1 > jour2)) {
                // echange des teches si la date d'echeance est plus grande
                temp = taches[j];
                taches[j] = taches[j + 1];
                taches[j + 1] = temp;
            }
        }
    }

    printf("Taches triees par date d'echeance :\n");
    afficherListeTaches(taches, nombreTaches);
}

void filtrerParPriorite(Tache* taches, int nombreTaches) {
    int prioriteFiltre;
    printf("Entrez la priorite a filtrer : ");
    scanf("%d", &prioriteFiltre);
    printf("Taches avec priorite %d :\n", prioriteFiltre);
    for (int i = 0; i < nombreTaches; i++) {
        if (taches[i].priorite == prioriteFiltre) {
            printf("Description : %s\n", taches[i].description);
            printf("Date d'echeance : %s\n", taches[i].dateEcheance);
            printf("Priorite : %d\n", taches[i].priorite);
            printf("Statut : %s\n", taches[i].statut == 0 ? "Incomplet" : "Complet");
            printf("\n");
        }
        else {
            printf("il n'existe aucune tache avec cette priorite choisie\n");
        }
    }
}

void filtrerParStatut(Tache* taches, int nombreTaches) {
    int statutFiltre;
    printf("Entrez le statut a filtrer (0 pour incomplet, 1 pour complet) : ");
    scanf("%d", &statutFiltre);
    printf("Taches avec statut %s :\n", statutFiltre == 0 ? "Incomplet" : "Complet");
    for (int i = 0; i < nombreTaches; i++) {
        if (taches[i].statut == statutFiltre) {
            printf("Description : %s\n", taches[i].description);
            printf("Date d'echeance : %s\n", taches[i].dateEcheance);
            printf("Priorite : %d\n", taches[i].priorite);
            printf("Statut : %s\n", taches[i].statut == 0 ? "Incomplet" : "Complet");
            printf("\n");
        }
        else {
            printf("choix invalide , veillez reessayer\n");
        }
    }
}
void sauvegarderTachesDansFichier(Tache* taches, int nombreTaches) {
    FILE *fichier;
    fichier = fopen("taches.txt", "w"); // Ouverture du fichier en mode ecriture

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.");
        return;
    }

    for (int i = 0; i < nombreTaches; i++) {
        fprintf(fichier, "%s;%s;%d;%d\n", taches[i].description, taches[i].dateEcheance, taches[i].priorite, taches[i].statut);
    }

    fclose(fichier); // Fermeture du fichier
}

void chargerTachesDepuisFichier(Tache* taches, int* nombreTaches) {
    FILE *fichier;
    fichier = fopen("taches.txt", "r"); // Ouverture du fichier en mode lecture

    if (fichier == NULL) {
        printf("Fichier inexistant ou impossible a ouvrir.");
        return;
    }

    *nombreTaches = 0; // Reinitialisation du nombre de taches

    while (fscanf(fichier, "%[^;];%[^;];%d;%d\n", taches[*nombreTaches].description, taches[*nombreTaches].dateEcheance, &taches[*nombreTaches].priorite, &taches[*nombreTaches].statut) != EOF) {
        (*nombreTaches)++;
    }

    fclose(fichier); // Fermeture du fichier
}

int main() {
    Tache taches[MAX_TACHES];
    int nombreTaches = 0;
    int choix;

    chargerTachesDepuisFichier(taches, &nombreTaches);
    printf("\nBienvenue sur l'application GESTION DES TACHES\n");
    printf("N.B: respecter la forme des dates ANNEE-MOIS-JOUR dans la saisie !!!\n");
    printf("Logiquement tous les taches seront declarees incompletes dans la premiere saisie, pour les rendre completes , voir l'option 3\n");

    do {

        printf("\nMenu Principal\n");
        printf("1. Ajouter une tache\n");
        printf("2. Afficher la liste des taches\n");
        printf("3. Modifier une tache\n");
        printf("4. Supprimer une tache\n");
        printf("5. Ordonner les taches par date d'echeance\n");
        printf("6. filtrer par priorite\n");
        printf("7. filtrer par statut\n");
        printf("0. Quitter\n");

        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouterTache(taches, &nombreTaches);
                break;
            case 2:
                afficherListeTaches(taches, nombreTaches);
                break;
            case 3:
                modifierTache(taches, nombreTaches);
                break;
            case 4:
                supprimerTache(taches, &nombreTaches);
                break;
            case 5:
                trierTachesParDate(taches, nombreTaches);
                break;
            case 6:
                filtrerParPriorite(taches, nombreTaches);
                break;
            case 7:
                filtrerParStatut(taches, nombreTaches);
                break;
            case 0:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
        }
    } while (choix != 0);

    sauvegarderTachesDansFichier(taches, nombreTaches);

    return 0;
}

