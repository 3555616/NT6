// chan.c 秋风尘法 缠字诀

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("牵制攻击只能对战斗中的对手使用。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真气不够！\n");

        if ((int)me->query_skill("qiufeng-chenfa", 1) < 80)
                return notify_fail("你秋风尘法的修为不够，不能使用缠字诀！\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

        msg = CYN "$N" CYN "使出秋风尘法「缠」字诀，拂尘连挥企图把$n"
              CYN "的全身缠住。\n" NOR;

        me->start_busy(random(1));
        if( random(query("combat_exp", me)/100)>query("combat_exp", target)/200 )
        {
                msg += CYN "结果$p" CYN "被$P" CYN "攻了个措手不及。\n" NOR;
                target->start_busy( (int)me->query_skill("whip") / 28 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的企图，并没有上当。\n" NOR;
                me->start_busy(4);
        }
        message_combatd(msg, me, target);
        addn("neili", -100, me);
        return 1;
}