#include <stdio.h>
#include <string.h>

#define maxt 20
#define maxc 20
#define Nbcmpt 0

int nbClients = 0;
int nbcmpt = 0;

struct Date {
    int Jour;
    int Mois;
    int Annee;
};

struct Transaction {
    char type[6];
    int montant;
    struct Date date;
};

typedef struct Client {
    int codecli;
    char nom[maxt];
    char prenom[maxt];
    char adrs[maxt];
    struct Date date_nais;
    struct Transaction historique[100];
} Client;

Client clients[maxc];

typedef struct Compte {
    int code_cpt;
    int Code_cli;
    char typecmpt[15];  // Increased the size to accommodate "compte d'epargne"
    int solde;
    struct Date d_compte;
    int numTransactions;
    struct Transaction historique[100];
} Compte;

Compte comptes[maxc];

void design(const char *message);
void menu0(int x);
void menu1(int a);
void menu2(int a);
void menu3(int a);
void access();
void gerer_clients(int a, int nbcmpt);
int comparer(const void *a, const void *b);
void gerer_compte(int a, int nbClients, int nbcmpt);
void gerer_operation(int a);
void addTransaction(struct Compte *account, char transactionType, int transactionAmount);
void displayTransactionHistory(struct Compte account);


//compte les comptes associés à un clients donné
int getnbaccounts(Compte comptes[], int codeCli, int nbcmpt) {
    int count = 0;

    for (int i = 0; i < nbcmpt; i++) {
        if (comptes[i].Code_cli == codeCli) {
            count++;
        }
    }

    return count;
}
//affiche l'historique des transactions
void displayTransactionHistory(struct Compte account) {
    printf("\nTransaction History for Account %d:\n", account.code_cpt);
    for (int i = 0; i < 100 && account.historique[i].montant != 0; i++) {
        printf("Type: %s, Amount: %d, Date: %d/%d/%d\n",
               account.historique[i].type,
               account.historique[i].montant,
               account.historique[i].date.Jour,
               account.historique[i].date.Mois,
               account.historique[i].date.Annee);
    }
}

