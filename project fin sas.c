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
