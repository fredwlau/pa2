#include "first.h"

// function to create a node with the desired data
// and to initialize all the children of the newly
// created node to NULL
node *makeNode(char c){
    node *temp=NULL;
    temp = (node*)malloc(sizeof(node));
    if (temp){
        int i;
        temp->data=c;
        temp->isword = 0, temp->occur=0, temp->prefix=0, temp->numChild=0;
        for (i=0; i<26; i++){
            temp->child[i]=NULL;
        }
    }
    return temp;
}

// recursive function to traverse the Trie in order to print
// the correct data into the output file
void traverse(node*temp, char word[200], int size){
    if(temp==NULL){
        return;
    }
    if(temp->isword){
        
        word[size]='\0';
        fprintf(outputFile, "%s %d %d\n", word, temp->occur, temp->prefix);
    }
    int i;
    for(i=0; i<26; i++){
        if(temp->child[i]){
            
            word[size]='a'+i;
            traverse(temp->child[i], word, size+1);
        }
    }
}

// function to insert a word into the Trie
// calls the makeNode function to properly
// handle the resulting children
void insertword(char *temparr, node *root){
    int i, j, k=strlen(temparr);
    node *temp=root;
    for (i=0; i<k; i++){
        j=CHAR_TO_INDEX(temparr[i]);
        if(!temp->child[j]){
            temp->numChild++;
            temp->child[j]=makeNode(temparr[i]);

        }
        
        temp=temp->child[j];
    }
    temp->isword=1;
}

// function to match the word provided to us from
// the data file and see if a word in our Trie matches
// completely or as a prefix
void matchStr(char*temparr){
    int i, j, k=strlen(temparr);
    node* temp=root;
    for (i=0; i<k; i++){
        j=CHAR_TO_INDEX(temparr[i]);
        if(temp->child[j]){
            if(temp->child[j]->isword&&i==strlen(temparr)-1){
                temp->child[j]->occur++;
                break;
            
            }
            else if(temp->child[j]->isword&&i<strlen(temparr)-1){
                temp->child[j]->prefix++;
                temp=temp->child[j];
                continue;
                
            }
            else{
                temp=temp->child[j];
            
            }
            
        }
    }
    
}

// function to retrieve a word from the dictionary file 
// and store it into a char array so that it can be
// inserted into the trie
void readDict(FILE *dict){
    char temp= '\0';
    
    while (fscanf(dict, "%c", &temp)!=EOF){
        
        if(isalpha(temp)){
            
            temp=tolower(temp);
            char *temparr=(char*)malloc(sizeof(char)*2);
            temparr[0]=temp;
            temparr[1]='\0';
            
            while(fscanf(dict, "%c", &temp)!=EOF){
                
                if(isalpha(temp)){
                    
                    temp=tolower(temp);
                    int length=strlen(temparr);
                    temparr=(char*)realloc(temparr, (length+2)*sizeof(char));
                    temparr[length]=temp;
                    temparr[length+1]='\0';
                }
                else{
                    insertword(temparr, root);
                    break;
                }
            }
        }
    }
}

// function to retrieve a word from the data file
// and store it properly such that we can use it to
// compare with our Trie
void readData(FILE *data){
    char temp= '\0';
    while (fscanf(data, "%c", &temp)!=EOF){
        
        if(isalpha(temp)){
            
            temp=tolower(temp);
            char *temparr=(char*)malloc(sizeof(char)*2);
            temparr[0]=temp;
            temparr[1]='\0';
            
            while(fscanf(data, "%c", &temp)!=EOF){
                
                if(isalpha(temp)){
                    
                    temp=tolower(temp);
                    int length=strlen(temparr);
                    temparr=(char*)realloc(temparr, (length+2)*sizeof(char));
                    temparr[length]=temp;
                    temparr[length+1]='\0';
                }
                else{
                    matchStr(temparr);
                    break;
                }
            }
        }
    }
}

// function to create all the necessary variables so that we can
// output the correct information to the output files
void printResult(){
    count++;
    char filename[16];
    sprintf(filename, "out%d.txt", count);
    FILE* current=fopen(filename, "w");
    outputFile=current;
    char word[200];
    traverse(root, word, 0);
    fclose(outputFile);
    
}

int main(int argc, char** argv){
    
    FILE *fp;
    fp=fopen(argv[1], "r");
    char dictarr[50], datarr[50];
    count=0;
    
    while(fscanf(fp, "%s %s", dictarr, datarr)!=EOF){
        FILE *dict=fopen(dictarr, "r");
        FILE *data=fopen(datarr, "r");
        
        if(dict==NULL){
            printf("Error \n");
            exit(0);
        }
        
        root=(node*)malloc(sizeof(node));
        readDict(dict);
        readData(data);
        printResult();
        free(root);
    }
    
        
    return 1;

}
