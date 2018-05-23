inherit ROOM;

void create()
{
        set("short", "东大街");
        set("long", @LONG
东大街是开封府内东街区的主要通道。道路的两端店铺府第不断。
行人如缕，观光的，作生意的，攀交情的，以至走亲访友的，喧闹无
比。南边一个小角门内似乎是个小菜园子。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"jiaomen",
                  "north" : __DIR__"eroad1",
                "east" : __DIR__"dongmen",
        ]));

        set("outdoors", "kaifeng");

	set("coor/x", -5030);
	set("coor/y", 2220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}