// Code of JHSH
// jinglisuck.c

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int exert(object me, object target)
{
        int sp, dp, jl;

        if( !target ) target = offensive_target(me);

        if( !objectp(target) || target == me)
                return notify_fail("你要吸取谁的精力？\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("这里不能战斗，你不可以使用化功大法吸人的精力。\n");

        if( query_temp("sucked", me) )
                return notify_fail("你刚刚吸取过精力！\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("必须空手才能够吸取别人的精力！\n");

        if( !me->is_fighting() || !target->is_fighting() || !living(target) )
                return notify_fail("你必须在战斗中才能吸取对方的精力！\n");

        if( (int)me->query_skill("huagong-dafa",1) < 90 )
                return notify_fail("你的化功大法功力不够，不能吸取对方的内力！\n");

        if( query("neili", me)<300 )
                return notify_fail("你的内力不够，不能使用化功大法。\n");

        if( query("jingli", me)<100 )
                return notify_fail("你的精力不够，不能使用化功大法。\n");

        if( query("jingli", me) >= query("max_jingli", me)*5/2 )
                return notify_fail("你吸取的精力充塞全身，无法再吸取精力！\n");

        if( query("max_jingli", target) <= 0 )
                return notify_fail( target->name() +
                        "没有任何精力！\n");

        if( query("jingli", target)<query("max_jingli", target)/10 )
                return notify_fail( target->name() + "已经精力涣散，你已经无法从他体内吸取任何精力了！\n");


        message_vision(HIR "$N朝$n微微一笑，突然翻掌变爪，扣向$n的手腕！\n\n" NOR, me, target );

        if( !target->is_killing(me) ) target->kill_ob(me);

        sp=me->query_skill("force")+me->query_skill("dodge")+query("kar", me)*50;
        dp=target->query_skill("force")+target->query_skill("dodge")+query("kar", target)*50;
        sp+=query("combat_exp", me)/1000;
        dp+=query("combat_exp", target)/1000;

        set_temp("sucked", 1, me);

        if( random(sp+dp) > dp )
        {
                tell_object(target, HIR "你腕内会宗穴被" + me->name() + "突然扣住，动弹不得，只觉精力如洪水般自会宗穴奔腾而出！\n" NOR);
                tell_object(me, HIG "你觉得" + target->name() + "的精力自手掌源源不绝地流了进来。\n" NOR);

                jl = (1+random(3)) * (int)me->query_skill("huagong-dafa", 1)/2;
                if( query("jingli", target)>jl )
                {
                        addn("jingli", -1*jl, target);
                        addn("jingli", jl, me);
                }else{
                        addn("jingli", jl/2, me);
                        addn("jingli", -jl/2, target);
                        }
                if( query("combat_exp", target) >= query("combat_exp", me)/2){
                        addn("potential", 1, me);
                        addn("combat_exp", 1, me);
                        if( query("potential", me)>me->query_potential_limit() )
                        set("potential", me->query_potential_limit(), me);
                }

                me->start_busy(1+random(3));
                target->start_busy(1+random(3));
                addn("neili", -me->query_skill("huagong-dafa",1)/6, me);
                addn("jingli", -5, me);

                call_out("del_sucked", 2, me);
        }
        else
        {
                message_vision(HIY "可是$p看破了$P的企图，没让$P扣住手腕。\n" NOR, me, target);
                addn("jingli", -20, me);
                me->start_busy(2+random(2));
                call_out("del_sucked", 5, me);
        }

        return 1;
}

void del_sucked(object me)
{
        if( query_temp("sucked", me) )
        delete_temp("sucked", me);
}