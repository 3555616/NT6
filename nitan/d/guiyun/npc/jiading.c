// jiading.c �Ҷ�

inherit NPC;

void create()
{
        set_name("�Ҷ�", ({ "jia ding", "jia", "ding" }));
        set("gender", "����");
        set("age", 35);
        set("long", "����ׯ�Ҷ���\n");
        set("combat_exp", 40000);
        set_skill("dodge", 50);
        set_skill("unarmed", 50);
        set_temp("apply/attack",  50);
        set_temp("apply/defense", 50);
        set("shen_type", 1);
        setup();

        add_money("silver",3);
        carry_object("/clone/misc/cloth")->wear();
}

int accept_object(object who, object ob)
{
        if( query("id", ob) == "guiyun shuxin" )
        {
                command("bow"+query("id", this_player()));
                set_temp("marks/guiyun", 1, this_player());
                write("�Ҷ�˵����" + RANK_D->query_respect(ob) + "ԭ������ׯ�������ѣ���������\n");
                return 1;
        }
        return 0;
}