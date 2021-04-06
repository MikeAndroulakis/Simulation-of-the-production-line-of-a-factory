#include <unistd.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>

union semun{//domh aparaithth gia kapoies synarthseis twn shmaforwn
    int val;
    struct semid_ds *buf;
    ushort *array;
};

int semCreate(key_t,int,int);

int semDown(int,int);

int semUp(int,int);

int semDel(int);
