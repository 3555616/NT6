// baiyunwan.c �����ܵ���

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIW"�����ܵ���"NOR, ({"baiyun xiongdanwan", "wan"}));
        set("unit", "��");
        set("vegetable", 26);
        set("nostrum", 92);
        set("level", 40);
        set("pour_type", "1");
        set("long", "����һ�������ܵ��裬ѩ��͸����\n");
        setup();
}

int do_eat(string arg)
{
        object me=this_player();

        if(!id(arg)) return notify_fail("��Ҫ��ʲô��\n");
        if(!present(this_object(), me))
                return notify_fail("��Ҫ��ʲô��\n");
        if( me->is_busy() )
                return notify_fail("�𼱣������ԣ�С�ı�ҭ���ˡ�\n");

        if( query("eff_jing", me) >= query("max_jing", me) && 
                query("eff_qi", me) >= query("max_qi", me) && 
                query("neili", me) >= query("max_neili", me) )
        {
                message_vision("$Nû��Ҫ�԰����ܵ��衣\n",me);
        }
        else
        {
                set("eff_jing",query("max_jing",  me), me);
                set("jing",query("eff_jing",  me), me);
                set("eff_qi",query("max_qi",  me), me);
                set("qi",query("eff_qi",  me), me);
                set("neili",query("max_neili",  me), me);
                message_vision("$N����һ�������ܵ��裬ֻ���������Ⱥ����ģ�ʮ����̹��\n",me);
                destruct(this_object());
        }
        return 1;
}