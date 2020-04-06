#include<iostream>
#include<string>
#include<stdio.h>
#include<iomanip>
using namespace std;

const int inf = 999999999;
const int MAX = 10;

enum{red = 0, blue = 1};
enum{dragon = 0, ninja = 1, iceman = 2, lion = 3, wolf = 4}; // 给战士编号
enum{sword = 0, bomb = 1, arrow = 2};

const char* warrior_names[5] = {"dragon", "ninja", "iceman", "lion", "wolf"}; 
const char* weapon_names[3] = {"sword", "bomb", "arrow"};
const char* side_names[2] = {"red", "blue"};
// 双方创建顺序
const int red_seq[5] = {iceman, lion, wolf, ninja, dragon}; 
const int blue_seq[5] = {lion, dragon, ninja, iceman, wolf};

// 全局变量
int red_M = 0, blue_M = 0, M = 0, N = 0, R = 0, K = 0, T = 0;
int red_M_temp = 0, blue_M_temp = 0;
int hour = 0, minute = 0;
int warrior_strengths[5], warrior_dams[5];
bool war_over = false;
int red_cur_born = 0, blue_cur_born = 0;
int red_num = 0, blue_num = 0;
int red_headquarter_enemy = 0, blue_headquarter_enemy = 0;

class Warrior;

struct info // 记录城市信息,城市指针管理武士， NULL代表没有武士
{
    Warrior * pred = NULL; // 存放当前位置武士信息
    Warrior * pblue = NULL;
    Warrior * temp_red = NULL; // temp 指针存放刚刚移动到该地点的武士
    Warrior * temp_blue = NULL;
	bool red_flag = false; // 旗帜
	bool blue_flag = false;
	int red_flag_cnt = 0;
	int blue_flag_cnt = 0;
	int element = 0; // 城市储存生命元
}map[25];

// 武器类
class Weapon
{
    public:
    int weapon_code = 0;
    int left_num = 0;
    int weapon_dam = 0;

    Weapon() {}
    Weapon(int weapon_code_, int user_dam): weapon_code(weapon_code_) // 武器伤害取决于使用者
    {
        switch(weapon_code)
        {
            case sword: left_num = inf; weapon_dam = user_dam * 2 / 10; break;
            case bomb: left_num = 1; weapon_dam = inf; break;
            case arrow: left_num = 3; weapon_dam = R; break;
        }
    }
    Weapon & operator=(const Weapon & wep)
	{
		weapon_code = wep.weapon_code;
		weapon_dam = wep.weapon_dam;
		left_num = wep.left_num;
        return *this;
	}
};

class Warrior // 基类
{
    public: 
    string name;
    int side;
    int strength;
    int damage;
    int num;
    bool dead = false;
    Weapon weapons[3]; // 最多三件武器
    int position; // 所在城市位置

    Warrior(string name_, int side_, int num_, int strength_, int damage_): name(name_), side(side_), num(num_), strength(strength_), damage(damage_)
    {
        // 武士出生位置
        if(side == red)
            position = 0;
        else
            position = N + 1;
    }

    virtual void hurted(int dam, Warrior * attacker, bool is_arrow = false)
    {
        strength -= dam;
        if(strength <= 0){
			strength = 0;
            dead = true;
			if(!is_arrow) // 被arrow射死不输出
				printf("%03d:%02d %s %s %d was killed in city %d\n", hour, minute, side_names[side], name.c_str(), num, position);
		}
    }

	virtual void fight_back(Warrior * enemy)
	{
		if(dead) return;
		int dam = damage / 2;
		if(weapons[sword].weapon_dam > 0){
			dam += weapons[sword].weapon_dam;
			weapons[sword].weapon_dam = weapons[sword].weapon_dam * 8 / 10;
		}
		printf("%03d:%02d %s %s %d fought back against %s %s %d in city %d\n", hour, minute, side_names[side], name.c_str(), num, side_names[enemy->side], enemy->name.c_str(), enemy->num, position);
		enemy->hurted(dam, this);
	}
    
