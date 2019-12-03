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

void init_playing(TEAM *, int);
int playing(TEAM *, int tnum);
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
                init_playing(team, 2);
                break;
            case 4:
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
    printf("3. 시합 시작\n");
    printf("4. 종료\n");

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
void init_playing(TEAM * team, int len){
    int result;
    
    int strike = 0, ball = 0, out = 0, hit = 0;
    int c1 = 1, c2 = 0, flag = 0, s1, s2;

    printf("%.*s VS %.*s의 시합을 시작합니다.\n", strlen(team[0].teamName), team[0].teamName, strlen(team[1].teamName), team[1].teamName);
    
    while(1)
    {
        //6회 종료후 7회일때 동점일 경우 무승부처리
        if(c1 == 7 && s1 == s2)
        {
            printf("경기 종료\n");
            break;
        }

        //c2 == 0 : 초, c2 == 1: 말
        if(c2 == 0){
            printf("%d초 %.*s 공격", c1, strlen(team[c2].teamName), team[c2].teamName);
        } else {
            printf("%d말 %.*s 공격", c1, strlen(team[c2].teamName), team[c2].teamName);
            c1++; //X회
        }

        result = playing(team, c2);

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
        
        c2 = ~c2;
    }
}

/****************************************/
/* 0: 스트라이크, 1:볼, 2: 아웃, 3: 안타  */
/****************************************/ 
int playing(TEAM * team, int tnum)
{
    
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

