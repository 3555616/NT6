// qin.c
#include <weapon.h>
#include <ansi.h>
inherit SWORD;
void create()
{
        set_name(HIW"��������"NOR, ({ "yao qin", "qin"}));
        set("taskobj", 1);
        set_weight(6000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ���ð������ɵ����١�\n");
                set("value", 0);
                set("material", "steel");
                set("wield_msg", "$N�ӱ���$n�������С�\n");
                set("unwield_msg", "$N�����е�$n�Żر���\n");
        }
        setup();
}