//1997-3-10 by qyz
#include <room.h>

inherit ROOM;


void create()
{
	set("short","紫霄崖");
	set("long",@LONG
在「齐云广志」里面曾称紫霄崖“壁立五百馀仞，势欲压。过之者足未涉而
气已夺”，在紫霄崖的壁上有“天下奇观”等石刻，崖前一大石酷似骆驼，是以
也有人将紫霄崖称为“紫驼峰”，悬崖高处有一个小洞龛，中有三尊神像，周围
环境清幽，实是道家品茗说道，打坐修仙的绝佳之所。
LONG);
	set("exits",
	([
          "east" : __DIR__"qipan_ling",
          	]));
        set("outdoors","kongdong");
	set("objects", ([
		__DIR__"npc/o_yizhe" : 1,
		__DIR__"obj/qipan" : 1,
		__DIR__"npc/y_yizhe" : 1,
		]) );
        setup();
        //place_program(ROOM);
}
