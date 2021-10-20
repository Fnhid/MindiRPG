// MindiRPG v1.1
// How to compile :
// Normal version : gcc -o MindiRPG MindiRPG.c
// Leakable version : gcc -o MindiRPG MindiRPG.c -no-pie -z relro -fno-stack-protector  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int pattern;
struct Mob gremlin;
struct Mob cobolt;
struct Mob goblin;
struct Mob orc;
struct Mob giant;
struct Mob dragon;
struct Character {
    int hp;
    int mp;
    int level;
    int exp;
    int attack;
    int defense;
    int canDragon;
    char name[20];
}player;

struct Mob {
    char name[20];
    int hp;
    int attack;
};
void dragonFight();
void exkali();
void heal();
int levelTest(int nowLevel);
int attack(int mobHp);
int defense(int playerHp, int mobAttack);
void characterDefault();
void characterRefill();
void mobDefault();
void stat();
void fightStat(int MobHP);
void menu();
int playerAttack(int MobHP);
int mobAttack(int mobAttack);
void hunt();
void gameOver();


int main(){
    int choose;
    char tmpchar[20];
    printf("MinDiRPG v1.1에 오신 것을 환영합니다!\n");
    printf("사냥을 통해 강해져서 용을 잡으세요!\n");
    printf("용사의 이름은? [최대 20자] > ");
    scanf("%s", tmpchar);
    strcpy(player.name, tmpchar);
    if(!strcasecmp(player.name, "MinDi")){
        printf("사망했습니다..\n");
        exit(1);
    }
    printf("안녕하세요! %s!\n", player.name);
    characterDefault();
    mobDefault();
    while (1){
        menu();
        scanf("%d", &choose);
        switch (choose){ 
            case 1:
                hunt();
                break;
            case 2:
                heal();
                break;
            case 3:
                exkali();
                break;    
            case 4:
                dragonFight();
                break;
            case 5:
                stat();
                break;
            case 6:
                printf("MinDiRPG를 떠납니다!\n");
                exit(0);
                break;
            default:
                printf("올바르지 않은 옵션입니다!\n");
            
        }
    }
    
    
}
void dragonFight(){
    char key[10] = {'M', 'i', 'n', 'd', 'i', 'm', 'I', 'N', 'D', 'I'};
    pattern = 0;
    char hey;
    printf("Dragon과 전투를 시작합니다!");
                while(1){
                    if(pattern >= 10){
                        pattern = 0;
                    }
                    sleep(1);
                    fightStat(dragon.hp);
                    hey = 0;
                    printf("%c를 입력해 공격하세요! > \n", key[pattern]);
                    
                    hey = getchar();
                    
                    if(hey){
                        if(hey == key[pattern])
                            dragon.hp -= playerAttack(dragon.hp);
                        else{
                            printf("올바른 입력이 아닙니다! 당신의 공격은 빗나갔습니다!\n");
                            printf("적이 공격합니다!");
                            player.hp -= mobAttack(dragon.attack);
                        }
                    }
                        
                    sleep(1);
                    pattern++;
                    if(dragon.hp <= 0){
                        printf("당신은 마침내 Dragon를 쓰러뜨렸습니다!\n");
                        printf("Mindi대륙의 사람들이 %s를 기억할 것입니다!\n", player.name);
                        gameOver();
                        exit(0);
                        break;
                    }
                    if(player.hp <= 0){
                        printf("당신은 죽었습니다..\n");
                        printf("Mindi마을의 주민이 %s을 기억할 것입니다.\n", player.name);
                        exit(1);
                    }
                    
                }
                
            
}

void exkali(){
    if(player.level == 6){
        printf("당신은 사기템 엑스칼리버를 뽑았습니다!\n");
        printf("당신의 공격력이 상승합니다!\n");
        player.attack = 999999;
    }
    else{
        printf("당신은 엑스칼리버를 뽑기에 너무 약했습니다..\n");
        printf("사망했습니다..\nMindi마을의 주민들이 %s를 기억할 것입니다..", player.name);
        exit(1);
    }
}

void heal(){
    printf("여관에서 휴식을 취합니다!\n");
    sleep(2);
    printf("당신의 모든 체력이 회복됩니다!\n");
    characterRefill();
}
int levelTest(int nowLevel){
    if(player.level == nowLevel){
        return 0;
    }
    else{
        printf("당신은 이 몬스터와 전투할 수준이 아닙니다..\n");
        return 1;
    }
}
int attack(int mobHp){
    return mobHp - player.attack;
}

int defense(int playerHp, int mobAttack){
    return playerHp - mobAttack;
}
void characterDefault(){
    player.hp = 100;
    player.level = 1;
    player.attack = 10;
    player.defense = 10;
    player.canDragon = 0;
}
void characterRefill(){
    player.hp = 100 + 50 * player.level;
    player.attack = 10 + 5 * player.level;
    player.defense = 10 + 5 * player.level;
}
void mobDefault(){
    
    gremlin.hp = 100;
    gremlin.attack = 15;
    cobolt.hp = 150;
    cobolt.attack = 25; 
    goblin.hp = 200;
    goblin.attack = 35;
    orc.hp = 250;
    orc.attack = 45;
    giant.hp = 350;
    giant.attack = 55;
    dragon.hp = 1000000;
    dragon.attack = 70;
}

