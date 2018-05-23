#include <ansi.h>

string name() { return HIY "一苇渡江" NOR; }

inherit F_SSERVER;

void remove_effect(object me, int amount, int amount1);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int count, skill;

        if( query_temp("dujiang", me) )
                return notify_fail("你已经运起" + name() + "了。\n");

        if ((int)me->query_skill("shaolin-shenfa", 1) < 150)
                return notify_fail("你的少林身法等级不够，难以施展" + name() + "。\n");

        if ((int)me->query_dex() < 33)
                return notify_fail("你的身法不够，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force", 1) < 150)
                return notify_fail("你的内功火候不够，难以施展" + name() + "。\n");

        if ((int)me->query_skill("dodge", 1) < 150)
                return notify_fail("你的轻功修为不够，难以施展" + name() + "。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的内力修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<250 )
                return notify_fail("你此时的内力不足，难以施展" + name() + "。\n");

        msg = HIY "$N" HIY "足尖轻点地面，施展一苇渡江，凌空跃起，身形顿时变得轻松自如。\n\n" NOR;

        message_combatd(msg, me, target);
        skill = me->query_skill("shaolin-shenfa", 1);

        count = skill / 50;

        if (me->is_fighting())
                me->start_busy(2);

        addn_temp("dex", count, me);
        set_temp("dujiang", 1, me);
        me->start_call_out((: call_other,  __FILE__, "remove_effect", me, count :), skill / 2);

        addn("neili", -200, me);
        return 1;
}

void remove_effect(object me, int amount, int amount1)
{
        if( query_temp("dujiang", me) )
        {
                addn_temp("dex", -amount, me);
                delete_temp("dujiang", me);
                tell_object(me, "你的" + name() + "运行完毕，将内力收回丹田。\n");
        }
}
