#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
//USERNAME: Raiyan Ashraf
//Password: 1907023
typedef struct admininfo{
    char name[200],pass[200];
}admin;

typedef struct teacherinfo{
    char name[200],pass[200];
	char courses[2][200];
}teacher;


typedef struct studentinfo{
    char name[200],pass[200];
    char courses[2][200];
    int marks_1, marks_2;
}student;


//*********************************************START OF ADMIN PANEL***********************************//
void admin_panel();
//FUNCTIONS USED IN ADMIN PANEL.

int admin_verify();
//Admin verified.
void teacher_sec();
//Teacher section start, Necessary functions for teacher sec below:
void add_teacher();
void teacher_up();
void check_names_teacher();
void add_course_teacher();
//Teacher section end

void student_sec();
//Student section start...necessary functions for it.
void add_student();
void student_up();
void add_course_student();
void check_names_student();
//Student sec ends.
//*********************************************END OF ADMIN PANEL*************************************//

/*
int main()
{
    FILE *fp;
    fp = fopen("admin_info.txt", "w");
    admin a;
    fflush(stdin);
    strcpy(a.name, "Raiyan");
    strcpy(a.pass, "1907023");
    fwrite(&a, sizeof(a), 1, fp);
    return 0;
}
*/


//FUNCTIONS OF ADMIN PANEL.
int admin_verify()
{
    char un[200], pw[200];
    int x;
    admin b;
    FILE *fp;
    fp = fopen("admin_info.txt", "r");
    fread(&b, sizeof(admin), 1, fp);
    printf("Admin name : %s\n", b.name);
    printf("Admin pass : %s\n", b.pass);

    printf("Verifying Admin.\n");
    printf("Username: ");
    fflush(stdin);
    gets(un);

    printf("Password: ");
    fflush(stdin);
    gets(pw);

    //printf("%s\n%s", b.name, b.pass);
    int a;
    if(strcmp(b.name, un) == 0 && strcmp(b.pass, pw) == 0)
    {
        a = 1;
    }
    else a = 0;
    fclose(fp);
    return a;

}

//******************TEACHER SECTION FUNCTIONS********************
void add_teacher()
{
        FILE *fpt;
        fpt = fopen("teacher_info.txt", "a+");//Has to be a file called teacher info
        teacher tc;
        int x = 2, y;
        printf("Please Enter the name of the teacher: ");
        char s[200];
        fflush(stdin);
        gets(s);
        while(fread(&tc, sizeof(teacher), 1, fpt))
        {
            if(strcmp(tc.name, s) == 0)
            {
                printf("Teacher already enlisted!!!\n");
                printf("press 1 to update.\n");
                printf("press 0 to exit.\n");
                fflush(stdin);
                scanf("%d", &x);
            }
        }

        if(x == 1)
        {
            teacher_up();
            fclose(fpt);
            return ;
        }
        else if(x == 0) return;

        strcpy(tc.name, s);


        while(1)
        {
            char s1[100], s2[100];
        printf("Please Enter new password: ");
        fflush(stdin);
        gets(s1);
        printf("Please Re enter the password:(%s): ", s1);
        fflush(stdin);
        gets(s2);
        if(strcmp(s1, s2) == 0)
        {
            strcpy(tc.pass, s1);
            printf("Password enlisted successfully.\n");
            break;
        }
        else
        {
            printf("Password didn't match, try again.\n");
        }

        }
           strcpy(tc.courses[0], "NULL");
           strcpy(tc.courses[1], "NULL");
           fwrite(&tc, sizeof(tc), 1, fpt);

           printf("\n******New teacher enlisted successfully.******\n");

        fclose(fpt);

}

void check_names_teacher()
{
        FILE *fpp;
        teacher x;
        fpp=fopen("teacher_info.txt","r");
        while((fread(&x,sizeof(teacher),1,fpp)))
        {
            printf("%s ",x.name);
            printf("%s ",x.pass);
            printf("Courses : %s %s\n", x.courses[0], x.courses[1]);
        }


        fclose(fpp);
}

