// Room: /city/ymdongting.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "��������");
        set("long", @LONG
���϶����������ס������һ������������������ϸ������ǽ��
����һ�����ң����顺����������ĸ���������Ĵ��֡�֪��������
�İ����������飬ʦү�����ں�
LONG );
	set("exits", ([
		"east"  : "/d/city/dongting",
		"west"  : "/d/city/xiting",
		"north" : "/d/city/neizhai",
		"south" : "/d/city/yamen",
	]));
	set("objects", ([
		"/d/city/npc/cheng" : 1,
		"/d/city/npc/shiye" : 1,
	]));
//	set("no_clean_up", 0);
	set("coor/x", -10);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}