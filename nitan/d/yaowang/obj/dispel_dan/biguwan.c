#include <ansi.h>
inherit ITEM;

void create()
{
     set_name(HIG"�ٹ���"NOR, ({ "bigu wan", "wan" })); set("unit", "��");
        set("long", "һ�ű���ɫ��ҩ�裬��\n");
        set_weight(1000);
        set("yaowang", 1);
        set("no_get", 1);
        set("no_give", 1);
        set("no_sell", 1);
        set("no_drop", 1);
        set("value", 0);
        setup();
}

void init()
{
        object me, ob;
        int obj;

        me = this_player();
        ob = this_object();
        obj = (int)me->query_skill("medical",1);

        if( query_temp("liandan", me) == 1
                 && query("value", ob) == 0 )
        {
                if(obj<100) {
                        set("value", (random(2000)+2000), ob);}
                if(obj>=100 && obj<150) {
                        set("value", (random(4000)+4000), ob);}
                if(obj>=150 && obj<200) {
                        set("value", (random(8000)+7000), ob);}
                if(obj>=200 && obj<250) {
                        set("value", (random(15000)+15000), ob);}
                if(obj>=250) {
                        set("value", (random(20000)+30000), ob);
                        }
        }
        
        add_action("do_eat", "eat");
        add_action("do_eat", "chi");
}

int do_eat(string arg)
{
        object me = this_player();
        int i=query("value", this_object())/10;

        if (!id(arg))
                return notify_fail("��Ҫ��ʲô��\n");

        if (me->is_busy() )
                return notify_fail("�𼱣������ԣ�С�ı�ҭ���ˡ�\n");

        if( query("food", me) >= ((query("str", me)*10)+100 )
                 && query("water", me) >= ((query("str", me)*10)+100) )
                return notify_fail("���ƺ���������\n");

        addn("food", i, me);
        addn("water", i, me);
//      me->addn("neili", i);
        message_vision(HIG"$N����һ�űٹ��裬�پ�һ������֮���Ӹ�������\n"NOR, me);
        destruct(this_object());
        return 1;
}
