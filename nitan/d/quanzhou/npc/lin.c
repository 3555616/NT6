// lin.c
// Last Modified by winder on May. 29 2001

inherit NPC;
#include <ansi.h>
void create()
{
        set_name("������", ({ "lin shaoning", "lin" }));
        set("long", "��������Ȫ����ݹݳ���\n");
        set("gender", "����");
        set("age", 35);
        set_skill("dodge", 80);
        set_skill("force", 80);
        set_skill("parry", 80);
        set_skill("claw", 80);
        set_skill("hand", 80);
        set_skill("strike", 80);
        set_skill("finger", 80);
        set_skill("cuff", 80);
        set_skill("blade", 80);
        set_skill("stick", 80);
        set_skill("club", 80);
        set_skill("staff", 80);
        set_skill("sword", 80);
        set_skill("throwing", 80);
        set_skill("changquan", 40);
        set_skill("sanshou", 40);
        map_skill("cuff", "changquan");
        map_skill("hand", "sanshou");
        prepare_skill("cuff", "changquan");
        prepare_skill("hand", "sanshou");

        set("combat_exp", 400000);
        set("shen_type", 1);
        setup();

}
int accept_object(object who, object ob)
{
        if( query("combat_exp", who) >= 3500 )
        {
                message_vision("����������$N˵������书Ӧ���������������ٳ�����������û�������ˡ�\n", who);
                return 0;
        }
        if( query("money_id", ob) && ob->value() >= 500 )
        {
                set_temp("marks/quanzhou_paied", 1, who);
                message_vision("��������$N˵���ã���λ" + RANK_D->query_respect(who) + "��ѧʲô�أ�\n" , who);
                return 1;
        }
        else
                message_vision("��������ü��$N˵��Ǯ�Ҳ��ں�������Ҳ����Ҳ̫���˵���ɣ�\n", who);
        return 0;
}

int recognize_apprentice(object ob)
{
        if( !query_temp("marks/quanzhou_paied", ob) == 1)return 0;
        return 1;
}
