// danhuangshayi.c ����ɴ��

#include <ansi.h>
#include <armor.h>
inherit CLOTH;
void create()
{
        set_name( YEL "����ɴ��" NOR, ({ "danhuang shayi", "cloth" }) );
        set_weight(800);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 600);
                set("armor_prop/armor", 1);
                set("material", "cloth");
                set("female_only", 1);
        }
        setup();
}