#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H
#define MAX_LAST_NAME_SIZE 16

typedef unsigned int HashCode;
typedef struct __PHONE_BOOK_ENTRY{
    char lastName[MAX_LAST_NAME_SIZE];
    HashCode hash;
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
    struct __PHONE_BOOK_ENTRY *pNext;
} PhoneBook;

typedef char SINGLE_NAME [MAX_LAST_NAME_SIZE];

extern char *NAME_LIST_FILE_NAME;
extern int LAST_NAME_COUNT;

extern char *pNameArray;
extern PhoneBook *pPhoneBookLinkList;
extern PhoneBook* *pAddressArray;
extern int *pPosition;
extern HashCode *pHashArray;

extern void read_names(void);
extern void build_link_list(void);
extern HashCode toHash(char *pName);

#endif
