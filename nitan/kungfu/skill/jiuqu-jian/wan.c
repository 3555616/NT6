#include <ansi.h>
#include <combat.h>

#define WAN "「" HIM "九曲十八弯" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int i, attack_time;

        if( userp(me) && !query("can_perform/jiuqu-jian/wan", me) )
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(WAN "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不对，难以施展" WAN "。\n");

        if ((int)me->query_skill("jiuqu-jian", 1) < 100)
                return notify_fail("你的九曲剑法不够娴熟，难以施展" WAN "。\n");

        if (me->query_skill_mapped("sword") != "jiuqu-jian")
                return notify_fail("你没有激发九曲剑法，难以施展" WAN "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你目前的真气不够，难以施展" WAN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "\n$N" HIW "蓦的一声清啸，施出绝学「" HIM "九曲十八弯"
              HIW "」，手中" + weapon->name() + HIW "呼呼作响。霎时间"
              "九曲剑法剑招连绵涌出，此起彼伏，剑气笼罩$n" HIW "全身。\n" NOR;

        message_sort(msg, me, target);

        attack_time = 4;

        ap = me->query_skill("sword");
        dp = target->query_skill("dodge");

        attack_time += random(ap / 40);

        if (attack_time > 8)
                attack_time = 8;

        addn("neili", -attack_time*20, me);

        if (ap / 2 + random(ap) > dp)
        {
                msg = HIY "$n" HIY "见$P" HIY "剑势汹涌，寒意顿生，竟"
                      "被逼得连连后退，狼狈不已。\n" NOR;
        } else
        {
                msg = HIC "$n" HIC "见$N" HIC "这几剑来势迅猛无比，毫"
                      "无破绽，只得小心应付。\n" NOR;
        }

        message_vision(msg, me, target);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1 + random(attack_time));

        return 1;
}