inherit ROOM;

void create()
{
        set("short", "������¥");
        set("long", @LONG
�����Ǳ�������¥������������Ƹߣ�һ��΢�紵����˵������
��ˬ�����ݳǵķ��Ҳ�����۵ס�
LONG );
        set("exits", ([  
                  "down" : __DIR__"baita1",
        ]));
        set("objects", ([
                "/d/beijing/npc/shiren" : 1,
        ]));
        set("no_clean_up", 0);

        set("coor/x", -7090);
	set("coor/y", -2040);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}