//gestion des comptes
void gerer_compte(int a, int nbClients,int nbcmpt) {
    if (a == 1) {
        struct Compte cmpt;
        struct Compte cmpt0;
        FILE *file;
        FILE *fl;

        printf("Code Compte : ");
        scanf("%d", &cmpt.code_cpt);

        fl = fopen("compte.txt", "r");

        int found = 0;
        while (fread(&cmpt0, sizeof(struct Compte), 1, fl) && found == 0) {
            if (cmpt0.code_cpt == cmpt.code_cpt)
                found = 1;
        }

        if (found == 1) {
            printf("code existant\n");
            fclose(fl);
            return;
        }

        printf("Code Client : ");
        scanf("%d", &cmpt.Code_cli);

        struct Client cl;
        FILE *bdc;


        // Check if the client exists
        int clientExiste = 0;
        printf("Number of Clients: %d\n", nbClients);
        for (int i = 0; i < nbClients; i++) {
            printf("clients[%d].codecli = %d, cmpt.Code_cli = %d\n", i, clients[i].codecli, cmpt.Code_cli);
            if (clients[i].codecli == cmpt.Code_cli) {
                clientExiste = 1;
                break;
            }
        }

        if (!clientExiste) {


        printf("Nom : ");
        scanf("%s", cl.nom);

        printf("Prenom : ");
        scanf("%s", cl.prenom);


         printf("Adresse : ");
         scanf("%s", cl.adrs);


         printf("Date de naissance | ");
        printf("Jour : ");
        scanf("%d", &cl.date_nais.Jour);
        printf("Mois : ");
        scanf("%d", &cl.date_nais.Mois);
        printf("Annee : ");
        scanf("%d", &cl.date_nais.Annee);
        }

        printf("type du compte \n");
         printf("1-compte courant \n");
          printf("2- compte d'epargne\n");
        int w;
        scanf("%d", &w);
        if (w=1){strcpy(cmpt.typecmpt, "compte courant");}
        else {strcpy(cmpt.typecmpt, "compte d'epargne");}


        printf("Date de creation du compte | ");
        printf("Jour : ");
        scanf("%d", &cmpt.d_compte.Jour);
        printf("Mois : ");
        scanf("%d", &cmpt.d_compte.Mois);
        printf("Annee : ");
        scanf("%d", &cmpt.d_compte.Annee);
        printf("Somme : ");
        scanf("%d", &cmpt.solde);
        fclose(fl);
        file = fopen("compte.txt", "a");
        fwrite(&cmpt, sizeof(cmpt), 1, file);


        if (fwrite != 0)
            {printf("compte ajoute avec succes");
            nbcmpt++;}

        else
            printf("erreur");

        fclose(file);


        bdc = fopen("client.txt", "a");
        fwrite(&cl, sizeof(cl), 1, bdc);
        fclose(bdc);
        (nbClients)++;


          printf("\n 1- retour au menu precedent");
            printf("\n 2-quitter le programme");
            int z;
            scanf("%d", &z);
            if (z==1) {menu1(2);}
            else if (z=2){return;}
            else return;
    }
    else if (a == 2)
    {
        struct Compte cmpt;
        int code;
        FILE *file;

        printf("Code compte : ");
        scanf("%d", &code);

        file = fopen("compte.txt", "r");
        int found = 0;
        while (fread(&cmpt, sizeof(struct Compte), 1, file) && found == 0)
        {
            if (cmpt.code_cpt == code)
            {
                printf("\n Code compte : %d", cmpt.code_cpt);
                printf("\n Code client : %d", cmpt.Code_cli);
                printf("\n Code client : %d", cmpt.typecmpt);
                printf("\n Date creation %d / %d / %d", cmpt.d_compte.Jour, cmpt.d_compte.Mois, cmpt.d_compte.Annee);
                printf("\n Somme %d", cmpt.solde);
                found = 1;
            }
        }
        if (found == 0)
            printf("code non existant\n");
        fclose(file);
          printf("\n 1- retour au menu precedent");
            printf("\n 2-quitter le programme");
            int z;
            scanf("%d", &z);
            if (z==1) {menu1(2);}
            else if (z=2){return;}
            else return;
    }
    else if (a == 3)
    {
        struct Compte cmpt;
        FILE *file;

        file = fopen("compte.txt", "r");

        while (fread(&cmpt, sizeof(struct Compte), 1, file))
        {
            printf("\n Code compte : %d", cmpt.code_cpt);
            printf("\n Code client : %d", cmpt.Code_cli);
            printf("\n Date creation %d / %d / %d", cmpt.d_compte.Jour, cmpt.d_compte.Mois, cmpt.d_compte.Annee);
            printf("\n Somme %d", cmpt.solde);
            printf("\n-----------------------------------------");
        }
        fclose(file);
          printf("\n 1- retour au menu precedent");
            printf("\n 2-quitter le programme");
            int z;
            scanf("%d", &z);
            if (z==1) {menu1(2);}
            else if (z=2){return;}
            else return;
    }
    else if (a == 4)
    {
        struct Compte cmpt;
        int code;
        FILE *file;

        printf("Code Compte a supprimer : ");
        scanf("%d", &code);

        file = fopen("compte.txt", "r");

        int nb = 0;
        struct Compte comptes[100];

        while (fread(&cmpt, sizeof(struct Compte), 1, file))
        {
            comptes[nb] = cmpt;
            nb++;
        }
        fclose(file);
        remove("compte.txt");

        FILE *nf;
        nf = fopen("nv.txt", "a");
        for (int i = 0; i < nb; i++)
        {
            if (comptes[i].code_cpt != code)
                fwrite(&comptes[i], sizeof(comptes[i]), 1, nf);
        }
        fclose(nf);
        rename("nv.txt", "compte.txt");
          printf("\n 1- retour au menu precedent");
            printf("\n 2-quitter le programme");
            int z;
            scanf("%d", &z);
            if (z==1) {menu1(2);}
            else if (z=2){return;}
            else return;
    }
    else if (a == 5)
        menu1(2);
}

