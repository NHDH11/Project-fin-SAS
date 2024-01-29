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