void stat(){
    printf("====================\n");
    printf("당신의 LEVEL : %d\n", player.level);
    printf("당신의 HP : %d\n", player.hp);
    printf("당신의 공격력 : %d\n", player.attack);
    printf("당신의 방어력 : %d\n", player.defense);
    printf("====================\n");
}
void fightStat(int MobHP){
    printf("====================\n");
    printf("당신의 HP : %d\n", player.hp);
    printf("적의 HP : %d\n", MobHP);
    printf("====================\n");
}

void menu(){
    printf("====================\n");
    printf("1) 사냥\n");
    printf("2) 여관으로 가기\n");
    printf("3) 엑스칼리버 뽑기\n");
    printf("4) 용잡기\n");
    printf("5) 내 스탯\n");
    printf("6) MinDiRPG 끝내기\n");
    printf("====================\n");
}

int playerAttack(int MobHP){
    printf("당신의 공격은 적에게 %d의 데미지를 입혔습니다!\n", player.attack);
    return player.attack;
}

int mobAttack(int mobAttack){
    unsigned int ret;
    ret = mobAttack - player.defense;
    printf("적이 %d의 데미지의 공격을 시도합니다!\n", mobAttack);
    printf("단단한 방패가 %d의 데미지를 막아냅니다!\n", player.defense);
    printf("당신은 %d의 데미지를 입었습니다!\n", mobAttack - player.defense);
    return ret;
}