//gestion des clients
void gerer_clients (int a,int nbcmpt)
{
    FILE *file;
    int code;

    if (a == 1)
    {
        struct Client cl;
        FILE *bdc;

        printf("Code Client : ");
        scanf("%d", &cl.codecli);

        printf("Nom : ");
        scanf("%s", cl.nom);

        printf("Prenom : ");
        scanf("%s", cl.prenom);


         printf("Adresse : ");
         scanf("%s", cl.adrs);


         printf("Date de naissance | ");
        printf("Jour : ");
        scanf("%d", &cl.date_nais.Jour);
        printf("Mois : ");
        scanf("%d", &cl.date_nais.Mois);
        printf("Annee : ");
        scanf("%d", &cl.date_nais.Annee);

        bdc = fopen("client.txt", "a");
        fwrite(&cl, sizeof(cl), 1, bdc);
        fclose(bdc);
        nbClients++;
        printf("client ajoute avec succes");
         printf("\n 1- retour au menu precedent");
            printf("\n 2-quitter le programme");
            int z;
            scanf("%d", &z);
            if (z==1) {menu1(1);}
            else if (z=2){return;}
            else return;
    }
    else if (a == 2)
    {
        struct Client cl;
        struct Client cl1;
        FILE *bdc;

        printf("donner le Code Client : ");
        scanf("%d", &cl1.codecli);
        printf("donner le nouveau nom : ");
        scanf("%s", cl1.nom);

        printf("donner le nouveau prenom : ");
        scanf("%s", cl1.prenom);

        printf("Adresse : ");
        scanf("%s", cl1.adrs);


        printf("Date de naissance | ");
        printf("Jour : ");
        scanf("%d", &cl1.date_nais.Jour);
        printf("Mois : ");
        scanf("%d", &cl1.date_nais.Mois);
        printf("Annee : ");
        scanf("%d", &cl1.date_nais.Annee);



        bdc = fopen("client.txt", "r");

        int nbClients = 0;

        while (fread(&cl, sizeof(struct Client), 1, bdc))
        {
            clients[nbClients] = cl;
            nbClients++;
        }
        fclose(bdc);
        remove("client.txt");

        FILE *f1;
        f1 = fopen("f1.txt", "a");
        for (int i = 0; i < nbClients; i++)
        {
            if (clients[i].codecli == cl1.codecli)
                fwrite(&cl1, sizeof(cl1), 1, f1);
            else
                fwrite(&clients[i], sizeof(clients[i]), 1, f1);
        }
        fclose(f1);
        rename("f1.txt", "client.txt");

         printf("\n 1- retour au menu precedent");
            printf("\n 2-quitter le programme");
            int z;
            scanf("%d", &z);
            if (z==1) {menu1(1);}
            else if (a=z){return;}
            else return;
    }
    else if (a == 3)
    {
        struct Client cl;
        int code;
        FILE *file;

        printf("Code Client a supprimer : ");
        scanf("%d", &code);

        file = fopen("client.txt", "r");

        int nbClients = 0;

        while (fread(&cl, sizeof(struct Client), 1, file))
        {
            clients[nbClients] = cl;
            nbClients++;
        }
        fclose(file);
        remove("client.txt");

        FILE *nf;
        nf = fopen("nv.txt", "a");
        for (int i = 0; i < nbClients; i++)
        {
            if (clients[i].codecli != code)
                fwrite(&clients[i], sizeof(clients[i]), 1, nf);
        }
        fclose(nf);
        rename("nv.txt", "client.txt");

         printf("\n 1- retour au menu precedent");
            printf("\n 2-quitter le programme");
            int z;
            scanf("%d", &z);
            if (z==1) {menu1(1);}
            else if (z=2){return;}
            else return;
    }
    else if (a == 4)
    {
        struct Client cl;
        FILE *file;

        file = fopen("client.txt", "r");

        int nbClt = 0;

        while (fread(&cl, sizeof(struct Client), 1, file))
        {
            clients[nbClt] = cl;
            nbClt++;
        }
        fclose(file);
        qsort(clients, nbClt, sizeof(struct Client), comparer);

        int nbaccounts;

        if (nbClt!=0){
        for (int c = 0; c < nbClt; c++)
        {
            printf("\nCode client : %d", clients[c].codecli);
            printf("\nNom: %s | Prenom: %s", clients[c].nom, clients[c].prenom);
            printf("\n Date de naissance %d / %d / %d", clients[c].date_nais.Jour, clients[c].date_nais.Mois, clients[c].date_nais.Annee);
            nbaccounts = getnbaccounts(comptes, cl.codecli,nbcmpt ); // Assuming nb is the count of accounts
            printf("\nNumber of accounts for client %d: %d\n", cl.codecli, nbaccounts);


            printf("\n");

            printf("\n 1- retour au menu precedent");
            printf("\n 2-quitter le programme");
            int z;
            scanf("%d", &z);
            if (z==1) {menu1(1);}
            else if (z=2){return;}
            else return;}


        }
        else {printf("pas de clients enregistres pour le moment");
        printf("\n 1- retour au menu precedent");
            printf("\n 2-quitter le programme");
            int z;
            scanf("%d", &z);
            if (z==1) {menu1(1);}
            else if (z=2){return;}
            else return; }
    }
    else if (a == 5)
        menu0(1);
}





