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
//prototypes used in functions
void admin_info_update();
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

//********************************************Functions for Teacher panel*****************************//

int teacher_verify();
int count_student();
void find_student();
void teacher_panel();
//**********************************************end of teacher panel**********************************//



void admin_info_update()//This one is used to update admin username and password.
{
    FILE *fp;
    fp = fopen("admin_info.txt", "w");
    admin a;
    fflush(stdin);
    strcpy(a.name, "Raiyan Ashraf");
    strcpy(a.pass, "1907023");
    fwrite(&a, sizeof(a), 1, fp);
    fclose(fp);
    return;
}



//FUNCTIONS OF ADMIN PANEL.
//This function is used to verify admin.
int admin_verify()
{
    char un[200], pw[200];
    int x;
    admin b;
    FILE *fp;
    fp = fopen("admin_info.txt", "r");
    fread(&b, sizeof(admin), 1, fp);
    //printf("Admin name : %s\n", b.name);
    //printf("Admin pass : %s\n", b.pass);

    printf("Verifying Admin.\n");
    printf("Username: ");
    fflush(stdin);
    gets(un);
    //printf("Input name : %s\n", un);

    printf("Password: ");
    fflush(stdin);
    gets(pw);
    //printf("Input password : %s\n", pw);

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
void add_teacher()//Function to create teacher account via admin panel.
{
        FILE *fpt;
        fpt = fopen("teacher_info.txt", "a+");//teacher_info file is opened for appending.
        teacher tc;
        int x = 2;
        printf("Please Enter the username of the teacher: ");
        char s[200];
        fflush(stdin);
        gets(s);
        while(fread(&tc, sizeof(teacher), 1, fpt))  //reading data from teacher file and storing in it.
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
           strcpy(tc.courses[0], "NULL");     //Assigining NULL in courses as default. Which shows that the course is not assigned yet.
           strcpy(tc.courses[1], "NULL");
           fwrite(&tc, sizeof(tc), 1, fpt);  //writing new info in teacher txt file.

           printf("\n******New teacher enlisted successfully.******\n");

        fclose(fpt);

}

void check_names_teacher()//Check enlisted names in the current data base. It will show garbage value if no input is enlisted before.
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

void teacher_up() //This function updates teacher names and password.
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
            while(fread(&a,sizeof(teacher), 1, fpt2))  //Finds the name of the teacher user intents to change.
            {
                if(strcmp(a.name, s) == 0)
                {
                    flag = 1;                         // flags if teacher is found.
                    break;
                }
            }
            fclose(fpt2);
            if(!flag)
            {
                printf("\n******Teacher not found. Please try again.******\n");  //The teacher is not enlisted. So there is no question of updating.
            }
            else
            {
            printf("Teacher found.\n");
            //IF TEACHER NAME IS FOUND.
            printf("press 1 to update the name.\n");                            //teacher found. Trying to update name or password.
            printf("press 2 to update the password.\n");
            char x;
            fflush(stdin);
            scanf("%c", &x);
            if(x == '1')
            {
                printf("Enter the name you want to replace with:  ");
                char s[200];
                fflush(stdin);
                gets(s);
                FILE *fpt1, *fpt2;
                fpt1 = fopen("teacher_info.txt", "r");       //A Temp file is created. At first the contents read from the main file are written in the temp file.
                fpt2 = fopen("temp.txt", "w");              // Then the changed name is given here.
                teacher b;                                  //Changed struct is written in the temp.

                while(fread(&b, sizeof(teacher), 1, fpt1))    //Replace the name with the previous one.
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
            else if(x=='2')
            {
                fpt2 = fopen("teacher_info.txt", "r");
                fpt1 = fopen("temp.txt", "w");
                printf("Enter the password you want to replace with: ");
                char s[200];
                fflush(stdin);
                gets(s);
                teacher b;

                while(fread(&b, sizeof(b), 1, fpt2))                      //Replacing the password in same way, by writing in temp file.
                {
                    if(strcmp(b.pass, a.pass) == 0)
                    {
                          strcpy(b.pass, s);
                    }
                    fwrite(&b, sizeof(teacher), 1, fpt1);


                }
                fclose(fpt2);
                fclose(fpt1);
                fpt2 = fopen("teacher_info.txt", "w");                 //New teacher info is created.
                fpt1 = fopen("temp.txt", "r");                         //The new modified info is in the temp file.
                while(fread(&b, sizeof(b), 1, fpt1))
                {
                    fwrite(&b, sizeof(b), 1, fpt2);                    //The modified info is written in the teacher info file.
                }
                printf("\n******Updated password successfully.******\n");
                fclose(fpt1);
                fclose(fpt2);

                }
                else
                {
                    printf("Invalid input!!!. Please try again!!\n");  //wrong key given, returns the function.
                    return;
                }
            }

}

void add_course_teacher()                     //Assigning courses to the teachers here.(can be said updating courses)
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
    while(fread(&tc, sizeof(teacher), 1, fpt1))                  //Finds the teacher as given in the input.
    {                                                            //Temp file is created so that we can use it when change is happened.
        if(strcmp(s, tc.name) == 0)
        {
            flag = 1;
            break;
        }
        fwrite(&tc, sizeof(teacher), 1, fpt2);
    }
    if(flag == 0)
    {
        printf("Teacher not found. Please try again.\n");        //Teacher not found. So no question of updating.
        return;

    }
        printf("Teacher found.\n");
        printf("Assigned courses to %s is: %s %s\n", tc.name, tc.courses[0], tc.courses[1]);   //The ourse assigned to this teacher will be shown.
        printf("press any key to update\n");                                                   //NULL means no course has been assigned yet.
        printf("press 0 to exit\n");
        fflush(stdin);
        char x;
        scanf("%c", &x);
        if(x == '0') return;

        char s1[100], s2[100];
        printf("Enter the name of the course 1(type NULL if you don't want to):");
        fflush(stdin);                      //FFLUSH is used to clear the buffer....otherwise garbage input is assigned.
        gets(s1);
        strcpy(tc.courses[0], s1);
        printf("Enter the name of the course 2:(type NULL if you don't want to):");//The two courses are assigned.
        fflush(stdin);
        gets(s2);
        strcpy(tc.courses[1], s2);
        fwrite(&tc, sizeof(teacher), 1, fpt2);
         while(fread(&tc, sizeof(teacher), 1, fpt1))
        {
         fwrite(&tc, sizeof(teacher), 1, fpt2);                           //The rest of the contents from teacher info txt is written here.
        }
        fclose(fpt1);
        fclose(fpt2);

        fpt1 = fopen("temp.txt", "r");                                   //the modified contents are written in the temp file.
        fpt2 = fopen("teacher_info.txt", "w");                          //New teacher info file created

        while((fread(&tc,sizeof(teacher),1,fpt1))>0)                    //The contents of temp file is written in the new teacher file.
            {
               fwrite(&tc,sizeof(teacher),1,fpt2);
            }

            fclose(fpt1);
            fclose(fpt2);

            printf("Course updated successfully.\n");                 //new changed updated teacher file.





}

