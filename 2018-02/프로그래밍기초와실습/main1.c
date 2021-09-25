#include <stdio.h>
#include <stdlib.h>

typedef struct student
{
    int score;
    char grade;
} Student;

typedef struct class_students
{
    Student s_1, s_2, s_3, s_4;
    float average;
} Class_Students;

int precheck(int n)
{
    if((n<0)||(n>100))
        return 1;
    else
        return 0;
}

char pregrade(float score, float average)
{
    float score_gap = score - average;

    if(10 <= score_gap)
        return 'A';
    else if(0 <= score_gap)
        return 'B';
    else if(-10 <= score_gap)
        return 'C';
    else
        return 'D';
}

void show_grade(Class_Students class_in)
{
    printf("The 1st student : %d %c grade \n", class_in.s_1.score, class_in.s_1.grade);
    printf("The 2nd student : %d %c grade \n", class_in.s_2.score, class_in.s_2.grade);
    printf("The 3rd student : %d %c grade \n", class_in.s_3.score, class_in.s_3.grade);
    printf("The 4th student : %d %c grade \n", class_in.s_4.score, class_in.s_4.grade);
}

int main(void)
{
    Class_Students class_n;
    int execute = 1;

    //Input_Data//
    printf("Input each of 4 students score (0~100) : ");
    scanf("%d %d %d %d", &class_n.s_1.score, &class_n.s_2.score, &class_n.s_3.score, &class_n.s_4.score);

    //Invalid_Check//
    if(precheck(class_n.s_1.score)||precheck(class_n.s_2.score)||precheck(class_n.s_3.score)||precheck(class_n.s_4.score))
    {
        printf("Invalid entry!");
        execute = 0;
    }
    else
    {
        class_n.average = ((float)(class_n.s_1.score)+(float)class_n.s_2.score+(float)class_n.s_3.score+(float)class_n.s_4.score)/4;
        printf("The average score : %.2f \n", class_n.average);
    }

    //Grading - Quit the program if an invalid entry exists//
    if(execute == 1)
    {
        class_n.s_1.grade = pregrade(class_n.s_1.score, class_n.average);
        class_n.s_2.grade = pregrade(class_n.s_2.score, class_n.average);
        class_n.s_3.grade = pregrade(class_n.s_3.score, class_n.average);
        class_n.s_4.grade = pregrade(class_n.s_4.score, class_n.average);

        show_grade(class_n);

        return 0;
    }
    else
        return 0;
}