    virtual void attack(Warrior * enemy)
    {
        if(enemy->dead || dead) return; // 敌人已经被arrow射死
		int dam = damage;
		if(weapons[sword].weapon_dam > 0){
			dam += weapons[sword].weapon_dam;
			weapons[sword].weapon_dam = weapons[sword].weapon_dam * 8 / 10;
		}
		printf("%03d:%02d %s %s %d attacked %s %s %d in city %d with %d elements and force %d\n", hour, minute, side_names[side], name.c_str(), num, side_names[enemy->side], enemy->name.c_str(), enemy->num, position, strength, damage);
		enemy->hurted(dam, this);
		enemy->fight_back(this);
    }


    void declare_weapon() // 武士声明自己当前武器状态
    {
		printf("%03d:%02d %s %s %d has ", hour, minute, side_names[side], name.c_str(), num);
		bool has_arrow = false, has_bomb = false, has_sword = false;
		if(weapons[arrow].left_num > 0){
			printf("arrow(%d)", weapons[arrow].left_num);
			has_arrow = true;
		}
		if(weapons[bomb].left_num > 0){
			if(has_arrow) printf(",");
			printf("bomb");
			has_bomb = true;
		}
		if(weapons[sword].weapon_dam > 0){
			if(has_arrow || has_bomb) printf(",");
			printf("sword(%d)", weapons[sword].weapon_dam);
			has_sword = true;
		}
		if(!has_arrow && !has_bomb && !has_sword){
			printf("no weapon");
		}
		printf("\n");
    }

    virtual void declare_born() // 声明出生，派生类中lion dragon不同
    {
        printf("%03d:%02d %s %s %d born\n", hour, minute, side_names[side], name.c_str(), num);
    }

    virtual void move() // 移动到下一个城市
    {
        if(side == red && position != N + 1)
            position++;
        else if(side == blue && position != 0)
            position--;
    } 

	bool evaluate_killed(Warrior * enemy, bool attacker)
	{
		if(enemy->dead) return false;
		int dam;
		if(attacker){ // 自己主动进攻
            if(damage + weapons[sword].weapon_dam >= enemy->strength){
                return false;
            }else{
                if(enemy->name == "ninja"){
                    return false;
                }else{
                    dam = enemy->damage / 2 + enemy->weapons[sword].weapon_dam;
                }
            }    
		}else{
			dam = enemy->damage + enemy->weapons[sword].weapon_dam;
		}
		return dam >= strength;
	}

    virtual void battle_result(Warrior * enemy) // 一场清算战斗结果，dragon wolf不同
    { 
        // 1 获取所有生命元
        if(!dead && enemy->dead){
            if(side == red){ 
                red_M_temp += map[position].element;
            }else{
                blue_M_temp += map[position].element;
            }
            printf("%03d:%02d %s %s %d earned %d elements for his headquarter\n", hour, minute, side_names[side], name.c_str(), num, map[position].element);
            map[position].element = 0;
        }
        // 2 升旗
        if(!enemy->dead){ // 没有胜利，中断连胜
            if(side == red) map[position].red_flag_cnt = 0;
            if(side == blue) map[position].blue_flag_cnt = 0;
        }else if(!dead && enemy->dead){ // 胜利
            if(side == red){ 
                map[position].red_flag_cnt++;
                if(map[position].red_flag_cnt == 2){ // 连胜两场
                    map[position].red_flag_cnt = 0;
                    map[position].blue_flag = false;
                    if(!map[position].red_flag){
                        printf("%03d:%02d red flag raised in city %d\n", hour, minute, position);
                        map[position].red_flag = true;
                    }
                }
            }else if(side == blue){
                map[position].blue_flag_cnt++;
                if(map[position].blue_flag_cnt == 2){
                    map[position].blue_flag_cnt = 0;
                    map[position].red_flag = false;
                    if(!map[position].blue_flag){
                        printf("%03d:%02d blue flag raised in city %d\n", hour, minute, position);
                        map[position].blue_flag = true;
                    }
                }
            }
        }
    }
};

