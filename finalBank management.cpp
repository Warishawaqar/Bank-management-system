#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<unistd.h>
void create(char[],char[],int*,float*);
void login(char[],char[],int*,float*);
void deposit(char[],char[],int*,float*);
void withdraw(char[],char[],int*,float*);
void transfer(char[],char[],int*,float*);
void inquiry(char[],char[],int*,float*);
void saving(int*,float*);
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
	
	for(;;){
	system("cls");
	printf("\n                  WELCOME %s !\n",name);
	printf("                     1. Balance deposit\n                     2.Balance withdrawl\n                     3.Money transfer\n                     4.Bank inquiry\n                     5.Virtual savings pot\n");
    printf("Enter your choice: ");
    scanf("%d",&choice2);
    switch(choice2){
    	case 1:
    		deposit(name,pin,&id,&money);
    		break;
    	case 2:
    		withdraw(name,pin,&id,&money);
    		break;
    	case 3:
    		transfer(name,pin,&id,&money);
    		break;
    	case 4:
    		inquiry(name,pin,&id,&money);
    		break;
    	case 5:
	    	saving(&id,&money);
	    	break;
	    case 6:
	    	return 0;
	    
}
sleep(3);
}
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
void deposit(char name[],char pin[],int *id,float *money){
	float deposit,money01;
	FILE *fp=NULL;
	FILE *fp1=NULL;
	char name01[30],pin01[14];
	int id01;
	printf("\nEnter the amount of money you want to deposit: ");
	scanf("%f",&deposit);
	*money+=deposit;
	fp=fopen("bank.txt","r");
	fp1=fopen("bank01.txt","w");
	if (fp == NULL || fp1 == NULL) {
    printf("\nERROR: Failed to open database files. Check file names and permissions.\n");

	}
	while(fscanf(fp,"%30[^,],%d,%14[^,],%f\n",name01,&id01,pin01,&money01)==4){
		
		if(id01==*id){
			money01=*money;
		}
		fprintf(fp1,"%s,%d,%s,%.2f\n",name01,id01,pin01,money01);
	}
	printf("\nBank balance: %.2f ",*money);
	fclose(fp);
	fclose(fp1);
	remove("bank.txt");
	rename("bank01.txt", "bank.txt");
	
}
void withdraw(char name[], char pin[], int *id, float *money)
{
    float amount, money01;
    FILE *fp=NULL;
    FILE *fp1=NULL;
    char name01[30], pin01[14];
    int id01;

    printf("\nEnter amount to withdraw: ");
    scanf("%f", &amount);

    if(amount > *money){
        printf("\nERROR: Insufficient balance!\n");
        return;
    }
    
    *money -= amount;

    fp = fopen("bank.txt", "r");
    fp1 = fopen("bank01.txt", "w");

    if(fp == NULL || fp1 == NULL){
        printf("\nERROR: File opening failed.\n");
        return;
    }

    while(fscanf(fp,"%30[^,],%d,%14[^,],%f\n",name01,&id01,pin01,&money01)==4){
        if(id01 == *id){
            money01 = *money;
        }
        fprintf(fp1,"%s,%d,%s,%.2f\n",name01,id01,pin01,money01);
    }

    printf("\nWithdrawal successful! New balance: %.2f\n", *money);

    fclose(fp);
    fclose(fp1);
    remove("bank.txt");
    rename("bank01.txt", "bank.txt");
}
void inquiry(char name[], char pin[], int *id, float *money){
    printf("\n            BANK INQUIRY             \n");
    printf("Name: %s\n", name);
    printf("Account ID: %d\n", *id);
    printf("Current Balance: %.2f\n", *money);
    
}
void transfer(char name[], char pin[], int *id, float *money){
    int recID;
    float amount;
    int id01;
    float money01;
    char name01[30], pin01[14];

    printf("\nEnter receiver account ID: ");
    scanf("%d", &recID);

    printf("\nEnter amount to transfer: ");
    scanf("%f", &amount);

    if(amount > *money){
        printf("\nERROR: Insufficient funds!\n");
        return;
    }

    FILE *fp = fopen("bank.txt", "r");
    FILE *fp1 = fopen("bank01.txt", "w");

    while(fscanf(fp,"%30[^,],%d,%14[^,],%f\n", name01, &id01, pin01, &money01)==4){

        if(id01==*id){   
            money01=*money-amount;
            *money = money01;
        }
        else if(id01==recID){  
            money01+=amount;
        }

        fprintf(fp1,"%s,%d,%s,%.2f\n", name01, id01, pin01, money01);
    }

    printf("\nTransfer successful! New balance: %.2f\n", *money);

    fclose(fp);
    fclose(fp1);

    remove("bank.txt");
    rename("bank01.txt", "bank.txt");}

void saving(int *id,float *money){
	char pur[20],tpur[20],title[20];
	int choice,tid;
	float mon,tmon,amount,tamount,deposit;
	FILE *fp=NULL,*fp1=NULL;
	printf("\n                   Virtual Savings pot\n");
	printf("                  1. Create a virtual savings pot\n                  2.View all your virtual savings pot\n                  3.Deposit\n");
	printf("\nSelect your option: ");
	scanf("%d",&choice);
	switch(choice){
		case 1:
			printf("\nMention the following details ");
			printf("\nPurpose: ");
			getchar();
			gets(pur);
			printf("\nTarget money: ");
			scanf("%f",&mon);
			printf("Enter the amount of money you want to deposit: ");
			scanf("%f",&amount);
			fp=fopen("saving.txt","a");
			if (fp == NULL) 
             printf("\nERROR: Failed to open database files. Check file names and permissions.\n");
             else{
			fprintf(fp,"%d,%s,%.2f,%.2f\n",*id,pur,mon,amount);
			fclose(fp);
			break;}
		case 2:
			fp=fopen("saving.txt","r");
		    while(fscanf(fp,"%d,%[^,],%f,%f\n",&tid,tpur,&tmon,&tamount)==4){
			if(*id==tid){
				printf("--------------------------------\n");
				printf("|Purpose: %s\n",tpur);
				printf("|Money desposited: %.2f\n",tamount);
				printf("|Target money: %.2f",tmon);
				printf("\n--------------------------------\n");
				}
			}
			fclose(fp);
				break;
			case 3: 
			fp=fopen("saving.txt","r");
			fp1=fopen("saving01.txt","w");
			printf("\nEnter the title/purpose of the virtual savings pot:  ");
			getchar();
			gets(title);
			printf("\nEnter the amount to be depsoited: ");
			scanf("%f",&deposit);
			while(fscanf(fp,"%d,%[^,],%f,%f\n",&tid,tpur,&tmon,&tamount)==4){
				if((!strcmp(tpur,title))&&(*id==tid)){
					tamount+=deposit;
				}
				fprintf(fp1,"%d,%s,%.2f,%.2f\n",tid,tpur,tmon,tamount);
			}
			fclose(fp);
			fclose(fp1);
		
			remove("saving.txt");
			rename("saving01.txt","saving.txt");
			break;
		}
	
			
}

