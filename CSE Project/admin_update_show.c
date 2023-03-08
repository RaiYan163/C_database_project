#include<stdio.h>
#include<string.h>

typedef struct admininfo{
    char name[200],pass[200];
}admin;

int main()
{
    char pw[200];
    printf("Enter the key to join: ");
    gets(pw);
    if(strcmp(pw, "1907023") == 0)
    {
         while(1)
         {
         FILE *fpt;
         char c;
         printf("press 0 to exit.\n");
         printf("press 1 to show admin username and password.\n");
         printf("press 2 to update admin username and password.\n");
         fflush(stdin);
         scanf("%c", &c);
         if(c == '0')
         {
             fclose(fpt);
             return 0;
         }
         else if(c == '1')
         {
            fpt = fopen("admin_info.txt", "r");
            admin b;
            fread(&b, sizeof(admin), 1, fpt);
            printf("Admin username: %s\n", b.name);
            printf("Admin password: %s\n", b.pass);
            fclose(fpt);
         }
         else if(c == '2')
         {
            fpt = fopen("admin_info.txt", "w");
            admin b;
            char un[200], pw[200];
            printf("Enter new username:");
            fflush(stdin);
            gets(un);
            printf("Enter new password:");
            fflush(stdin);
            gets(pw);
            strcpy(b.name, un);
            strcpy(b.pass, pw);
            fwrite(&b, sizeof(admin), 1, fpt);
            fclose(fpt);
         }
         else
         {
             printf("Wrong key!! Try again.\n");
         }


         fpt = fopen("admin_info.txt", "r");
         admin b;
         fread(&b, sizeof(admin), 1, fpt);
         }
    }
}
