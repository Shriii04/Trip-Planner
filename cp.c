#include <stdio.h>
#include <Windows.h>
#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define MAX_CITIES 6

typedef struct
{
    int distance[MAX_CITIES][MAX_CITIES];
} Graph;
void disinfo()
{
    printf("Press 1 to see good restaurants:\n");
    printf("Press 2 to see nearby hospitals:\n");
    printf("Press 3 to see nearby places to visit:\n");
}
void printc()
{
    char *cities[] = {
        "Mumbai-0", "Pune-1", "Nagpur-2", "Nashik-3", "Amravati-4", "Akola-5",
        // "Solapur-6", "Aurangabad-7", "Ratnagiri-8", "Kolhapur-9", "Chandrapur-10", "Yavatmal-11",
        // "Satara-12", "Jalgaon-13", "Dhule-14", "Parbhani-15", "Nanded-16", "Sangli-17",
        // "Beed-18", "Buldhana-19", "Gadchiroli-20", "Osmanabad-21", "Sindhudurg-22", "Ahmednagar-23",
        // "Jalna-24", "Latur-25", "Raigad-26", "Thane-27", "Palghar-28", "Nandurbar-29",
        // "Hingoli-30", "Gondia-31", "Washim-32", "Wardha-33", "Bhandara-34", "Mumbai Suburban-35"
    };
    int i;
    for (i = 0; i < 36; i++)
    {
        printf("%s\n", cities[i]);
    }
}

void info(){
    int i1;
    printf("Enter the city code where you want to go :\n");
    scanf("%d", i1);
    switch (i1)
    {
        int n;
    case 0:
        printf("\tMumbai\n");
        disinfo();
        scanf("%d", &n);
        if (n == 1)
            printf("info res\n");
        else if (n == 2)
            printf("info hos\n");
        else
            printf("info place\n");
        break;
    case 1:
        printf("\tMumbai\n");
        disinfo();
        scanf("%d", &n);
        if (n == 1)
            printf("info res\n");
        else if (n == 2)
            printf("info hos\n");
        else
            printf("info place\n");
    }
}

void init_graph(Graph *graph)
{
    int i, j;
    for (i = 0; i < MAX_CITIES; i++)
    {
        for (j = 0; j < MAX_CITIES; j++)
        {
            if (i == j)
            {
                graph->distance[i][j] = 0;
            }
            else
            {
                graph->distance[i][j] = 9999;
            }
        }
    }

    graph->distance[0][1] = 240; // Amravati - Nashik
    graph->distance[0][2] = 675; // Amravati - Pune
    graph->distance[0][3] = 900; // Amravati - Mumbai
    graph->distance[0][4] = 440; // Amravati - Akola
    graph->distance[0][5] = 680; // Amravati - Nagpur

    graph->distance[1][0] = 240; // Nashik - Amravati
    graph->distance[1][2] = 210; // Nashik - Pune
    graph->distance[1][3] = 600; // Nashik - Mumbai
    graph->distance[1][4] = 340; // Nashik - Akola
    graph->distance[1][5] = 690; // Nashik - Nagpur

    graph->distance[2][0] = 675; // Pune - Amravati
    graph->distance[2][1] = 210; // Pune - Nashik
    graph->distance[2][3] = 120; // Pune - Mumbai
    graph->distance[2][4] = 290; // Pune - Akola
    graph->distance[2][5] = 710; // Pune - Nagpur

    graph->distance[3][0] = 900; // Mumbai - Amravati
    graph->distance[3][1] = 600; // Mumbai - Nashik
    graph->distance[3][2] = 120; // Mumbai - Pune
    graph->distance[3][4] = 580; // Mumbai - Akola
    graph->distance[3][5] = 680; // Mumbai - Nagpur

    graph->distance[4][0] = 440; // Akola - Amravati
    graph->distance[4][1] = 340; // Akola - Nashik
    graph->distance[4][2] = 290; // Akola - Pune
    graph->distance[4][3] = 580; // Akola - Mumbai
    graph->distance[4][5] = 290; // Akola - Nagpur

    graph->distance[5][0] = 680; // Nagpur - Amravati
    graph->distance[5][1] = 690; // Nagpur - Nashik
    graph->distance[5][2] = 710; // Nagpur - Pune
    graph->distance[5][3] = 680; // Nagpur - Mumbai
    graph->distance[5][4] = 290; // Nagpur - Akola
}

void display(int dist[])
{
    printf("Vertex\t Distance from source\n");
    for (int i = 0; i < MAX_CITIES; i++)
    {
        printf("%d\t%d\n", i, dist[i]);
    }
}
int vertex(int dist[], int vset[])
{
    int min = 9999, index = -1;
    for (int i = 0; i < MAX_CITIES; i++)
    {
        if (vset[i] == 0 && dist[i] < min)
        {
            min = dist[i];
            index = i;
        }
    }
    return index;
}
void dijkstras(int src, Graph *graph, int des)
{
    int dist[MAX_CITIES], vset[MAX_CITIES], prev[MAX_CITIES];
    for (int i = 0; i < MAX_CITIES; i++)
    {
        dist[i] = 9999;
        vset[i] = 0;
        prev[i] = -1;
    }
    dist[src] = 0;
    for (int i = 0; i < MAX_CITIES - 1; i++)
    {
        int u = vertex(dist, vset);
        if (u == -1)
        {
            printf("No path found!!\n");
        }
        vset[u] = 1;
        for (int i = 0; i < MAX_CITIES; i++)
        {
            if (vset[i] != 1 && graph->distance[u][i] && dist[u] != 9999 && dist[u] + graph->distance[u][i] < dist[i])
            {
                dist[i] = dist[u] + graph->distance[u][i];
                prev[i] = u;
            }
        }
    }
    printf("Shortest distance between %d and %d: %d\n", src, des, dist[des]);
    printf("Path: ");
    int path[MAX_CITIES];
    int path_len = 0;
    int curr_city = des;
    while (curr_city != src)
    {
        path[path_len++] = curr_city;
        curr_city = prev[curr_city];
    }
    path[path_len++] = src;
    for (int i = path_len - 1; i >= 0; i--)
    {
        printf("%d", path[i]);
        if (i != 0)
        {
            printf(" -> ");
        }
    }
    printf("\n");
}

