//draw-input-move-eat-death?-sleep--draw
#include<stdio.h>
#include<conio.h>
#define HEIGHT 30
#define WIDTH 25
#include<stdlib.h>
#include<time.h>
#include<windows.h>

int foodx,foody;
int len=3;
int sankex[100],sankey[100];
int dir = 2;
int score=0;
int speed = 150;
int quickSpeed = 40;   
int isPressA = 0;      

void draw()
{
    system("cls");
    for(int i=0;i<WIDTH;i++){
        printf("#");
    }
    printf("\n");

    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            if(j == 0 || j == WIDTH - 1)
            {
                printf("#");
            }
            else if(i == foody && j == foodx)
            {
                printf("&");
            }
            else{
                int sanke=0;
                for(int k=0;k<len;k++){
                    if(sankex[k]==j&&sankey[k]==i){
                        printf("O");
                        sanke=1;
                        break;
                    }
                }
                if(sanke!=1)
                    printf(" ");
            }
        }
        printf("\n");
    }
    for(int i=0;i<WIDTH;i++){
        printf("#");
    }
    printf("\n");
    printf("Your score is:%d\n",score);
    printf("Hold A to speed up\n");
}
void move()
{
    for(int k = len-1; k>0; k--)
    {
        sankex[k] = sankex[k-1];
        sankey[k] = sankey[k-1];
    }

    switch(dir)
    {
        case 1: sankey[0]--; break;
        case 2: sankex[0]++; break;
        case 3: sankey[0]++; break;
        case 4: sankex[0]--; break;
    }
}
void input(){
    isPressA = 0;   
    if (_kbhit()){
        int ch=_getch();
        if(ch==224){
            ch=_getch();
            switch(ch)
            {
                case 72: if(dir != 3) dir = 1; break;
                case 77: if(dir != 4) dir = 2; break;
                case 80: if(dir != 1) dir = 3; break;
                case 75: if(dir != 2) dir = 4; break;
            } 
        }
        else if(ch == 'a' || ch == 'A'){
            isPressA = 1;
        }
        else if(ch == 'd' || ch == 'D'){
            if(speed < 300) speed += 30;
        }
    }
}
void eat(){
    if(sankex[0]==foodx&&sankey[0]==foody){
        len++;
        score++;
        foodx = rand() % (WIDTH - 2) + 1;
        foody = rand() % (HEIGHT - 2) + 1;
    }
}
int death(){
    if(sankex[0] <= 0 || sankex[0] >= WIDTH-1 || sankey[0] <=0 || sankey[0] >= HEIGHT-1)
    {
        return 1;
    }
    for(int k=1;k<len;k++)
    {
        if(sankex[0]==sankex[k] && sankey[0]==sankey[k])
        {
            return 1;
        }
    }
    return 0;
}
int main(){
    srand(time(NULL));
    foodx = rand() % (WIDTH - 2) + 1;
    foody = rand() % (HEIGHT - 2) + 1;

    sankex[0] = WIDTH/2;
    sankey[0] = HEIGHT/2;
    sankex[1] = WIDTH/2 - 1;
    sankey[1] = HEIGHT/2;
    sankex[2] = WIDTH/2 - 2;
    sankey[2] = HEIGHT/2;


    while(1)
    {
        draw();
        input();
        move();
        eat();
        if(death())
        {
            system("cls");
            printf("====GAMEOVER!====\n");
            printf("END SCORE:%d\n",score);
            break;
        }
        if(isPressA){
            Sleep(quickSpeed);
        }else{
            Sleep(speed);
        }
    }
    return 0;
}
