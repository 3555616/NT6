#include "herb.h"

void create()
{
        set_name(NOR + WHT "����" NOR, ({ "fu zi", "fu", "zi", "herb_fuzi" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "�����ǳ�������ҩҩ�ġ�\n" NOR);
                set("base_unit", "��");
                set("base_value", 1000);
                set("base_weight", 20);
                set("no_sell", "ҩ���ȵĵ�ҩ�ǳ�����������ͨ��ҩ��ض��а���"); 
                set("yaowang", 1); 
        }
        setup();
}