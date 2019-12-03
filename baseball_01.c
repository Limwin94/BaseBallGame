#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

/* 팀원 상세정보 */
typedef struct{
    int num;
    char name[64];
    double hit_rate;
}TEAM_DATA;

/* 팀 구조체    */
typedef struct{
    char teamName[128];
    TEAM_DATA data[9];
}TEAM;

/* 데이터 입력, 출력 */
int init_menu();
void insert_team(TEAM *, int);
void print_team(TEAM *, int);
/********************/

void init_playing();
void start_playing();
int playing();
void clear(int *, int *);
void next_alarm(int);

void main(){
    int menu_result;
    srand(time(NULL));

    //2단계, 현재는 2팀뿐이므로 2개만, 나중에 malloc으로 교체해야 할지도..
    TEAM team[2];

    while(1)
    {
    menu_result = init_menu();

        switch(menu_result)
        {
            case 1:
                insert_team(team, 2);
                break;
            case 2:
                print_team(team, 2);
                break;
            case 3:
                exit(0);
        }
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
    printf("3. 종료\n");

    printf("메뉴선택 (1 - 2)");
    scanf("%d", &sel);
    printf("\n");
    return sel;
}

void insert_team(TEAM * team, int len)
{
    memset(team, 0x00, sizeof(TEAM));
    int data_size = sizeof(team[0].data)/sizeof(TEAM_DATA);
    char t_name[128];
    char name[64];
    char hit_rate[5+1];
    int k=0;

    for(int i=0; i<len; i++)
    {
        memset(t_name, 0x00, sizeof(t_name));
        getchar();
        printf("%d팀의 이름을 입력하세요> ", i+1);
        fgets(t_name, sizeof(t_name), stdin);
        //scanf(" %s", t_name);
        t_name[strlen(t_name)-1] = '\0';
        memcpy(team[i].teamName, t_name, strlen(t_name));
        for(int j=0; j < 3; j++)
        {
            memset(name, 0x00, sizeof(name));
            memset(hit_rate, 0x00, sizeof(hit_rate));
            printf("%d번 타자 정보 입력>\n", j+1);
            team[i].data[j].num = j+1;
            
            printf("1) 이름 : ");
            scanf(" %s", name);
            memcpy(team[i].data[j].name, name, strlen(name));

            printf("2) 타율 : ");
            scanf(" %s", hit_rate);
            if(atof(hit_rate) < 0.1 || atof(hit_rate) > 0.5 || strlen(hit_rate) < 5)
            {
                printf("타율은 0.1~0.5 사이이며 소수 세째 자리까지 입력하세요\n");
                j--;
                continue;
            } else {
                team[i].data[j].hit_rate = atof(hit_rate);
            }
        }
    }
    printf("\n팀 데이터 입력이 완료되었습니다.\n");
}

void print_team(TEAM * team, int len)
{
    int data_size = sizeof(team[0].data)/sizeof(TEAM_DATA);
    for(int i=0; i<len; i++)
    {
        printf("\n%.*s 팀 정보\n", strlen(team[i].teamName), team[i].teamName);
        for(int j=0; j<data_size; j++)
        {
            printf("%d번 %s, %.3f\n", team[i].data[j].num, team[i].data[j].name, team[i].data[j].hit_rate);
        }
    }
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

/****************************************/
/* 스트라이크, 볼 갯수 초기화             */
/****************************************/ 
void clear(int * strike, int * ball)
{
    *strike = 0;
    *ball = 0;
}

/****************************************/
/* 타자 입장 알림                        */
/****************************************/ 
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

