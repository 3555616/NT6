// heshouwu.c ������

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(WHT"������"NOR, ({"he shouwu"}));
        set_weight(800);
        set("vegetable", 4);
        set("nostrum", 1);
        set("unit", "֧");
        set("long", "����һ֧�ѳ����εĺ����ڣ�����������ҩ��\n");
        set("pour_type", "1");
        setup();
}

int do_eat(string arg)
{
        object me = this_player();

        if(!id(arg)) return notify_fail("��Ҫ��ʲô��\n");
        if(!present(this_object(), me))
                return notify_fail("��Ҫ��ʲô��\n");
        if( me->is_busy() )
                return notify_fail("�𼱣������ԣ�С�ı�ҭ���ˡ�\n");

        if( query("max_jingli", me) <= 200 )
        {
                write("�������һ֧�����ڣ�ֻ���þ�����֮����\n");
                addn("max_jingli", 2, me);
                addn("jingli", 2, me);
        }
        else {
                write("�������һ֧�����ڣ����Ǻ���ûʲô�á�\n");
        }
        destruct(this_object());
        return 1;
}