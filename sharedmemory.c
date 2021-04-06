#include "sharedmemory.h"

int ShMCreate(key_t key){

    if(key<0){
      printf("*** key error ***");
      return -1;
    }

    return shmget(key, sizeof(MemData), IPC_CREAT | 0666);//dhmioyrgia id gia th mnhmh
}

MemData* ShMAttach(int ShmID){//epistrofh deikth sth mnhmh
    return shmat(ShmID, (void *)0, 0);
}

int ShMDetach(MemData* ShmPTR){//apodesmeysh mnhmhs
    return shmdt(ShmPTR);
}

int ShMDelete(int ShmID){//katastrofh toy shared memory
    return shmctl(ShmID, IPC_RMID, 0);
}
