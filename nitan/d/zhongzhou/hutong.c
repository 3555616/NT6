inherit ROOM;

void create()
{
        set("short", "С��ͬ");
        set("long", @LONG
������һ��С��ͬ�����ڰ�������Ҳ�ǻ谵������
LONG);
        set("outdoors", "zhongzhou");

        set("exits", ([
                "southwest" : __DIR__"wendingnan3",
                "northeast" : __DIR__"hutong1",                  
        ]));

        set("coor/x", -9030);
	set("coor/y", -1020);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}