void teacher_up()
{

            FILE *fpt1, *fpt2;
            teacher a;
            char s[200];
            fpt2 = fopen("teacher_info.txt", "r");
            printf("*******Update Teacher's info********\n");
            printf("Enter the name of the teacher you want to update: ");
            fflush(stdin);
            gets(s);
            int flag = 0;
            while(fread(&a,sizeof(teacher), 1, fpt2))
            {
                if(strcmp(a.name, s) == 0)
                {
                    flag = 1;
                    break;
                }
            }
            fclose(fpt2);
            if(!flag)
            {
                printf("\n******Teacher not found. Please try again.******\n");
            }
            else
            {
            printf("Teacher found.\n");
            //IF TEACHER NAME IS FOUND.
            //CAUTION: NAME TA SAVE KORA ACHE.
            printf("press 1 to update the name.\n");
            printf("press 2 to update the password.\n");
            int x;
            fflush(stdin);
            scanf("%d", &x);
            if(x == 1)
            {
                printf("Enter the name you want to replace with:  ");
                char s[200];
                fflush(stdin);
                gets(s);
                FILE *fpt1, *fpt2;
                fpt1 = fopen("teacher_info.txt", "r");
                fpt2 = fopen("temp.txt", "w");
                teacher b;

                while(fread(&b, sizeof(teacher), 1, fpt1))
                 {
                        if(strcmp(b.name, a.name) == 0)
                        {
                                strcpy(b.name, s);
                                //strcpy(b.pass, "1123");
                        }
                    fwrite(&b, sizeof(teacher), 1, fpt2);
                 }

                    fclose(fpt1);
                    fclose(fpt2);
                    fpt1 = fopen("temp.txt", "r");
                    fpt2 = fopen("teacher_info.txt", "w");

                    while((fread(&b,sizeof(teacher),1,fpt1))>0)
                    {
                        fwrite(&b,sizeof(teacher),1,fpt2);
                    }
                        fclose(fpt1);
                        fclose(fpt2);
                    printf("\n******Updated name successfully.******\n");

                }
            else if(x==2)
            {
                fpt2 = fopen("teacher_info.txt", "r");
                fpt1 = fopen("temp.txt", "w");
                printf("Enter the password you want to replace with: ");
                char s[200];
                fflush(stdin);
                gets(s);
                teacher b;

                while(fread(&b, sizeof(b), 1, fpt2))
                {
                    if(strcmp(b.pass, a.pass) == 0)
                    {
                          strcpy(b.pass, s);
                    }
                    fwrite(&b, sizeof(teacher), 1, fpt1);


                }
                fclose(fpt2);
                fclose(fpt1);
                fpt2 = fopen("teacher_info.txt", "w");
                fpt1 = fopen("temp.txt", "r");
                while(fread(&b, sizeof(b), 1, fpt1))
                {
                    fwrite(&b, sizeof(b), 1, fpt2);
                }
                printf("\n******Updated password successfully.******\n");
                fclose(fpt1);
                fclose(fpt2);

                }
            }

}

