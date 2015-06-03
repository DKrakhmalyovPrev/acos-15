#include"hash.h"

struct list{
    char* key;
    int value;
    struct list* next;
};

     
struct list** MakeTable(int n){
    int i;
    struct list** result;
    result = (struct list**) malloc(sizeof(struct list*)*n);
    for(i=0;i<n;i++){
        result[i] = NULL;
    }
    return result;
};


int hash(char* v, int n){	
	int i=0,j;
	int code=0;
	
	for(j=0;j<strlen(v);j++){
        	i = (i+v[j]) % n;
    	}
	return(i);	
};


struct list* Add(struct list* to,char* v, int n){
    struct list* now = (struct list*) malloc(sizeof(struct list));
    now->key = v;
    now->next = to;
    now->value = n;
	printf("%s added as %d\n", v);
    return now;
};

void deleteElement(struct list** table, char* v){
	int ind=hash(v);
        struct list* ex = table[ind];
        if (table[ind] != NULL){
        	if (table[ind]->key == v){
            		struct list* h = table[ind];
            		table[ind] = table[ind]->next;
            		free(h);
        	}
        	else{
            	int key = 0;
            	if (table[ind]->next != NULL){
                	while ((ex->next->next != NULL) && (key == 0)){
                    		if (ex->next->key == v){key = 1;}
                    		else{ex = ex->next;}         
			}
                	if (key != 0){
                    		struct list* help = ex->next;
                    		ex->next = ex->next->next;
                    		free(help);
                	}
            	}
                }
        }
	printf("Mymory free now\n");
}	

void deleteTable(struct list** table){
	int i,j;
	struct list *one, *two;
	for(i=0;i<277;i++)
		free(table[i]);
	printf("Table free now\n");
}

int* Search(char *v, struct list**table){
	int ind=hash(v);
	struct list* odin = table[ind];
	int key=0;
	while((odin!=NULL)&&(key==0)){
		if(odin->key==v){key=1;}
			else{odin=odin->next;};
	};
	if(key==1){return&(odin->value);}
		else{return NULL;};
};


