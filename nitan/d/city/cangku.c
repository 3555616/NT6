// Room: /city/cangku.c

inherit ROOM;
void init();

void create()
{
	set("short", "�ֿ�");
        set("long", @LONG
������һ�������Ĳֿ⣬�������Ƽҵĸ��������������һ
�ֿ⡣�������Ǳ��˹������������ġ�
LONG );
	set("valid_startroom", "1");
	set("no_fight", 1);
//	set("no_clean_up", 0);

	set("objects", ([
		"/d/city/obj/jitui" : 3,
		"/d/city/obj/jiudai" : 1,
	]));
	setup();
}

void init()
{
	object ob;

	ob = this_player();
set("startroom", "/d/city/cangku", 	ob);
set_temp("selled", 1, 	ob);
}