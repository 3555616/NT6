// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me) 
                return notify_fail("你只能用混天气功来提升自己的战斗力。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的内力不够。\n");
                
        if( query_temp("powerup", me) )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_combatd(
                HIR "$N微一凝神，运起混天气功，全身骨节发出一阵爆豆般的声响ⅵ\n" NOR, me);

        addn_temp("apply/attack", skill*2/5, me);
        set_temp("powerup", 1, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill * 2 / 5 :),  skill);

        if (me->is_fighting() && ! me->is_busy()) 
                me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -amount, me);
                delete_temp("powerup", me);
                tell_object(me, HIY "你的混天气功运行完毕，将内力收回丹田。\n" NOR);
        }
}
