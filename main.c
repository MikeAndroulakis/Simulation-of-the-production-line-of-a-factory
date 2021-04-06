#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>
#include <sys/sem.h>
#include "semaphores.h"
#include "sharedmemory.h"

typedef struct comp{
    int id;
    char type;
    struct comp *previous;

}component;

int main(int argc,char **argv){
    srand(time(NULL));
    int N;
    int i,j;
    N=atoi(argv[1]);//arithmos eksarthmatwn
    
    key_t key;
    if ((key = ftok("main.c", 'q')) == -1) {
        printf("*** ftok error ***\n");
        exit(1);
    }
    int shmid1=ShMCreate(key);//epistrefei ena kleidi kai dimioyrgei to shm oso kai to SHSIZE me 666 kritiria
    if(shmid1<0){//ean ayto poy epistrefei einai mikrotero toy 0 tote to shared memory den egine
	perror("shmget");
	exit(1);
    }
    MemData *shmptr;
    shmptr=ShMAttach(shmid1);//epistrefei enan deikti se ayto to shm wste na apothikeyoume ekei ta eksartimata arxizontas apo ayton
    if(shmptr==(MemData *)-1){
	perror("shmat");
        exit(1);
    }
    shmptr->numofcomponents=0;//arxikopoihsh twn metablhtwn toy shared memory
    shmptr->numofcomp1=0;//arxikopoihsh twn metablhtwn toy shared memory
    shmptr->numofcomp2=0;//arxikopoihsh twn metablhtwn toy shared memory
    shmptr->numofcomp3=0;//arxikopoihsh twn metablhtwn toy shared memory



    if ((key = ftok("main.c", 'o')) == -1) {//dhmioyrgia tyxaioy kleidioy
        printf("*** ftok error ***\n");
        exit(1);
    }
    int semidnumberofcomp=semCreate(key,1,1);//dhmioyrgia shmaforoy gia th kataskeyh twn components

    if ((key = ftok("main.c", 's')) == -1) {//dhmioyrgia tyxaioy kleidioy
        printf("*** ftok error ***\n");
        exit(1);
    }
    int sembafeio=semCreate(key,1,1);//dhmioyrgia shmaforoy gia to bafeio
    
    if ((key = ftok("main.c", 'g')) == -1) {//dhmioyrgia tyxaioy kleidioy
        printf("*** ftok error ***\n");
        exit(1);
    }
    int semcheck1=semCreate(key,1,1);//dhmioyrgia shmaforoy gia ton elegxo twn eksarthmatwn 1

    if ((key = ftok("main.c", 'h')) == -1) {//dhmioyrgia tyxaioy kleidioy
        printf("*** ftok error ***\n");
        exit(1);
    }
    int semcheck2=semCreate(key,1,1);//dhmioyrgia shmaforoy gia ton elegxo twn eksarthmatwn 2

    if ((key = ftok("main.c", 'k')) == -1) {//dhmioyrgia tyxaioy kleidioy
        printf("*** ftok error ***\n");
        exit(1);
    }
    int semcheck3=semCreate(key,1,1);//dhmioyrgia shmaforoy gia ton elegxo twn eksarthmatwn 3
    
    if ((key = ftok("main.c", 'b')) == -1) {//dhmioyrgia tyxaioy kleidioy
        printf("*** ftok error ***\n");
        exit(1);
    }
    int semconstruction=semCreate(key,1,1);//dhmioyrgia shmaforoy gia th kataskeyh
    
    

    for(i=0;i<3000;i++){//arxikopoihsh twn pinakwn toy shared memory
	shmptr->comp1[i]=0;
	shmptr->comp2[i]=0;
	shmptr->comp3[i]=0;
    }
    for(i=0;i<9000;i++){//arxikopoihsh twn pinakwn toy shared memory
	shmptr->bafeio[i]=0;
    }
    shmptr->numofpaintedcomp=0;
    for(i=0;i<3000;i++){//arxikopoihsh twn pinakwn toy shared memory
	shmptr->check1[i]=0;
	shmptr->check2[i]=0;
	shmptr->check3[i]=0;
    }
    shmptr->numofcheck1=0;
    shmptr->numofcheck2=0;
    shmptr->numofcheck3=0;
    shmptr->numofconstructed=0;
    for(i=0;i<3000;i++){//arxikopoihsh twn pinakwn toy shared memory
	for(j=0;j<3;j++){
	    shmptr->constructedcomponents[i][j]=0;
	}
    }
    for(i=0;i<3;i++){//arxikopoihsh twn pinakwn toy shared memory
	shmptr->currentcomp[1][i]=0;
    }
    pid_t pid=1;
    for(i=0;i<9;i++){//h for tha ginei gia ta 8 stadia
	if(pid>0){//an eimaste sto patera tote dhmioyrghse paidi
	    pid=fork();
	}
	if(pid==-1){//an apetyxe epestrepse lathos
	    printf("Failed to create the fork\n");
	}
	else if(pid==0){//an einai to paidi
	    switch(i){
		case 1:
		    semDown(semidnumberofcomp,0);//katalipsi toy kataskeyastikoy kentroy twn eksartimatwn
		    while(shmptr->numofcomp1<N){//mexri na kataskeyastoyn N eksarthmata 1hs takshs
			shmptr->comp1[shmptr->numofcomp1]=1000+shmptr->numofcomp1;//edw apothikeyontai ta id twn eksartimatwn 1(ta id twn eksartimatwn 1 arxizoyn apo 1000)
			shmptr->numofcomp1++;
			shmptr->numofcomponents++;//ayksanetai o arithmos twn eksartimatwn poy exoyn ftiaxtei
		    }
		    semUp(semidnumberofcomp,0);//apodesmeyetai to kentro gia allo eksartima
		    break;
		case 2:
		    semDown(semidnumberofcomp,0);//katalipsi toy kataskeyastikoy kentroy twn eksartimatwn
		    while(shmptr->numofcomp2<N){//mexri na kataskeyastoyn N eksarthmata 2hs takshs
			shmptr->comp2[shmptr->numofcomp2]=4000+shmptr->numofcomp2;//edw apothikeyontai ta id twn eksartimatwn 2(ta id twn eksartimatwn 2 arxizoyn apo 4000)
			shmptr->numofcomp2++;
			shmptr->numofcomponents++;//ayksanetai o arithmos twn eksartimatwn poy exoyn ftiaxtei
		    }
		    semUp(semidnumberofcomp,0);//apodesmeyetai to kentro gia allo eksartima
		    break;
		case 3:
		    semDown(semidnumberofcomp,0);//katalipsi toy kataskeyastikoy kentroy twn eksartimatwn
		    while(shmptr->numofcomp3<N){//mexri na kataskeyastoyn N eksarthmata 3hs takshs
			shmptr->comp3[shmptr->numofcomp3]=7000+shmptr->numofcomp3;//edw apothikeyontai ta id twn eksartimatwn 3(ta id twn eksartimatwn 3 arxizoyn apo 7000)
			shmptr->numofcomp3++;
			shmptr->numofcomponents++;
		    }
		    semUp(semidnumberofcomp,0);
		    break;
		case 4:
		    while(shmptr->numofpaintedcomp<3*N){//mexri na bafoyn ola ta eksartimata
			int k;
			for(k=0;k<N;k++){
			    clock_t start,end;
			    double cpu_time_used;
			    start=clock();//o yparxon xronos
			    semDown(sembafeio,0);//katalipsi bafeioy
			    end=clock();//o xronos me to poy desmeytike to bafeio
			    cpu_time_used=((double)(end-start));//o xronos poy ekane gia na katalifthei
			    shmptr->timeforpaint[shmptr->numofpaintedcomp]=cpu_time_used;//o xronos aytoy toy eksartimatos fylassetai sto pinaka
			    if(shmptr->comp1[k]!=0){//an ayto to antikeimeno den exei baftei
				shmptr->bafeio[shmptr->numofpaintedcomp]=shmptr->comp1[k];//apothikeyetai to id sto pinaka toy bafeioy
				shmptr->numofpaintedcomp++;
				shmptr->comp1[k]=0;
			    }
			    else if(shmptr->comp2[k]!=0){//an ayto to antikeimeno den exei baftei
				shmptr->bafeio[shmptr->numofpaintedcomp]=shmptr->comp2[k];//apothikeyetai to id sto pinaka toy bafeioy
				shmptr->numofpaintedcomp++;//ayksanetai o metritis
				shmptr->comp2[k]=0;
			    }
			    else if(shmptr->comp3[k]!=0){//an ayto to antikeimeno den exei baftei
				shmptr->bafeio[shmptr->numofpaintedcomp]=shmptr->comp3[k];//apothikeyetai to id sto pinaka toy bafeioy
				shmptr->numofpaintedcomp++;
				shmptr->comp3[k]=0;
			    }
			    semUp(sembafeio,0);//apodesmeysh bafeioy
			}
		    }
		    break;
		case 5:
		    while(shmptr->numofcheck1<N){//mexri na elegxtoyn ola ta eksartimata 1hs takshs
			semDown(semcheck1,0);//desmeysh toy kentroy elegxoy twn eksartimatwn 1
			int k;
			for(k=0;k<3*N;k++){
			    if(shmptr->bafeio[k]>=1000&&shmptr->bafeio[k]<4000){//an to eksartima einai typoy 1
				shmptr->check1[shmptr->numofcheck1]=shmptr->bafeio[k];//apotheikeysi sto pinaka
				//printf("check1:%d\n",shmptr->check1[shmptr->numofcheck1]);
				shmptr->numofcheck1++;
				shmptr->bafeio[k]=0;
				
			    }
			}
			semUp(semcheck1,0);//apodesmeysh toy kentroy elegxoy twn eksartimatwn 1
		    }
		    break;
		case 6:
		    
		    while(shmptr->numofcheck2<N){//mexri na elegxtoyn ola ta eksartimata 2hs takshs
			semDown(semcheck2,0);//desmeysh toy kentroy elegxoy twn eksartimatwn 2
			int k;
			for(k=0;k<3*N;k++){
			    if(shmptr->bafeio[k]>=4000&&shmptr->bafeio[k]<7000){//an to eksartima einai typoy 2
				shmptr->check2[shmptr->numofcheck2]=shmptr->bafeio[k];//apotheikeysi sto pinaka
				//printf("check2:%d\n",shmptr->check2[shmptr->numofcheck2]);
				shmptr->numofcheck2++;
				shmptr->bafeio[k]=0;
				break;
			    }
			}
			semUp(semcheck2,0);//apodesmeysh toy kentroy elegxoy twn eksartimatwn 2
		    }
		    break;
		case 7:
		    while(shmptr->numofcheck3<N){//mexri na elegxtoyn ola ta eksartimata 3hs takshs
			semDown(semcheck3,0);//desmeysh toy kentroy elegxoy twn eksartimatwn 3
			int k;
			for(k=0;k<3000;k++){//NA ALLAKSW TO 3000 SE 9000
			    if(shmptr->bafeio[k]>=7000&&shmptr->bafeio[k]<10000){//an to eksartima einai typoy 3
				shmptr->check3[shmptr->numofcheck3]=shmptr->bafeio[k];//apotheikeysi sto pinaka
				shmptr->numofcheck3++;
				shmptr->bafeio[k]=0;
				break;
			    }
			}
		        semUp(semcheck3,0);//apodesmeysh toy kentroy elegxoy twn eksartimatwn 3
		    }
		    break;
		case 8:
		    sleep(3);//anamonh wste na elegxthoun kapoia antikeimena
		    while(shmptr->numofconstructed<N){//mexri na kataskeyastoyn N antikeimena
			semDown(semconstruction,0);//desmeysh toy kataskeyastikoy kentroy
			int k;
			if(shmptr->currentcomp[0][0]==0){//ean dhmioyrgoyme neo antikeimeno
			    for(k=0;k<N;k++){//elegxoyme ta kenta elegxoy
				int value=rand()%3;//epilegoyme tyxaia mia apo tis 3 kathgories eksartimatwn
				int pos=rand()%shmptr->numofcheck1;//epilegoyme tyxaia ena eksartima poy exei elegxthei
				if((shmptr->check1[pos]!=0)&&(value==0)){//an einai eksartima 1 
				    shmptr->currentcomp[0][0]=shmptr->check1[pos];//to apothikeyoyme ston proswrino pinaka
				    shmptr->check1[pos]=0;//mhdenizetai to eksartima wste na mi ksanampei se kataskeyh
				    break;
				}
				else if((shmptr->check2[pos]!=0)&&(value==1)){//an einai eksartima 2
				    shmptr->currentcomp[0][0]=shmptr->check2[pos];//to apothikeyoyme ston proswrino pinaka
				    shmptr->check2[pos]=0;//mhdenizetai to eksartima wste na mi ksanampei se kataskeyh
				    break;
				}
				else if((shmptr->check3[pos]!=0)&&(value==2)){//an einai eksartima 3
				    shmptr->currentcomp[0][0]=shmptr->check3[pos];//to apothikeyoyme ston proswrino pinaka
				    shmptr->check3[pos]=0;//mhdenizetai to eksartima wste na mi ksanampei se kataskeyh
				    break;
				}
			    }
			}
			else if(shmptr->currentcomp[0][1]==0){//an exei mpei ena eksartima hdh sth synarmologisi 
			    if(shmptr->currentcomp[0][0]<4000){//elegxoyme ti typoy eksartima einai
				for(k=0;k<N;k++){//an einai typoy 1
				    int value=rand()%2;
				    int pos=rand()%shmptr->numofcheck2;//dialegoyme tyxaia ena typoy 2 h 3
				    if((shmptr->check2[pos]!=0)&&(value==0)){//an exei elegxthei ayto
					shmptr->currentcomp[0][1]=shmptr->check2[pos];//to apothikeyoyme ston proswrino pinaka
					shmptr->check2[pos]=0;//mhdenizetai to eksartima wste na mi ksanampei se kataskeyh
					break;
				    }
				    else if((shmptr->check3[pos]!=0)&&(value==1)){//an exei elegxthei
					shmptr->currentcomp[0][1]=shmptr->check3[pos];//to apothikeyoyme ston proswrino pinaka
					shmptr->check3[pos]=0;//mhdenizetai to eksartima wste na mi ksanampei se kataskeyh
					break;
				    }
				}
			    }
			    else if(shmptr->currentcomp[0][0]<7000){//an to antikeimeno poy exei mpei sth synarmologhsh einai typoy 2
				for(k=0;k<N;k++){
				    int value=rand()%2;
				    int pos=rand()%shmptr->numofcheck1;//epilegoyme tyxaia ena typoy 1 h 3
				    if((shmptr->check1[pos]!=0)&&(value==0)){//an exei elegxthei to typou 1
					shmptr->currentcomp[0][1]=shmptr->check1[pos];//to apothikeyoyme ston proswrino pinaka
					shmptr->check1[pos]=0;//mhdenizetai to eksartima wste na mi ksanampei se kataskeyh
					break;
				    }
				    else if((shmptr->check3[pos]!=0)&&(value==1)){//an exei elegxthei to typou 3
					shmptr->currentcomp[0][1]=shmptr->check3[pos];//to apothikeyoyme ston proswrino pinaka
					shmptr->check3[pos]=0;//mhdenizetai to eksartima wste na mi ksanampei se kataskeyh
					break;
				    }
				}
			    }
			    else{//alliws an to antikeimeno poy exei mpei einai typoy 3
				for(k=0;k<N;k++){
				    int value=rand()%2;//epilegoyme tyxaia ena typoy 1 h 2
				    int pos=rand()%shmptr->numofcheck1;
				    if((shmptr->check1[pos]!=0)&&(value==0)){
					shmptr->currentcomp[0][1]=shmptr->check1[pos];//to apothikeyoyme ston proswrino pinaka
					shmptr->check1[pos]=0;//mhdenizetai to eksartima wste na mi ksanampei se kataskeyh
					break;
				    }
				    else if((shmptr->check2[pos]!=0)&&(value==1)){
					shmptr->currentcomp[0][1]=shmptr->check2[pos];//to apothikeyoyme ston proswrino pinaka
					shmptr->check2[pos]=0;//mhdenizetai to eksartima wste na mi ksanampei se kataskeyh
					break;
				    }
				}
			    }
			}
			else if(shmptr->currentcomp[0][2]==0){//an sth trexoysa synarmologhsh exoyn mpei 2 eksartimata
			    if((shmptr->currentcomp[0][0]<7000)&&(shmptr->currentcomp[0][1]<7000)){//an ta eksartimata poy exoyn mpei einai typou 1 kai 2 tote theloyme eksartima typoy 3
				for(k=0;k<N;k++){
				    if(shmptr->check3[k]!=0){
					shmptr->currentcomp[0][2]=shmptr->check3[k];//to apothikeyoyme ston proswrino pinaka
					shmptr->check3[k]=0;//mhdenizetai to eksartima wste na mi ksanampei se kataskeyh
				        break;
				    }
				}
			    }
			    else if((shmptr->currentcomp[0][0]>4000)&&(shmptr->currentcomp[0][1]>4000)){//an ta eksartimata poy exoyn mpei sth synarmologhsh einai typoy 2 kai 3 tote theloyme na baloyme typoy 1
				for(k=0;k<N;k++){
				    if(shmptr->check1[k]!=0){
					shmptr->currentcomp[0][2]=shmptr->check1[k];//to apothikeyoyme ston proswrino pinaka
					shmptr->check1[k]=0;//mhdenizetai to eksartima wste na mi ksanampei se kataskeyh
				        break;
				    }
				}
			    }
			    else{//alliws an ta eksartimata poy exoyn mpei einai typoy 1 kai 3 theloyme na baloyme ena typoy 2
				for(k=0;k<N;k++){
				    if(shmptr->check2[k]!=0){
					shmptr->currentcomp[0][2]=shmptr->check2[k];//to apothikeyoyme ston proswrino pinaka
					shmptr->check2[k]=0;//mhdenizetai to eksartima wste na mi ksanampei se kataskeyh
				        break;
				    }
				}
			    }
			    shmptr->constructedcomponents[shmptr->numofconstructed][0]=shmptr->currentcomp[0][0];//apothikeysi twn
			    shmptr->constructedcomponents[shmptr->numofconstructed][1]=shmptr->currentcomp[0][1];//eksartimatwn
			    shmptr->constructedcomponents[shmptr->numofconstructed][2]=shmptr->currentcomp[0][2];//poy exoyn synarmologithei
			    shmptr->numofconstructed++;
			    for(k=0;k<3;k++){
				shmptr->currentcomp[0][k]=0;//o proswrinos pinakas mhdenizetai gia thn epomenh synarmologisi
			    }
			}
			semUp(semconstruction,0);//apeleytherwsh toy synarmologitikoy kentroy
		    }
		    break;
	    }
	}
	if(pid==0){
	    break;
	}
	
    }
    int status=0;
    int wpid;
    int k;
    double time=0;
    double averagetime;
    while ((wpid = wait(&status)) > 0);//o pateras perimenei to paidi
    if(i==9){//an eimaste sto teleytaio paidi ginontai oi ektypwseis
	for(k=0;k<shmptr->numofpaintedcomp;k++){
	    time+=shmptr->timeforpaint[k];
	}
	averagetime=((double)time)/((double)(shmptr->numofpaintedcomp));
	
        for(i=0;i<shmptr->numofconstructed;i++){
            printf("%d  %d  %d\n",shmptr->constructedcomponents[i][0],shmptr->constructedcomponents[i][1],shmptr->constructedcomponents[i][2]);
        }
	printf("Mesos xronos anamonhs gia katalahpsh bafeioy:%f nanoseconds\n",averagetime);
        printf("Arithmos kataskeyasmatwn:%d\n",shmptr->numofconstructed);
	semDel(semidnumberofcomp);//diagrafh twn shmaforwn
	semDel(sembafeio);//diagrafh twn shmaforwn
	semDel(semcheck1);//diagrafh twn shmaforwn
	semDel(semcheck2);//diagrafh twn shmaforwn
	semDel(semcheck3);//diagrafh twn shmaforwn
	semDel(semconstruction);//diagrafh twn shmaforwn
	ShMDetach(shmptr);//apodesmeysh mnhmhs
	ShMDelete(shmid1);//diagrafh mnhmhs
    }
}