class Dragon : public Warrior
{
    public:
	double morale;
    Dragon(int side_, int num_, int strength_, int damage_, double morale_): Warrior("dragon", side_, num_, strength_, damage_), morale(morale_)
    {
		weapons[num % 3] = Weapon(num % 3, damage);
    }

	void yell(bool attacker)
	{
		if(morale > 0.8 && attacker && !dead){
			printf("%03d:%02d %s dragon %d yelled in city %d\n", hour, minute, side_names[side], num, position);
		}
	}

	void update_morale(bool victory)
	{
		morale += victory ? 0.2 : -0.2;
	}

	virtual void declare_born() // 声明出生
    {
        printf("%03d:%02d %s %s %d born\n", hour, minute, side_names[side], name.c_str(), num);
        //printf("Its morale is %.2lf\n", morale);
        cout << "Its morale is " << fixed << setprecision(2) << morale << endl;
    }

    virtual void battle_result(Warrior * enemy)
    {
        // 1 欢呼
        // (1)士气改变
        update_morale(enemy->dead);
        // (2)欢呼
        yell( // 判断是否是进攻方
            (side == red && (map[position].red_flag || (!map[position].red_flag && !map[position].blue_flag && position % 2 == 1))) ||
            (side == blue && (map[position].blue_flag || (!map[position].red_flag && !map[position].blue_flag && position % 2 == 0)))
        );
        // 2 获取所有生命元
        if(!dead && enemy->dead){
            if(side == red){ 
                red_M_temp += map[position].element;
            }else{
                blue_M_temp += map[position].element;
            }
            printf("%03d:%02d %s %s %d earned %d elements for his headquarter\n", hour, minute, side_names[side], name.c_str(), num, map[position].element);
            map[position].element = 0;
        }
        // 3 升旗
        if(!enemy->dead){ // 没有胜利，中断连胜
            if(side == red) map[position].red_flag_cnt = 0;
            if(side == blue) map[position].blue_flag_cnt = 0;
        }else if(!dead && enemy->dead){ // 胜利
            if(side == red){ 
                map[position].red_flag_cnt++;
                if(map[position].red_flag_cnt == 2){ // 连胜两场
                    map[position].red_flag_cnt = 0;
                    map[position].blue_flag = false;
                    if(!map[position].red_flag){
                        printf("%03d:%02d red flag raised in city %d\n", hour, minute, position);
                        map[position].red_flag = true;
                    }
                }
            }else if(side == blue){
                map[position].blue_flag_cnt++;
                if(map[position].blue_flag_cnt == 2){
                    map[position].blue_flag_cnt = 0;
                    map[position].red_flag = false;
                    if(!map[position].blue_flag){
                        printf("%03d:%02d blue flag raised in city %d\n", hour, minute, position);
                        map[position].blue_flag = true;
                    }
                }
            }
        }
    }
};

class Ninja : public Warrior
{
    public:
    Ninja(int side_, int num_, int strength_, int damage_): Warrior("ninja", side_, num_, strength_, damage_) 
    {
        weapons[num % 3] = Weapon(num % 3, damage), weapons[(num + 1) % 3] = Weapon((num + 1) % 3, damage);
    }
    virtual void fight_back(Warrior * enemy) {} // ninja不反击
};

class Iceman : public Warrior
{
    public:
	int step = 0;
    Iceman(int side_, int num_, int strength_, int damage_): Warrior("iceman", side_, num_, strength_, damage_)
    {
        weapons[num % 3] = Weapon(num % 3, damage);
    }

