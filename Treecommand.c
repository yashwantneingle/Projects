#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
#define   TRUE	1
#define   FALSE 0


typedef struct node
{
	char* filename;
	char filetype;
	int isdir;	
	long int size;
	struct node *in_file;	
	struct node *next_dir;
}node;

node* create_tree(char *);
void print_tree(node *t);
void d_tree(node *t);
void a_tree(node *start);
void i_tree(node *start);
void Q_tree(node *t);
void noreport_tree(node *start);
void f_tree(char *path,node *start);
void help_tree();
void P_tree(node *start);
void s_tree(node *start);
int isdir(char *address);
node* getnode(char* name,char filetype);
int count;
int dir=0,d=0,f=0;
int files=0;
int direc=0,fil=0;
int main(int args, char** argv)
{
	node *t;
	char *root;
	root = (char*)malloc(sizeof(char)*20);
	char *a = (char *)calloc(2000,sizeof(char));
	int choice=1;
	while(choice < 10)
	{
	     printf("1.create_tree\n2.-d flag\n3.-a flag\n4.-i flag\n5.-Q flag\n6.-f flag\n7.--noreport\n8.--help\n9.exit()\n");
	     scanf("%d",&choice);
	     switch(choice)
	     {
	         case 1 : printf("Enter root name\n");
	                  scanf("%s",root);
	                  t=getnode(root,'d');
	                  if(args>2)
	                  {
		              printf("\n USAGE : ./a.out [PATH]");
		               exit(0);
	                  }
	                   t->isdir=TRUE;
	                   t->in_file=create_tree(argv[1]);
	                   break;
	        case 2 :  printf("\n-d flag\n");
	                  d_tree(t);
	                  break;
	        case 3 : printf("\n-a flag\n");
	                 a_tree(t);
	                 printf("\n %d Directories and  %d files\n",direc-1,fil);
	                 break;
	        case 4 : printf("-i flag\n");
			  i_tree(t);
		         printf("\n %d Directories and  %d files\n",d-1,f);
		         break;
		case 5 : printf("-Q flag\n");
		 	Q_tree(t);
		        printf("\n %d Directories and  %d files\n",d-1,f);
		        break;
		case 6 : printf("-f flag\n");
	                 f_tree(a,t);
	                 printf("\n %d Directories and  %d files\n",d-1,f);
	                 break;
	       case 7 : printf("--noreport flag\n");
	                 noreport_tree(t);
	                 break;
	      case 8 : help_tree();
	                 break;
	      case 9 : choice = 10;
	                break;
	     }
	     printf("\n******************//******************\n");
	  }
          /*  printf("Enter root name\n");
	    scanf("%s",root);
	                  t=getnode(root,'d');
	                  if(args>2)
	                  {
		              printf("\n USAGE : ./a.out [PATH]");
		               exit(0);
	                  }
	                   t->isdir=TRUE;
	                   t->in_file=create_tree(argv[1]);
	printf("root=%s \n",t->filename);
	print_tree(t);
	printf("\n %d Directories and  %d files\n",dir-1,files);
	printf("-d flag\n");
	d_tree(t);
	printf("\n-a flag\n");
	a_tree(t);
	printf("\n %d Directories and  %d files\n",direc-1,fil);
	printf("-i flag\n");
	i_tree(t);
	printf("\n %d Directories and  %d files\n",d-1,f);
	printf("-Q flag\n");
	Q_tree(t);
	printf("\n %d Directories and  %d files\n",d-1,f);
	char *a = (char *)calloc(2000,sizeof(char));
	
	printf("-f flag\n");
	f_tree(a,t);
	printf("\n %d Directories and  %d files\n",d-1,f);
	printf("--noreport flag\n");
	noreport_tree(t);*/
	printf("\n");
	return 0;
}

node* create_tree(char *root_name)
{
	DIR *dir=opendir(root_name);
	
	struct dirent *dr={NULL};
	node *t=NULL,*temp=NULL,*temp1=NULL;
	char *name=(char *)calloc(2000,sizeof(char));


	if(dir==NULL)
	{
		printf("\nFailed to open ..!!");
		return NULL;
	}

	while((dr=readdir(dir)) != NULL)
	{
			if(strcmp((dr->d_name),".")!=0 && strcmp((dr->d_name),"..")!=0) 
				temp=getnode(dr->d_name,dr->d_type);
			else
			{
				temp=NULL;
				continue;
			}
			
			if(temp1!=NULL)
			{
				temp1->next_dir=temp;
			
			}
			else
			{
				t=temp;
			}

			if((dr->d_type)==DT_DIR ) 
			{
				temp->isdir=TRUE;
				strcpy(name,root_name);
				strcat((strcat(name,"/")),dr->d_name);
				temp->in_file=create_tree(name);
				strcpy(name,root_name);
			}
			else
			{
				(temp)->isdir=FALSE;
				(temp)->in_file=NULL;		
			}

		temp1=temp;
	}
       return t;
}

node* getnode(char* n,char filetype)
{
	node *temp=(node*)malloc(sizeof(node));
	temp->filename=n;
	temp->filetype=filetype;
	temp->in_file=NULL;
	temp->next_dir=NULL;
        return temp;
}

