inherit SKILL;

mapping *action = ({
([      "action" : "$Nһ�С��ǹ���á���˫ȭ����, ����$n��$l",
        "force"  : 120,
        "dodge"  : 10,
        "damage" : 2,
        "lvl"    : 0,
        "skill_name" : "�ǹ����",
        "damage_type" : "����"
]),
([      "action" : "$Nһ�С�ҡ����λ����һȭ��ɨ��������磬����$n��$l",
        "force"  : 140,
        "dodge"  : 12,
        "damage" : 5,
        "lvl"    : 20,
        "skill_name" : "ҡ����λ",
        "damage_type" : "����"
]),
([      "action" : "$N��Ӱ��Ʈ��������΢Ц��һ�С��ǹ����ա�����ȭ��������$n��$l",
        "force"  : 150,
        "dodge"  : 16,
        "damage" : 15,
        "lvl"    : 40,
        "skill_name" : "�ǹ�����",
        "damage_type" : "����"
]),
([      "action" : "$Nһ�С�Ⱥ����˸����˫ȭ�������ϣ�$nֻ��������$N��ȭӰ",
        "force"  : 160,
        "dodge"  : 18,
        "damage" : 22,
        "lvl"    : 60,
        "skill_name" : "Ⱥ����˸",
        "damage_type" : "����"
]),
([      "action" : "$Nʩչ����ǧ���򻯡�����$nһת���������ߣ�ȭ����磬��ס�Ļ���$n��",
        "force"  : 170,
        "dodge"  : 21,
        "damage" : 26,
        "lvl"    : 80,
        "skill_name" : "ǧ����",
        "damage_type" : "����"
]),
([      "action" : "ֻ��$NͻȻ�Ϳ��������ѵ�$n��ǰ����ȭ������Ѹ����ף�"
                   "һ�С������꡹����$n��ǰ��",
        "force"  : 220,
        "dodge"  : 22,
        "damage" : 30,
        "lvl"    : 100,
        "skill_name" : "��ʯ�ɽ�",
        "damage_type" : "����"
]),
([      "action" : "$Nһ�С��������ɡ���ȭӰ������������һ�빥��$n��",
        "force"  : 250,
        "dodge"  : 25,
        "damage" : 35,
        "lvl"    : 120,
        "skill_name" : "��������",
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("������ȭ��������֡�\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("����ڹ���򲻹����޷�������ȭ����\n");

        if( query("max_neili", me)<120 )
                return notify_fail("�������̫�����޷�������ȭ����\n");

        if ((int)me->query_skill("cuff", 1) < 20)
                return notify_fail("��Ļ���ȭ�����̫ǳ��\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("qixing-quan", 1))
                return notify_fail("��Ļ���ȭ��ˮƽ���ޣ��޷��������������ȭ����\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("qixing-quan",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<50 )
                return notify_fail("�������̫���ˡ�\n");

        if( query("neili", me)<30 )
                return notify_fail("�����������������ȭ����\n");

        me->receive_damage("qi", 36);
        addn("neili", -18, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"qixing-quan/" + action;
}