void gerer_operation(int a)
{
    if (a == 1)
    {
        struct Compte cmpt;
        int code,soldefinal, m;
        FILE *file;

        printf("Code Compte : ");
        scanf("%d", &code);

        file = fopen("compte.txt", "r");

        int nb = 0;

        while (fread(&cmpt, sizeof(struct Compte), 1, file))
        {
            comptes[nb] = cmpt;
            nb++;
        }
        fclose(file);
        remove("compte.txt");




        FILE *nf;
        nf = fopen("nv.txt", "a");
        for (int i = 0; i < nb; i++)
        {
            if (comptes[i].code_cpt == code)
            {
                 do
                {
                    printf("\n montant : ");
                    scanf("%d", &m);
                    if (m > 1000)
                        printf("\n le montant ne doit pas depasser 1000 DT");
                    soldefinal = comptes[i].solde - m;
                    if (soldefinal < 50)
                        printf("\n le solde ne doit pas etre inferieur a 50 DT");
                }while (m > 1000 || soldefinal < 50);

                addTransaction(&comptes[i], "debit", m);
                comptes[i].solde = comptes[i].solde- m;

            }else {"code de compte inexistant";}
            fwrite(&comptes[i], sizeof(comptes[i]), 1, nf);
        }
        fclose(nf);
        rename("nv.txt", "compte.txt");
         printf("\n 1- retour au menu precedent");
            printf("\n 2-quitter le programme");
            int z;
            scanf("%d", &z);
            if (z==1) {menu1(2);}
            else if (z=2){return;}
            else return;
    }
    else if (a == 3)
    {
        struct Compte cmpt;
        int code1, code2, soldefinal,m;
        FILE *file;

        printf("Code Compte d'envoi : ");
        scanf("%d", &code1);

        printf("Code compte destinataire : ");
        scanf("%d", &code2);

        file = fopen("compte.txt", "r");

        int nb = 0;

        while (fread(&cmpt, sizeof(struct Compte), 1, file))
        {
            comptes[nb] = cmpt;
            nb++;
        }
        fclose(file);
        remove("compte.txt");

        FILE *nf;
        nf = fopen("nv.txt", "a");
        for (int i = 0; i < nb; i++)
        {
            if (comptes[i].code_cpt == code1)
            {
                 do
                {
                    printf("\n montant : ");
                    scanf("%d", &m);
                    if (m > 1000)
                        printf("\n le montant ne doit pas depasser 1000 DT");
                    soldefinal = comptes[i].solde - m;
                    if (soldefinal < 50)
                        printf("\n le solde ne doit pas etre inferieur a 50 DT");
                }  while (m > 1000 || soldefinal < 50);
               addTransaction(&comptes[i], "debit", m);

                comptes[i].solde = comptes[i].solde - m;
                printf("\n-----------------------------------------");
            }
            else if (comptes[i].code_cpt == code2)
            {    addTransaction(&comptes[i], "credit", m);
                comptes[i].solde = comptes[i].solde + m;

                printf("\n-----------------------------------------");
            }
            fwrite(&comptes[i], sizeof(comptes[i]), 1, nf);
        }
        fclose(nf);
        rename("nv.txt", "compte.txt");
         printf("\n 1- retour au menu precedent");
            printf("\n 2-quitter le programme");
            int z;
            scanf("%d", &z);
            if (z==1) {menu1(2);}
            else if (z=2){return;}
            else return;
    }
    else if (a == 2){

        struct Compte cmpt;
        int code,soldefinal, m;
        FILE *file;

        printf("Code Compte : ");
        scanf("%d", &code);

        file = fopen("compte.txt", "r");

        int nb = 0;

        while (fread(&cmpt, sizeof(struct Compte), 1, file))
        {
            comptes[nb] = cmpt;
            nb++;
        }
        fclose(file);
        remove("compte.txt");




        FILE *nf;
        nf = fopen("nv.txt", "a");
        for (int i = 0; i < nb; i++)
        {
            if (comptes[i].code_cpt == code)
            {
                 do
                {
                    printf("\n montant : ");
                    scanf("%d", &m);
                    if (m > 1000)
                        printf("\n le montant ne doit pas depasser 6000 DT");
                    soldefinal = comptes[i].solde - m;
                    if (soldefinal < 50)
                        printf("\n le solde ne doit pas etre inferieur a 50 DT");
                }while (m > 1000 || soldefinal < 50);

                addTransaction(&comptes[i], "credit", m);
                comptes[i].solde = comptes[i].solde+m;

            }else {"code de compte inexistant";}
            fwrite(&comptes[i], sizeof(comptes[i]), 1, nf);
        }
        fclose(nf);
        rename("nv.txt", "compte.txt");
         printf("\n 1- retour au menu precedent");
            printf("\n 2-quitter le programme");
            int z;
            scanf("%d", &z);
            if (z==1) {menu1(2);}
            else if (z=2){return;}
            else return;

}
}


