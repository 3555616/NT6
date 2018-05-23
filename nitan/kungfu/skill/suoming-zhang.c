inherit SKILL;

mapping *action = ({
([      "action": "$N΢һ������ʹ����������������$wЯ���Ŵ̶�����������ɨ��$n�Ľ���",
        "force" : 100,
        "attack": 10,
        "dodge" : -5,
        "parry" : 9,
        "damage": 15,
        "damage_type":"����"
]),
([      "action": "$N������ס�ȶˣ�һ�С��л굿�ǡ�����һ��������ƾ���Ե���$n�ļ�ͷ",
        "force" : 110,
        "attack": 15,
        "dodge" : -10,
        "parry" : 15,
        "damage": 15,
        "damage_type":"����"
]),
([      "action": "$Nһ����ȣ�ʩһ�С��йٷ�����������$w���������ã�����ǵ�Ϯ��$n",
        "force" : 120,
        "attack": 20,
        "dodge" : -5,
        "parry" : 19,
        "damage": 20,
        "damage_type":"����"
]),
([      "action": "$N����Ծ��һ�С��������š�������$w������ֱ�����������$n���ɲ�",
        "force" : 280,
        "attack": 50,
        "dodge" : -5,
        "parry" : 55,
        "damage": 50,
        "lvl"   : 130,
        "damage_type":"����"
]),
([      "action": "$N�߾�$wʩչ���޳�����������������Ȱ�Ʈ������׼$n�������һ�ȴ���",
        "force" : 330,
        "attack": 61,
        "dodge" : -5,
        "parry" : 62,
        "damage": 60,
        "damage_type":"����"
]),
([      "action": "$N˫�۷��죬һ�С��ٹ����ޡ���������$w���ǧ�ٸ����ƣ�����$nȫ������Ҫ��",
        "force" : 350,
        "attack": 65,
        "dodge" : -5,
        "parry" : 67,
        "damage": 60,
        "damage_type":"����"
]),
});

int valid_enable(string usage) { return usage == "staff" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<500 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("����ڹ����̫ǳ��\n");

        if ((int)me->query_skill("staff", 1) < (int)(int)me->query_skill("suoming-zhang", 1))
                return notify_fail("��Ļ����ȷ�ˮƽ���ޣ��޷���������������ȷ���\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("suoming-zhang",1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "staff" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("qi", me)<80 )
                return notify_fail("������������������ȷ���\n");

        if( query("neili", me)<75 )
                return notify_fail("������������������ȷ���\n");

        me->receive_damage("qi", 70);
        addn("neili", -69, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"suoming-zhang/" + action;
}