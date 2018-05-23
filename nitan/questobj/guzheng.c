// guzheng.c 古筝

#include <ansi.h>;

inherit ITEM;

void create()
{
        set_name(HIG"古筝"NOR, ({ "gu zheng", "zheng", "qin" }));
        set_weight(2000);
        set("taskobj", 1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "张");
                set("long",
                HIG"这是一张做工十分考究的古筝，古香古色，音质极好。\n"NOR);
                set("value", 0);
                set("material", "steel");
        }
}
