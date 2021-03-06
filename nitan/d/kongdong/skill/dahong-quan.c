// dahong.c
// 大洪拳

inherit SKILL;

mapping *action = ({
([	"action"    :"$N双掌一错，使出「十指点兵」，对准$n的$l连续拍出三掌",
    "lian"      :"$N双掌一错，使出「十指点兵」，结果左手把右手打得生疼",
    "jibie"     :16,      
    "zhaoshi":"「十指点兵」",
    "sen"       :1,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :15,
	"damage_type":	"瘀伤"
]),
([	"action"    :"$N使出一招「守将接印」，脚踩七星步，一拳向$n$l击去",
    "lian"      :"$N慢慢使出一招「守将接印」，仔细揣摩每一个变化",
    "jibie"     :48,
    "zhaoshi":"「守将接印」",
    "sen"       :1,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :15,
	"damage_type":	"瘀伤"
]),
([	"action"    :"$N使出一招「武松上铐」，左掌虚按，右拳下击，直奔$n的$l而去",
    "lian"      :"$N左掌虚按，右拳下击，体会「武松上铐」的感觉..",
    "jibie"     :56,  
    "zhaoshi":"「武松上铐」",
    "sen"       :2,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :20,
	"damage_type":	"瘀伤"
]),
([	"action"    :"$N使出「推窗望月」，大步跨前，立右拳，挽左拳向$n的$l击去",
    "lian"      :"$N大步跨前，立右拳，挽左拳，寻找「推窗望月」的感觉",
    "jibie"     :64, 
    "zhaoshi":"「推窗望月」",
    "sen"       :2,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :30,
	"damage_type":	"瘀伤"
]),
    ([   "action"  :"$N使出一招「乌风进洞」，左掌直立，右掌穿出击向$n的$l",
         "lian"    :"$N使出一招「乌风进洞」，左掌直立，右掌向前击出。",
         "zhaoshi" : "「乌风进洞」",
         "sen"   : 6,
         "parry" : 20,
         "dodge" : 15,
         "jibie" : 0,
         "damage": 5,
         "damage_type":  "瘀伤"
    ]),
    ([   "action"  :"$N一招「乌风扫地」，左掌化虚为实击向$n的$l",
         "lian"    :"$N一招「乌风扫地」，左掌虚虚实实击出。",
         "zhaoshi" : "「乌风扫地」",
         "damage" : 20,
         "sen"    : 8,
         "parry"  : 20,
         "dodge"  : 20,
         "jibie"  : 5,   
         "damage_type":  "瘀伤"
    ]),
    ([   "action": "$N双掌一错，使出「鹰爪捉食」，身形飞起，对准$n的$l连续拍出",
         "lian"  :"$N双掌一错，使出「鹰爪捉食」，身形飞起数尺。",
         "zhaoshi" : "「鹰爪捉食」",
         "damage":  20,
         "sen"  :  8,
         "parry" : 60,
         "dodge" : 60,
         "jibie":    20,
         "damage_type":  "瘀伤"
    ]),
    ([   "action": "$N左掌上扬，右掌推出，一招「绕手躲步」击向$n$l",
         "lian"  : "$N左掌上扬，右掌推出，一招「绕手躲步」快速拍出。",
         "zhaoshi" : "「绕手躲步」",
         "sen"  : 6,
         "jibie": 30,
         "parry" : 50,
         "dodge" : 40,
         "damage": 60,
         "damage_type":  "瘀伤"
    ]),
});

string * parry_msg = ({
    "$n一招「双扑心」，双掌翻舞，$N眼前一花，失去了$n的踪影。\n",
    "$n两手握拳，一招「单扑心」，格开了$N的一击。\n",
    "但见$n一招「犀牛献角」，跟上一步，化开了$N的攻势。\n",
});
    
int valid_learn(object me)
{
    if ( me->query_temp("weapon") || me->query_temp("secondary_weapon") )
    {    
        write("练拳必须空手。\n");
        return 0;
    }
    return 1;
}

int valid_lian( object me )
{   
    return valid_learn(me);
}

mapping query_action(int jibie)
{
	int i, size;

	size = sizeof( action );
	for ( i = 0; i < sizeof( action ); i++ )
		if ( action[ i ][ "jibie" ] > jibie )
		{
			size = i;
			break;
		}
    return action[ random( size ) ];
}

string query_zhaoshi( int jibie )
{
    int i;
    for ( i = 0; i < sizeof(action); i++ )
    {
        if ( action[ i ][ "jibie" ] >= jibie )
            return action[ i ][ "zhaoshi" ];
    }
    return "";
}

string query_xiuwei_type() { return "unarmed"; }

int query_dengji() { return 3; }
  
string query_parry_msg(object weapon)
{
    return parry_msg[random(sizeof(parry_msg))];
}

int query_youxiao_jibie() { return 12; }

int query_parry_ratio() { return 9; }