    virtual void move() // iceman move 损失体力
    {
		if(side == red && position != N + 1)
            position++;
        else if(side == blue && position != 0)
            position--;
		step++;
		if(step == 2){
			step = 0;
			if(strength > 9)
				strength -= 9;
			else
				strength = 1;
			damage += 20;
		}
    }
};

class Lion : public Warrior
{
    public:
    int loyalty;
    Lion(int side_, int num_, int strength_, int damage_, int loyalty_): Warrior("lion", side_, num_, strength_, damage_), loyalty(loyalty_) {}

    virtual void declare_born() // 声明出生
    {
        printf("%03d:%02d %s %s %d born\n", hour, minute, side_names[side], name.c_str(), num);
        printf("Its loyalty is %d\n", loyalty);
    }

	void update_loyalty(bool victory)
	{
		if(!victory)
			loyalty -= K;
	}

	bool run_away()
    {
		if((side == red && position == N + 1) || (side == blue && position == 0) || loyalty > 0){ // 在敌方司令部、loyalty > 0不会逃跑
			return false;
		}else{
        	dead = true;
        	printf("%03d:%02d %s lion %d ran away\n", hour, minute, side_names[side], num);
			return true;
		}
    }

	virtual void hurted(int dam, Warrior * attacker, bool is_arrow) // lion被杀会有伤害转移
	{
		int pre_strength = strength;
		strength -= dam;
		if(strength <= 0){
			strength = 0;
			dead = true;
			if(!is_arrow){ // 被arrow射死，不会有输出和收益
				printf("%03d:%02d %s %s %d was killed in city %d\n", hour, minute, side_names[side], name.c_str(), num, position);
				attacker->strength += pre_strength;
			}
		}
	}

    virtual void attack(Warrior * enemy) // lion未获胜会降低忠诚度
    {
        if(enemy->dead || dead) return; // 敌人已经被arrow射死
		int dam = damage;
		if(weapons[sword].weapon_dam > 0){
			dam += weapons[sword].weapon_dam;
			weapons[sword].weapon_dam = weapons[sword].weapon_dam * 8 / 10;
		}
		printf("%03d:%02d %s %s %d attacked %s %s %d in city %d with %d elements and force %d\n", hour, minute, side_names[side], name.c_str(), num, side_names[enemy->side], enemy->name.c_str(), enemy->num, position, strength, damage);
		enemy->hurted(dam, this);
		enemy->fight_back(this);
        update_loyalty(enemy->dead);
    }

    virtual void fight_back(Warrior * enemy) // lion反击未获胜会降低忠诚度
	{
		if(dead) return;
		int dam = damage / 2;
		if(weapons[sword].weapon_dam > 0){
			dam += weapons[sword].weapon_dam;
			weapons[sword].weapon_dam = weapons[sword].weapon_dam * 8 / 10;
		}
		printf("%03d:%02d %s %s %d fought back against %s %s %d in city %d\n", hour, minute, side_names[side], name.c_str(), num, side_names[enemy->side], enemy->name.c_str(), enemy->num, position);
		enemy->hurted(dam, this);
        update_loyalty(enemy->dead);
	}
};

class Wolf : public Warrior
{
    public:
    Wolf(int side_, int num_, int strength_, int damage_): Warrior("wolf", side_, num_, strength_, damage_) {}

	void get_weapon(Warrior * enemy)
	{
		if(weapons[sword].weapon_dam == 0 && enemy->weapons[sword].weapon_dam > 0)
			weapons[sword] = enemy->weapons[sword];
		if(weapons[bomb].left_num == 0 && enemy->weapons[bomb].left_num > 0)
			weapons[bomb] = Weapon(bomb, damage);
		if(weapons[arrow].left_num == 0 && enemy->weapons[arrow].left_num > 0)
			weapons[arrow] = enemy->weapons[arrow];
	}