void add_course_teacher()
{
    printf("***************Assigning courses to teacher****************\n");
    printf("Enter the name of the teacher you want to assign course to: ");
    char s[100];
    fflush(stdin);
    gets(s);
    FILE *fpt1, *fpt2;
    fpt1 = fopen("teacher_info.txt", "r");
    fpt2 = fopen("temp.txt", "w");
    teacher tc;
    int flag = 0;
    while(fread(&tc, sizeof(teacher), 1, fpt1))
    {
        if(strcmp(s, tc.name) == 0)
        {
            flag = 1;
            break;
        }
        fwrite(&tc, sizeof(teacher), 1, fpt2);
    }
    if(flag == 0)
    {
        printf("Teacher not found. Please try again.\n");
        return;

    }
        printf("Teacher found.\n");
        printf("Assigned courses to %s is: %s %s\n", tc.name, tc.courses[0], tc.courses[1]);
        printf("press 1 to update\n");
        printf("press 0 to exit\n");
        fflush(stdin);
        int x;
        scanf("%d", &x);
        if(x == 0) return;

        char s1[100], s2[100];
        printf("Enter the name of the course 1: ");
        fflush(stdin);
        gets(s1);
        strcpy(tc.courses[0], s1);
        printf("Enter the name of the course 2: ");
        fflush(stdin);
        gets(s2);
        strcpy(tc.courses[1], s2);
        fwrite(&tc, sizeof(teacher), 1, fpt2);
         while(fread(&tc, sizeof(teacher), 1, fpt1))
        {
         fwrite(&tc, sizeof(teacher), 1, fpt2);
        }
        fclose(fpt1);
        fclose(fpt2);

        fpt1 = fopen("temp.txt", "r");
        fpt2 = fopen("teacher_info.txt", "w");

        while((fread(&tc,sizeof(teacher),1,fpt1))>0)
            {
               fwrite(&tc,sizeof(teacher),1,fpt2);
            }

            fclose(fpt1);
            fclose(fpt2);

            printf("Course updated successfully.\n");





}

void teacher_sec()
{
    while(1)
    {
    printf("****Welcome to teacher info update section.****\n");
    printf("0 to exit.\n");
    printf("1 to create new teacher account.\n");
    printf("2 to update teacher informations.\n");
    printf("3 to assign courses.\n");
    printf("4 to show current list\n");
    fflush(stdin);
    char n;
    scanf("%c", &n);
    if(n == '0')
    {
        return;
    }
    else if(n == '1')
    {
        add_teacher();
    }
    else if(n == '2')
    {
        teacher_up();
    }
    else if(n == '3')
    {
        add_course_teacher();
    }
    else if(n == '4')
    {
        check_names_teacher();
    }
    else
    {
        printf("Invalid!!! Wrong Key!! Please try again.\n");
    }

    }

    return;
}

//**************************END OF TEACHER SECTION FUNCTIONS********************

//***************************STUDENT SECTION FUNCTIONS**************************

void add_student()
{
        FILE *fpt;
        fpt = fopen("student_info.txt", "a+");//Has to be a file called teacher info
        student tc;
        int x = 2, y;
        printf("Please Enter the name of the student: ");
        char s[200];
        fflush(stdin);
        gets(s);
        while(fread(&tc, sizeof(student), 1, fpt))
        {
            if(strcmp(tc.name, s) == 0)
            {
                printf("Student already enlisted!!!\n");
                printf("press 1 to update.\n");
                printf("press 0 to exit.\n");
                fflush(stdin);
                scanf("%d", &x);
            }
        }

        if(x == 1)
        {
            student_up();
            fclose(fpt);
            return ;
        }
        else if(x == 0) return;

        strcpy(tc.name, s);


        while(1)
        {
            char s1[100], s2[100];
        printf("Please Enter new password: ");
        fflush(stdin);
        gets(s1);
        printf("Please Re enter the password:(%s): ", s1);
        fflush(stdin);
        gets(s2);
        if(strcmp(s1, s2) == 0)
        {
            strcpy(tc.pass, s1);
            printf("Password enlisted successfully.\n");
            break;
        }
        else
        {
            printf("Password didn't match, try again.\n");
        }

        }
           strcpy(tc.courses[0], "NULL");
           strcpy(tc.courses[1], "NULL");
           tc.marks_1 = -1;
           tc.marks_2 = -1;
           fwrite(&tc, sizeof(tc), 1, fpt);

           printf("\n******New student enlisted successfully.******\n");

        fclose(fpt);

}

void check_names_student()
{
        FILE *fpp;
        student x;
        fpp=fopen("student_info.txt","r");
        while((fread(&x,sizeof(student),1,fpp)))
        {
            printf("%s ",x.name);
            printf("%s ",x.pass);
            printf("Courses : %s %s .", x.courses[0], x.courses[1]);
            printf(" Marks 1 = %d, Marks 2 = %d\n", x.marks_1, x.marks_2);
        }


        fclose(fpp);
}