void d_tree(node *start)
{
     char *s="|-----",*s1="|     ";
     if(start==NULL)
	return;
     node* temp = start;
     if(temp->isdir == FALSE)
     {
           return;
     }
     else
     {
          printf("\n");
         for(int i=0;i<(count-1);i++)
         {
		printf("%s",s1);
	 }
	 if(count>0)
		printf("%s",s);

         printf("%s\n",temp->filename);
     }
     if(temp->isdir==TRUE)
     {		
         count++;
         d_tree(temp->in_file); 
         count--;
     }
     d_tree(temp->next_dir);	
     return;
	
}
void print_tree(node *start)
{
	char *s="|-----",*s1="|     ";
	node *temp=start;
	int i;

		if(start==NULL)
			return;
		printf("\n");
		for(i=0;i<(count-1);i++)
			printf("%s",s1);
		if(count>0)
			printf("%s",s);
		
		if((char*)temp->filename == ".")
		{
		   return;
		}
		printf("%s",temp->filename);
		
		if(temp->isdir==TRUE)
		{	
		        dir++;
			count++;    
			print_tree(temp->in_file);
			count--;
		}
		else
		{
		    files++;
                }
		print_tree(temp->next_dir);	
		return;

}
void a_tree(node *start)
{
	char *s="|-----",*s1="|     ";
	node *temp=start;
	int i;

		if(start==NULL)
			return;

		printf("\n");
		for(i=0;i<(count-1);i++)
			printf("%s",s1);
		if(count>0)
			printf("%s",s);
		printf("%s",temp->filename);
		if(temp->isdir==TRUE)
		{
	               direc++;
			count++;
			a_tree(temp->in_file);
			count--;
		}
		else
		{
		     fil++;
		}
		a_tree(temp->next_dir);	
		return;

}
void noreport_tree(node *start)
{
     char *s="|-----",*s1="|     ";
	node *temp=start;
	int i;

		if(start==NULL)
			return;

		printf("\n");
		for(i=0;i<(count-1);i++)
			printf("%s",s1);
		if(count>0)
			printf("%s",s);
		printf("%s",temp->filename);
		if(temp->isdir==TRUE)
		{
			count++;
			noreport_tree(temp->in_file);
			count--;
		}
		noreport_tree(temp->next_dir);	
		return;
}
void i_tree(node *t)
{
    node* temp = t;
    if(t == NULL)
    {
       return;
    }
    printf("%s\n",temp->filename);
    if(temp->isdir==TRUE)
     {
            d++;
            i_tree(temp->in_file);
     }
     else
     {
          f++;
     }
     i_tree(temp->next_dir);
     return;
 }       
 void Q_tree(node *t)
 {
      
       char *s="|-----",*s1="|     ";
       char *s2 = "''";
	node *temp=t;
	int i;

		if(t==NULL)
			return;

		printf("\n");
		for(i=0;i<(count-1);i++)
			printf("%s",s1);
		if(count>0)
			printf("%s",s);
		printf("%s%s%s",s2,temp->filename,s2);
		if(temp->isdir==TRUE)
		{
			count++;
			Q_tree(temp->in_file);
			count--;
		}
		Q_tree(temp->next_dir);	
		return;
}
void help_tree()
{
    printf("\n--------Tree usage details(flags)--------\n");
    printf(" --Listing options--\n");
    printf("-d         = list directories only\n");
    printf("-a         = print all files\n");
    printf("-f         = print full path for each file\n");
    printf("--noreport = don't return directories and files count at the end of listing\n");
    printf("*********//********\n");
    printf(" --Graphics options--\n");
    printf("-i         = don't print indentation\n");
    printf("*********//********\n");
    printf(" --Miscellaneous options--\n");
    printf("--help     =  helps in tree commands usage\n");
    return;
}
void f_tree(char *path,node *start)
{
     
      char *s="|-----",*s1="|     ";
      char *a = (char *)calloc(2000,sizeof(char));
      strcpy(a,path);
	node *temp=start;
	int i;
      
		if(start==NULL)
			return;

		printf("\n");
		for(i=0;i<(count-1);i++)
			printf("%s",s1);
		if(count>0)
			printf("%s",s);
	        strcat(a,"/");
		printf("%s",a);
		if(temp->isdir==TRUE)
		{
	                strcat(a,temp->filename);
			count++;
			f_tree(a,temp->in_file);
			count--;
		}
		strcpy(a,path);
		f_tree(a,temp->next_dir);	
		return;

}   
int isdir(char *address)
{
    DIR *fp;
    fp = opendir(address);
    if(fp)
    {
        closedir(fp);
        return 1;
    }
    else
    {
        return 0;
    }
}
void s_tree(node *start)
{
     char *s="|-----",*s1="|     ";
	node *temp=start;
	int i;

		if(start==NULL)
			return;

		printf("\n");
		for(i=0;i<(count-1);i++)
			printf("%s",s1);
		if(count>0)
			printf("%s",s);
		printf("%s",temp->filename);
		if(temp->isdir==TRUE)
		{
			count++;
			noreport_tree(temp->in_file);
			count--;
		}
		noreport_tree(temp->next_dir);	
		return;
}
void P_tree(node *start)
{
	char *s="|-----",*s1="|     ";
	node *temp=start;
	int i;

		if(start==NULL)
			return;

		printf("\n");
		for(i=0;i<(count-1);i++)
			printf("%s",s1);
		if(count>0)
			printf("%s",s);
		printf("%s",temp->filename);
		printf("-%c",temp->filetype);
		if(temp->isdir==TRUE)
		{
		        dir++;	
			count++;
			P_tree(temp->in_file);
			count--;
		}
		P_tree(temp->next_dir);	
		return;

}
