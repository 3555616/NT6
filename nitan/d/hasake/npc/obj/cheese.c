#include <ansi.h>

inherit ITEM;

void init()
{
       add_action("do_drink", "drink");
}


void create()
{
        set_name(HIW "����" NOR, ({"cheese"}));
        set_weight(700);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "һ������������ң��������ҾͲ����������ԭ��\n");
                set("unit", "��");
               set("value", 5000);
             }
}

int do_drink(string arg)
{        
        object me = this_player();
        if (!living(me)) return notify_fail("�뵱����\n");
        if (!id(arg)) return 0;
        if( query("water", me)<me->max_water_capacity()){
        message_vision(HIG"$N��µ��µ�غ���һ��"+query("name", this_object())+HIG"��Ĩ��Ĩ�졣\n"NOR,me);
        if( query("food", me)<me->max_food_capacity() )
           addn("food", 100, me);
        addn("water", 100, me);
               destruct(this_object());       
        return 1;
        }
}
