// bicanfeng.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(RED "彩虹菌" NOR, ({"caihong jun", "jun"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一袋剧毒的毒药，如果用来炼暗器有见血封喉之效。\n");
                set("unit", "袋");
                set("value", 20000);
                set("poison_type", "yaowang_poison");
                set("can_pour", 1);
                set("can_daub", 1);
                set("can_drug", 1);
                set("poison", ([
                        "level" : 200,
                        "id"    : "yaowang",
                        "name"  : "剧毒",
                        "duration": 15,
                ]));
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        message_vision("$N仰头把一小袋" + name() + "都咽了下去。\n", me);
        set_temp("die_reason", "吞了彩虹菌，莫名其妙的见了阎王", me);
        me->die();
        destruct(this_object());
        return 1;
}
