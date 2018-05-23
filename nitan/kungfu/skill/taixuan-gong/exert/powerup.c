#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill, amount;

        if (target != me)
                return notify_fail("你只能用太玄功来提升自己的战斗力。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的内力不够。\n");

        if( query_temp("powerup", me) )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_combatd(HIW "$N" HIW "默运太玄功，将内力积聚于周身经脉，顿觉"
                        "全身浑然有力，坚不可摧。\n" NOR, me);
        //打通任督二脉的效果
        
        if( query("breakup", me) )
        {    
                addn_temp("apply/attack", skill*2/3, me);
                addn_temp("apply/defense", skill*2/3, me);
                set_temp("powerup", 1, me);
        }
        else
        {
                addn_temp("apply/attack", skill/3, me);
                addn_temp("apply/defense", skill/2, me);
                set_temp("powerup", 1, me);
        }
        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("powerup", me) )
        {
                if( query("breakup", me) )
                {
                        addn_temp("apply/attack", -(amount*2/3), me);
                        addn_temp("apply/defense", -(amount*2/3), me);
                }
                else
                {
                        addn_temp("apply/attack", -(amount/3), me);
                        addn_temp("apply/defense", -(amount/2), me);
                }
                delete_temp("powerup", me);
                tell_object(me, "你的太玄功运行完毕，将内力收回丹田。\n");
        }

}

