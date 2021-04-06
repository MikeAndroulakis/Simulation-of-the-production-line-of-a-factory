#include "semaphores.h"

int semCreate(key_t key, int nsems, int val){//epistrefei to id toy shmaforoy poy eftiakse
    int semid,i;
    union semun arg;
    int error;

    if ((key < 0) || (nsems <= 0))
        return -1;

    semid = semget(key, nsems, 0666|IPC_CREAT);//id gia ton shmaforo

    if (semid < 0)//an einai arnhtiko tote epestrepse lathos
        return -1;

    arg.val = val;

    for(i = 0; i < nsems; i++){

        error = semctl(semid,i,SETVAL,arg);
        if (error < 0)
            return -1;
    }

    return semid;
}

int semDown(int semid,int sem_num){
    struct sembuf sb;

    if((semid < 0) || (sem_num < 0))
        return -1;

    sb.sem_num = sem_num;
    sb.sem_op = -1;//h timh ginetai -1 wste na mh mporei na prospelastei
    sb.sem_flg = 0;

    return semop(semid,&sb,1);
}

int semUp(int semid, int sem_num){
    struct sembuf sb;

    if((semid < 0) || (sem_num < 0))
        return -1;

    sb.sem_num = sem_num;
    sb.sem_op = 1;//h timh ginetai ksana 1 kai einai ksana prospelasimos o shmaforos
    sb.sem_flg = 0;

    return semop(semid,&sb,1);
}

int semDel(int semid){

    if(semid < 0)
        return -1;

    return semctl(semid,0,IPC_RMID);//diagrafh shmaforou
}



