// longsword.c ����

#include <weapon.h>
inherit WHIP;

void create()
{
        set_name("����", ({ "changbian", "bian" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long","����һ������ר�õĳ���,�����Ǳ�Ѱ����\n");
                set("value", 0);
                set("material", "leather");
                set("wield_msg", "$N��ৡ���һ������һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n�������䡣\n");
        }
        init_whip(100);
        setup();
}