void verify();
int menu();
void createaccount();
void login();
void gotoxy(int, int);
FILE *fp;
struct user u, U;
int choice;

char fname[20], lname[20], uname[20], pss[20], C;
struct user
{
    char pass[20];
    char username[20];
    char fname[20];
    char lname[20];
};

int main()
{
    Graph graph1;
    init_graph(&graph1);
    int start, end, departure_time;

    while (1)
    {
        switch (menu())
        {
        case 1:
            createaccount();
            break;

        case 2:
            verify();
            break;

        case 3:
            login();
            goto end;

        end:
            disinfo();
            // printc();
            // info();
            printf("Enter start city (Mumbai-0, Pune-1, Nagpur-2, Nashik-3, Amravati-4, Akola-5): ");
            scanf("%d", &start);
            printf("Enter end city (Mumbai-0, Pune-1, Nagpur-2, Nashik-3, Amravati-4, Akola-5): ");
            scanf("%d", &end);

            dijkstras(start, &graph1, end);
            exit(0);
        }
    }

    return 0;
}

int menu()
{
    int ch;
    printf("\n\n------------------Welcome to TRIP PLANNER---------------------\n");
    printf("\n [1] : Create Account:  \n");
    printf("[2] : Verify Details:  \n");
    printf("[3] : Login:  \n");
    printf("[4] : Exit:  \n");
    printf("   Enter your choice :  ");
    scanf("%d", &ch);
    return ch;
}
void createaccount()
{
    struct user U;
    FILE *fp;
    system("cls");
    gotoxy(57, 3);
    puts("<--<<Create Account>>-->");
    printf("\n\n");
    printf("    Enter First Name: ");
    fflush(stdin);
    gets(U.fname);
    printf("\n");
    printf("    Enter Last Name: ");
    gets(U.lname);
    printf("\n");
    printf("    Enter Username: ");
    scanf("%s", U.username);
    printf("\n");
    printf("    Enter Password: ");
    scanf("%s", U.pass);
    fp = fopen("D:\\CHATBOT\\uname", "wb+");

    if (fp == NULL)
    {
        printf("\nError opened file\n");
        exit(1);
    }
    fwrite(&U, sizeof(struct user), 1, fp);
    fclose(fp);
    system("cls");
    gotoxy(55, 20);
    printf(" Account Created Successfully.");
    gotoxy(75, 25);
    printf("Press any key to continue...");
    getch();
    system("cls");
}
void verify()
{
    FILE *fp;
    struct user u;
    system("cls");
    gotoxy(52, 3);
    printf("    Your Details Are..\n\n");
    fp = fopen("D:\\CHATBOT\\uname", "rb+");
    if (fp == NULL)
    {
        printf("\"File not found\"");
    }
    while (fread(&u, sizeof(struct user), 1, fp))
    {
        printf("\n    Name: %s %s \n", u.fname, u.lname);
        printf("\n    Username: %s\n\n    ", u.username);
    }
    fclose(fp);
    gotoxy(75, 16);
    printf("Press any key to continue...");
    getch();
    system("cls");
}
void login()
{
    char uname[20], pss[20];
    FILE *fp;
    struct user u;
    system("cls");
    gotoxy(53, 3);
    printf("<--<<LOGIN TO YOUR ACCOUNT>>->\n\n");
    printf(" Enter Username: ");
    scanf("%s", uname);
    printf("\n");
    printf(" Enter Password: ");
    scanf("%s", pss);
    fp = fopen("D:\\CHATBOT\\uname", "rb+");
    if (fp == NULL)
    {
        printf("\"File not found\"");
    }
    while (fread(&u, sizeof(struct user), 1, fp))
    {
        if (strcmp(uname, u.username) == 0 && strcmp(pss, u.pass) == 0)
        {
            printf(" \n Username And Password is Correct.\n");
            printf(" Press any key to continue...");
            getch();
            gotoxy(57, 12);
            printf(" Welcome %s %s ", u.fname, u.lname);
            getch();
        }
        else
        {
            printf("\n Username And Password is Incorrect.\n\n");
            exit(0);
            printf("\n Press any key to continue...");
            getch();
        }
    }
    fclose(fp);
    system("cls"); // stdlib.h
}
void gotoxy(int x, int y)
{
    COORD c; // windows.h ---it hold screen coordinates..
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c); // windows.h
}
// #include<graphics.h>
//  #include <stdio.h>
// gotoxy --- conio.h
