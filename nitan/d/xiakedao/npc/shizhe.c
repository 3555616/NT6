//NPC /npc/shizhe.c

inherit NPC;
#include <ansi.h>
#include <command.h>

void greeting(object);
void init();
int ask_for_xkd();

void create()
{
        set_name("����ʹ��", ( { "shi zhe", "zhe" }) );
        set("gender", "����" );
        set("age", 30);
        set("long", "���Ǹ����Ż��µ���ʮ���꺺�ӣ��ֳ�ľ�������ޱ��顣\n");
        set("attitude", "friendly");
        set("no_get", 1);
        set("shen_type", 1);

        set("str", 30);
        set("int", 39);
        set("con", 30);
        set("dex", 30);

        set("max_qi", 330);
        set("max_jing", 320);
        set("neili", 300);
        set("max_neili", 300);

        set("combat_exp", 16000);
        set("score", 10000);

        set_skill("force", 50);
        set_skill("dodge", 50);
        set_skill("unarmed", 50);
        set_skill("parry", 50);
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/damage", 50);
        set_temp("apply/armor", 50);

        create_family("���͵�", 2, "����");

        set("inquiry", ([
                "���͵�" : (: ask_for_xkd :),
                "����"   : "�ϱ߻��м��Ҵ������Լ�����ȥ�ɣ�\n",
        ]));
        setup();
}

void init()
{
        object ob;

        ::init();

        if( interactive(ob = this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{

        if( !ob || environment(ob) != environment() ) return;
        say("����ʹ��˵������λ" + RANK_D->query_respect(ob) + "����ҽй�������ʲô����\n");
        return;
}

/*int accept_object(object who, object ob)
{
        object ling1;
        object ling2;
        object room, myenv;
 
        if( !who || environment(who) != environment() ) return 0;
        if ( !objectp(ob) ) return 0;
        if ( !present(ob, who) ) return notify_fail("��û�����������\n");

        if( query("id", ob) != "shanpai"
                 && query("id", ob) != "epai" )
        {
                return notify_fail("�Ҳ���Ҫ���������\n");
        }
        
        if ( query_temp("times")==0 )
        {
                return notify_fail("��̫���ˣ����������\n");
        }

        if( !query("xkd/ling", who) )
        {
                tell_object( who, "����ʹ��˵�������͵�ֻ��������������ϵ�����λ" + RANK_D->query_respect(who) + "������ذɡ�\n" );
                return 0;
        }
        
        if( query("id", ob) == "shanpai" )
        {
                if( query("own", ob) != query("id", who) )
                {
                        message_vision("�ⲻ��������ӡ���������ƭ�ң������뺦�Ҽ���������\n",who);
                        return 0;
                }
                if (query_temp("ling")==2)
                {
                        message_vision("ʹ��һ��������ͭ�ƣ�����Ǹ��ض�$N˵���ϵ���ͭ�ƹ����飬�㻹ȱһ�鷣��ͭ�ơ�\n",who);
                        return 0;
                }
                addn_temp("ling",2);
                if(!( room = find_object("/d/xiakedao/duchuan")) )
                        room = load_object("/d/xiakedao/duchuan");
        
                room = find_object("/d/xiakedao/duchuan");
                addn_temp("pai", 2, room);
        
                if( query_temp("ling")==2 )
                { 
                        message_vision("ʹ��һ��������ͭ�ƣ�������ϲ�ض�$N˵���㻹��һ�鷣��ͭ����\n",who);
                        return 1;
                }
        }

        if( query("id", ob) == "epai" )
        {
                if( query("own", ob) != query("id", who) )
                {
                        message_vision("�ⲻ��������ӡ���������ƭ�ң������뺦�Ҽ���������\n",who);
                        return 0;
                }
                if(query_temp("ling")==1)
                {
                        message_vision("ʹ��һ���Ƿ���ͭ�ƣ������ź��ض�$N˵������ͭ��һ�����飬�㻹ȱ����ͭ�ơ�\n",who);
                        return 0;
                }
                addn_temp("ling",1);
                if(!( room = find_object("/d/xiakedao/duchuan")) )
                        room = load_object("/d/xiakedao/duchuan");
                room = find_object("/d/xiakedao/duchuan");
                addn_temp("pai", 1, room);
        
                if( query_temp("ling")==1 )
                {
                        message_vision("ʹ��һ���Ƿ���ͭ�ƣ�������ϲ�ض�$N˵���㻹������ͭ����\n",who);
                        destruct( ob );
                        return 1;
                }
        }

        command("smile"+query("id", who));
        tell_object( who, HIG"ԭ�������͵��Ĺ������������ϵ�ȥ�ɡ�\n"NOR );
        ling1 = new("/d/xiakedao/obj/tongpai1");
        set_temp("own",query("id",  who), ling1);
        ling1->move(who);
        ling2 = new("/d/xiakedao/obj/tongpai2");
        set_temp("own",query("id",  who), ling2);
        ling2->move(who);
        set_temp("ling",0);
//        addn_temp("times",-1);
        myenv = environment (who) ;
        who->move("/d/xiakedao/duchuan");
        tell_room(myenv,"����ʹ���������֣�һֻС�ۿ�����"+query("name", who)+"�粽�ϴ���\n");
        call_out("goto_xiake",10,who) ;
        return 1;
}*/

int ask_for_xkd()
{
        object who = this_player();
        object ling1,ling2;
        object myenv;        
        object* inv;
        int i;
        
        if( !who || environment(who) != environment() ) return 0;
        
//        if ( !who->query("xkd/ling") || time() > who->query("xkd/time") )
        if( !query("xkd/ling", who) )
        {
                message_vision("����ʹ��˵����С���������һ���ӣ�����û��˵����\n", who );
                return 1;
        }
                /*
        if ( !objectp( ling1 = present( "shan pai", who ) ) ||
                !objectp( ling2 = present( "e pai", who ) ) )
        {
                message_vision( "����ʹ��˵���������͵�Ҫ�����Ʒ������λ" + RANK_D->query_respect(who) + "������ذɣ�\n", who );
                return 1;
        }
        
        if( query("own", ling1) != query("id", who) || 
                query("own", ling2) != query("id", who) )
        {
                message_vision( "����ʹ��˵����" + RANK_D->query_respect(who) + "�õĲ����Լ������ӡ�������ƭ�ң������뺦�Ҽ���������\n", who );
                return 1;
        }
*/        
        inv = all_inventory(who);
        for(i=0; i<sizeof(inv); i++)
                if ( userp(inv[i]) )
                {
                        message_vision( "����ʹ��˵���������������ֻ��ӭ��" + RANK_D->query_respect(who)+ "һ��ǰ����\n���Ƕ���һ�ˣ�С�۹����㸲��С��Ҳ���׼�������\n", who );
                        return 1;
                }
                
        command("smile"+query("id", who));
        tell_object( who, HIG"ԭ�������͵��Ĺ������������ϵ�ȥ�ɡ�\n"NOR );
        myenv = environment (who) ;        
        who->move("/d/xiakedao/duchuan");
        tell_room(myenv,"����ʹ���������֣�һֻС�ۿ�����"+query("name", who)+"�粽�ϴ���\n");
        call_out("goto_xiake",10,who) ;        
        return 1;
}

void goto_xiake(object ob)
{
        tell_object(ob, HIB"���ں��Ϻ�����������ҹ��������ͣ����һ��С���ߡ������´�����\n" ) ;
        ob->move ("/d/xiakedao/haitan") ;
}