#include<iostream>
#include<string>
#include<vector>
#include<stdio.h>
#include<algorithm>
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
int red_M = 0, blue_M = 0, M = 0, N = 0, K = 0, T = 0;
int hour = 0, minute = 0;

// 司令部声明生命元数量
void headquarter_declare() 
{
    printf("%03d:%02d %d elements in red headquarter\n", hour, minute, red_M);
    printf("%03d:%02d %d elements in blue headquarter\n", hour, minute, blue_M);
}

// 武器类
class Weapon
{
    public:
    int weapon_code;
    int left_num;
    int weapon_dam;

    Weapon() {}
    Weapon(int weapon_code_, int user_dam): weapon_code(weapon_code_) // 武器伤害取决于使用者
    {
        switch(weapon_code)
        {
            case 0: left_num = inf; weapon_dam = user_dam * 2 / 10; break;
            case 1: left_num = 1; weapon_dam = user_dam * 4 / 10; break;
            case 2: left_num = 2; weapon_dam = user_dam * 3 / 10; break;
        }
    }
    Weapon(const Weapon & wep): weapon_code(wep.weapon_code), left_num(wep.left_num), weapon_dam(wep.weapon_dam) {}

};

class cmp1 // 战斗前排序，编号小，用过的在前
{
    public:
    bool operator()(Weapon & w1, Weapon & w2)
    {
        if(w1.weapon_code == w2.weapon_code)
            return w1.left_num < w2.left_num;
        return w1.weapon_code < w2.weapon_code;
    }
};

class cmp2 // 抢夺、缴获武器时排序，编号小，没用过的在后
{
    public:
    bool operator()(Weapon & w1, Weapon & w2)
    {
        if(w1.weapon_code == w2.weapon_code)
            return w1.left_num < w2.left_num;
        return w1.weapon_code > w2.weapon_code;
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
    vector<Weapon> weapons; // 持有武器序列
    int weapon_num = 0; // 拥有武器数量
    int position; // 所在城市位置

    Warrior(string name_, int side_, int num_, int strength_, int damage_): name(name_), side(side_), num(num_), strength(strength_), damage(damage_)
    {
        // 武士出生位置
        if(side == red)
            position = 0;
        else
            position = N + 1;
    }

    void hurted(int dam)
    {
        strength -= dam;
        if(strength <= 0)
            dead = true;
    }
    
    virtual void attack(Warrior * enemy, Weapon & wep)
    {
        int dam = wep.weapon_dam; // 当前使用武器的伤害值
        enemy->hurted(dam);
        // bomb
        if(wep.weapon_code == bomb)
            this->hurted(dam / 2);
        wep.left_num--; // 当前使用武器数量减少
    }

    void declare_cur() // 武士声明自己当前状态
    {
        int weapon_cnt[3] = {0}; // 各种武器数量计数
        for(auto i = weapons.begin(); i != weapons.end(); ++i)
            weapon_cnt[i->weapon_code]++;
        printf("%03d:%02d %s %s %d has %d sword %d bomb %d arrow and %d elements\n", hour, minute, side_names[side], name.c_str(), num, weapon_cnt[sword], weapon_cnt[bomb], weapon_cnt[arrow], strength);
    }

    virtual void declare_born() // 声明出生，派生类中只有lion不同
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

    void weapon_sort() // 战斗前武器排序
    {
        if(weapons.size())
            sort(weapons.begin(), weapons.end(), cmp1());
    }

    void change_weapon_dam() // 抢来的武器改变攻击力
    {
        for(auto i = weapons.begin(); i != weapons.end(); ++i)
        {
            switch(i->weapon_code)
            {
                case 0: i->weapon_dam = damage * 2 / 10; break;
                case 1: i->weapon_dam = damage * 4 / 10; break;
                case 2: i->weapon_dam = damage * 3 / 10; break;
            }
        }
    }

    void get_weapon(Warrior * enemy) // 缴获武器
    {
        sort(enemy->weapons.begin(), enemy->weapons.end(), cmp2()); // 编号最小，未被使用的在最后
        for(auto i = enemy->weapons.rbegin(); weapon_num < MAX && i != enemy->weapons.rend();) // 反向迭代器
        {
            weapons.push_back(enemy->weapons.back());
            ++i;
            enemy->weapons.pop_back();
            ++weapon_num, --(enemy->weapon_num);
        }
        change_weapon_dam();
    }  

    int sword_cnt()
    {
        int ans = 0;
        for(auto i = weapons.begin(); i != weapons.end(); ++i)
            if(i->weapon_code == sword)
                ans++;
        return ans;
    }
};

class Dragon : public Warrior
{
    public:
    Dragon(int side_, int num_, int strength_, int damage_): Warrior("dragon", side_, num_, strength_, damage_)
    {
        weapon_num = 1;
        weapons.push_back(Weapon(num % 3, damage)); // 出生时获得一件武器
    }
};

class Ninja : public Warrior
{
    public:
    Ninja(int side_, int num_, int strength_, int damage_): Warrior("ninja", side_, num_, strength_, damage_) 
    {
        weapon_num = 2;
        weapons.push_back(Weapon(num % 3, damage)); weapons.push_back(Weapon((num + 1) % 3, damage)); // 出生时获得两件武器
    }
    // ninja不受bomb自己伤害
    virtual void attack(Warrior * enemy, Weapon & wep)
    {
        int dam = wep.weapon_dam; // 当前使用武器的伤害值
        enemy->hurted(dam);
        wep.left_num--; // 当前使用武器数量减少
    }
};

class Iceman : public Warrior
{
    public:
    Iceman(int side_, int num_, int strength_, int damage_): Warrior("iceman", side_, num_, strength_, damage_)
    {
        weapon_num = 1;
        weapons.push_back(Weapon(num % 3, damage)); // 出生时获得一件武器
    }

