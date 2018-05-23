// This program is a part of NT MudLIB
// hebi.c 全真剑之与玉女剑合璧

#include <ansi.h>

inherit F_SSERVER;

string name() { return "双剑合璧"; }

void check_fight(object me, object target, object victim, int amount);
private int remove_effect(object me, int amount);

int perform(object me, object target)
{
        int skill, skill1, skill2;
        object victim;
        object weapon;

        if( !victim ) victim = offensive_target(me);

        if( !victim || !victim->is_character() || !me->is_fighting(victim) )
                return notify_fail("双剑合璧只能对战斗中的对手使用。\n");

        if( !target )
                return notify_fail("你想与谁进行双剑合璧？\n");

        if( query("id", victim) == query("id", target) )
                return notify_fail("不能与敌人进行双剑合璧！\n");

        if( !target->is_fighting(victim) )
                return notify_fail("你想与其双剑合璧的对象并未与你的敌人搏斗！\n");

        if( target->query_skill_mapped("sword") != "yunv-jian" )
                return notify_fail("你想与其双剑合璧的对象所使用的并非玉女剑法！\n");

        if( !objectp(weapon=query_temp("weapon", target) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("你想与其双剑合璧的对象并没有用剑！\n");

        if( query_temp("hebi", me) )
                return notify_fail("你正与"+target->name()+"进行双剑合璧。\n");

        if( query_temp("hebi", target) )
                return notify_fail("你想与其双剑合璧的对象正与他人合壁战斗中，无暇与你合璧！\n");

        if( query_temp("yunv_hebi", target) )
                return notify_fail("你想与其双剑合璧的对象正独自运用玉女、全真剑法交错中，无力与你合璧！\n");

        skill1 = me->query_skill("sword");
        skill2 = target->query_skill("sword");
        skill =  ( skill1 + skill2 ) / 4;

        if( mapp(query("couple", me)) &&
            query("couple/couple_id", me) == query("id", target) )
        skill += skill/2;

        message_combatd(
        HIR "\n$N与$n突然间双剑一交，全真剑法与玉女剑法配合得天衣无缝，攻势及守势骤然大增！\n\n" NOR, me, target);

        addn_temp("apply/attack", skill/2, me);
        addn_temp("apply/damage", skill, me);
        addn_temp("apply/dodge", skill/2, me);
        addn_temp("apply/parry", skill/2, me);
        set_temp("hebi", 1, me);

        addn_temp("apply/attack", skill/2, target);
        addn_temp("apply/damage", skill, target);
        addn_temp("apply/parry", skill/2, target);
        addn_temp("apply/dodge", skill/2, target);
        set_temp("hebi", 1, target);

        addn_temp("apply/damage", skill, me);
        addn_temp("apply/damage", skill, target);
        COMBAT_D->do_attack(me,victim,query_temp("weapon", me));
        COMBAT_D->do_attack(target,victim,query_temp("weapon", target));
        COMBAT_D->do_attack(me,victim,query_temp("weapon", me));
        COMBAT_D->do_attack(target,victim,query_temp("weapon", target));
        COMBAT_D->do_attack(me,victim,query_temp("weapon", me));
        COMBAT_D->do_attack(target,victim,query_temp("weapon", target));

        addn_temp("apply/damage", -skill, me);
        addn("neili", -150, me);
        addn_temp("apply/damage", -skill, target);
        addn("neili", -150, target);


        me->start_call_out( (: call_other, __FILE__, "check_fight", me, target, victim, skill/2 :), 1);

        return 1;
}

void check_fight(object me, object target, object victim, int amount)
{
        object weapon;
        if( !query_temp("hebi", me) || !query_temp("hebi", target))return ;

       if( !living(victim) || !present(query("id",victim), environment(me)) || 
                query("qi", victim) <= 50 && me->is_fighting(victim) && target->is_fighting(victim) )
        {
                remove_effect(me, amount);
                remove_effect(target, amount);
                message_vision(HIY"$N与$n个自收招，相视一笑。\n\n"NOR, me, target);
                                return;
        }
        else if( (!present(query("id", victim),environment(me)) && target->is_fighting(victim) )
         || (!present(query("id", target),environment(me)) && me->is_fighting(victim))){
                remove_effect(me, amount);
                remove_effect(target, amount);
                tell_object(me, HIR"双剑合璧已然瓦解！\n"NOR);
                tell_object(target, HIR"双剑合璧已然瓦解！\n"NOR);
                tell_object(victim, HIY"双剑合璧已然瓦解，压力顿减，你不由然地松了一口气。\n"NOR);
                                return;
        }
         else if( !present(query("id", target),environment(me) )
        || !target->is_fighting() || !me->is_fighting() || !living(target)
        || !living(me) || target->is_ghost() || me->is_ghost() ) {
                remove_effect(me, amount);
        remove_effect(target, amount);
                tell_object(me, HIR"双剑合璧已然瓦解！\n"NOR);
                tell_object(target, HIR"双剑合璧已然瓦解！\n"NOR);
                tell_object(victim, HIY"双剑合璧已然瓦解，压力顿减，你不由然地松了一口气。\n"NOR);
                                return;
        }
        else if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword"){
                remove_effect(me, amount);
                remove_effect(target, amount);
                tell_object(me, HIR"双剑合璧已然瓦解！\n"NOR);
                tell_object(target, HIR"双剑合璧已然瓦解！\n"NOR);
                tell_object(victim, HIY"双剑合璧已然瓦解，压力顿减，你不由然地松了一口气。\n"NOR);
                                return;
        }
        else if( !objectp(weapon=query_temp("weapon", target) )
         || query("skill_type", weapon) != "sword"){
                remove_effect(me, amount);
                remove_effect(target, amount);
                tell_object(me, HIR"双剑合璧已然瓦解！\n"NOR);
                tell_object(target, HIR"双剑合璧已然瓦解！\n"NOR);
                tell_object(victim, HIY"双剑合璧已然瓦解，压力顿减，你不由然地松了一口气。\n"NOR);
                                return;
        }
        else if( me->query_skill_mapped("sword") != "quanzhen-jian")
        {
                remove_effect(me, amount);
                remove_effect(target,amount);
                message_vision(HIR"$N"HIR"突然剑招一转，不再使用全真剑法，双剑合璧顷刻瓦解。\n"NOR,me);
                return;
        }
        else if( target->query_skill_mapped("sword") != "yunv-jian")
        {
                remove_effect(me, amount);
                remove_effect(target,amount);
                message_vision(HIR"$N"HIR"突然剑招一转，不再使用玉女剑法，双剑合璧顷刻瓦解。\n"NOR,target);
                return;
        }
        call_out("check_fight", 1, me, target, victim, amount);
}

private int remove_effect(object me, int amount)
{
        addn_temp("apply/attack", -amount, me);
        addn_temp("apply/damage", -amount*2, me);
        addn_temp("apply/parry", -amount, me);
        addn_temp("apply/dodge", -amount, me);
        delete_temp("hebi", me);

        return 0;
}
