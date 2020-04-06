#include<iostream>
#include"Warcraft_game_settings.h"
using namespace std;

/**
 * @brief 
*/

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