void student_up()
{

            FILE *fpt1, *fpt2;
            student a;
            char s[200];
            fpt2 = fopen("student_info.txt", "r");
            printf("*******Update Student's info********\n");
            printf("Enter the name of the Student you want to update: ");
            fflush(stdin);
            gets(s);
            int flag = 0;
            while(fread(&a,sizeof(student), 1, fpt2))
            {
                if(strcmp(a.name, s) == 0)
                {
                    flag = 1;
                    break;
                }
            }
            fclose(fpt2);
            if(!flag)
            {
                printf("\n******Student not found. Please try again.******\n");
            }
            else
            {
            printf("Student found.\n");
            //IF STUDENT NAME IS FOUND.
            //CAUTION: NAME TA SAVE KORA ACHE.
            printf("press 1 to update the name.\n");
            printf("press 2 to update the password.\n");
            int x;
            fflush(stdin);
            scanf("%d", &x);
            if(x == 1)
            {
                printf("Enter the name you want to replace with:  ");
                char s[200];
                fflush(stdin);
                gets(s);
                FILE *fpt1, *fpt2;
                fpt1 = fopen("student_info.txt", "r");
                fpt2 = fopen("temp.txt", "w");
                student b;

                while(fread(&b, sizeof(student), 1, fpt1))
                 {
                        if(strcmp(b.name, a.name) == 0)
                        {
                                strcpy(b.name, s);
                                //strcpy(b.pass, "1123");
                        }
                    fwrite(&b, sizeof(student), 1, fpt2);
                 }

                    fclose(fpt1);
                    fclose(fpt2);
                    fpt1 = fopen("temp.txt", "r");
                    fpt2 = fopen("student_info.txt", "w");

                    while((fread(&b,sizeof(student),1,fpt1))>0)
                    {
                        fwrite(&b,sizeof(student),1,fpt2);
                    }
                        fclose(fpt1);
                        fclose(fpt2);
                    printf("\n******Updated name successfully.******\n");

                }
            else if(x==2)
            {
                fpt2 = fopen("student_info.txt", "r");
                fpt1 = fopen("temp.txt", "w");
                printf("Enter the password you want to replace with: ");
                char s[200];
                fflush(stdin);
                gets(s);
                student b;

                while(fread(&b, sizeof(b), 1, fpt2))
                {
                    if(strcmp(b.pass, a.pass) == 0)
                    {
                          strcpy(b.pass, s);
                    }
                    fwrite(&b, sizeof(student), 1, fpt1);


                }
                fclose(fpt2);
                fclose(fpt1);
                fpt2 = fopen("student_info.txt", "w");
                fpt1 = fopen("temp.txt", "r");
                while(fread(&b, sizeof(b), 1, fpt1))
                {
                    fwrite(&b, sizeof(b), 1, fpt2);
                }
                printf("\n******Updated password successfully.******\n");
                fclose(fpt1);
                fclose(fpt2);

                }
            }

}

void add_course_student()
{
    printf("******Assigning courses to student******\n");
    printf("Enter the name of the student you want to assign course to: ");
    char s[100];
    fflush(stdin);
    gets(s);
    FILE *fpt1, *fpt2;
    fpt1 = fopen("student_info.txt", "r");
    fpt2 = fopen("temp.txt", "w");
    student tc;
    int flag = 0;
    while(fread(&tc, sizeof(student), 1, fpt1))
    {
        if(strcmp(s, tc.name) == 0)
        {
            flag = 1;
            break;
        }
        fwrite(&tc, sizeof(student), 1, fpt2);
    }
    if(flag == 0)
    {
        printf("Student not found. Please try again.\n");
        return;

    }
        printf("Student found.\n");
        printf("Assigned courses to %s is: %s %s\n", tc.name, tc.courses[0], tc.courses[1]);
        printf("press 1 to update\n");
        printf("press 0 to exit\n");
        fflush(stdin);
        int x;
        fflush(stdin);
        scanf("%d", &x);
        if(x == 0) return;

        char s1[100], s2[100];
        printf("Enter the name of the course 1: ");
        fflush(stdin);
        gets(s1);
        strcpy(tc.courses[0], s1);
        printf("Enter the name of the course 2: ");
        fflush(stdin);
        gets(s2);
        strcpy(tc.courses[1], s2);
        fwrite(&tc, sizeof(student), 1, fpt2);
         while(fread(&tc, sizeof(student), 1, fpt1))
        {
         fwrite(&tc, sizeof(student), 1, fpt2);
        }
        fclose(fpt1);
        fclose(fpt2);

        fpt1 = fopen("temp.txt", "r");
        fpt2 = fopen("student_info.txt", "w");

        while((fread(&tc,sizeof(student),1,fpt1))>0)
            {
               fwrite(&tc,sizeof(student),1,fpt2);
            }

            fclose(fpt1);
            fclose(fpt2);

            printf("Course updated successfully.\n");





}