    virtual void move() // iceman move 损失体力
    {
        if(side == red && position != N + 1)
        {
            position++;
            strength -= strength * 1 / 10;
        }
        else if(side == blue && position != 0)
        {
            position--;
            strength -= strength * 1 / 10;
        }
        if(strength <= 0)
            dead = true;
    }
};

class Lion : public Warrior
{
    public:
    int loyalty;
    Lion(int side_, int num_, int strength_, int damage_, int loyalty_): Warrior("lion", side_, num_, strength_, damage_), loyalty(loyalty_)
    {
        weapon_num = 1;
        weapons.push_back(Weapon(num % 3, damage)); // 出生时获得一件武器
    }

    virtual void move() // lion move损失loyalty
    {
        if(side == red && position != N + 1)
        {
            position++;
            loyalty -= K;
        }
        else if(side == blue && position != 0)
        {
            position--;
            loyalty -= K;
        }
    }

    virtual void declare_born() // 声明出生，派生类中只有lion不同
    {
        printf("%03d:%02d %s %s %d born\n", hour, minute, side_names[side], name.c_str(), num);
        printf("Its loyalty is %d\n", loyalty);
    }

    void run_away()
    {
        dead = true;
        printf("%03d:%02d %s lion %d ran away\n", hour, minute, side_names[side], num);
    }
};

class Wolf : public Warrior
{
    public:
    Wolf(int side_, int num_, int strength_, int damage_): Warrior("wolf", side_, num_, strength_, damage_) {}

