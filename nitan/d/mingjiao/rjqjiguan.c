//RJQJIGUAN.C

inherit ROOM;

void create()
{
        set("short", "�ܵ�");
        set("long", @LONG
������һ���ص��ľ�ͷ��ʯǽ֮��Ƕ����յ�͵ƣ�������������
����ȥ���ڰ�����Щ������
LONG );
        set("exits", ([
                "north" : __DIR__"rjqmishi",
//                "down" : __DIR__"rjqmenlou1",
        ]));
//        set("outdoors", "mingjiao");
        set("no_clean_up", 0);
        setup();
//        replace_program(ROOM);
}

void init()
{
        object me;
        int q,d,eq;
        me=this_player();
        q=query("max_qi", me);
        d=(int)me->query_skill("dodge");
        if( (query("mingjiao", me) != 1) && (d <= 100) )
        {
                message_vision("$Nֻ���������м�������Ѫ��������������ɴ��һ��\n",me);
                eq=query("qi", me)-q+(q*d/100);
                set("qi", eq, me);
                set("eff_qi", eq, me);
        }
        if (eq<=0) me->die();
}