    virtual void battle_result(Warrior * enemy)
    {
        // 1 获取所有生命元
        if(!dead && enemy->dead){
            if(side == red){ 
                red_M_temp += map[position].element;
            }else{
                blue_M_temp += map[position].element;
            }
            printf("%03d:%02d %s %s %d earned %d elements for his headquarter\n", hour, minute, side_names[side], name.c_str(), num, map[position].element);
            map[position].element = 0;
        }
        // 2 升旗
        if(!enemy->dead){ // 没有胜利，中断连胜
            if(side == red) map[position].red_flag_cnt = 0;
            if(side == blue) map[position].blue_flag_cnt = 0;
        }else if(!dead && enemy->dead){ // 胜利
            if(side == red){ 
                map[position].red_flag_cnt++;
                if(map[position].red_flag_cnt == 2){ // 连胜两场
                    map[position].red_flag_cnt = 0;
                    map[position].blue_flag = false;
                    if(!map[position].red_flag){
                        printf("%03d:%02d red flag raised in city %d\n", hour, minute, position);
                        map[position].red_flag = true;
                    }
                }
            }else if(side == blue){
                map[position].blue_flag_cnt++;
                if(map[position].blue_flag_cnt == 2){
                    map[position].blue_flag_cnt = 0;
                    map[position].red_flag = false;
                    if(!map[position].blue_flag){
                        printf("%03d:%02d blue flag raised in city %d\n", hour, minute, position);
                        map[position].blue_flag = true;
                    }
                }
            }
        }
        // 3 缴获武器
        if(enemy->dead)
            get_weapon(enemy);
    }
}; 

void map_clear() // 删除所有指针
{
    for(int i = 0; i <= N + 1; ++i)
    {
        delete map[i].pred, map[i].pred = NULL;
        delete map[i].pblue, map[i].pblue = NULL;
        delete map[i].temp_red, map[i].temp_red = NULL;
        delete map[i].temp_blue, map[i].temp_blue = NULL;
		map[i].red_flag = map[i].blue_flag = false;
		map[i].red_flag_cnt = map[i].blue_flag_cnt = 0;
        map[i].element = 0;
    }
}

void headquarter_report() 
{
    printf("%03d:%02d %d elements in red headquarter\n", hour, minute, red_M);
    printf("%03d:%02d %d elements in blue headquarter\n", hour, minute, blue_M);
    minute += 5;
}

void input()
{
	cin >> M >> N >> R >> K >> T; 
    for(int i = 0; i < 5; ++i)
        cin >> warrior_strengths[i];
    for(int i = 0; i < 5; ++i)
        cin >> warrior_dams[i];
}

void initialize()
{
	hour = minute = 0;
    red_M = blue_M = M;
    red_M_temp = 0, blue_M_temp = 0;
	war_over = false;
	red_cur_born = 0, blue_cur_born = 0;
	red_num = 0, blue_num = 0;	
	red_headquarter_enemy = 0, blue_headquarter_enemy = 0;
}

