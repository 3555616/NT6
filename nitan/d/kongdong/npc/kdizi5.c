inherit NPC;


void create()
{
        set_name("烧火小道士", ({ "shaohuo daoshi","daoshi" }) );
        set("title","崆峒弟子");
        set("gender", "男性" );
        set("class","taoist");
        set("age",16);
	create_family("崆峒派", 2, "弟子");
	set_wugong("dahong-quan",60,60,1);
	set_wugong("jiben-qinggong",60,60,1);
	set_xiuwei("unarmed",250);
	set_xiuwei("dodge",100);
        set("social_exp",2000);
        set("combat_exp",10000);
        set("force",200);
        set("max_force",200);
        set("force_factor",10);
	set("food_apply",15);
        setup();
        carry_object(__DIR__"obj/cloth3")->wear();
}

void init()
{
        object ob;
        if(interactive(ob=this_player()) && !is_fighting()){
		remove_call_out("show_msg");
            call_out("show_msg",1,ob);
            }
        add_action("do_yao","yao");
}

void show_msg(object ob)
{
        if(!ob||!present(ob,environment(this_object())))return;
        say("这几个小道士正手忙脚乱地引火做饭，没有注意到你。\n");
}
int do_yao()
{
    object who = this_player();
    object me = this_object();

    if( who->query("family/family_name")!="崆峒派" || query("food_apply") < 0 )
        {
               message_vision("小道士对着$N摇了摇头说：这位施主，实在对不起，\n"
                        "斋饭还没有做好，烦请多等一会儿。\n",who);  
               return 1;
        }
    if ( (who->query("water") >= who->max_water_capacity()/2)
        &&(who->query("food") >= who->max_food_capacity()/2) ){
        return notify_fail("你吃得饱饱的，喝得足足来这里添什么乱？！\n");
        }

    message_vision("$N揉着肚子可怜兮兮得对$n说：\n"
        "“小师兄，还有剩饭吗？实在是饿得不行了。”\n\n",who,me);
        printf("小道士忙说：这位%s，饭还没好，我先找给你点东西充饥吧。\n",
                (who->query("gender")=="男性") ? "师兄" : "师姐" );
    who->set("food" ,who->max_food_capacity());
    who->set("water",who->max_water_capacity());

    return 1;
}

int accept_object(object who, object ob)
{
        if(ob->value() >= 1000)
        {
                message_vision("小道士迟疑地看着"+ob->name()+"，嘴里嘟囔着：\n"
                "这怎么好意思呢？\n",who);
                message_vision("小道士想了想，从食橱里拿给$N一块素饼和一个葫"
                        "芦，\n说：要有人问起，你可别说是我拿给你的。\n",who);
                message_vision("小道士转过身去，继续引火。\n",who);
                new(__DIR__"obj/subing")->move(who);
                new(__DIR__"obj/hulu")->move(who);
                return 1;
        }
        else 
        {
                message_vision("小道士摇摇头：师傅说过，不能随便要别人的东西。\n",who);
                return 0;
        }
}

                
