// Code of ShenZhou
//  shedan.c
//  xuy 09/21/96
//  modified by ryu, 6/2/97

#include <ansi.h>
inherit ITEM;

nosave int used = 0;
void delete_benefit(object me);
void decay();
int cure_ob(string);
void init()
{
        if (used) return;
        remove_call_out("decay");
        call_out("decay", 120);
}

void create()
{
        set_name("���ߵ�", ({"shedan", "dan" }));
        set("unit", "ö");
        set("long", "һö����ɫ�����ߵ��������ȳ���\n");
        set("value", 20000);
                set("no_sell", 1);
        set("medicine", 1);
        set("no_cleanup", 1);
        setup();
}

int cure_ob(object me)
{
        if( !living(this_player()) ) return 0;
        if( used ) return 0;
        if( me->is_busy() )
                return notify_fail("����һ��������û����ɡ�\n");

        if ((int)me->query_condition("bonze_drug") > 0
        || (int)me->query_condition("mang_shedan") > 0){
        addn("eff_jingli", -1, me);
        addn("max_jingli", -1, me);
        message_vision(HIR "$N����һ���ߵ���ֻ����ͷ�ؽ��ᣬҡҡ������
ԭ����ʳ̫��̫�࣬ҩЧ�ʵ��䷴��\n" NOR, me);
        destruct(this_object());
        return 1;
        }        

        addn("food", 10, me);
        addn("water", 10, me);
        addn_temp("apply/con", 1, me);
        addn_temp("apply/str", 1, me);
        addn("eff_jingli", 1, me);
        addn("max_jingli", 1, me);
        addn("jingli", 100, me);
        me->apply_condition("bonze_drug", 30+me->query_condition("bonze_drug"));
        me->apply_condition("mang_shedan", 30);
        set_temp("dan_effect", 1, me);
        tell_object(me, MAG"���ſ�����һҧ���ߵ���Ƥ�㼴���ѣ��Ǿ����ڿ�֭���ȼ��༫������ҪŻ��������\n"
                        + "���Թ�Ƭ�̣���ֻ������˳��������Ŀ��������ˬ��������������\n"NOR);

        message("vision", MAG + me->name() + "����һ�����ߵ��������������ʤƽʱ��\n"NOR, 
                        environment(me), ({me}));
//        me->start_call_out( (: call_other, __FILE__, "delete_benefit", me :), 800);
        used = 1;
//        remove_call_out("decay");
//        move(VOID_OB);
        destruct(this_object());        
        return 1;
}

void decay()
{
        object where = environment(this_object());
        if ( interactive(where) )
                message("vision", MAG"�ߵ�ž��һ�����ˣ�Ū����һ�������ȳ���\n"NOR, 
                        where); 
        else
                message("vision", MAG"�ߵ�ž��һ�����ˣ�֭ˮ����һ�ء�\n"NOR,
                        where);
        destruct(this_object());
}

/*void delete_benefit(object me)
{
        addn_temp("apply/str", -1, me);
        addn_temp("apply/con", -1, me);
        destruct(this_object());
}
*/