void warrior_born()
{
	if(red_M >= warrior_strengths[red_seq[red_cur_born]])
	{
    	red_M -= warrior_strengths[red_seq[red_cur_born]];
        red_num++;
        switch(red_seq[red_cur_born])
        {
            case dragon: map[0].pred = new Dragon(red, red_num, warrior_strengths[dragon], warrior_dams[dragon], (double)red_M / (double)warrior_strengths[dragon]); break;
            case ninja: map[0].pred = new Ninja(red, red_num, warrior_strengths[ninja], warrior_dams[ninja]); break;
            case iceman: map[0].pred = new Iceman(red, red_num, warrior_strengths[iceman], warrior_dams[iceman]); break;
            case lion: map[0].pred = new Lion(red, red_num, warrior_strengths[lion], warrior_dams[lion], red_M); break;
            case wolf: map[0].pred = new Wolf(red, red_num, warrior_strengths[wolf], warrior_dams[wolf]); break;
        }
        map[0].pred->declare_born(); // 输出降生信息
        red_cur_born = (red_cur_born + 1) % 5;
    }
    if(blue_M >= warrior_strengths[blue_seq[blue_cur_born]])
    {
        blue_M -= warrior_strengths[blue_seq[blue_cur_born]];
        blue_num++;
        switch(blue_seq[blue_cur_born])
        {
            case dragon: map[N + 1].pblue = new Dragon(blue, blue_num, warrior_strengths[dragon], warrior_dams[dragon], (double)blue_M / (double)warrior_strengths[dragon]); break;
            case ninja: map[N + 1].pblue = new Ninja(blue, blue_num, warrior_strengths[ninja], warrior_dams[ninja]); break;
            case iceman: map[N + 1].pblue = new Iceman(blue, blue_num, warrior_strengths[iceman], warrior_dams[iceman]); break;
            case lion: map[N + 1].pblue = new Lion(blue, blue_num, warrior_strengths[lion], warrior_dams[lion], blue_M); break;
            case wolf: map[N + 1].pblue = new Wolf(blue, blue_num, warrior_strengths[wolf], warrior_dams[wolf]); break;
        }
        map[N + 1].pblue->declare_born(); // 输出降生信息
        blue_cur_born = (blue_cur_born + 1) % 5;
    }
	minute += 5;
}

bool Clock()
{
	return hour * 60 + minute > T;
}

void lion_escape()
{
	for(int i = 0; i <= N + 1; ++i)
	{
        if(map[i].pred && map[i].pred->name == "lion")
		{
			Lion * li = dynamic_cast<Lion*>(map[i].pred); // 基类指针转换为lion类
            if(li->run_away()){
				delete map[i].pred;
				map[i].pred = NULL;
			}
		}
			
        if(map[i].pblue && map[i].pblue->name == "lion")
        {
        	Lion * li = dynamic_cast<Lion*>(map[i].pblue);
			if(li->run_away()){
				delete map[i].pblue;
				map[i].pblue = NULL;
			}
		}
	}
	minute += 5;
}

void warrior_move()
{
	for(int i = 0; i <= N + 1; ++i)
	{
        if(map[i].pred && i != N + 1){
        	map[i].pred->move(); 
            int cur_pos = map[i].pred->position; // 移动后的位置
            // 两个位置交换指针，移动后武士存放在temp指针
            map[cur_pos].temp_red = map[i].pred;
            map[i].pred = NULL;
        }
        if(map[i].pblue && i != 0){
            map[i].pblue->move(); 
            int cur_pos = map[i].pblue->position; // 移动后的位置
            // 两个位置交换指针, 移动后武士存放在temp指针
            map[cur_pos].temp_blue = map[i].pblue;
            map[i].pblue = NULL;
        }
    }
    // 对于所有temp，输出移动事件
    for(int i = 0; i <= N + 1; ++i)
    {
        if(map[i].temp_red){
            if(i == N + 1){ // 到达蓝色司令部
            	printf("%03d:%02d red %s %d reached blue headquarter with %d elements and force %d\n", hour, minute, map[i].temp_red->name.c_str(), map[i].temp_red->num, map[i].temp_red->strength, map[i].temp_red->damage);
				blue_headquarter_enemy++;
				if(blue_headquarter_enemy == 2){
					printf("%03d:%02d blue headquarter was taken\n", hour ,minute);
                    war_over = true;
				}
			}else{
        	    printf("%03d:%02d red %s %d marched to city %d with %d elements and force %d\n", hour, minute, map[i].temp_red->name.c_str(), map[i].temp_red->num, i, map[i].temp_red->strength, map[i].temp_red->damage);
            }
        }
        if(map[i].temp_blue){
            if(i == 0){ // 到达红色司令部
                printf("%03d:%02d blue %s %d reached red headquarter with %d elements and force %d\n", hour, minute, map[i].temp_blue->name.c_str(), map[i].temp_blue->num, map[i].temp_blue->strength, map[i].temp_blue->damage);
				red_headquarter_enemy++;
				if(red_headquarter_enemy == 2){
					printf("%03d:%02d red headquarter was taken\n", hour ,minute);
                    war_over = true;
				}
            }else{
                printf("%03d:%02d blue %s %d marched to city %d with %d elements and force %d\n", hour, minute, map[i].temp_blue->name.c_str(), map[i].temp_blue->num, i, map[i].temp_blue->strength, map[i].temp_blue->damage);
            }
    	}
	}
    if(war_over) return;
    // 暂时存放新到的指针转正
    for(int i = 0; i <= N + 1; ++i)
    {
        if(map[i].temp_red){
            map[i].pred = map[i].temp_red;
            map[i].temp_red = NULL;
        }
        if(map[i].temp_blue){
            map[i].pblue = map[i].temp_blue;
            map[i].temp_blue = NULL;
        }
    }
	minute += 10;
}

