// xiucai.c
inherit NPC;

void create()
{
        set_name("老秀才", ({ "lao xiucai", "lao" }));
        set("long", "一个穷困潦倒的落第秀才，在这里开堂授课为生。\n");
        set("gender", "男性");
        set("age", 65);

        set_skill("literate", 100);
        set_skill("taoism", 100);

        set_skill("unarmed", 80);
        set_skill("dodge", 80);
        set_skill("parry", 80);
        set_temp("apply/attack", 80);
        set_temp("apply/defense", 80);
        set_temp("apply/damage", 20);

        set("combat_exp", 40000);
        set("shen_type", 1);
        setup();

        carry_object("/clone/misc/cloth")->wear();
}

int recognize_apprentice(object ob)
{
        if( !query_temp("mark/朱", ob) )
                return 0; 
        addn_temp("mark/朱", -1, ob);
        return 1;
}

int accept_object(object who, object ob)
{
        if( !query_temp("mark/朱", who) )
                set_temp("mark/朱", 0, who);
        if( query("money_id", ob) && ob->value() >= 5000){
                message_vision("老秀才同意指点$N一些问题。\n", who);
                addn_temp("mark/朱", ob->value()/250, who);
                return 1;
        }
        return 0;
}