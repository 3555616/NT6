// zhao.c

inherit NPC;
#include <ansi.h>;
void create()
{
        set_name("赵峄", ({ "zhao yi", "yi", "zhao" }) );
        set("long", "他是一个矮小老者。嵩山派掌门人的师弟。\n");
        set("gender", "男性");
        set("class", "swordsman");
        set("age", 58);
        set("attitude", "peaceful");
        set("str", 26);
        set("con", 30);
        set("dex", 30);
        set("int", 28);

        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 30);
        set("max_qi",2000);
        set("max_jing",1200);
        set("combat_exp", 700000);
        set("shen_type", -1);

        set_skill("literate", 50);
        set_skill("strike", 100);
        set_skill("hand", 100);
        set_skill("sword", 100);
        set_skill("force", 100);
        set_skill("parry", 100);
        set_skill("dodge", 100);
        set_skill("songshan-sword", 150);
        set_skill("songyang-strike", 150);
        set_skill("poyun-hand", 150);
        set_skill("hanbing-zhenqi", 100);
        set_skill("fuguanglueying", 150);
        map_skill("strike", "songyang-strike");
        map_skill("hand", "poyun-hand");
        map_skill("sword", "songshan-sword");
        map_skill("parry", "songshan-sword");
        map_skill("dodge", "fuguanglueying");
        map_skill("force", "hanbing-zhenqi");
        prepare_skill("strike", "songyang-strike");
        prepare_skill("hand", "poyun-hand");
        set("env/wimpy", 60);
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "sword.shuiyuan" :),
                (: perform_action, "sword.jianqi" :),
                (: perform_action, "sword.feiwu" :),
                (: perform_action, "strike.yinyang" :),
                (: perform_action, "hand.chanyun" :),
                (: exert_function, "powerup" :),
                (: exert_function, "regenerate" :),
                (: exert_function, "recover" :),
        }) );
        create_family("嵩山派", 13, "弟子");
        setup();

        carry_object(WEAPON_DIR+"kuojian")->wield();
        carry_object(__DIR__"obj/yellow-cloth")->wear();
}
