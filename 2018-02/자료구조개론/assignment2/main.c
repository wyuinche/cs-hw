#include <stdio.h>
#include <stdlib.h>

//maze point
typedef struct spot{
    int x;
    int y;
    int parent;
} Spot;

char maze[300][300] = {0,}; // maze
int n = 0, m = 0; //dimension of the maze
int exist_path = 0; //whether the path exist

Spot warp_points[20] = {{0, },}; // save the warp points
int warp_length = 0; // the num of warps
int warp_used = 0; // whether the warp is used in the path

Spot* path; //stack
int top = 0; //top index of path

int* cases;//store the number of each case of the path
int walk = 0; //the length of cases

Spot* real_path; //final path
int real_top = 0; // top index of real_path

void receive_maze(); //read maze from input file
int point_search(int parent_spot); // search the points from the parent point
void path_search(int cur_walk); //search the points accessing available
void finish(FILE* out); //print out the result

void print_top(){
    printf("(%d, %d) \n", path[top].x+1, path[top].y+1);
} // print out the top point of the path

int main()
{
    FILE* input = fopen("hw2_input.txt","rt");
    FILE* output = fopen("hw2_output.txt", "wt"); //file stream
    path = (Spot*)malloc(sizeof(Spot));
    cases = (int*)malloc(sizeof(int));
    real_path = (Spot*)malloc(sizeof(Spot)); //allocate the memory

    //file check
    if(input == NULL){
        printf("File Open Fail!\n");
        return 0;
    }
    if(output == NULL){
        printf("File Open Fail!\n");
        return 0;
    }

    receive_maze(input);
    fclose(input);

    cases[0] = 1; //the start point

    path_search(0); //search from the start point
    finish(output); //print out the result
    fclose(output);

    return 0;
}

void receive_maze(FILE* input){
    //store the maze
    while(1){
        char readchar = 0; //store the char read

        fscanf(input, "%c", &readchar); //read a char data

        switch(readchar){
        case '\n':
            n++;
            m = 0;
            break;
        case '*':
            maze[n][m] = '*';
            m++;
            break;
        case '0':
            maze[n][m] = '0';
            m++;
            break;
        case 's':
            maze[n][m] = 's';
            m++;
            path[0].x = n;
            path[0].y = m-1;
            path[0].parent = -1;
            break;
        case 'e':
            maze[n][m] = 'e';
            m++;
            break;
        case 'w':
            maze[n][m] = 'w';
            warp_points[warp_length].x = n;
            warp_points[warp_length].y = m;
            m++;
            warp_length++;
            break;
        }
        if(feof(input) != 0){
            printf("file read complete\n");
            break;
        }
    }

    n++;

    //print it to monitor
    printf("<maze>");
    for(int i = 0; i < n; i++){
        printf("\n");
        for(int j = 0; j < m; j++)
            printf("%c ", maze[i][j]);
    }
    printf("\n");
    printf("dim : %d %d\n", n, m);
    printf("start point : (%d, %d)\n", path[0].x+1, path[0].y+1);

}

