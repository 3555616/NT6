#include <ansi.h>

inherit COMBINED_ITEM;
#include "meat.h"

void create()
{
        set_name(NOR + WHT "����" NOR, ({ "gou rou", "gou", "rou" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "����һ��ɢ�����������Ĺ��⡣\n" NOR);
                set("base_unit", "��");
                set("base_value", 40);
        }
        setup();
        set_amount(1);
}