void teacher_sec()             //The function to add or modify teacher information through admin section.
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

void add_student() //function to create new student account
{
        FILE *fpt;
        fpt = fopen("student_info.txt", "a+");           //Appending info in the student file.
        student tc;
        int x = 2;
        printf("Please Enter the name of the student: ");
        char s[200];
        fflush(stdin);
        gets(s);
        while(fread(&tc, sizeof(student), 1, fpt))        //searching the given name.
        {
            if(strcmp(tc.name, s) == 0)
            {
                printf("Student already enlisted!!!\n");     //If the name is previously added. This option is given so that there is no redundancy.
                printf("press 1 to update.\n");
                printf("press 0 to exit.\n");
                fflush(stdin);
                scanf("%d", &x);
            }
        }

        if(x == 1)
        {
            student_up();               //updating the name as previously stated.
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
           strcpy(tc.courses[0], "NULL");                   //NULL course is assigned to student as default.
           strcpy(tc.courses[1], "NULL");                   //It means that no course is assigned.
           tc.marks_1 = -1;
           tc.marks_2 = -1;
           fwrite(&tc, sizeof(tc), 1, fpt);

           printf("\n******New student enlisted successfully.******\n");

        fclose(fpt);

}

void check_names_student()               //Function to show to existing student info panel. Will show garbage value if no student is added before.
{
        FILE *fpp;
        student x;
        fpp=fopen("student_info.txt","r");
        while(fread(&x,sizeof(student),1,fpp))
        {
            printf("%s ",x.name);
            printf("%s ",x.pass);
            printf("Courses : %s %s .", x.courses[0], x.courses[1]);
            printf(" Marks 1 = %d, Marks 2 = %d\n", x.marks_1, x.marks_2); //Show student complete info(with marks and course)
        }


        fclose(fpp);
}

void student_up()            //For updating existing student informations.
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
                if(strcmp(a.name, s) == 0)                //Checking if the given name exists.
                {
                    flag = 1;
                    break;
                }
            }
            fclose(fpt2);
            if(!flag)
            {
                printf("\n******Student not found. Please try again.******\n");  //returns if the name doesnt exist.
            }
            else
            {
            printf("Student found.\n");
            //IF STUDENT NAME IS FOUND.
            //CAUTION: NAME TA SAVE KORA ACHE.
            printf("press 1 to update the name.\n");                //The given name was enlisted before. And it is found.
            printf("press 2 to update the password.\n");
            char x;
            fflush(stdin);
            scanf("%c", &x);
            if(x == '1')
            {
                printf("Enter the name you want to replace with:  ");
                char s[200];
                fflush(stdin);
                gets(s);
                FILE *fpt1, *fpt2;
                fpt1 = fopen("student_info.txt", "r");
                fpt2 = fopen("temp.txt", "w");
                student b;

                while(fread(&b, sizeof(student), 1, fpt1))    //Updating the name by similar method used previously  in teacher update section.
                 {
                        if(strcmp(b.name, a.name) == 0)      // pointing the memory to the desired name, then changing it.
                        {
                                strcpy(b.name, s);
                                //strcpy(b.pass, "1123");
                        }
                    fwrite(&b, sizeof(student), 1, fpt2);
                 }                                          // The changed and updated student info is written in temp file.

                    fclose(fpt1);
                    fclose(fpt2);
                    fpt1 = fopen("temp.txt", "r");
                    fpt2 = fopen("student_info.txt", "w");

                    while((fread(&b,sizeof(student),1,fpt1))>0)
                    {                                          //The contents of the temp file is written in the new student info file.
                        fwrite(&b,sizeof(student),1,fpt2);     //The new updated student info file is created.
                    }
                        fclose(fpt1);
                        fclose(fpt2);
                    printf("\n******Updated name successfully.******\n");

                }
            else if(x=='2')
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
                printf("\n******Updated password successfully.******\n");            //Updated the password in a similar manner as before.
                fclose(fpt1);
                fclose(fpt2);

                }
                else
                {
                    printf("Invalid Key!! please try again!!\n");
                    return;
                }
            }

}

