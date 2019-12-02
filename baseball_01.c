#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

/* 팀원 상세정보 */
typedef struct{
    char name[64];
    int hit_rate;
}TEAM_DATA;

/* 팀 구조체    */
typedef struct{
    char teamName[128];
    TEAM_DATA data[9];
}TEAM;

/* 데이터 입력, 출력 */
int init_menu();
void insert_team(TEAM * []);
void print_team(TEAM * []);
/********************/

void init_playing();
void start_playing();
int playing();
void clear(int *, int *);
void next_alarm(int);

void main(){
    int menu_result;
    srand(time(NULL));

    TEAM * team[2];

    //memset(team, 0x00, sizeof(TEAM));
    printf("!!!");
    menu_result = init_menu();

    switch(menu_result)
    {
        case 1:
            insert_team(team);
            break;
        case 2:
            print_team(team);
            break;
    }

    //init_playing();

}

/****************************************/
/* 메뉴선택                              */
/****************************************/ 
int init_menu(){
    int sel;
    printf("신나는 야구시합\n");
    printf("1. 데이터 입력\n");
    printf("2. 데이터 출력\n");

    printf("메뉴선택 (1 - 2)");
    scanf("%d", &sel);
    return sel;
}

void insert_team(TEAM * team[])
{
    int len = sizeof(&team);
    printf("TEAM len : %d\n", len);
    for(int i=0; i<len; i++)
    {
        break;
    }
}

void print_team(TEAM * team[])
{

}

/****************************************/
/* 경기진행                              */
/****************************************/ 
void init_playing(){
    int result;
    
    int strike = 0;
    int ball = 0;
    int out = 0;
    int hit = 0;

    int flag = 0;

    start_playing();
    while(1)
    {
        result = playing();

        switch(result)
        {
            case 0:
                strike++;
                printf("스트라이크!\n");
                if(strike == 3)
                {
                    out++;
                    clear(&strike, &ball);
                }
                break;
            case 1:
                ball++;
                printf("볼!\n");
                if(ball == 4)
                {
                    hit++;
                    clear(&strike, &ball);
                }
                break;
            case 2:
                out++;
                clear(&strike, &ball);
                if(out == 3){
                    printf("아웃!\n");
                    flag = 1;
                }
                break;
            case 3:
                hit++;
                clear(&strike, &ball);
                break;
        }
        
        if(out != 3)
            next_alarm(result);
        
        printf("%dS %dB %dO\n\n", strike, ball, out);
    
        if(flag == 1)
        {
            printf("최종 안타수 : %d\fnGAME OVER\n", hit);
            break;
        }
        
    }
    system("pause");
}

/****************************************/
/* 초기화                               */
/****************************************/ 
void start_playing(){
    printf("신나는 야구시합!\n");
    printf("첫 번째 타자가 타석에 입장했습니다.\n\n");
}

/****************************************/
/* 0: 스트라이크, 1:볼, 2: 아웃, 3: 안타  */
/****************************************/ 
int playing()
{
    int random;
    random = rand() % 4; 

    return random;
}

void clear(int * strike, int * ball)
{
    *strike = 0;
    *ball = 0;
}

void next_alarm(int state)
{
    if(state == 2)
    {
        printf("아웃! 다음 타자가 타석에 입장했습니다.\n");
    }
    else if(state == 3)
    {
        printf("안타! 다음 타자가 타석에 입장했습니다.\n");
    }
}

