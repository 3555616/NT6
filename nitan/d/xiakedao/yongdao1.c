// yongdao1.c ��


inherit ROOM;

void create()
{
        set("short", "��");
        set("long", @LONG
����һ���������������ߵ����͵ƣ������䰵��ȴҲ�ɱ��
·��������Լ�������ٲ���¡¡ˮ��������ˮ���ɽ�����������ʪ
��
LONG );
        set("exits", ([
               "south" : __DIR__"yongdao2",
               "out" : __DIR__"pubu",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3100);
        set("coor/y", -22060);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}