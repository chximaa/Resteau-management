#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_PLATS = 100;
const int MAX_COMMANDES = 100;

typedef struct {
    char numeroplat[50];
    char nomplat[50];
    float prix;
} Plat;

typedef struct {
    int numerocommande;
    char numeroplat[10];
    int quantite;
    float total;
} commande;
void afficherCommandesJour(commande c[], int nbCommandes) {
    if (nbCommandes == 0) {
        printf("Aucune commande n'a ete effectuee aujourd'hui.\n");
        return;
    }else
        printf("--- Commandes du Jour ---\n");
    for (int i = 0; i < nbCommandes; i++) {
        printf("Commande n°%d :\n", c[i].numerocommande);
        printf("Numero du plat : %s, Quantite : %d, Total : %.2f MAD\n",
               c[i].numeroplat, c[i].quantite, c[i].total);
        printf("-------------------------\n");
    }
}


void ajouter(Plat p[], int *nbPlats) {
    if (*nbPlats >= MAX_PLATS) {
        printf("Le menu est plein. Impossible d'ajouter un nouveau plat.\n");
        return;
    }
    printf("Numero du plat : ");
    scanf("%s", p[*nbPlats].numeroplat);

    for (int i = 0; i < *nbPlats; i++) {
        if (strcmp(p[i].numeroplat, p[*nbPlats].numeroplat) == 0) {
            printf("Ce numero de plat existe dejà.\n");
            return;
        }
    }

    printf("Nom du plat : ");
    scanf("%s", p[*nbPlats].nomplat);
    printf("Prix : ");
    scanf("%f", &p[*nbPlats].prix);
    (*nbPlats)++;
    printf(">> Plat ajoute avec succès !\n");
}

void supprimer(Plat p[], int *nbPlats) {
    char num[50];
    printf("Entrer le numero du plat : ");
    scanf("%s", num);

    for (int i = 0; i < *nbPlats; i++) {
        if (strcmp(p[i].numeroplat, num) == 0) {
            for (int j = i; j < *nbPlats - 1; j++) {
                p[j] = p[j + 1];
            }
            (*nbPlats)--;
            printf(">> Plat supprime avec succès !\n");
            return;
        }
    }

    printf("Le numero n'existe pas.\n");
}

void modifier(Plat p[], int nbPlats) {
    char num[50];
    printf("Numero du plat à modifier : ");
    scanf("%s", num);

    for (int i = 0; i < nbPlats; i++) {
        if (strcmp(p[i].numeroplat, num) == 0) {
            printf("Nom actuel : %s, Nouveau nom : ", p[i].nomplat);
            scanf("%s", p[i].nomplat);
            printf("Prix actuel : %.2f, Nouveau prix : ", p[i].prix);
            scanf("%f", &p[i].prix);
            printf(">> Plat modifie avec succès !\n");
            return;
        }
    }

    printf("Plat non trouve.\n");
}

void gestion(Plat p[], int *nbPlats) {
    int choix_2;
    printf("--- MENU GESTION ---\n");
    printf("1. Ajouter un Plat\n");
    printf("2. Supprimer un Plat\n");
    printf("3. Modifier un Plat\n");
    printf("4. Retour\n");
    printf("Votre choix : ");
    scanf("%d", &choix_2);

    switch (choix_2) {
        case 1: ajouter(p, nbPlats); break;
        case 2: supprimer(p, nbPlats); break;
        case 3: modifier(p, *nbPlats); break;
        case 4: return;
        default: printf("Choix invalide. Veuillez reessayer.\n");
    }
}

void prendre(commande c[], int *nbCommandes, Plat p[], int nbPlats) {
    if (nbPlats == 0) {
        printf("Le menu est vide. Impossible de prendre une commande.\n");
        return;
    }

    commande cmd;
    cmd.numerocommande = *nbCommandes + 1;
    cmd.total = 0;
    int nbPlatsCommande;

    printf("Nombre de plats dans la commande : ");
    scanf("%d", &nbPlatsCommande);

    for (int i = 0; i < nbPlatsCommande; i++) {
        int platExiste = 0;
        printf("Numero du plat : ");
        scanf("%s", cmd.numeroplat);

        for (int j = 0; j < nbPlats; j++) {
            if (strcmp(cmd.numeroplat, p[j].numeroplat) == 0) {
                printf("Quantite : ");
                scanf("%d", &cmd.quantite);
                cmd.total += p[j].prix * cmd.quantite;
                platExiste = 1;
                break;
            }
        }

        if (!platExiste) {
            printf("Plat non trouve.\n");
        }
    }

    c[*nbCommandes] = cmd;
    (*nbCommandes)++;
    printf(">> Total de la commande : %.2f MAD\n", cmd.total);
}

void afficher(commande c[], int nbCommandes) {
    if (nbCommandes == 0) {
        printf("Aucune commande n'a ete effectuee aujourd'hui.\n");
        return;
    }else
        printf("--- Commandes du Jour ---\n");
        for (int i = 0; i < nbCommandes; i++) {
        printf("Commande n°%d :\n", c[i].numerocommande);
        printf("Numero du plat : %s, Quantite : %d, Total : %.2f MAD\n",
               c[i].numeroplat, c[i].quantite, c[i].total);
        printf("-------------------------\n");
    }
}

void Menuprincipal() {
    printf("--- MENU PRINCIPAL ---\n");
    printf("1. Gestion du menu\n");
    printf("2. Prendre une commande\n");
    printf("3. Afficher les commandes du jour\n");
    printf("4. Quitter\n");
    printf("Votre choix : ");
}

int main() {
    Plat p[MAX_PLATS];
    commande c[MAX_COMMANDES];
    int nbPlats = 0, nbCommandes = 0;
    int choix;

    do {
        Menuprincipal();
        scanf("%d", &choix);

        switch (choix) {
            case 1: gestion(p, &nbPlats); break;
            case 2: prendre(c, &nbCommandes, p, nbPlats); break;
            case 3: afficherCommandesJour(c, nbCommandes); break;
            case 4: break;
            default: printf("Choix invalide. Veuillez reessayer.\n");
        }
    } while (choix != 4);

    return 0;
}