    void rob_weapons(Warrior * enemy)
    {
        if(enemy->weapons.size() == 0)
            return;
        sort(enemy->weapons.begin(), enemy->weapons.end(), cmp2()); // 编号最小，未被使用的在最后
        int min_weapon = enemy->weapons.back().weapon_code; // 敌方最小编号武器
        int cnt = 0; // 抢夺个数
        for(auto i = enemy->weapons.rbegin(); weapon_num < MAX && i->weapon_code == min_weapon && i != enemy->weapons.rend();)
        {
            weapons.push_back(enemy->weapons.back());
            ++i;
            enemy->weapons.pop_back();
            ++weapon_num, --(enemy->weapon_num);
            ++cnt;
        }     
        change_weapon_dam();
        if(cnt != 0)
            printf("%03d:%02d %s wolf %d took %d %s from %s %s %d in city %d\n", hour, minute, side_names[side], num, cnt, weapon_names[min_weapon], side_names[enemy->side], enemy->name.c_str(), enemy->num, position);
    }
    
};

struct info
{
    Warrior * pred = NULL;
    Warrior * pblue = NULL;
    Warrior * temp_red = NULL; // temp 指针存放刚刚移动到该地点的武士
    Warrior * temp_blue = NULL;
}map[25]; // 记录城市信息,城市指针管理武士， NULL代表没有武士

void map_clear() // 删除所有指针
{
    for(int i = 0; i <= N + 1; ++i)
    {
        delete map[i].pred, map[i].pred = NULL;
        delete map[i].pblue, map[i].pblue = NULL;
    }
}

int main()
{
    int t;
    cin >> t;
    for(int CASE = 1; CASE <= t; ++CASE)
    {
        cin >> M >> N >> K >> T;
        int warrior_strengths[5], warrior_dams[5];
        for(int i = 0; i < 5; ++i)
            cin >> warrior_strengths[i];
        for(int i = 0; i < 5; ++i)
            cin >> warrior_dams[i];

        bool war_over = false;
        hour = minute = 0;
        red_M = blue_M = M;
        int red_cur_born = 0, blue_cur_born = 0;
        int red_num = 0, blue_num = 0;
        
        cout << "Case " << CASE << ":" << endl;
        while(hour * 60 + minute <= T && !war_over)
        {
            // 00 武士降生
            if(red_M >= warrior_strengths[red_seq[red_cur_born]])
            {
                red_M -= warrior_strengths[red_seq[red_cur_born]];
                red_num++;
                switch(red_seq[red_cur_born])
                {
                    case dragon: map[0].pred = new Dragon(red, red_num, warrior_strengths[dragon], warrior_dams[dragon]); break;
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
                    case dragon: map[N + 1].pblue = new Dragon(blue, blue_num, warrior_strengths[dragon], warrior_dams[dragon]); break;
                    case ninja: map[N + 1].pblue = new Ninja(blue, blue_num, warrior_strengths[ninja], warrior_dams[ninja]); break;
                    case iceman: map[N + 1].pblue = new Iceman(blue, blue_num, warrior_strengths[iceman], warrior_dams[iceman]); break;
                    case lion: map[N + 1].pblue = new Lion(blue, blue_num, warrior_strengths[lion], warrior_dams[lion], blue_M); break;
                    case wolf: map[N + 1].pblue = new Wolf(blue, blue_num, warrior_strengths[wolf], warrior_dams[wolf]); break;
                }
                map[N + 1].pblue->declare_born(); // 输出降生信息
                blue_cur_born = (blue_cur_born + 1) % 5;
            }
            minute += 5;
            if(hour * 60 + minute > T)
                break;

            // 05 lion逃跑
            for(int i = 0; i <= N + 1; ++i)
            {
                if(map[i].pred)
                {
                    if(map[i].pred->name == "lion")
                    {
                        Lion * li = dynamic_cast<Lion*>(map[i].pred); // 基类指针转换为lion类
                        if(li->loyalty <= 0 && i != N + 1)
                        {
                            li->run_away();
                            li = NULL;
                            delete map[i].pred;
                            map[i].pred = NULL;
                        }
                    }
                }
                if(map[i].pblue)
                {
                    if(map[i].pblue->name == "lion")
                    {
                        Lion * li = dynamic_cast<Lion*>(map[i].pblue);
                        if(li->loyalty <= 0 && i != 0)
                        {
                            li->run_away();
                            li = NULL;
                            delete map[i].pblue;
                            map[i].pblue = NULL;
                        }
                    }
                }
            }
            minute += 5;
            if(hour * 60 + minute > T)
                break;

            // 10 武士前进
            for(int i = 0; i <= N + 1; ++i)
            {
                if(map[i].pred) 
                {
                    map[i].pred->move(); 
                    int cur_pos = map[i].pred->position; // 移动后的位置
                    // 两个位置交换指针，移动后武士存放在temp指针
                    map[cur_pos].temp_red = map[i].pred;
                    map[i].pred = NULL;
                }
                if(map[i].pblue)
                {
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
                if(map[i].temp_red)
                {
                    if(i == N + 1) // 到达蓝色司令部
                    {
                        printf("%03d:%02d red %s %d reached blue headquarter with %d elements and force %d\n", hour, minute, map[i].temp_red->name.c_str(), map[i].temp_red->num, map[i].temp_red->strength, map[i].temp_red->damage);
                        printf("%03d:%02d blue headquarter was taken\n", hour ,minute);
                        war_over = true;
                    }
                    else
                        printf("%03d:%02d red %s %d marched to city %d with %d elements and force %d\n", hour, minute, map[i].temp_red->name.c_str(), map[i].temp_red->num, i, map[i].temp_red->strength, map[i].temp_red->damage);
                }
                if(map[i].temp_blue)
                {
                    if(i == 0) // 到达红色司令部
                    {
                        printf("%03d:%02d blue %s %d reached red headquarter with %d elements and force %d\n", hour, minute, map[i].temp_blue->name.c_str(), map[i].temp_blue->num, map[i].temp_blue->strength, map[i].temp_blue->damage);
                        printf("%03d:%02d red headquarter was taken\n", hour ,minute);
                        war_over = true;
                    }
                    else
                        printf("%03d:%02d blue %s %d marched to city %d with %d elements and force %d\n", hour, minute, map[i].temp_blue->name.c_str(), map[i].temp_blue->num, i, map[i].temp_blue->strength, map[i].temp_blue->damage);
                }
            }
            // 暂时存放新到的指针转正
            for(int i = 0; i <= N + 1; ++i)
            {
                if(map[i].temp_red)
                {
                    map[i].pred = map[i].temp_red;
                    map[i].temp_red = NULL;
                }
                if(map[i].temp_blue)
                {
                    map[i].pblue = map[i].temp_blue;
                    map[i].temp_blue = NULL;
                }
            }
            minute += 25;
            if(war_over || hour * 60 + minute > T)
                break;

            // 35 wolf抢夺武器
            for(int i = 1; i <= N; ++i)
            {
                if(map[i].pred && map[i].pblue)
                {
                    if(map[i].pred->name == "wolf" && map[i].pblue->name != "wolf")
                    {
                        Wolf * wolf = dynamic_cast<Wolf*>(map[i].pred); // 临时指针,转换为wolf类
                        wolf->rob_weapons(map[i].pblue);
                    }
                    if(map[i].pblue->name == "wolf" && map[i].pred->name != "wolf")
                    {
                        Wolf * wolf = dynamic_cast<Wolf*>(map[i].pblue);
                        wolf->rob_weapons(map[i].pred);
                    }
                }
            }
            minute += 5;
            if(hour * 60 + minute > T)
                break;

            // 40 发生战斗
            for(int i = 1; i <= N; ++i)
            {
                if(map[i].pred && map[i].pblue) // 开打
                {
                    bool battle_over = false;
                    // 双方武器排序
                    map[i].pred->weapon_sort(); map[i].pblue->weapon_sort();

                    // 指向双方武器序列的迭代器
                    vector<Weapon>::iterator wep_red = map[i].pred->weapons.begin();
                    vector<Weapon>::iterator wep_blue = map[i].pblue->weapons.begin();

                    if(i % 2 == 1) // red first
                    {
                        while(!battle_over)
                        {
                            // 武器序列循环
                            if(wep_red == map[i].pred->weapons.end())
                                wep_red = map[i].pred->weapons.begin();
                            if(wep_blue == map[i].pblue->weapons.end())
                                wep_blue = map[i].pblue->weapons.begin();
                            // 战斗结束条件是双方都只剩下sword且不再对对方造成伤害
                            int red_strength = map[i].pred->strength, blue_strength = map[i].pblue->strength;  // 回合开始时体力
                            int red_sword = map[i].pred->sword_cnt(), blue_sword = map[i].pblue->sword_cnt();
                            
                            if(map[i].pred->weapons.size()) // red有武器
                            {
                                if(wep_red->left_num <= 0)
                                {
                                    wep_red = map[i].pred->weapons.erase(wep_red);
                                    map[i].pred->weapon_num--;
                                }

                                map[i].pred->attack(map[i].pblue, *wep_red);
                                // 武器更换
                                if(wep_red->left_num <= 0) // 用完了，删除这个武器，迭代器指向下一个
                                {
                                    wep_red = map[i].pred->weapons.erase(wep_red);
                                    map[i].pred->weapon_num--;
                                }
                                else 
                                    wep_red++;
                                if(map[i].pblue->dead || map[i].pred->dead)
                                {
                                    battle_over = true;
                                    break;
                                }
                            }

                            if(map[i].pblue->weapons.size()) // blue有武器
                            {
                                if(wep_blue->left_num <= 0)
                                {
                                    wep_blue = map[i].pblue->weapons.erase(wep_blue);
                                    map[i].pblue->weapon_num--;
                                }

                                map[i].pblue->attack(map[i].pred, *wep_blue);
                                // 武器更换
                                if(wep_blue->left_num <= 0)
                                {
                                    wep_blue = map[i].pblue->weapons.erase(wep_blue);
                                    map[i].pblue->weapon_num--;
                                }
                                else
                                    wep_blue++;            
                                if(map[i].pred->dead || map[i].pblue->dead)
                                {
                                    battle_over = true;
                                    break;
                                }
                            }
                            // 每回合二者体力均不变化
                            if(map[i].pred->strength == red_strength && map[i].pblue->strength == blue_strength && map[i].pred->weapon_num == red_sword && map[i].pblue->weapon_num == blue_sword)
                                battle_over = true;
                        }
                    }
                    else if(i % 2 == 0) // blue first
                    {
                        while(!battle_over)
                        {
                            if(wep_red == map[i].pred->weapons.end())
                                wep_red = map[i].pred->weapons.begin();
                            if(wep_blue == map[i].pblue->weapons.end())
                                wep_blue = map[i].pblue->weapons.begin();
                            
                            int red_strength = map[i].pred->strength, blue_strength = map[i].pblue->strength;  // 回合开始时体力
                            int red_sword = map[i].pred->sword_cnt(), blue_sword = map[i].pblue->sword_cnt();

                            if(map[i].pblue->weapons.size()) // blue有武器
                            {
                                if(wep_blue->left_num <= 0)
                                {
                                    wep_blue = map[i].pblue->weapons.erase(wep_blue);
                                    map[i].pblue->weapon_num--;
                                }

                                map[i].pblue->attack(map[i].pred, *wep_blue);
                                // 武器更换
                                if(wep_blue->left_num <= 0)
                                {
                                    wep_blue = map[i].pblue->weapons.erase(wep_blue);
                                    map[i].pblue->weapon_num--;
                                }
                                else
                                    wep_blue++;
                            
                                if(map[i].pred->dead || map[i].pblue->dead)
                                {
                                    battle_over = true;
                                    break;
                                }
                            }

                            if(map[i].pred->weapons.size()) // red有武器
                            {
                                if(wep_red->left_num <= 0)
                                {
                                    wep_red = map[i].pred->weapons.erase(wep_red);
                                    map[i].pred->weapon_num--;
                                }
                                    
                                map[i].pred->attack(map[i].pblue, *wep_red);
                                // 武器更换
                                if(wep_red->left_num == 0)
                                {
                                    wep_red = map[i].pred->weapons.erase(wep_red);
                                    map[i].pred->weapon_num--;
                                }
                                else
                                    wep_red++;

                                if(map[i].pblue->dead || map[i].pred->dead)
                                {
                                    battle_over = true;
                                    break;
                                }
                            }
                            if(map[i].pred->strength == red_strength && map[i].pblue->strength == blue_strength && map[i].pred->weapon_num == red_sword && map[i].pblue->weapon_num == blue_sword)
                                battle_over = true;
                        }
                    }
                    // 战斗结束
                    // 1. red win
                    if(!map[i].pred->dead && map[i].pblue->dead)
                    {
                        printf("%03d:%02d red %s %d killed blue %s %d in city %d remaining %d elements\n", hour, minute, map[i].pred->name.c_str(), map[i].pred->num, map[i].pblue->name.c_str(), map[i].pblue->num, i, map[i].pred->strength);
                        if(map[i].pred->name == "dragon")
                            printf("%03d:%02d red dragon %d yelled in city %d\n", hour, minute, map[i].pred->num, i);
                        map[i].pred->get_weapon(map[i].pblue); // 缴获武器
                    }
                    // 2. blue win
                    if(!map[i].pblue->dead && map[i].pred->dead)
                    {
                        printf("%03d:%02d blue %s %d killed red %s %d in city %d remaining %d elements\n", hour, minute, map[i].pblue->name.c_str(), map[i].pblue->num, map[i].pred->name.c_str(), map[i].pred->num, i, map[i].pblue->strength);
                        if(map[i].pblue->name == "dragon")
                            printf("%03d:%02d blue dragon %d yelled in city %d\n", hour, minute, map[i].pblue->num, i);
                        map[i].pblue->get_weapon(map[i].pred); // 缴获武器
                    }
                    // 3. both die
                    if(map[i].pred->dead && map[i].pblue->dead)
                        printf("%03d:%02d both red %s %d and blue %s %d died in city %d\n", hour, minute, map[i].pred->name.c_str(), map[i].pred->num, map[i].pblue->name.c_str(), map[i].pblue->num, i);
                    // 4. both alive
                    if(!map[i].pred->dead && !map[i].pblue->dead)
                    {
                        printf("%03d:%02d both red %s %d and blue %s %d were alive in city %d\n", hour, minute, map[i].pred->name.c_str(), map[i].pred->num, map[i].pblue->name.c_str(), map[i].pblue->num, i);  
                        if(map[i].pred->name == "dragon")
                            printf("%03d:%02d red dragon %d yelled in city %d\n", hour, minute, map[i].pred->num, i);
                        if(map[i].pblue->name == "dragon")
                            printf("%03d:%02d blue dragon %d yelled in city %d\n", hour, minute, map[i].pblue->num, i);
                    }
                }       
            }
            // 清理战场，删除死亡武士
            for(int i = 1; i <= N; ++i)
            {
                if(map[i].pred)
                {
                    if(map[i].pred->dead)
                    {
                        delete map[i].pred;
                        map[i].pred = NULL;
                    }
                }
                if(map[i].pblue)
                {
                    if(map[i].pblue->dead)
                    {
                        delete map[i].pblue;
                        map[i].pblue = NULL;
                    }
                }
            }
            minute += 10;
            if(hour * 60 + minute > T)
                break;

            // 50 司令部汇报
            headquarter_declare();
            minute += 5;
            if(hour * 60 + minute > T)
                break;

            // 55 武士汇报
            for(int i = 0; i <= N + 1; ++i)
            {
                if(map[i].pred)
                    map[i].pred->declare_cur();
                if(map[i].pblue)
                    map[i].pblue->declare_cur();
            }

            // 一回合结束
            hour++; minute = 0;
        }

        // case结束，清除地图
        map_clear();
    }
    system("pause");
    return 0;
}