void city_creat_element()
{
	for(int i = 1; i <= N; ++i){
		map[i].element += 10;
	}
	minute += 10;
}

void warrior_collect_element()
{
	for(int i = 1; i <= N; ++i){
		if(map[i].pred && !map[i].pblue){
			red_M += map[i].element;
			printf("%03d:%02d red %s %d earned %d elements for his headquarter\n", hour, minute, map[i].pred->name.c_str(), map[i].pred->num, map[i].element);
			map[i].element = 0;
		}else if(map[i].pblue && !map[i].pred){
			blue_M += map[i].element;
			printf("%03d:%02d blue %s %d earned %d elements for his headquarter\n", hour, minute, map[i].pblue->name.c_str(), map[i].pblue->num, map[i].element);
			map[i].element = 0;
		}
	}
	minute += 5;
}

void fire_arrow()
{
	for(int i = 0; i <= N + 1; ++i)
	{
		if(map[i].pred && i < N && map[i + 1].pblue && map[i].pred->weapons[arrow].left_num > 0){
			map[i + 1].pblue->hurted(R, map[i].pred, true);
			map[i].pred->weapons[arrow].left_num--;
			printf("%03d:%02d red %s %d shot", hour, minute, map[i].pred->name.c_str(), map[i].pred->num);
			if(map[i + 1].pblue->dead){
				printf(" and killed blue %s %d", map[i + 1].pblue->name.c_str(), map[i + 1].pblue->num);
			}
			printf("\n");
		}
		if(map[i].pblue && i > 1 && map[i - 1].pred && map[i].pblue->weapons[arrow].left_num > 0){
			map[i - 1].pred->hurted(R, map[i].pblue, true);
			map[i].pblue->weapons[arrow].left_num--;
			printf("%03d:%02d blue %s %d shot", hour, minute, map[i].pblue->name.c_str(), map[i].pblue->num);
			if(map[i - 1].pred->dead){
				printf(" and killed red %s %d", map[i - 1].pred->name.c_str(), map[i - 1].pred->num);
			}
			printf("\n");
		}
	}
	minute += 3;
}

void warrior_evaluate()
{
	for(int i = 1; i <= N; ++i)
	{
		if(map[i].pred && map[i].pblue && !map[i].pred->dead && !map[i].pblue->dead){ // 有两个武士且都活着
			if(map[i].pred->weapons[bomb].left_num > 0){
				if(map[i].pred->evaluate_killed(map[i].pblue, (i % 2 == 1 && !map[i].red_flag && !map[i].blue_flag) || map[i].red_flag)){
					printf("%03d:%02d red %s %d used a bomb and killed blue %s %d\n", hour, minute, map[i].pred->name.c_str(), map[i].pred->num, map[i].pblue->name.c_str(), map[i].pblue->num);
					delete map[i].pred; delete map[i].pblue;
					map[i].pred = map[i].pblue = NULL;
                    continue;
				}
			}
			if(map[i].pblue->weapons[bomb].left_num > 0){
				if(map[i].pblue->evaluate_killed(map[i].pred, (i % 2 == 0 && !map[i].red_flag && !map[i].blue_flag) || map[i].blue_flag)){
					printf("%03d:%02d blue %s %d used a bomb and killed red %s %d\n", hour, minute, map[i].pblue->name.c_str(), map[i].pblue->num, map[i].pred->name.c_str(), map[i].pred->num);
					delete map[i].pred; delete map[i].pblue;
					map[i].pred = map[i].pblue = NULL;
                    continue;
				}
			}
		}
	}
    minute += 2;
}

