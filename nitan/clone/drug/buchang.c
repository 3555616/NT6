// Code of ShenZhou

#include <ansi.h>

inherit ITEM;

void init();

void create()
{
        set_name(HIW "�Ҹ�ɢ" NOR, ({"xingfu san", "san"}));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 50);
                set("medicine", 1);
                set("no_sell", 1);
                set("no_get", 1);
                set("no_steal", 1);
                set("no_drop", 1);
                set("no_sell", 1);
                set("only_do_effect", 1);
        }

        setup();
}

int do_effect(object me)
{
        addn("shenzhou/pts", 40, me);
        message_vision(HIG "$N������һЩ�Ҹ�ɢ�����з�Թ���һ�ʹ���! \n" NOR, me); 

        destruct(this_object());
        return 1;
}