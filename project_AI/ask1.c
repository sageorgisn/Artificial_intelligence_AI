#include <stdio.h>
#include <stdlib.h>

#define M 10
#define K1 3
#define K2 4


#define MIN 100
#define MAX 200
#define MINWINS 0
#define MAXWINS 1

struct node{
	int type; 
	int red;
	int green;
	int value; 
	struct node *first; 
	struct node *second; 
	struct node *third; 
	struct node *fourth; 
	struct node *choice; 
};


struct node *root;


struct node *createSubtree(int red, int green, int type);



int main()
{

	struct node *tmp;
	root = createSubtree(M,M,MAX);
	int userchoice;
	int isok;
	
	tmp = root;
	while(tmp!=NULL && (tmp->red>0 || tmp->green >0) ){
		printf("RED: %d GREEN %d\n",tmp->red,tmp->green);
		if(tmp->choice ==tmp->first){
			printf("Computer removes ONE red\n");
		}
		else if(tmp->choice == tmp->second){
			printf("Computer removes ONE green\n");
		}
		else if(tmp->choice == tmp->third){
			printf("Computer removes K1=%d red\n",K1);
		}
		else if(tmp->choice == tmp->fourth){
			printf("Computer removes K2=%d green\n",K2);
		}
		tmp = tmp->choice; 
		if(tmp->red==0 && tmp->green==0){
			printf("COMPUTER WINS!!!\n");
			break;
		}
		do{
			printf("RED: %d GREEN %d\n",tmp->red,tmp->green);
			printf("1. Remove ONE red\n");
			printf("2. Remove ONE green\n");
			printf("3. Remove K1=%d red\n",K1);
			printf("4. Remove K2=%d green\n",K2);
			printf("Choice > ");
			scanf("%d",&userchoice);
			isok = 1;
			if(userchoice==1 && tmp->first!=NULL){
				tmp=tmp->first;
			}
			else if(userchoice==2 && tmp->second!=NULL){
				tmp = tmp->second;
			}
			else if(userchoice==3 && tmp->third !=NULL){
				tmp = tmp->third;
			}
			else if(userchoice==4 && tmp->fourth!=NULL){
				tmp = tmp->fourth;
			}
			else{
				printf("Wrong choice\n");
				isok=0;
			}
		}while(isok==0);
		
		if(tmp->red==0 && tmp->green==0){
			printf("PLAYER  WINS!!!\n");
			break;
		}
	}
	
}

int other(int type){
	if(type==MAX) return MIN;
	if(type==MIN) return MAX;
}


struct node *createSubtree(int red, int green, int type)
{
	struct node *newnode;
	
	if(red<0) return NULL;
	if(green<0) return NULL;
	
	newnode = (struct node *)malloc(sizeof(struct node ));
	if(newnode==NULL){
		printf("error in malloc");
		exit(1);
	}
	
	newnode->type = type;
	newnode->red = red;
	newnode->green = green;
	
	if(red==0 && green==0){
		if(type==MAX){
			newnode->value = MINWINS;
		}
		else{
			newnode->value = MAXWINS;
		}
		return newnode; 
	}
	
	newnode->first = createSubtree(red-1,green,other(type));
	newnode->second = createSubtree(red,green-1,other(type));
	newnode->third = createSubtree(red-K1,green,other(type));
	newnode->fourth = createSubtree(red,green-K2,other(type));
	
	
	if(type==MAX){
		if(newnode->first!=NULL && newnode->first->value==MAXWINS){
			newnode->value = MAXWINS;
			newnode->choice = newnode->first;
		}
		else if(newnode->second!=NULL && newnode->second->value==MAXWINS){
			newnode->value = MAXWINS;
			newnode->choice = newnode->second;
		}
		else if(newnode->third!=NULL && newnode->third->value==MAXWINS){
			newnode->value = MAXWINS;
			newnode->choice = newnode->third;
		}
		else if(newnode->fourth!=NULL && newnode->fourth->value==MAXWINS){
			newnode->value = MAXWINS;
			newnode->choice = newnode->fourth;
		}
		else{
			newnode->value = MINWINS;
			if(newnode->first!=NULL){
				newnode->choice = newnode->first;
			}
			else if(newnode->second!=NULL){
				newnode->choice = newnode->second;
			}
			else if(newnode->third!=NULL){
				newnode->choice = newnode->third;
			}
			else{
				newnode->choice = newnode->fourth;
			}
		}
	}
	else{
		if(newnode->first!=NULL  && newnode->first->value==MINWINS){
			newnode->value = MINWINS;
		}
		else if(newnode->second != NULL && newnode->second->value==MINWINS){
			newnode->value = MINWINS;
		}
		else if(newnode->third!=NULL && newnode->third->value==MINWINS){
			newnode->value = MINWINS;
		}
		else if(newnode->fourth!=NULL && newnode->fourth->value==MINWINS){
			newnode->value = MINWINS;
		}
		else{
			newnode->value = MAXWINS;
		}
	}
	
	return newnode;
}