//search the points from the parent_point by 1 walk
int point_search(int parent_spot){
    Spot parent_point;
    parent_point.x = path[parent_spot].x;
    parent_point.y = path[parent_spot].y;
    parent_point.parent = path[parent_spot].parent;
    int walk_case = 0; //the number of points accessed

    printf("\nparent_spot : (%d, %d) %d\n", parent_point.x+1, parent_point.y+1, parent_point.parent);
    printf("walk : %d\n", walk);

    //if points is on the sides of rows
    if(parent_point.x == 0){
        if(maze[parent_point.x+1][parent_point.y] == '0'){
            int check = 0;
            for(int i = 0; i < top+1; i++)
                if((path[i].x == parent_point.x+1)&&(path[i].y == parent_point.y)){
                    check++;
                    break;
                }
            if(check == 0){
                top++;
                path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                path[top].x = parent_point.x+1;
                path[top].y = parent_point.y;
                path[top].parent = parent_spot;
                print_top();
                walk_case++;
            }
        }
        else if(maze[parent_point.x+1][parent_point.y] == 'e'){
            top++;
            path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
            path[top].x = parent_point.x+1;
            path[top].y = parent_point.y;
            path[top].parent = parent_spot;
            print_top();
            walk_case++;
            return -1;
        }
        else if(maze[parent_point.x+1][parent_point.y] == 'w'){
            if(warp_used == 0){
                warp_used = 1;
                int first_warp = 0;
                top++;
                path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                path[top].x = parent_point.x+1;
                path[top].y = parent_point.y;
                path[top].parent = parent_spot;
                print_top();
                walk_case++;
                parent_spot = top;
                for(int i = 0; i < warp_length; i++)
                    if((warp_points[i].x == path[top].x)&&(warp_points[i].y == path[top].y))
                        first_warp = i;
                for(int i = 0; i < first_warp; i++){
                    top++;
                    path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                    path[top].x = warp_points[i].x;
                    path[top].y = warp_points[i].y;
                    path[top].parent = parent_spot;
                    print_top();
                    walk_case++;
                }
                for(int i = first_warp+1; i <warp_length; i++){
                    top++;
                    path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                    path[top].x = warp_points[i].x;
                    path[top].y = warp_points[i].y;
                    path[top].parent = parent_spot;
                    print_top();
                    walk_case++;
                }
            }
        }
    }
    else if(parent_point.x == n-1){
        if(maze[parent_point.x-1][parent_point.y] == '0'){
            int check = 0;
            for(int i = 0; i < top+1; i++)
                if((path[i].x == parent_point.x-1)&&(path[i].y == parent_point.y)){
                    check++;
                    break;
                }
            if(check == 0){
                top++;
                path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                path[top].x = parent_point.x-1;
                path[top].y = parent_point.y;
                path[top].parent = parent_spot;
                print_top();
                walk_case++;
            }
        }
        else if(maze[parent_point.x-1][parent_point.y] == 'e'){
                top++;
                path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                path[top].x = parent_point.x-1;
                path[top].y = parent_point.y;
                path[top].parent = parent_spot;
                print_top();
                walk_case++;
            return -1;
        }
        else if(maze[parent_point.x-1][parent_point.y] == 'w'){
            if(warp_used == 0){
                warp_used = 1;
                int first_warp = 0;
                top++;
                path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                path[top].x = parent_point.x-1;
                path[top].y = parent_point.y;
                path[top].parent = parent_spot;
                print_top();
                walk_case++;
                parent_spot = top;
                for(int i = 0; i < warp_length; i++)
                    if((warp_points[i].x == path[top].x)&&(warp_points[i].y == path[top].y))
                        first_warp = i;
                for(int i = 0; i < first_warp; i++){
                    top++;
                    path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                    path[top].x = warp_points[i].x;
                    path[top].y = warp_points[i].y;
                    path[top].parent = parent_spot;
                    print_top();
                    walk_case++;
                }
                for(int i = first_warp+1; i <warp_length; i++){
                    top++;
                    path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                    path[top].x = warp_points[i].x;
                    path[top].y = warp_points[i].y;
                    path[top].parent = parent_spot;
                    print_top();
                    walk_case++;
                }
            }
        }
    }
    //if the point is not on the sides of rows
    else{
        if(maze[parent_point.x+1][parent_point.y] == '0'){
            int check = 0;
            for(int i = 0; i < top+1; i++)
                if((path[i].x == parent_point.x+1)&&(path[i].y == parent_point.y)){
                    check++;
                    break;
                }
            if(check == 0){
                top++;
                path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                path[top].x = parent_point.x+1;
                path[top].y = parent_point.y;
                path[top].parent = parent_spot;
                print_top();
                walk_case++;
            }
        }
        else if(maze[parent_point.x+1][parent_point.y] == 'e'){
            top++;
            path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
            path[top].x = parent_point.x+1;
            path[top].y = parent_point.y;
            path[top].parent = parent_spot;
            print_top();
            walk_case++;
            return -1;
        }
        else if(maze[parent_point.x+1][parent_point.y] == 'w'){
            if(warp_used == 0){
                warp_used = 1;
                int first_warp = 0;
                top++;
                path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                path[top].x = parent_point.x+1;
                path[top].y = parent_point.y;
                path[top].parent = parent_spot;
                print_top();
                walk_case++;
                parent_spot = top;
                for(int i = 0; i < warp_length; i++)
                    if((warp_points[i].x == path[top].x)&&(warp_points[i].y == path[top].y))
                        first_warp = i;
                for(int i = 0; i < first_warp; i++){
                    top++;
                    path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                    path[top].x = warp_points[i].x;
                    path[top].y = warp_points[i].y;
                    path[top].parent = parent_spot;
                    print_top();
                    walk_case++;
                }
                for(int i = first_warp+1; i <warp_length; i++){
                    top++;
                    path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                    path[top].x = warp_points[i].x;
                    path[top].y = warp_points[i].y;
                    path[top].parent = parent_spot;
                    print_top();
                    walk_case++;
                }
            }
        }

        if(maze[parent_point.x-1][parent_point.y] == '0'){
            int check = 0;
            for(int i = 0; i < top+1; i++)
                if((path[i].x == parent_point.x-1)&&(path[i].y == parent_point.y)){
                    check++;
                    break;
                }
            if(check == 0){
                top++;
                path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                path[top].x = parent_point.x-1;
                path[top].y = parent_point.y;
                path[top].parent = parent_spot;
                print_top();
                walk_case++
;            }
        }
        else if(maze[parent_point.x-1][parent_point.y] == 'e'){
            top++;
            path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
            path[top].x = parent_point.x-1;
            path[top].y = parent_point.y;
            path[top].parent = parent_spot;
            print_top();
            walk_case++;
            return -1;
        }
        else if(maze[parent_point.x-1][parent_point.y] == 'w'){
            if(warp_used == 0){
                warp_used = 1;
                int first_warp = 0;
                top++;
                path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                path[top].x = parent_point.x-1;
                path[top].y = parent_point.y;
                path[top].parent = parent_spot;
                print_top();
                walk_case++;
                parent_spot = top;
                for(int i = 0; i < warp_length; i++)
                    if((warp_points[i].x == path[top].x)&&(warp_points[i].y == path[top].y))
                        first_warp = i;
                for(int i = 0; i < first_warp; i++){
                    top++;
                    path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                    path[top].x = warp_points[i].x;
                    path[top].y = warp_points[i].y;
                    path[top].parent = parent_spot;
                    print_top();
                    walk_case++;
                }
                for(int i = first_warp+1; i <warp_length; i++){
                    top++;
                    path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                    path[top].x = warp_points[i].x;
                    path[top].y = warp_points[i].y;
                    path[top].parent = parent_spot;
                    print_top();
                    walk_case++;
                }
            }
        }
    }

    //if the point is on the sides of columns
    if(parent_point.y == 0){
        if(maze[parent_point.x][parent_point.y+1] == '0'){
            int check = 0;
            for(int i = 0; i < top+1; i++)
                if((path[i].x == parent_point.x)&&(path[i].y == parent_point.y+1)){
                    check++;
                    break;
                }
            if(check == 0){
                top++;
                path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                path[top].x = parent_point.x;
                path[top].y = parent_point.y+1;
                path[top].parent = parent_spot;
                print_top();
                walk_case++;
            }
        }
        else if(maze[parent_point.x][parent_point.y+1] == 'e'){
                top++;
                path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                path[top].x = parent_point.x;
                path[top].y = parent_point.y+1;
                path[top].parent = parent_spot;
                print_top();
                walk_case++;
            return -1;
        }
        else if(maze[parent_point.x][parent_point.y+1] == 'w'){
            if(warp_used == 0){
                warp_used = 1;
                int first_warp = 0;
                top++;
                path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                path[top].x = parent_point.x;
                path[top].y = parent_point.y+1;
                path[top].parent = parent_spot;
                print_top();
                walk_case++;
                parent_spot = top;
                for(int i = 0; i < warp_length; i++)
                    if((warp_points[i].x == path[top].x)&&(warp_points[i].y == path[top].y))
                        first_warp = i;
                for(int i = 0; i < first_warp; i++){
                    top++;
                    path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                    path[top].x = warp_points[i].x;
                    path[top].y = warp_points[i].y;
                    path[top].parent = parent_spot;
                    print_top();
                    walk_case++;
                }
                for(int i = first_warp+1; i <warp_length; i++){
                    top++;
                    path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                    path[top].x = warp_points[i].x;
                    path[top].y = warp_points[i].y;
                    path[top].parent = parent_spot;
                    print_top();
                    walk_case++;
                }
            }
        }
    }
    else if(parent_point.y == m-1){
        if(maze[parent_point.x][parent_point.y-1] == '0'){
            int check = 0;
            for(int i = 0; i < top+1; i++)
                if((path[i].x == parent_point.x)&&(path[i].y == parent_point.y-1)){
                    check++;
                    break;
                }
            if(check == 0){
                path = (Spot*)realloc(path, sizeof(Spot)*(++top));
                top++;
                path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                path[top].x = parent_point.x;
                path[top].y = parent_point.y-1;
                path[top].parent = parent_spot;
                print_top();
                walk_case++;
            }
        }
        else if(maze[parent_point.x][parent_point.y-1] == 'e'){
            top++;
            path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
            path[top].x = parent_point.x;
            path[top].y = parent_point.y-1;
            path[top].parent = parent_spot;
            print_top();
            walk_case++;
            return -1;
        }
        else if(maze[parent_point.x][parent_point.y-1] == 'w'){
            if(warp_used == 0){
                warp_used = 1;
                int first_warp = 0;
                top++;
                path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                path[top].x = parent_point.x;
                path[top].y = parent_point.y-1;
                path[top].parent = parent_spot;
                print_top();
                walk_case++;
                parent_spot = top;
                for(int i = 0; i < warp_length; i++)
                    if((warp_points[i].x == path[top].x)&&(warp_points[i].y == path[top].y))
                        first_warp = i;
                for(int i = 0; i < first_warp; i++){
                    top++;
                    path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                    path[top].x = warp_points[i].x;
                    path[top].y = warp_points[i].y;
                    path[top].parent = parent_spot;
                    print_top();
                    walk_case++;
                }
                for(int i = first_warp+1; i <warp_length; i++){
                    top++;
                    path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                    path[top].x = warp_points[i].x;
                    path[top].y = warp_points[i].y;
                    path[top].parent = parent_spot;
                    print_top();
                    walk_case++;
                }
            }
        }
    }
    //if the point is not on the sides of columns
    else{
        if(maze[parent_point.x][parent_point.y+1] == '0'){
            int check = 0;
            for(int i = 0; i < top+1; i++)
                if((path[i].x == parent_point.x)&&(path[i].y == parent_point.y+1)){
                    check++;
                    break;
                }
            if(check == 0){
                top++;
                path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                path[top].x = parent_point.x;
                path[top].y = parent_point.y+1;
                path[top].parent = parent_spot;
                print_top();
                walk_case++;
            }
        }
        else if(maze[parent_point.x][parent_point.y+1] == 'e'){
                top++;
                path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                path[top].x = parent_point.x;
                path[top].y = parent_point.y+1;
                path[top].parent = parent_spot;
                print_top();
                walk_case++;
            return -1;
        }
        else if(maze[parent_point.x][parent_point.y+1] == 'w'){
            if(warp_used == 0){
                warp_used = 1;
                int first_warp = 0;
                top++;
                path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                path[top].x = parent_point.x;
                path[top].y = parent_point.y+1;
                path[top].parent = parent_spot;
                print_top();
                walk_case++;
                parent_spot = top;
                for(int i = 0; i < warp_length; i++)
                    if((warp_points[i].x == path[top].x)&&(warp_points[i].y == path[top].y))
                        first_warp = i;
                for(int i = 0; i < first_warp; i++){
                    top++;
                    path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                    path[top].x = warp_points[i].x;
                    path[top].y = warp_points[i].y;
                    path[top].parent = parent_spot;
                    print_top();
                    walk_case++;
                }
                for(int i = first_warp+1; i <warp_length; i++){
                    top++;
                    path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                    path[top].x = warp_points[i].x;
                    path[top].y = warp_points[i].y;
                    path[top].parent = parent_spot;
                    print_top();
                    walk_case++;
                }
            }
        }
        if(maze[parent_point.x][parent_point.y-1] == '0'){
            int check = 0;
            for(int i = 0; i < top+1; i++)
                if((path[i].x == parent_point.x)&&(path[i].y == parent_point.y-1)){
                    check++;
                    break;
                }
            if(check == 0){
                top++;
                path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                path[top].x = parent_point.x;
                path[top].y = parent_point.y-1;
                path[top].parent = parent_spot;
                print_top();
                walk_case++;
            }
        }
        else if(maze[parent_point.x][parent_point.y-1] == 'e'){
            top++;
            path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
            path[top].x = parent_point.x;
            path[top].y = parent_point.y-1;
            path[top].parent = parent_spot;
            print_top();
            walk_case++;
            return -1;
        }
        else if(maze[parent_point.x][parent_point.y-1] == 'w'){
            if(warp_used == 0){
                warp_used = 1;
                int first_warp = 0;
                top++;
                path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                path[top].x = parent_point.x;
                path[top].y = parent_point.y-1;
                path[top].parent = parent_spot;
                print_top();
                walk_case++;
                parent_spot = top;
                for(int i = 0; i < warp_length; i++)
                    if((warp_points[i].x == path[top].x)&&(warp_points[i].y == path[top].y))
                        first_warp = i;
                for(int i = 0; i < first_warp; i++){
                    top++;
                    path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                    path[top].x = warp_points[i].x;
                    path[top].y = warp_points[i].y;
                    path[top].parent = parent_spot;
                    print_top();
                    walk_case++;
                }
                for(int i = first_warp+1; i <warp_length; i++){
                    top++;
                    path = (Spot*)realloc(path, sizeof(Spot)*(top+1));
                    path[top].x = warp_points[i].x;
                    path[top].y = warp_points[i].y;
                    path[top].parent = parent_spot;
                    print_top();
                    walk_case++;
                }
            }
        }
    }
    //return the number of cases
    return walk_case;
}

