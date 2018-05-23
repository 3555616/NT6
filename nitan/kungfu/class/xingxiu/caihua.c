// Last Modified by Winder on Apr. 25 2001

inherit NPC;

void create()
{
        set_name("�ɻ���", ({ "caihua zi", "caihua", "zi" }) );
        set("gender", "����" );
        set("nickname", "������");
        set("age", 38);
        set("long", 
                "�ɻ����������ɵ�һ��С��ޣ��书�䲻�ã���������а��"
                "�����������Ҹ�Ů���ǹٸ�ͨ���ķ��ˣ��ʶ�������������"
                "Ҳ��������������ӡ�\n");
        set("str", 25);
        set("dex", 30);
        set("con", 17);
        set("int", 15);
        set("shen_type", -1);
        set_skill("unarmed", 20);
        set_skill("force", 50);
        set_skill("dodge", 95);
        set_skill("zhaixinggong", 95);
        map_skill("dodge","zhaixinggong");
        set("combat_exp", 25000);
        set("max_qi", 300);
        set("max_jing", 100);
        set("neili", 500);
        set("max_neili", 500);
        create_family("������", 2, "����");

        set("attitude", "peaceful");
        set("inquiry", ([
                "name" : "��Ҳ�ǲ�����������˭�ˣ��������������źŲɻ��ӡ�",
                "�ɻ�" : "�ǿ���ѧ�ʣ��Ҳ������̡�",
                "ѧ��" : "�ٺ٣���������ţ������˷��ˣ�",
        ]) );
        setup();
        carry_object(CLOTH_DIR"male-cloth")->wear();
        carry_object(CLOTH_DIR"male-shoe")->wear();
        add_money("silver", 10);
}
void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player()) && !is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object me)
{
        mapping myfam;
        myfam=query("family", me);
        if (myfam && myfam["family_name"] == "������" &&
                (query("gender", me) == "����") )
                command("say �������ɽ����׽�˸�С�����ˮ�鼫�ˣ��͹����ҵ���ң���\n������һҹ����ү��ˬ���ˣ���Ҫ��Ҫ��ȥ���ԣ�");
        set_temp("marks/��", 0, me);
}

void attempt_apprentice(object ob)
{
        command("hehe");
        command("say ��ѧ�ҵĲɻ��񼼣�û�Ŷ���");
        return;
}

int accept_object(object me, object obj)
{
        mapping myfam;
        myfam=query("family", me);

        if (!myfam || myfam["family_name"] != "������") 
                command("say �ٸ����׽�����");
        else {
                if( !query("money_id", obj) )
                {
                        if( query("gender", me) == "Ů��" )
                        {
                                command("kiss"+query("id", me));
                                command("say �벻��ʦ��Ҳ��������á�");
                        }
                        else
                        {
                                command("bow"+query("id", me));
                                command("say ��лʦ�֡�");
                        }
                        command("say �Բ�����С��������ϱ���֪���ĸ��쵰�����ˣ�����\n����Խ���˯һ����");
                        set_temp("marks/��", 1, me);
                }
                else
                {
                        command("thank"+query("id", me));
                        command("say Ǯ���е��ǣ��㻹�Ǹ��ҵ���ʲô�ɡ�");
                }
        }
        return 1;
}