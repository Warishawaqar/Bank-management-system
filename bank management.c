#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
void create(char[],char[],int*,float*);
void login(char[],char[],int*,float*);
int main(){
	int choice1,id,choice2;
	char name[30],pin[14];
	float money;
	
	printf("               WELCOME TO BANK MANAGEMENT SYSTEM\n");
	printf("                    1. Login account\n                    2. Create an account\n");
	printf("Enter your option: ");
	scanf("%d",&choice1);
	switch(choice1){
		case 1:
			login(name,pin,&id,&money);
			break;
		case 2:
			create(name,pin,&id,&money);
			break;
	}
	system("cls");
	printf("\n                  WELCOME %s !\n",name);
	printf("                     1. Balance deposit\n                     2.Balance withdrawl\n                     3.Money transfer\n                     4.Bank inquiry\n                     5.Virtual savings pot\n");
    printf("Enter your choice: ");
    scanf("%d",&choice2);
}
void create(char name[],char pin[],int *id,float *money){
	int count_special=0,count_alpha=0,count_digit=0,count_upper=0,r=0;
    FILE *fp;
    fp=fopen("bank.txt","a");
	        printf("\nEnter your name: ");
			scanf("%s",name);
			printf("\nCreate an 8 digit account ID: ");
			scanf("%d",id);
		    while(r==0){
			
			printf("\nCreate a 12 character Password: ");
			scanf(" %s",pin);
			for(int i=0;i<strlen(pin);i++){
				if(!isalnum(pin[i])){
					count_special++;
				}
				if(isalpha(pin[i])){
					count_alpha++;
				}
				if(isdigit(pin[i])){
					count_digit++;
				}
				if(isupper(pin[i])){
					count_upper++;
				}
			}
			if(count_special<2){
				printf("\nError: Please enter atleast 2 special character.");
				continue;
			}
		
			if(count_digit<4){
				printf("\nError: Please enter atleast 4 digits.");
				continue;
			}
		
			if(count_upper<1){
				printf("\nError: Please enter atleast 1 uppercase alphabet.");
				continue;
			}
			r++;
		};
		printf("Enter the amount of money you want to deposit: ");
		scanf("%f",money);
		fprintf(fp,"%s,%d,%s,%.2f\n",name,*id,pin,*money);
		fclose(fp);
}
void login(char name[],char pin[],int *id,float *money){
	char tpin[14];
	int tid;
	float tmoney;
	FILE *fp=NULL;
	printf("\nEnter your account id: ");
	scanf("%d",id);
	printf("\nEnter the password: ");
	scanf("%s",pin);
	fp=fopen("bank.txt","r");
	while(!feof(fp)){
		fscanf(fp," %[^,],%d,%[^,],%f",name,&tid,tpin,money);
		if((*id==tid)&&!(strcmp(pin,tpin)))
		break;
	}
	fclose(fp);
}

