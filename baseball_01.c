#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void init();
int playing();
void clear(int *, int *);
void next_alarm(int);

void main(){
    int result;
    
    int strike = 0;
    int ball = 0;
    int out = 0;
    int hit = 0;

    int flag = 0;

    init();
    srand(time(NULL));

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
            printf("최종 안타수 : %d\nGAME OVER\n", hit);
            break;
        }
        
    }


}

/****************************************/
/* 초기화                               */
/****************************************/ 
void init(){
    printf("신나는 야구게임!\n");
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

