//bing1.c һ���
inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name(HIG "һ���" NOR, ({"bing1", "yixiubing"}));
        set("unit", "��");
        set("long", "����һ������һ�����\n");
        set("no_get", 1);
        set("no_drop", 1);
        set("no_put", 1);
        set("no_beg", 1);
        set("no_steal", 1);
        setup();
}

int do_eat(string arg)
{
        object me=this_player();
        if (!id(arg)) return notify_fail("��Ҫ��ʲô��\n");
        if( query("owner") != query("id", me) )
        {
                write(HIR"��ֻ�ܳ��Ը�Ӯ���ı���\n"NOR);
                return 1;
        }
        if(arg=="bing1"||arg=="yixiubing")
        {
                message_vision(HIY "$N�������ڳ���һ��$n��\n" NOR, this_player(), this_object());
                addn("combat_exp", 68, me);
                addn("potential", 18, me);
                destruct(this_object());
        }
        return 1;
}
void owner_is_killed()
{
        destruct(this_object());
}