void hunt(){
    char hey;
    switch (player.level){
        case 1:{
            if(!levelTest(player.level)){
                char key[10] = {'M', 'i', 'n', 'd', 'i', 'm', 'I', 'N', 'D', 'I'};
                pattern = 0;
                char hey;
                printf("Gremlin과 전투를 시작합니다!\n");
                while(1){
                    if(pattern >= 10){
                        pattern = 0;
                    }
                    fightStat(gremlin.hp);
                    hey = 0;
                    printf("%c를 입력해 공격하세요! > \n", key[pattern]);
                    while(!hey){
                        hey = getchar();
                    }
                    if(hey){
                    if(hey == key[pattern])
                        gremlin.hp -= playerAttack(gremlin.hp);
                    else{
                        printf("올바른 입력이 아닙니다! 당신의 공격은 빗나갔습니다!\n");
                        printf("적이 공격합니다!");
                        player.hp -= mobAttack(gremlin.attack);
                    }
                    }
                    pattern++;
                    if(gremlin.hp <= 0){
                        printf("Gremlin를 쓰러뜨렸습니다!\n");
                        printf("레벨 업! level 1 -> level 2\n");
                        player.level += 1;
                        break;
                    }
                    if(player.hp <= 0){
                        printf("당신은 죽었습니다..\n");
                        printf("Mindi마을의 주민이 %s을 기억할 것입니다.\n", player.name);
                        exit(1);
                    }
                }
            }else{
                printf("알맞은 레벨이 아닙니다..");
            }
            break;
            
        }
        case 2:{
            if(!levelTest(player.level)){
                char key[10] = {'M', 'i', 'n', 'd', 'i', 'm', 'I', 'N', 'D', 'I'};
                pattern = 0;
                char hey;
                printf("Cobolt과 전투를 시작합니다!\n");
                while(1){
                    if(pattern >= 10){
                        pattern = 0;
                    }
                    fightStat(cobolt.hp);
                    hey = 0;
                    printf("%c를 입력해 공격하세요! > \n", key[pattern]);
                    while(!hey){
                        hey = getchar();
                    }
                    if(hey){
                    if(hey == key[pattern])
                        cobolt.hp -= playerAttack(cobolt.hp);
                    else{
                        printf("올바른 입력이 아닙니다! 당신의 공격은 빗나갔습니다!\n");
                        printf("적이 공격합니다!");
                        player.hp -= mobAttack(cobolt.attack);
                    }}
                    pattern++;
                    if(cobolt.hp <= 0){
                        printf("Cobolt를 쓰러뜨렸습니다!\n");
                        printf("레벨 업! level 2 -> level 3\n");
                        player.level += 1;
                        break;
                    }
                    if(player.hp <= 0){
                        printf("당신은 죽었습니다..\n");
                        printf("Mindi마을의 주민이 %s을 기억할 것입니다.\n", player.name);
                        exit(1);
                        
                    }
                }
                
            }else{
                printf("알맞은 레벨이 아닙니다..");
            }
            break;

        }
        case 3:{
            if(!levelTest(player.level)){
                char key[10] = {'M', 'i', 'n', 'd', 'i', 'm', 'I', 'N', 'D', 'I'};
                pattern = 0;
                char hey;
                printf("Goblin과 전투를 시작합니다!\n");
                while(1){
                    if(pattern >= 10){
                        pattern = 0;
                    }
                    fightStat(goblin.hp);
                    hey = 0;
                    printf("%c를 입력해 공격하세요! > \n", key[pattern]);
                    while(!hey){
                        hey = getchar();
                    }
                    if(hey){
                    if(hey == key[pattern])
                        goblin.hp -= playerAttack(goblin.hp);
                    else{
                        printf("올바른 입력이 아닙니다! 당신의 공격은 빗나갔습니다!\n");
                        printf("적이 공격합니다!");
                        player.hp -= mobAttack(goblin.attack);
                    }}
                    pattern++;

                    if(goblin.hp <= 0){
                        printf("Goblin를 쓰러뜨렸습니다!\n");
                        printf("레벨 업! level 3 -> level 4\n");
                        player.level += 1;
                        break;
                    }
                    if(player.hp <= 0){
                        printf("당신은 죽었습니다..\n");
                        printf("Mindi마을의 주민이 %s을 기억할 것입니다.\n", player.name);
                        exit(1);
                    }
                }
                
            }else{
                printf("알맞은 레벨이 아닙니다..");
            }
            break;

        }
        case 4:{   
            if(!levelTest(player.level)){
                char key[10] = {'M', 'i', 'n', 'd', 'i', 'm', 'I', 'N', 'D', 'I'};
                pattern = 0;
                char hey;
                printf("Orc과 전투를 시작합니다!\n");
                while(1){
                    if(pattern >= 10){
                        pattern = 0;
                    }
                    fightStat(orc.hp);
                    hey = 0;
                    printf("%c를 입력해 공격하세요! > \n", key[pattern]);
                    while(!hey){
                        hey = getchar();
                    }
                    if(hey){
                    if(hey == key[pattern])
                        orc.hp -= playerAttack(orc.hp);
                    else{
                        printf("올바른 입력이 아닙니다! 당신의 공격은 빗나갔습니다!\n");
                        printf("적이 공격합니다!");
                        player.hp -= mobAttack(orc.attack);
                    }}
                    pattern++;

                    if(orc.hp <= 0){
                        printf("Orc를 쓰러뜨렸습니다!\n");
                        printf("레벨 업! level 4 -> level 5\n");
                        player.level += 1;
                        break;
                    }
                    if(player.hp <= 0){
                        printf("당신은 죽었습니다..\n");
                        printf("Mindi마을의 주민이 %s을 기억할 것입니다.\n", player.name);
                        exit(1);
                    }
                }
                
            }
            else{
                printf("알맞은 레벨이 아닙니다..");
            }
            break;

        }
        case 5:{
            if(!levelTest(player.level)){
                char key[10] = {'M', 'i', 'n', 'd', 'i', 'm', 'I', 'N', 'D', 'I'};
                pattern = 0;
                char hey;
                printf("Giant과 전투를 시작합니다!\n");
                while(1){
                    if(pattern >= 10){
                        pattern = 0;
                    }
                    fightStat(giant.hp);
                    hey = 0;
                    printf("%c를 입력해 공격하세요! > \n", key[pattern]);
                    while(!hey){
                        hey = getchar();
                    }if(hey){
                    if(hey == key[pattern])
                        giant.hp -= playerAttack(giant.hp);
                    else{
                        printf("올바른 입력이 아닙니다! 당신의 공격은 빗나갔습니다!\n");
                        printf("적이 공격합니다!");
                        player.hp -= mobAttack(giant.attack);
                    }}
                    pattern++;

                    if(giant.hp <= 0){
                        printf("Giant를 쓰러뜨렸습니다!\n");
                        printf("레벨 업! level 5 -> level 6\n");
                        printf("엑스칼리버를 뽑을 수 있습니다!\n");
                        player.level += 1;
                        break;
                    }
                    if(player.hp <= 0){
                        printf("당신은 죽었습니다..\n");
                        printf("Mindi마을의 주민이 %s을 기억할 것입니다.\n", player.name);
                        exit(1);
                    }
                }
            }
            else{
                printf("알맞은 레벨이 아닙니다..");
            }
            break;
        }
        default:{
            printf("더 이상 사냥할 몬스터가 없습니다..\n");
            printf("용 잡으러 가세요\n");
            break;
        }
    }
}

void gameOver(){
    printf("==CREDIT==\n");
    sleep(3);
    printf("Story by Fnhid\n");
    sleep(3);
    printf("Programmed by Fnhid\n");
    sleep(3);
    printf("Designed by Fnhid\n");
    sleep(3);
    printf("Copyrightⓒ2021 Fnhid. All rights reserved.\n");
    printf("You can find this source code in : https://github.com/Fnhid/MindiRPG\n");
    sleep(1);
    printf("\n\n\n\n\n\n\n");
    printf("===========\n");
    printf("=Game Over=\n");
    printf("===========\n");
}