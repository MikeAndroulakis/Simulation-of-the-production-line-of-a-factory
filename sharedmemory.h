#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

typedef struct data{        //shared memory storages a struct
    int numofcomponents;//synolikos arithmos eksartimatwn(1+2+3)
    int numofcomp1;//arithmos eksarthmatwn 1
    int numofcomp2;//arithmos eksarthmatwn 2
    int numofcomp3;//arithmos eksarthmatwn 3
    int comp1[1000];//edw fylagontai ta id twn eksarthmatwn 1
    int comp2[1000];//edw fylagontai ta id twn eksarthmatwn 2
    int comp3[1000];//edw fylagontai ta id twn eksarthmatwn 3
    int bafeio[3000];//edw fyllagontai ta id twn eksarthmatwn poy exoyn bgei apo to bafeio
    int numofpaintedcomp;//arithmos eksartimatwn poy baftikan
    int timeforpaint[3000];//xronos kathe eksartimatos wste na katalabei to bafeio
    int check1[1000];//pinakas me ta id twn eksartimatwn 1 poy exoyn elegxthei
    int numofcheck1;//arithmos eksartimatwn 1 poy exoyn elegxthei
    int check2[1000];//pinakas me ta id twn eksartimatwn 2 poy exoyn elegxthei
    int numofcheck2;//arithmos eksartimatwn 2 poy exoyn elegxthei
    int check3[1000];//pinakas me ta id twn eksartimatwn 3 poy exoyn elegxthei
    int numofcheck3;//arithmos eksartimatwn 3 poy exoyn elegxthei
    int constructedcomponents[3000][3];//pinakas me ta id twn eksartimatwn poy bghkan apo th synarmologisi
    int numofconstructed;//arithmos synarmologimenwn mhxanimatwn
    int currentcomp[1][3];//pinakas poy fyllaei ta eksartimata poy kataskeyazontai twra
}MemData;

int ShMCreate(key_t);

MemData *ShMAttach(int);

int ShMDetach(MemData*);

int ShMDelete(int);