//search the path from the cur_walk point
void path_search(int cur_walk){
    int point_walk = cases[cur_walk]; //the number of cases with walk cur_walk
    int cases_tmp = 0;
    int top_tmp = top;
    walk++;
    cases = (int*)realloc(cases, sizeof(int)*(walk+1)); //allocate the memory
    cases[walk] = 0;

    //search from the point path[top-point_walk+1] to the point path[top]
    for(int i = point_walk-1; i >= 0; i--){
        cases_tmp = point_search(top_tmp-i);
        if(cases_tmp == -1){
            cases[walk]++;
            return 0;
        } //if reached to e then exit
        else
            cases[walk] += cases_tmp;
            //save the number of cases
    }

    // if there is no available path anymore
    if(cases[walk] == 0){
        printf("no path\n");
        exist_path++;
        return 0;
    }
    else
        path_search(walk); //call the function again

}

//print out the result
void finish(FILE* out){
    int parent_point = top;
    int warp_used_real = 0;

    //print out "NULL" to the output file if there's no path
    if(exist_path > 0){
        fprintf(out, "NULL\n");
        return 0;
    }

    printf("\n");

    //save the real path from e to s
    do {
        Spot s;

        s.x = path[parent_point].x;
        s.y = path[parent_point].y;
        s.parent = path[parent_point].parent;

        real_top++;
        real_path = (Spot*)realloc(real_path, sizeof(Spot)*real_top);
        real_path[real_top-1] = s;

        parent_point = s.parent;

    } while(parent_point != 0); //quit if you access the s point

    real_path[real_top] = path[0];

    printf("%d\n", walk);
    fprintf(out, "%d\n", walk); //print out the walk from s to e

    //print out the path to the monitor
    for(int i = 0; i < real_top; i++)
        printf("(%d, %d),", real_path[real_top-i].x+1, real_path[real_top-i].y+1);

    //print out the path to the output file
    for(int i = 0; i < real_top; i++)
        fprintf(out, "(%d, %d),", real_path[real_top-i].x+1, real_path[real_top-i].y+1);

    //print out the last point
    printf("(%d, %d)", real_path[0].x+1, real_path[0].y+1);
    fprintf(out, "(%d, %d)", real_path[0].x+1, real_path[0].y+1);

    return 0;
}
