// Room: /yixing/shulin5.c
// Date: Nov.18 1998 by Winder

inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
��������߰�����ֻ������ͷ���ϴ���һЩ�����������ż����ï
�ܵ�Ҷ��͸����һ�߹������Ҷ�ڷ��衣��ľ���õ���ζ��������Ұ
�޵�Х��ʹ�˲�����ԥ��ǰ���ĽŲ���
LONG );
        set("outdoors", "yixing");
        set("no_clean_up", 0);
        set("exits", ([
                "southwest" : __DIR__"tiandi",
                "east"      : __DIR__"shulin2",
        ]));
        set("coor/x", 250);
	set("coor/y", -1010);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}