inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIM "�ֻء��һ�" NOR, ({"lunhui liehuo","lunhui","liehuo" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                 set("long", HIM "�ֻ�֮�ࡤ�һ������\n" NOR);
                set("unit", "��");
                set("value", 5000);
                set("enchase/name", "�ֻء��һ�");
                set("enchase/point", 100);
                  set("enchase/type", "all");
                set("enchase/cur_firm", 100);
                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}

