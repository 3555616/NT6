// This program is a part of NITAN MudLIB
// mingyue-blade.c (�������µ�)

#include <ansi.h>;
inherit SKILL;

mapping *action = ({
([      "action" : "$N���γ��ȣ�����$w�͵�һת��ʩչ�������ĵ�����һ�С��ٱ������¡���$n��$l����ȥ��",
        "force"  : 120,
        "attack" : 35,
        "dodge"  : -30,
        "parry"  : -12,
        "lvl"    : 0,
        "damage" : 240,
        "damage_type" : "����",
        "skill_name"  : "�ٱ�������",
]),
([      "action" : "$N����һת������һ��Բ����ͻȻ��������ʩչ�������̵�����������һ�С���Ӱ�����ˡ���",
        "force"  : 160,
        "attack" : 42,
        "dodge"  : -40,
        "parry"  : -15,
        "lvl"    : 40,
        "damage" : 250,
        "damage_type" : "����",
        "skill_name"  : "��Ӱ������",
]),
([      "action" : "$N����ͻȻ������ר����·����Ȼ����������·����ֻ��һ�С����Ĺ���ʱ����$n��$l��ȥ��",
        "force"  : 185,
        "attack" : 51,
        "dodge"  : -45,
        "parry"  : -17,
        "lvl"    : 60,
        "damage" : 260,
        "damage_type" : "����",
        "skill_name"  : "���Ĺ���ʱ",
]),
([      "action" : "$N���ڵ������ڲ��ϱ仯���������ƣ�ͻȻһ�С����������ڡ�ն��$n��$l!",
        "force"  : 220,
        "attack" : 55,
        "dodge"  : -55,
        "parry"  : -21,
        "lvl"    : 80,
        "damage" : 270,
        "damage_type" : "����",
        "skill_name"  : "����������",
]),
});

int valid_enable(string usage){ return usage == "blade" || usage == "parry";}

int valid_learn(object me)
{
        if( query("max_neili", me)<2000 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("����ڹ����̫ǳ��\n");

        if ((int)me->query_skill("blade", 1) < 140)
                return notify_fail("��Ļ����������������������������µ���\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("mingyue-blade", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷�����������������µ���\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("mingyue-blade", 1);
        if (random(me->query_skill("blade")) > 180
        &&  me->query_skill("force") > 200
         && query("neili", me)>1000
         && objectp(weapon=query_temp("weapon", me)) )
        {
                addn("neili", -300, me);
                return ([
                        "action": "$Nʹ��һ��" HIM "������������˼�᡹" NOR "��$w������������㣬���綬ҹ���������ǵ�ɨ��$n",
                        "damage": 500,
                        "dodge" : -100,
                        "parry" : -150,
                        "attack": 150,
                        "damage_type": "����"
                ]);
        }
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("qi", me)<80 )
                return notify_fail("��������������������������µ���\n");

        if( query("neili", me)<120 )
                return notify_fail("��������������������������µ���\n");

        me->receive_damage("qi", 64);
        addn("neili", -84, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        object weapon;
        int lvl = me->query_skill("mingyue-blade", 1);
        weapon=query_temp("weapon", me);

        if (lvl < 180 || lvl / 2 + random(lvl) < (int)victim->query_skill("dodge", 1) ||
            query("neili", me)<500 ||
            me->query_skill("dodge", 1) < 180 ||
            me->query_skill("force", 1) < 150 ||
            victim->is_busy() )
                 return 0;

        message_vision(HIW "\n$N" HIW "����" + weapon->name() + HIW "��Ȼ��ת������ͻ"
                       "�֣�ɲ�Ǽ��ѽ�$n" HIW "�Ƶ����޿��ˡ�\n" NOR, me, victim);
        addn("neili", -80, me);
        victim->start_busy(2 + random(lvl / 60));
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"mingyue-blade/" + action;
}