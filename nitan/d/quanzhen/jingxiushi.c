// jingxiushi.c ������
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
������ȫ��̵��Ӿ��޲������ķ��䣬�����С������ʰ�ĸ�
�ɾ��������ζ��ڷŵ��������룬����һ�����������
LONG
        );
        set("exits", ([
                "east" : __DIR__"houshan",
                "south" : __DIR__"diziju",
                "west" : __DIR__"houtang3",
        ]));
        set("objects", ([
                CLASS_D("quanzhen")+"/liu" : 1,
        ]));

        set("coor/x", -2730);
        set("coor/y", 110);
        set("coor/z", 170);
        setup();
}

int valid_leave(object me, string dir)
{
        mapping fam;

        if (dir == "east" )
        {
                if( !(fam=query("family", me)) || fam["family_name"] != "ȫ���" )
                {
                        if(present("liu chuxuan", environment(me)) && living(present("liu chuxuan", environment(me))))
                        {
                                return notify_fail(
"������������ס����������Ǳ�����ʦ����֮�أ�" + RANK_D->query_respect(me) + "��
ֹ����\n");
                        }
                        else
                                return ::valid_leave(me, dir);
                }
                else
                        return ::valid_leave(me, dir);
        }
        else
                return ::valid_leave(me, dir);

}