//JMQSHULIN2.C

inherit ROOM;

void create()
{
        set("short", "��ľ������");
        set("long", @LONG
����ǰ��Ȼһ���������У�ֻ������ǰ�󣬵�����������ǵص�
��֪���ľ����������ɰأ�������ɼ������һ����ʵ��֦Ҷ��һ��
���ɡ��������գ�������ա����ƺ���ʧ�˷�����ûͷ��Ӭ�㵽
���Ҵ���
LONG );
        set("exits", ([
                "east" : __DIR__"jmqshulin2",
                "west" :__DIR__"jmqshulin1",
                "north" : __DIR__"jmqshulin3",
                "south" : __DIR__"jmqshulin2",
        ]));
        set("objects", ([
                __DIR__"obj/pine" : random(5),
        ]));
        set("outdoors", "mingjiao");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}