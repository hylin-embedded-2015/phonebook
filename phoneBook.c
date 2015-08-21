#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "phoneBook.h"

// global variable definitions

char *NAME_LIST_FILE_NAME = "randomized_name_list.txt";
int LAST_NAME_COUNT = 8000;

char *pNameArray;
PhoneBook *pPhoneBookLinkList;
PhoneBook* *pAddressArray;
int *pPosition;
HashCode *pHashArray;

// local function prototypes
int getOffset(int N);
void shuffle_link_list(void);

void read_names(){
    FILE *pFile = NULL;
    SINGLE_NAME *pSingleName = NULL;
    int i;
    char buf[80];

    //

    pNameArray = (char*)calloc(  LAST_NAME_COUNT, sizeof(SINGLE_NAME)  );
    pSingleName = (SINGLE_NAME*)pNameArray;

    pFile = fopen(NAME_LIST_FILE_NAME, "r");

    while(  (fgets((char*)pSingleName, MAX_LAST_NAME_SIZE, pFile)) != NULL  ){
        (*pSingleName)[  strlen((char*)pSingleName) - 1  ] = 0;

        pSingleName++;
    }

    fclose(pFile);

    printf("File name: %s\n", NAME_LIST_FILE_NAME);
    printf("Name count: %d\n", LAST_NAME_COUNT);
}

void build_link_list(void){
    SINGLE_NAME *pSingleName = NULL;
    int i = 0;
    int nameHash = 0;
    int offset;

    char tmpBuf[16];

    //

    pPhoneBookLinkList = calloc(  LAST_NAME_COUNT, sizeof(PhoneBook)  );


    // copy phonebook addresses

    pAddressArray = calloc(  LAST_NAME_COUNT, sizeof(PhoneBook*)  );

    for(i = 0; i < LAST_NAME_COUNT; i++){
        *(pAddressArray + i) = pPhoneBookLinkList + i;
    }

    // shuffle the linked list

    shuffle_link_list();

    // assign name into linked list

    pSingleName = (SINGLE_NAME*)pNameArray;
    for(i = 0; i < LAST_NAME_COUNT; i++){
        strcpy(  (pPhoneBookLinkList + i)->lastName, (char*)(pSingleName + i)  );

        nameHash = toHash((char*)(pSingleName + i));
        (pPhoneBookLinkList + i)->hash = nameHash;
    }

    // assign pNext

    for(i = 0; i < LAST_NAME_COUNT - 1; i++){
        offset = getOffset(i + 1);

        (pPhoneBookLinkList + i)->pNext = *(pAddressArray + offset);
    }

    (pPhoneBookLinkList + LAST_NAME_COUNT - 1)->pNext = NULL;

    // assign hashes to pHashArray

    pHashArray = calloc(LAST_NAME_COUNT, sizeof(HashCode));

    pSingleName = (SINGLE_NAME*)pNameArray;
    for(i = 0; i < LAST_NAME_COUNT; i++){
        nameHash = toHash((char*)(pSingleName + i));
        *(pHashArray + i) = nameHash;
    }
}

void shuffle_link_list(){
    int i = 0, j = 0, tmp = 0;
    PhoneBook *pPhoneBookTmp = NULL;

    pPosition = calloc(LAST_NAME_COUNT, sizeof(int));

    for(i = 0; i < LAST_NAME_COUNT; i++){
        *(pPosition + i) = i;
    }

    srand(8413);

    for(i = 1; i < LAST_NAME_COUNT - 1; i++){
        j = i + (rand() % (LAST_NAME_COUNT - 1 - i));

        pPhoneBookTmp = *(pAddressArray + i);
        *(pAddressArray + i) = *(pAddressArray + j);
        *(pAddressArray + j) = pPhoneBookTmp;

        tmp = *(pPosition + i);
        *(pPosition + i) = *(pPosition + j);
        *(pPosition + j) = tmp;
    }
}

HashCode toHash(char *pName){
    HashCode h = 0;
    int c, i;

    int len = strlen(pName);
    for(i = 0; i < len; i++){
        c = *(pName + i);
        h = c + (h << 6) + (h << 16) - h;
    }

    //printf("0x%08X\n", h);

    return(h);
}

int getOffset(int N){
    int i = 0;

    for(i = 0; i < LAST_NAME_COUNT; i++){
        if(  *(pPosition + i) == N  )
            return(i);
    }
    printf("No offset found for '%d'\n", N);

    return(-1);
}
