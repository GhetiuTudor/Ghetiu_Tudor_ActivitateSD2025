#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

//STACK
struct Nod{
    Masina info;
    struct Nod* next;
};
typedef struct Nod Nod;
//Alegeti prin ce veti reprezenta stiva si creati structura necesara acestei stive
//putem reprezenta o stiva prin LSI, LDI sau vector
void pushStack(Nod** stiva, Masina masina) {
    Nod* nou= (Nod*)malloc(sizeof(Nod));
    nou->info=masina;
    nou->next=*stiva;
    *stiva=nou;
}

Masina popStack(Nod** stiva) {
if(*stiva) 
{
   Nod* temp = *stiva;
    Masina m = temp->info;
    *stiva = temp->next;
    free(temp);
    return m;
}
else 
{
    Masina* m;
    return m;
}
}

int emptyStack(Nod* stiva) {
    if(stiva) return 1;
    else 0;
}

void* citireStackMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
    FILE* f= fopen(numeFisier,"r");
    Nod* stiva=NULL;
    while(!feof(f))
    {
        Masina m= citireMasinaDinFisier(f);
        pushStack(&stiva,m);
    }
    fclose(f);
    return stiva;
}

void dezalocareStivaDeMasini(Nod** stiva) {
	//sunt dezalocate toate masinile si stiva de elemente
    while(*stiva)
    {
        Masina m= popStack(stiva);
        free(m.model);
        free(m.numeSofer);
    }
}

int size(Nod* stiva) {
	//returneaza numarul de elemente din stiva
    int i=0;
    while(stiva) 
    {
        i++;
        stiva=stiva->next;
    }
}

//QUEUE
//Alegeti prin ce veti reprezenta coada si creati structura necesara acestei cozi
//putem reprezenta o coada prin LSI, LDI sau vector
struct NodDublu{
    struct NodDublu* next;
    struct NodDublu* prev;
    Masina info;
};
typedef struct NodDublu NodDublu;

struct Coada
{
NodDublu* front ;
NodDublu* rear;
};
typedef struct Coada Coada;

void enqueue(Coada* coada, Masina masina) {
	//adauga o masina in coada
    NodDublu* nou=(NodDublu*)malloc(sizeof(NodDublu));
    nou->info=masina;
    nou->next=NULL;
    nou->prev=NULL;
    if(coada->rear)
    {
        coada->rear->next=nou;
        //coada->rear=nou;
    }
    else 
    {
        coada->front=nou;
    }
    coada->rear=nou;
}



Masina dequeue(Coada* coada) {
	//extrage o masina din coada
    if(coada->front)
    {
        Masina m=coada->front->info;
        NodDublu* x=coada->front;
        coada->front=coada->front->next;
        free(x);
        if(coada->front=NULL)
        {
            coada->rear=NULL;
        }
        else coada->front->prev=NULL;
    return m;
    }
    Masina m;
    m.id=-1;
    return m;
}

Coada citireCoadaDeMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
    FILE* f= fopen(numeFisier,"r");
    Coada coada;
    coada.front=NULL;
    coada.rear=NULL;
    while(!feof(f))
    {
        Masina m= citireMasinaDinFisier(f);
        enqueue(&coada,m);
    }
    fclose(f);
    return coada;
}

void dezalocareCoadaDeMasini(Nod** stiva) {
	//sunt dezalocate toate masinile si coada de elemente
    Nod* temp=NULL;
    float sum=0;
    while(!emptyStack(*stiva))
    {
        Masina m=popStack(stiva);
        sum+=m.pret;
        pushStack(&temp,m);
    }
    while(!emptyStack(temp))
    {
        pushStack(stiva,popStack(&temp));
    }
    return sum;
}



int main() {


	return 0;
}
