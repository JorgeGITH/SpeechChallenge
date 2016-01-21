#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

FILE *appleComputer;
FILE *appleFruit;

// Relevant words:
// Words that are different in both tests
char **relWordsComp;
char **relWordsFruit;

#define MAX_WORDS_TRAINING 1000000

void obtain_relevant()
{
    int c1,c2;
    char *wordComp[MAX_WORDS_TRAINING];
    char *wordFruit[MAX_WORDS_TRAINING];
    int i=0,j=0,len,m,n,k,z;
    int found;
    
    appleComputer = fopen("apple-computers.txt", "r");
    if(!appleComputer)
    {
        printf("Error opening file: appleComputer \n");
        fflush(stdout);
    }
    
    do
    {
        wordComp[i] = (char*) malloc (100*sizeof(char));
        fscanf(appleComputer,"%s",wordComp[i]);
        
        len = strlen(wordComp[i]);
        if (wordComp[i][len-1]=='.' || wordComp[i][len-1]==',' || wordComp[i][len-1]==':')
            wordComp[i][len-1]='\0';
        
        //printf("%s",wordComp[i]);
        //fflush(stdout);
        
        i++;   
        
    }while((c1=getc(appleComputer))!= EOF);
    
    fclose(appleComputer);  
    
    appleFruit = fopen("apple-fruit.txt", "r");
    if(!appleFruit)
    {
        printf("Error opening file: appleFruit \n");
        fflush(stdout);
    }     
    
    do
    {
        wordFruit[j] = (char*) malloc (100*sizeof(char));
        fscanf(appleFruit,"%s",wordFruit[j]);
            
        len = strlen(wordFruit[j]);
        if (wordFruit[j][len-1]=='.' || wordFruit[j][len-1]==',' || wordFruit[j][len-1]==':')
            wordFruit[j][len-1]='\0';
        
        //printf("%s\n", wordFruit[j]);
        //fflush(stdout);
         
        j++;        
    }while((c2=getc(appleFruit))!= EOF);
    
    fclose(appleFruit);
    
    //Relevant context words for Apple-computer:
    k=0;
    relWordsComp = (char**) malloc (MAX_WORDS_TRAINING);
    for (m=0;m<i-1;m++)
    {
        found = 0;
        
        for(n=0;n<j-1;n++)
        {
            if (strcmp(wordComp[m],wordFruit[n])==0)
            {
                found=1;
                break;   
            }
        }
        
        if (found==0)
        {
           relWordsComp[k] = (char*) malloc (100*sizeof(char));
           strcpy(relWordsComp[k],wordComp[m]);
           //printf("relevant: %s \n",relWordsComp[k]);
           //fflush(stdout);
           k++;
        }       
    }
    
    //Relevant context words for Apple-fruit:
    k=0;
    relWordsFruit = (char**) malloc (MAX_WORDS_TRAINING);
    for (n=0;n<j-1;n++)
    {
        found = 0;
        
        for(m=0;m<i-1;m++)
        {
            if (strcmp(wordFruit[n], wordComp[m])==0)
            {
                found=1;
                break;   
            }
        }
        
        if (found==0)
        {
           
           relWordsFruit[k] = (char*) malloc (100*sizeof(char));
           strcpy(relWordsFruit[k],wordFruit[n]);
           //printf("relevant: %s \n",relWordsFruit[k]);
           //fflush(stdout);
           k++;
        }       
    }
}

int main() {

    char *line;
    int n=0,i,j,count;
    char c;
    
    //Decision counters:
    int isComputerRelated;
    int isFruitRelated;
    
    // This function get the differences between both tests. 
    obtain_relevant();
    
    scanf("%d",&n);
    
    if (n==0){
        printf("There are no lines to process \n");
        fflush(stdout);
        return -1;
    }
    
    for (i=0;i<n;i++)
    {
        count = 0;
        isComputerRelated = 0;
        isFruitRelated = 0;
        
        do{
            count ++;
            line = (char*)malloc(100*sizeof(char));
            scanf("%s", line);
           
            for (j = 0; relWordsComp[j] != NULL ; j++)
            {
                if (strcmp(relWordsComp[j],line)==0)
                    isComputerRelated++;                             
              
            }
            for (j = 0; relWordsFruit[j] != NULL ; j++)
            {
                if (strcmp(relWordsFruit[j],line)==0)
                    isFruitRelated++;
            }
            
            free(line);
            
        }while(((c=getc(stdin))!= '\n') && (count <= 1000));
        
        if(isComputerRelated > isFruitRelated)
            printf("computer-company\n");    
        else
            printf("fruit\n");
            
        fflush(stdout);
        
    }
    
    return 0;
}

