
inherit NPC;

#include <ansi.h>

#define TIME_TICK1 time()*60
string *list=({

"killer",

	});


int do_kill(string arg);

string do_quest1();
void create()
{
   int i;
   object *ob;
   
   set_name("拿钱买命",({ "shashou","sha" }) );
   set("gender", "男性" );
   set("nickname",HIR"拿人钱财，替人消灾"NOR);
   set("age", 32);
   set("long", "这就是武林中闻名杀手集团大老板。\n");
       
   set("combat_exp", 10000000);
   set("str",30);
   set("per", 30);
   set("dex",30);
   
   set("max_gin",3000);
   set("max_kee",3000);
   set("max_sen",3000);
   set("force",3000);
   set("max_force",3000);
   
   set_skill("force",500);
   set_skill("dodge",500);
   set_skill("parry",500);
   set_skill("sword",200);
   
   set_skill("yingzi-jianfa",200);
   set_skill("huanmo-shenfa",200);
   set_skill("wanshi-jue",200);
 
   set("inquiry",([

	  "刺杀": "好吧，请用 cisha 人物id  来告诉我杀谁吧!\n",
        
	
	   ]));
   set("vocation","杀手");
   set("vocation_skill","yingzi-jianfa");
   set_temp("apply/armor",100);
   setup();
   ob=children(__DIR__"obj/qingfeng-jian");
   for(i=0;i<sizeof(ob);i++)
     if(environment(ob[i])&&userp(environment(ob[i]))){
     tell_object(environment(ob[i]),"你手中的"+ob[i]->query("name")+"被它的主人收回去了！\n");
     if(ob[i]->query("equipped"))
      ob[i]->unequip();
     destruct(ob[i]);}
     else if(environment(ob[i])){
     tell_object(environment(ob[i]),ob[i]->query("name")+"被一阵风卷走了。\n");
     destruct(ob[i]);}
     else destruct(ob[i]);
   //carry_object(__DIR__"obj/qingfeng-jian")->wield();
  
}

void init()
{
	add_action("do_kill","cisha");
	
}

int do_kill(string arg)
{
	object *usr;object me,ob;int i,j;object victim;
	int vexp,gol;int money;
	me=this_player();
	ob=this_object();
	usr=users();
	if(!arg) return notify_fail("你让我去杀谁？明说好了!\n");
	j=0;
	if(me->query("id")==arg) return notify_fail("杀你自己？开玩笑吧？！\n");
	for(i=0;i<sizeof(usr);i++)
	{
	write("=====" + usr[i]->query("id")+ "=====\n");
		//if(usr[i]->query("id")==arg)
		//{ j=1;victim=usr[i];break;}
	}
	if(j==0) return notify_fail("恩？现在的江湖中有这个人吗？好好看看!\n");
	if(victim->is_ghost())
	return notify_fail("这个人已经死了，你还是积点阴德吧！\n");
	vexp=victim->query("combat_exp");
	gol=vexp/1000+random(vexp/1000);
	if(gol<=0) return notify_fail("哼，武功这么低微的人也值得我来杀?\n");
	tell_object(me,"这次行动要花掉你"+chinese_number(gol)+"两黄金!\n");
	money=gol*10000;
	switch(MONEY_D->player_pay(this_player(), money))
	{
	case 0: return notify_fail("哼，这么点钱，也想来找我？\n");
	case 2: return notify_fail("您的零钱不够了，银票又没人找得开。\n");
	default:
	tell_object(me,"拿钱买命点点头，道：收人钱财，与人消灾，你等着好了！\n");
	if(victim->query("combat_exp")>500000)
	ob->set("combat_exp",victim->query("combat_exp"));
	if(!objectp(victim)) return notify_fail("哎呀，这个人突然跑了，下次吧!\n");
	victim->start_busy(2);
	message_vision("$N身行一晃，踪迹不见!\n",ob);
	ob->move(environment(victim));
	message_vision(HIR"$N冲着$n叫道：有人雇我来杀你，你认命好了!\n"NOR,ob,victim);
	ob->kill_ob(victim);
log_file("killer_kill",sprintf("%s let yang kill %s\n",me->query("id"),victim->query("id")));
	call_out("yang_go",180,ob);
	return 1;
	}
	return 1;
}

void yang_go(object ob)
{
	string *dir=({"/d/luoyang/shanlu1"});
	if(!objectp(ob))
	{ remove_call_out("yang_go");return;}
	message_vision("$N四下看了看，身行一晃，踪迹不见!\n",ob);
	ob->move(dir[random(sizeof(dir))]);
	remove_call_out("yang_go");return;
}



int is_apprentice_of(object ob)
{
	return 1;
}
int recognize_apprentice(object ob)
{
         return 1;
}


