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

/* 경기 진행                */
void init_playing(TEAM *, int);
char playing(TEAM *, int , int);
void clear(int *, int *);
void score(int *, int, int);

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
                memset(team, 0x00, sizeof(team));
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

/****************************************/
/* 팀정보 삽입                           */
/****************************************/ 
void insert_team(TEAM * team, int len)
{
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
        for(int j=0; j < 9; j++)
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

/****************************************/
/* 팀정보 출                            */
/***************************************/ 
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
    char result;
    
    int strike = 0, ball = 0, out = 0, hit = 0;
    int c1 = 0, c2 = 1; //경기회수, 팀번호(0,1), 
    int ply = 0;        //선수번호
    int scr[2] = {0, }; //점수

    printf("%.*s VS %.*s의 시합을 시작합니다.\n", strlen(team[0].teamName), team[0].teamName, strlen(team[1].teamName), team[1].teamName);
    
    while(1)
    {
        //6회 종료후 게임 종료.
        if(out==3 || c1 == 0)
        {
             c1++; //X회
            //c2 == 0 : 초(1팀), c2 == 1: 말(2팀)
            if(c1 == 7)
            {
                printf("경기 종료\n");
                break;
            }
            if(c2 == 1){
                c2 = 0;
                printf("%d회 초 %.*s 공격\n", c1, strlen(team[c2].teamName), team[c2].teamName);
            } else {
                c2 = 1;
                printf("%d회 말 %.*s 공격\n", c1, strlen(team[c2].teamName), team[c2].teamName);
            }
            clear(&strike, &ball); clear(&hit, &ply);
            out = 0;
        }

        result = playing(team, c2, ply);
        printf("%d번 %.*s\n", team[c2].data[ply].num, strlen(team[c2].data[ply].name), team[c2].data[ply].name);

        switch(result)
        {
            case 's':
                strike++;
                printf("스트라이크!\n");
                if(strike == 3)
                {
                    out++;
                    ply++;
                    clear(&strike, &ball);
                }
                break;
            case 'b':
                ball++;
                printf("볼!\n");
                if(ball == 4)
                {
                    hit++;
                    ply++;
                    clear(&strike, &ball);
                }
                break;
            case 'o':
                printf("아웃!\n");
                out++;
                ply++;
                clear(&strike, &ball);
                break;
            case 'h':
                printf("안타!\n");
                hit++;
                ply++;
                clear(&strike, &ball);
                break;
        }

        printf("%dS %dB %dO %dH\n\n", strike, ball, out, hit);
        if(ply > 8)
            ply = 0;

        score(scr, c2, hit);
    }

     printf("%.*s VS %.*s\n", strlen(team[0].teamName), team[0].teamName, strlen(team[1].teamName), team[1].teamName);
     printf("%d : %d\n Thank you!\n", scr[0], scr[1]);
}

/****************************************************/
/*0: 스트라이크, 1:볼, 2: 아웃, 3: 안타 확률계산
-안타: h, 0.1 < h < 0.5
-스트라이크: (1 - h) / 2 - 0.05
-볼: (1 - h) / 2 - 0.05
-아웃: 0.1
*input  : struct TEAM, 팀 번호, n번째 타자
*output : o(아웃), h(안타), s(스트라이크), b(볼) 중 1 */
/****************************************************/ 
char playing(TEAM * team, int tnum, int pnum)
{
    double hit = team[tnum].data[pnum].hit_rate;
    double stk = (1-hit)/2 - 0.05;
    double ball = stk;
    double out = 0.1;
    double cal = 0.0, dtemp = 0.0;
    char ctemp;
    //맵핑을 위해 만들었으나 개선필요.
    double value[4] = {out, hit, stk, ball};
    char key[4] = {'o', 'h', 's', 'b'};
    int i, j;

    double r = rand() / (double)32767; //0~1까지 실수형 출력
    //오름차순정렬
    for (i = 0; i < 4; i++)
    {
		for (j = 0; j < 3; j++)
		{
        	if (value[j] > value[j + 1]) 
            {
				dtemp = value[j];
                ctemp = key[j];
				value[j] = value[j + 1];
                key[j] = key[j + 1];
				value[j + 1] = dtemp;
                key[j + 1] = ctemp;
			}
        }
    }

    for(i=0; i<4; i++)
    {
        cal += value[i];
        if(r <= cal)
            return key[3-i];
    }


}

/****************************************/
/* 들어오는 매개변수를 0으로 초기화       */
/****************************************/ 
void clear(int * num1, int * num2)
{
    *num1 = 0;
    *num2 = 0;
}

/****************************************/
/* 점수 관리                             */
/* input : 점수 배열, 팀 넘버, 안타개수
/****************************************/ 
void score(int * scr, int tnum, int hit)
{
    if(hit >= 4)
        scr[tnum]++;
}

