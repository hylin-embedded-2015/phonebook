#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "phoneBook.h"

void release_memory(void);
void dumpLinkList(void);
void dumpAddressArray(void);

PhoneBook *FindName(char Last[], PhoneBook *pHead){
    while (pHead != NULL) {
        if(strcasecmp(Last, pHead->lastName) == 0) return pHead;
        pHead = pHead->pNext;
    }

    return NULL;
}

PhoneBook *FindNameVer2(char *pName, PhoneBook *pHead){
    HashCode nameHash = toHash(pName);

    while (pHead != NULL) {
        if(nameHash == pHead->hash){
            if(strcasecmp((char*)pName, pHead->lastName) == 0) return pHead;
        }
        pHead = pHead->pNext;
    }

    return NULL;
}

PhoneBook *FindNameVer3(char *pName, PhoneBook *pHead){
    int i = 0;
    HashCode nameHash = toHash(pName);
    PhoneBook *pbTmp = NULL;
    PhoneBook* *ppbTmp = NULL;

    for(i = 0; i < LAST_NAME_COUNT; i++){
        if(nameHash != *(pHashArray + i)) continue;

        ppbTmp = (pAddressArray + i);
        pbTmp = *ppbTmp;

        if(strcasecmp((char*)pName, (char*)pbTmp->lastName) != 0) continue;

        return *(pAddressArray + i);
    }

    return NULL;
}

int main(void){
    int repeatCount = 1000, i = 0, c = 0;

    char target[] = "sada";
    PhoneBook *found = NULL;

    clock_t t_begin, t_end;
    double t_spent;

    /* VERSIONS */
    PhoneBook* (*FindNameAlgorithm[3])(char*, PhoneBook*);
    int ALGORITHM_NUM = 3;

    //

    read_names();

    //
    build_link_list();

    /* different versions of algorithms for finding last name*/
    FindNameAlgorithm[0] = FindName;
    FindNameAlgorithm[1] = FindNameVer2;
    FindNameAlgorithm[2] = FindNameVer3;

    printf("\nTarget last name: '%s'\n", target);

    for(c = 0; c < ALGORITHM_NUM; c++){
        // timer begins
        t_begin = clock();

        // do the finding many times
        for(i = 0; i < repeatCount; i++){
            found = (*FindNameAlgorithm[c])(target, pPhoneBookLinkList);
        }

        // timer stopped
        t_end = clock();
        t_spent = (double)(t_end - t_begin) / CLOCKS_PER_SEC;
        printf("Ver %d: total time is %f sec \n", c, t_spent / (double)repeatCount);

        if(found == NULL){
            printf("name not found\n\n");
        }else{
            printf("found name is: '%s'\n\n", found->lastName);
        }
    }

    //
    release_memory();

    return(0);
}

void release_memory(void){
    free(pNameArray);
    free(pPhoneBookLinkList);
    free(pAddressArray);
    free(pPosition);
    free(pHashArray);
}
