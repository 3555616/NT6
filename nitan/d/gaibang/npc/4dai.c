#include <ansi.h>
inherit NPC;

#include "fight.h"

void create()                                                                   
{
        NPC_D->generate_cn_name(this_object());
        set("gender", "男性");
        set("long", "这是位衣着破烂的丐帮弟子，眉目间透出股英气。\n");
        set("title", "丐帮四袋弟子");
        set("age", 38);
        set("attitude", "peaceful");
        set("class", "beggar");

        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 1800);
        set("max_jing", 1200);
        set("neili", 1600);
        set("max_neili", 1600);
        set("jiali", 150);
        set("combat_exp", 300000);

        set_skill("force", 110);
        set_skill("huntian-qigong", 110);
        set_skill("dodge", 110);
        set_skill("feiyan-zoubi", 110);
        set_skill("staff", 110);
        set_skill("fengmo-zhang", 110);
        set_skill("hand", 110);
        set_skill("shexing-diaoshou", 110);
        set_skill("strike", 110);
        set_skill("xiaoyaoyou", 110);
        set_skill("parry", 110);
        set_skill("begging", 110);
        set_skill("checking", 110);
        set_skill("literate", 110);
        set_skill("martial-cognize", 90);

        map_skill("force", "huntian-qigong");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("staff", "fengmo-zhang");
        map_skill("strike", "xiaoyaoyou");
        map_skill("hand", "shexing-diaoshou");
        map_skill("parry", "fengmo-zhang");

        prepare_skill("hand", "shexing-diaoshou");

        create_family("丐帮", 20, "弟子");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "staff.luan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 60);
        set_temp("apply/unarmed_damage", 60);
        set_temp("apply/armor", 110);

        setup();

        carry_object("/clone/weapon/zhubang")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}