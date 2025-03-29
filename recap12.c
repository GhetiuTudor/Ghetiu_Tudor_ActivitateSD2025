#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Masina {
	int id;
	int anFabricatie;
	char* sofer;
	float kilometriiParcursi;
	char initialaProducator;
};

typedef struct Masina Masina;

Masina initializare(int id, int an, char* sofer, float km, char prod)
{
    Masina m;
    m.id=id;
    m.anFabricatie=an;
    if(sofer) 
    {
        m.sofer=(char*)malloc(strlen(sofer)+1);
        strcpy(m.sofer, sofer);
    }
    else m.sofer=NULL;
    m.kilometriiParcursi=km;
    m.initialaProducator=prod;
    return m;
}
 
void afisare(Masina m)
{
    printf("-------------------------\n");
    printf("ID: %d\n", m.id);
    printf("AN: %d\n", m.anFabricatie);
    printf("Sofer: %s \n",m.sofer );
    printf("Kilometri: %.2f\n", m.kilometriiParcursi);
    printf("Producator: %c\n", m.initialaProducator);
    printf("-------------------------\n");
}

void modSofer(Masina* m, char* sNou)
{
    if(m)
    {
        if(sNou)
        {
            free(m->sofer);
            m->sofer=NULL;
            m->sofer=(char*)malloc(strlen(sNou));
            strcpy(m->sofer, sNou);
        }
        else printf("sofer nou invalid");
    }
}

void dezalocare(Masina* m)
{
    if(m)
    {
        if(m->sofer)
        {
            free(m->sofer);
            m->sofer=NULL;
        }
    }
}

void afisareVector(Masina* vct, int nr)
{
    if(vct && nr>0)
    {
        for(int i=0;i<nr;i++)
        afisare(vct[i]);
    }
}

Masina* copiazaPrimeleElemente(Masina* vct, int nr, int nrElemCop)
{
    if(vct && nr && nrElemCop && nrElemCop<nr )
    {
        Masina* vctNou=malloc(sizeof(Masina)*nrElemCop);
        for(int i=0;i<nrElemCop;i++)
        {
            vctNou[i]=initializare(vct[i].id, vct[i].anFabricatie, vct[i].sofer, vct[i].kilometriiParcursi, vct[i].initialaProducator);

        }
        return vctNou;
    }
    return 0;
}

void dezalocareVector(Masina** vct, int nr)
{
    if((*vct) && nr>0)
    {
        for(int i=0;i<nr; i++)
        dezalocare(vct[i]);
        free(vct);
        vct=NULL;
    }
}

void copiazaMasiniCuKm(Masina* vct, char nr, float prag, Masina** vctNou, int* nrNou)
{
    if(vct && nr)
    {
        (*nrNou)=0;
        for(int i=0;i<nr;i++)
        if(vct[i].kilometriiParcursi>prag)
        (*nrNou)++;
        //dezalocareVector(vctNou,(*nrNou));
        free(*vctNou); //in caz ca primim un vct care nu e gol
        int c=0;
        (*vctNou)=malloc(sizeof(Masina)* (*nrNou));
        for(int i=0;i<nr;i++)
        if(vct[i].kilometriiParcursi>prag)
        {
            (*vctNou)[c]=initializare(vct[i].id, vct[i].anFabricatie, vct[i].sofer, vct[i].kilometriiParcursi,vct[i].initialaProducator);
            c++;
        }
    }
}

Masina getPrimulSofer(Masina* vct, int nr, const char* soferCautat)
{
    if(vct && nr && soferCautat)
    {
        for(int i=0;i<nr;i++)
        if(strcmp(soferCautat, vct[i].sofer)==0) return vct[i];
    }
    return initializare(-1,-1,NULL,-1,'-');
}

int main()
{
    Masina m=initializare(1,2022,"tudor", 20, 'B');
    modSofer(&m, "ghetiu");
    //afisare(m);
    Masina* vector=malloc(sizeof(Masina)*3);
    Masina m2=initializare(2,2023,"Alex", 30, 'P');
    Masina m3=initializare(3,2024,"Vlad", 40, 'M');
    vector[0]=m;
    vector[1]=m2;
    vector[2]=m3;
    //afisareVector(vector, 3);
    Masina* vctNou=copiazaPrimeleElemente(vector, 3, 2);
    //afisareVector(vctNou,2);
    int nrNou=2;
    copiazaMasiniCuKm(vector, 3, 25, &vctNou,&nrNou);
    //afisareVector(vctNou, nrNou);
    Masina m4=getPrimulSofer(vector, 3,"ghetiu");
    //Masina m4=getPrimulSofer(vector, 3,"tudor");  nu exista
    afisare(m4);
    
    return 0;
}