void add_course_student() // add courses to the existing student accounts.
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
            flag = 1;                                              //Checking Whether the given name was enlisted before.
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
        printf("press any key to update\n");   // Assigned courses for this student is shown.
        printf("press 0 to exit\n");
        fflush(stdin);
        char x;
        fflush(stdin);
        scanf("%c", &x);
        if(x == '0') return;

        char s1[100], s2[100];
        printf("Enter the name of the course 1(type NULL if you dont want to assign any): ");
        fflush(stdin);
        gets(s1);
        strcpy(tc.courses[0], s1);
        printf("Enter the name of the course 2(type NULL if you dont want to assign any): ");
        fflush(stdin);
        gets(s2);
        strcpy(tc.courses[1], s2);
        fwrite(&tc, sizeof(student), 1, fpt2);
         while(fread(&tc, sizeof(student), 1, fpt1))
        {
         fwrite(&tc, sizeof(student), 1, fpt2);                //Updated courses with previous data is recorded in the temp file.
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

            printf("Course updated successfully.\n");             //All the updated data is written in the new student info file.





}

void student_sec()   //Function for updating or creating student info through admin section.
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
    char n;
    scanf("%c", &n);
    if(n == '0')
    {
        return;
    }
    else if(n == '1')
    {
        add_student();
    }
    else if(n == '2')
    {
        student_up();
    }
    else if(n == '3')
    {
        add_course_student();
    }
    else if(n == '4')
    {
        check_names_student();
    }
    else
    {
        printf("Invalid key!! Please try again!!!");
    }
    }
}