void student_sec()
{
    while(1)
    {
    printf("****Welcome to student's info update section.****\n");
    printf("0 to exit.\n");
    printf("1 to create new student account.\n");
    printf("2 to update student informations.\n");
    printf("3 to assign courses.\n");
    printf("4 to show current list\n");
    fflush(stdin);
    int n;
    scanf("%d", &n);
    switch(n)
    {
    case 0:
        return ;
    case 1: //CREATING NEW TEACHER ACCOUNT.
        {

          add_student();

        printf("\n Do you want to continue? Y/N\n");
        char c;
        fflush(stdin);
        scanf("%c", &c);
        if(c == 'N') return ;
        break;
        }
    case 2:// TEACHER INFO UPDATE SECTION.
          {
              student_up();
              printf("\n\n");
              printf("\n\n");

               char c;
               printf("\n Do you want to continue? Y/N\n");
               fflush(stdin);
               scanf("%c", &c);
               if(c == 'N') return;
              break;
          }
    case 3:
        {
            add_course_student();
            char c;
               printf("\n Do you want to continue? Y/N\n");
               fflush(stdin);
               scanf("%c", &c);
               if(c == 'N') return;
            break;
        }
    case 4:
        {
            check_names_student();
            char c;
               printf("\n Do you want to continue? Y/N\n");
               fflush(stdin);
               scanf("%c", &c);
               if(c == 'N') return;
            break;
        }




    }
    }
}

void admin_panel()
{
    while(1)
    {
    int x;
    x = admin_verify();
    //printf("Value is %d \n", x);
    if(x)
    {
        while(1)
        {
        printf("Welcome to Admin panel\n");
        printf("0 to Exit.\n");
        printf("1 to enter student's section.\n");
        printf("2 to enter teacher's section.\n");
        printf("Enter your input here: ");
        char c;
        fflush(stdin);
        scanf("%c", &c);
        if(c == '0')
        {
            return;
        }
        else if(c == '1')
        {
            teacher_sec();
        }
        else if(c == '2')
        {
            student_sec();
        }
        else
        {
            printf("Wrong key!!! Try again!\n");
        }
        }

    }
    else
    {
        printf("Wrong username and password.\n");
        fflush(stdout);
        printf("0 to exit\n");
        printf("1 to try again.\n");
        fflush(stdout);
        int x;
        fflush(stdin);
        scanf("%d", &x);
        if(!x) return;
    }
  }

}





int main()
{

    printf("Welcome To Department Management System.\n");
    int x;
    printf("Please select any of the following option.\n");
    printf("0 to exit.\n");
    printf("1 for students.\n");
    printf("2 for teachers.\n");
    printf("3 for The Admin\n");
    printf("Please enter your input: ");
    fflush(stdin);
    scanf("%d", &x);

    switch(x)
    {
    case 1:
        //student();
        break;
    case 2:
        //teacher();
        break;
    case 3:
        admin_panel();
        break;
    case 0:
        return 0;

    }
}

/*
int main()
{
    int x;
    admin_panel();
    return 0;
}
*/
