// lifeheal.c
// Last Modified by winder on May. 29 2001

#include <ansi.h>

int exert(object me, object target)
{
  if ( userp(me) && !wizardp(me) && 
  !query("perform/lifeheal", me) && 
  !query("can_perform/zhanzhuang-gong/lifeheal", me) && 
  !query_temp("murong/xingyi", me) )
   return notify_fail("����ʹ�õ��ڹ���û�����ֹ��ܡ�");

        if( !target || !target->is_character() || target == me )
                return notify_fail("��Ҫ������Ϊ˭���ˣ�\n");

        if( me->is_fighting() || target->is_fighting())
                return notify_fail("ս�����޷��˹����ˣ�\n");

        notify_fail("������Ҫץ���ˣ���ʲô���֣�\n");
        if (!userp(target) && !target->accept_hit(me)) return 0;

        if( me->is_busy() )
                return notify_fail("��������æ���أ����п��˹���\n");

        if( target->is_busy())
                return notify_fail(target->name()+"������æ���أ�\n");

        if( (int)me->query_skill("zhanzhuang-gong", 1) < 20 )
                return notify_fail("���վ׮����Ϊ������\n");

        if( query("max_neili", me)<300 )
                return notify_fail("���������Ϊ������\n");

        if( query("neili", me)<150 )
                return notify_fail("�������������\n");
/*
        if( query("eff_qi", target) >= query("max_qi", target) )
                return notify_fail( target->name() + "ֻ�����ˣ�û�����ˣ�������������������ˣ�\n");
*/
        if( query("eff_qi", target)<query("max_qi", target)/5 )
                return notify_fail( target->name() + "�Ѿ����˹��أ����ܲ�����������𵴣�\n");

        message_combatd( HIY "$N�������������ڹ�������������$n���ģ������ؽ���������$n����....\n\n���˲��ã�$N��ͷ��ð������ĺ��飬$n�³�һ����Ѫ����ɫ������������ˡ�\n" NOR, me, target );

        target->receive_curing("qi", 10 + (int)me->query_skill("force")/3 );
        addn("qi", 10+me->query_skill("force")/3, target);
        if( query("qi", target)>query("eff_qi", target) )
                set("qi",query("eff_qi",  target), target);

        addn("neili", -100, me);
        me->start_busy(1);
        target->start_busy(2);
        if ( userp(target)) target->start_busy(2);

        return 1;
}
int help(object me)
{
        write(WHT"\nվ׮��֮���ƣ�"NOR"\n");
        write(@HELP

        ʹ�ù�Ч��
                Ϊ��������

        ����Ҫ��
                վ׮��20��
                ����300
HELP
        );
        return 1;
}