void battle()
{
    // 从西向东输出战斗信息
	for(int i = 1; i <= N; ++i){
		if(map[i].pred && map[i].pblue){
			if(map[i].red_flag || (i % 2 == 1 && !map[i].red_flag && !map[i].blue_flag)){ // red先攻击
				map[i].pred->attack(map[i].pblue);
			}else{ // blue先攻击
				map[i].pblue->attack(map[i].pred);
			}
            // 战斗结算
            map[i].pred->battle_result(map[i].pblue);
            map[i].pblue->battle_result(map[i].pred);
		}
	}
    // 红方司令部奖励生命元
    for(int i = N; i >= 1; --i){
        if(map[i].pred && map[i].pblue && map[i].pblue->dead && !map[i].pred->dead && red_M >= 8){
            map[i].pred->strength += 8;
            red_M -= 8;
        }
    }
    // 蓝方司令部奖励生命元
    for(int i = 1; i <= N; ++i){
        if(map[i].pred && map[i].pblue && map[i].pred->dead && !map[i].pblue->dead && blue_M >= 8){
            map[i].pblue->strength += 8;
            blue_M -= 8;
        }
    }
    // 将武士在城市中获得的生命元加入司令部
    red_M += red_M_temp; red_M_temp = 0;
    blue_M += blue_M_temp; blue_M_temp = 0;

    // 清除死亡武士
    for(int i = 1; i <= N; ++i){
        if(map[i].pred){
            if(map[i].pred->dead){
                delete map[i].pred;
                map[i].pred = NULL;
            }
        }
        if(map[i].pblue){
            if(map[i].pblue->dead){
                delete map[i].pblue;
                map[i].pblue = NULL;
            }
        }
    }
    minute += 10;
}

void warrior_report()
{
    for(int i = 0; i <= N + 1; ++i){
        if(map[i].pred)
            map[i].pred->declare_weapon();
    }
    for(int i = 0; i <= N + 1; ++i){
        if(map[i].pblue)
            map[i].pblue->declare_weapon();
    }
    hour += 1, minute = 0;
}

int main()
{
    int t;
    cin >> t;
    for(int CASE = 1; CASE <= t; ++CASE)
    {
        // 输入
        input();
        // 初始化
        initialize();
        cout << "Case " << CASE << ":" << endl;
        while(!war_over)
        {
            // 00 武士降生
            warrior_born();
            if(Clock()) break;	
            // 05 lion逃跑
           	lion_escape();
            if(Clock()) break;
            // 10 武士前进
            warrior_move();
            if(war_over || Clock()) break;
			// 20 城市产出生命元
			city_creat_element();
			if(Clock()) break;
			// 30 武士采集生命元
			warrior_collect_element();
			if(Clock()) break;
			// 35 武士放箭
			fire_arrow();
			if(Clock()) break;
			// 38 武士评估使用bomb
			warrior_evaluate();
			if(Clock()) break;
			// 40 发生战斗
			battle();
            if(Clock()) break;
            // 50 司令部汇报
            headquarter_report();
            if(Clock()) break;
            // 55 武士汇报
            warrior_report();
            if(Clock()) break;
        }
        // case结束，清除地图
        map_clear();
    }
    system("pause");
    return 0;
}