void admin_panel()    // Function for the access of the whole admin panel. Including login, student info and teacher info edit.
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
            student_sec();
        }
        else if(c == '2')
        {
            teacher_sec();
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


//******************************************Start of Teacher panel*******************************

int teacher_verify() //Verifying teacher by matching username and password from input and teacher info file.
{
   char s1[200], s2[200];
   printf("****Teacher Login*****\n");
   printf("username: ");
   fflush(stdin);
   gets(s1);
   printf("password: ");
   fflush(stdin);
   gets(s2);
   FILE *fpt;
   fpt = fopen("teacher_info.txt", "r");
   teacher b;
   while(fread(&b, sizeof(teacher), 1, fpt))
   {
       if((strcmp(s1, b.name) == 0) && (strcmp(s2, b.pass) == 0))
       {

           fclose(fpt);
           return 1;
       }
   }
   fclose(fpt);
   return 0;


}

int count_student() //Counts the number of the stduents by reading through the whole file of student.
{
    int x = 0;

    FILE *fpt;
    fpt = fopen("student_info.txt", "r");
    student b;
    while(fread(&b, sizeof(b), 1, fpt))
    {
        x++;
    }
    fclose(fpt);
    return x;
}

void find_student() //This function finds student according to given name then assign marks according to given course.
{
    printf("Please type your user name again: ");
    char t[200];
    fflush(stdin);
    gets(t);
    printf("Please type your password again: ");
    char tp[200];
    fflush(stdin);
    gets(tp);
    printf("Type the name of the student as enlisted before: ");
    char s[200];
    fflush(stdin);
    gets(s);
    FILE *fpt1, *fpt2, *fpt3;
    student b;
    teacher tc;
    fpt1 = fopen("student_info.txt", "r");
    fpt2 = fopen("temp.txt", "w");
    fpt3 = fopen("teacher_info.txt", "r");    //The username and password is  taken again to compare the assign courses of the teacher.
    char sub1[200], sub2[200];                //In case the teacher gives any course which is not assigned to him/her.
    int tc_flag = 1;
    while(fread(&tc, sizeof(teacher), 1, fpt3))
    {
        if(strcmp(t, tc.name) == 0 && strcmp(tp, tc.pass)== 0 )
        {
            strcpy(sub1, tc.courses[0]);
            strcpy(sub2, tc.courses[1]);
            fclose(fpt3);
            tc_flag = 0;                    //Flags if the username and passwords of the teaacher is matched.
            break;

        }
    }
    if(tc_flag)
    {
        printf("You have entered wrong username or password here. Please try again correctly.\n");
        return;
    }

    int flag = 1;
    while(fread(&b, sizeof(b), 1, fpt1))
    {
        if(strcmp(s, b.name) == 0)
        {
           flag = 0;                                //Searches whether the name of the student, the teacher wish to find, is enlisted.
           break;
        }
        fwrite(&b, sizeof(student), 1, fpt2);
    }
    if(flag)
    {
        printf("Student not found. Try again.\n"); //Student not enlisted. So returns.
        fclose(fpt1);
        fclose(fpt2);
        return;
    }
    int x;
    printf("Student %s is found!!!\n", b.name);
    printf("0 to exit.\n");
    printf("1 to update marks.\n");
    fflush(stdin);
    scanf("%d", &x);
    if(!x)
    {
        fclose(fpt1);
        fclose(fpt2);
        return;
    }

    printf("Enter the course name you want to update marks(as enlisted before): ");
    char s1[200];
    fflush(stdin);
    gets(s1);
    if(strcmp(sub1, s1) != 0 && strcmp(sub2, s1) != 0)           //Checks whether the course the teacher given is enlisted to him/her.
    {
        printf("Sorry!! You are not enlisted for the following course. Please try again.\n"); //If not, returns.
        fclose(fpt1);
        fclose(fpt2);
        return;
    }
    if(strcmp(s1, b.courses[0]) == 0)                    //If the course given by the teacher is assigned to the student before, only then
    {                                                    // the teacher can assign CT marks, otherwise not.
        int a;
        printf("Enter marks: ");
        fflush(stdin);
        scanf("%d", &a);
        b.marks_1 = a;
    }
    else if(strcmp(s1, b.courses[1]) == 0)
    {
        int a;
        printf("Enter marks: ");
        fflush(stdin);
        scanf("%d", &a);
        b.marks_2 = a;
    }
    else
    {
        printf("No such course is assigned to this student. Try again.\n");  //The student is not assigned with such course. So returns.
        fclose(fpt1);
        fclose(fpt2);
        return;

    }

    fwrite(&b, sizeof(student), 1, fpt2);
    while(fread(&b, sizeof(student), 1, fpt1))   //If everything matches, then the updated version is written in the temp file (along with Before).
    {
        fwrite(&b, sizeof(student), 1, fpt2);
    }
    fclose(fpt1);
    fclose(fpt2);

    fpt1 = fopen("temp.txt", "r");
    fpt2 = fopen("student_info.txt", "w");

     while(fread(&b, sizeof(student), 1, fpt1)) //The updated temp version is written in a new student info section.
    {
        fwrite(&b, sizeof(student), 1, fpt2);
    }
    fclose(fpt1);
    fclose(fpt2);

    printf("Marks updated successfully\n");

    return;




}

void teacher_panel() // The function for the teacher panel, used for finding student, giving CT marks, and counting student no.
{
    if(!teacher_verify())
    {
        printf("Invalid username and password.\n");
        return;
    }
    while(1)
    {
    printf("******Welcome to teacher panel******\n");
    printf("0 to exit.\n");
    printf("1 to find the student.\n");
    printf("2 to count student number.\n");
    char x;
    fflush(stdin);
    scanf("%c", &x);
    if(x == '0')
    {
        return;
    }
    else if(x == '1')
    {
        find_student();
    }
    else if(x == '2')
    {
        int x;
        x = count_student();
        printf("Total enlisted students: %d\n", x);
    }
    else
    {
        printf("Invalid key. Try again.\n");
    }
    }



    /*
    check_names_student();
    printf("\n\n");
    check_names_teacher();
    */
    return;

}
//*******************************************END OF TEACHER PANEL****************************************

//*******************************************START OF STUDENT PANEL***************************************
void student_login() //Student verification. If matches with the student_info file then shows the Course and CT marks of the student.
{
   char s1[200], s2[200];
   printf("****student Login*****\n");
   printf("username: ");
   fflush(stdin);
   gets(s1);
   printf("password: ");
   fflush(stdin);
   gets(s2);
   FILE *fpt;
   fpt = fopen("student_info.txt", "r");
   student b;
   while(fread(&b, sizeof(student), 1, fpt))
   {
       if((strcmp(s1, b.name) == 0) && (strcmp(s2, b.pass) == 0))
       {

           printf("Student name: %s\n", b.name);
           printf("Student CT marks in %s = %d\n",b.courses[0], b.marks_1 );
           printf("Student CT marks in %s = %d\n",b.courses[1], b.marks_2 );
           printf("\n\n********PLEASE NOTICE*********************************************\n");
           printf("The course \"NULL\" means no assigned course.\n");
           printf("The marks \"-1\" means marks have not been updated by the teacher yet.\n");
           printf("***********************************************************************\n\n\n");
           fclose(fpt);
           return;
       }
   }
   printf("Invalid username and password. Please try again.\n");
   fclose(fpt);
   return;


}

void student_panel() //The student panel segment for students to log in and know CT marks in courses. Shows NULL if no course given and
{                    //the shows -1 if no marks is assigned.
   while(1)
   {
       student_login();
       char c;
       printf("Press 0 to exit.\n");
       printf("Press any other key to continue.\n");
       fflush(stdin);
       scanf("%c", &c);
       if(c == '0')
       {
           return;
       }
   }
   return;

}

//*************************************************END OF STUDENT PANEL**********************************

int main() // The main function. Base functions.
{
    admin_info_update();
    while(1)
    {
    printf("**********************Welcome To Department Management System.*****************\n");
    printf("***********Developed by Raiyan Ashraf. Roll: 1907023****************************\n");
    printf("Please select any of the following option.\n");
    printf("0 to exit.\n");
    printf("1 for students.\n");
    printf("2 for teachers.\n");
    printf("3 for The Admin\n");
    printf("Please enter your input: ");

    char n;
    fflush(stdin);
    scanf("%c", &n);
    if(n == '0')
    {
        return 0;
    }
    else if(n == '1')
    {
        student_panel();
    }
    else if(n == '2')
    {
        teacher_panel();
    }
    else if(n == '3')
    {
        admin_panel();
    }
    else
    {
        printf("Invalid!!! Wrong Key!! Please try again.\n");
    }

    }
}


