// 太極劍意

#include <ansi.h>
#include <combat.h>

string name() { return HIM "太極劍意" NOR; }

inherit F_SSERVER;

string attack1(object me, object target, int damage);
string attack2(object me, object target, int damage);

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int ap, dp, fp;
        int xy;

        if( !query("reborn/times", me) )
                return notify_fail("你尚未转世重生，无法使用太極劍意！\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在战斗中对对手使用。\n");

        if( me->is_busy() )
                return notify_fail("你正忙着呢。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对！\n");

        if ((int)me->query_skill("taiji-jian", 1) < 1000)
                return notify_fail("你太极剑法不够娴熟，无法施展" + name() + "。\n");

        if( query("neili", me)<2000 )
                return notify_fail("你现在真气不够，无法施展" + name() + "！\n");

        if (me->query_skill_mapped("sword") != "taiji-jian")
                return notify_fail("你没有激发太极剑法，无法使用" + name() + "。\n");

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        addn("neili", -1000, me);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");
        fp = defense_power(target, "parry");

        xy = me->query_skill("tianwei-zhengqi", 1);

        ap = ap + ap*(xy/100<10?10:xy/100)/100;

        damage = damage_power(me, "sword");
        damage = damage + damage*(xy/50<10?10:xy/50)/100;
        damage *= 3;

        //target->start_busy(10);

        message_combatd(sort_msg(HIY "\n$N" HIY "身形一转，手中" + weapon->name() + HIY "轻灵而出，犹如碧"
                     "波荡漾，蜿蜒起伏，形态飘逸潇洒之极，颇具" HIC "太極" HIY "之意" HIY "……\n" NOR), me);

        msg = HIM "$N" HIM "将内力灌输于剑上，呼的一剑抖出，空气几欲凝固。\n" NOR;
        if (ap + random(ap / 2) < dp)
                msg += CYN "$n" CYN "眼明手快，斜身闪开。\n" NOR;
        else
        {

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 200 + (xy / 2 + random(xy / 2)>500?500:xy / 2 + random(xy / 2)),
                                           (: attack1, me, target, damage :));
        }

        msg += HIM "\n$N" HIM "轻摇" + weapon->name() + HIM "，霎时，剑气纵横，流光乍现，令人目不暇接。\n" NOR;
        if (ap + random(ap / 2) < fp)
                msg += CYN "$n" CYN "倒吸一口凉气，飞身一跳，狼狈地躲过这招。\n" NOR;
        else
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 200 + (xy / 2 + random(xy / 2)>500?500:xy / 2 + random(xy / 2)),
                                           (: attack2, me, target, damage :));
        }

        me->start_busy(2 + random(3));
        message_combatd(msg, me, target);

        return 1;
}


string attack1(object me, object target, int damage)
{
        string msg;

        msg = HIR "$N" HIR "剑法飘逸无比，令$n" HIR "毫无反应，"
              "竟呆立当场，不守不攻。\n" NOR;

        // if( random(2) != 1 ) return msg;
        //if( target->query_condition("no_perform") ) return msg;

        target->apply_condition("no_perform", 5);

        msg += WHT "$n" WHT "感到气脉受损，全身力道竟似涣散了一般，全然无法控制。\n" NOR;

        return msg;
}

void remove_effect(object target)
{
        if( !objectp(target) ) return;

        addn_temp("apply/avoid_busy", 90, target);
        addn_temp("apply/reduce_busy", 36, target);
        addn_temp("apply/avoid_weak", 90, target);
        addn_temp("apply/avoid_locked", 90, target);
        tell_object(target, HIR "你的忽视虚弱，忽视忙乱、忽视绝招冷冻能力终于解除封印。\n" NOR);
}

string attack2(object me, object target, int damage)
{
        string msg;

        msg = HIR "$N" HIR "剑法越发凌厉，将$n" HIR "逼得接连后退，"
              "剑光一闪，令$n" HIR "再也无从躲避。\n" NOR;

        if( random(2) != 1 ) return msg;

        addn_temp("apply/avoid_busy", -90, target);
        addn_temp("apply/reduce_busy", -36, target);
        addn_temp("apply/avoid_weak", -90, target);
        addn_temp("apply/avoid_locked", -90, target);
        call_out("remove_effect", 30, target);

        msg += WHT "$n" WHT "感到自身的忽视虚弱，忽视忙乱、忽视绝招冷冻能力被封印。\n" NOR;

        return msg;
}