//sous menu clients
void menu3(int a)
{
    if (a == 1)
    {
        struct Compte cmpt;
        int code;
        FILE *file;

        printf("Code compte : ");
        scanf("%d", &code);

        file = fopen("compte.txt", "r");
        int found = 0;
        while (fread(&cmpt, sizeof(struct Compte), 1, file) && found == 0)
        {
            if (cmpt.code_cpt == code)
            {
                printf("\n Code compte : %d", cmpt.code_cpt);
                printf("\n Code client : %d", cmpt.Code_cli);
                printf("\n Code client : %d", cmpt.typecmpt);
                printf("\n Date creation %d / %d / %d", cmpt.d_compte.Jour, cmpt.d_compte.Mois, cmpt.d_compte.Annee);
                printf("\n Somme %d", cmpt.solde);
                found = 1;
            }
        }
        if (found == 0)
            printf("code non existant\n");
            fclose(file);
            printf("\n 1- retour au menu precedent");
            printf("\n 2-quitter le programme");
            int z;
            scanf("%d", &z);
            if (z==1) {menu2(2);}
            else if (z=2){return;}
            else return;
                    }

    else if (a == 2)
    {   struct Compte cmpt;
        int code;
        FILE *file;

        printf("Code compte : ");
        scanf("%d", &code);

        file = fopen("compte.txt", "r");
        int found = 0;
        while (fread(&cmpt, sizeof(struct Compte), 1, file) && found == 0)
        {
            if (cmpt.code_cpt == code)
            {
        displayTransactionHistory(cmpt);
    }}}
    else if (a == 3)
    {
        gerer_operation(2);
    }
}}
