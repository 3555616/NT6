// qinglindong.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "���ֶ�");
        set("long", @LONG
�ֽ��ϻ�����ֻ�����ҵ������ӣ�����������������С�𡣶���
������ϻ�����һ�顰®���Ƿ�ᡱ�������Ͽ̻�ͷ�裬�м�����
����Ĳ�ᣬ���ҷ������⣬���ͣ���������������������ɽ��·��
С·���������򶫡�
LONG);
        set("exits", ([
                "eastup"    : __DIR__"cuiweiting",
                "westdown"  : __DIR__"feilaifeng",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "hangzhou");
        set("no_clean_up", 0);
	set("coor/x", 750);
	set("coor/y", -2070);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}