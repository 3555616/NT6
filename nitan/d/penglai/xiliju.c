inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "西篱居");
        set("long",@LONG
这里似乎是一处居所，不远处有一处茅屋，四周用篱笆围住。  
放眼远望，山影起伏，雾气阵阵，令人无限遐思。     
LONG);

        set("exits", ([
                "northeast"        : __DIR__"caijuyuan2",
                "southeast"        : __DIR__"caijuyuan3",
        ]));
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
        set("penglai", 1);           // 表示在蓬莱岛

        setup();
}

void init ()
{
        if (! this_player()->query_temp("apply/xianshu-lingwei"))
        {
                if (! this_player()->query("penglai/go_quest/ok"))
                {
                        this_player()->start_busy(3);
                        tell_object(this_player(), NOR + WHT "你到了此处，四周仙气缭绕令你一时间难以辨别方向。\n" NOR);
                }
                else
                {
                        if (random(2))
                        {
                                this_player()->start_busy(1);
                                tell_object(this_player(), NOR + WHT "你到了此处，四周仙气缭绕令你一时间难以辨别方向。\n" NOR);                
                        }
                }
        }
}