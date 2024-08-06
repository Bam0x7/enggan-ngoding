#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>

struct Word{
    char word[20];
    struct Word *next;
};

void addWord(struct Word **head,const char* word)
{
    struct Word *newNode = (struct Word*)malloc(sizeof(struct Word));
    if(newNode==NULL){
        perror("newNode: ");
    }
    strncpy(newNode->word,word,strlen(word));
    newNode->next = *head;
    *head = newNode;
}

const char *getRandomWord(struct Word *head)
{
    int count = 0;
    struct Word *current = head;
    while(current!=NULL){
        count++;
        current = current->next;
    }

    int randomIndex = rand()%count;

    current=head;
    for(int i=0;i<randomIndex;i++){
        current=current->next;
    }
    return current->word;
}

int main()
{
    srand(time(NULL));

    struct Word *wordlist = NULL;

    addWord(&wordlist, "sangu");
    addWord(&wordlist, "bangsat");
    addWord(&wordlist, "sayang");


    printf("permainan tebak kata\n");

    int score=10;
    int continuePlaying = 1;

    while(continuePlaying){
        const char *selectWord = getRandomWord(wordlist);

        char guess[20];
        printf(">> masukan kata: ");
        scanf("%s",guess);

        if(strcmp(guess,selectWord)==0){
            printf("benar!!\n");
            score +=2;
        }else{
            printf("salah!!\n");
            score -=2;
        }
        printf("skor anda: %d\n" ,score);
        if(score==0){
            printf("score anda habis, anda kalah\n");
            break;
        }else if(score==20){
            printf("anda hebat:D\n");
        }else if(score==50){
            printf("wow, savage\n");
        }else if(score==70){
            printf("OMG!!, legendary\n");
        }else if(score>100){
            printf("sungkem puh, sepuh ini mah\n");
        }
        printf("lanjut? (1: ya, 0: tidak)\n");
        scanf("%d" ,&continuePlaying);

        if(continuePlaying==1){
            continue;
        }else if(continuePlaying==0){
            printf("keluar\n");
            break;
        }else{
            printf("opsi salah,coba lagi\n");
            continue;
        }
    }

    struct Word *current = wordlist;
    struct Word *next;

    while(current!=NULL){
        next = current->next;
        free(current);
        current=next;
    }

    return EXIT_SUCCESS;
}