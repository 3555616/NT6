// /d/taishan/kedian2.c

inherit ROOM;

void create()
{
        set("short", "�͵��¥");
        set("long", @LONG
����һ��ܴ�Ŀͷ�������ʮ�ּ�ª����ǽ����ʮ����Сľ����
���ٿ��������¶��ԣ������Ӷ��Ǻ����Ĵ������������Ŵ��ǿյģ�
��������ŵ����˹�ȥ��
LONG );
        set("sleep_room",1);
        set("exits", ([
                "down" : __DIR__"kedian",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 80);
	set("coor/y", 30);
	set("coor/z", 10);
	setup();
}

int valid_leave(object me, string dir)
{

        if( dir == "down")delete_temp("rent_paid", me);

        return ::valid_leave(me, dir);
}