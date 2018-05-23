// cheng.c ���ϰ�

inherit NPC;
inherit F_DEALER;

string ask_me1();
string ask_me2();

void create()
{
        set_name("���ϰ�", ({ "cheng laoban", "cheng" }));
        set("title", "ȫ�۵��ϰ�");
        set("shen_type", 1);

        set("str", 20);
        set("gender", "����");
        set("age", 65);
        set("long", "���ϰ徭Ӫ�洫������ȫ�۵¾�¥���ж��ꡣ\n");

        set("combat_exp", 50000);

        set("qi", 300);
        set("max_qi", 300);
        set("attitude", "friendly");

        set_skill("unarmed", 60);
        set_skill("dodge", 60);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 30);

        set("vendor_goods", ({
                "/d/city/obj/hdjiudai",
                "/d/beijing/obj/kaoya",
                "/d/city/obj/kaoya",
        }));

        set("inquiry", ([
                "̷�Ѽ�" : (: ask_me1 :),
                "̷ʦү" : (: ask_me1 :),
                "�л���" : (: ask_me2 :),
        ]) );

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

string ask_me1()
{
        if( query_temp("marks/��2", this_player()) )
        {
                delete_temp("marks/��2", this_player());
                set_temp("marks/��3", 1, this_player());
                return "Ŷ������̷�������ġ���������ͱ�����ˡ���������ʲô����\n";
        }
        else if( query_temp("marks/��3", this_player()) )
                return "�Ҳ����㽭�ˣ�Ҳû������ô���£�\n";
        else
                return "ȥȥȥ���������������ӣ������Ǳ����ǣ����ӽ��£������������ʣ���\n";
}

string ask_me2()
{
        if( query_temp("marks/��3", this_player()) )
        {
                say("��Ȼ����ôϲ���Խл�������ǧ���������������ң�������һֻ�ɡ�\n");
                return "���ȸ������ƽ�����һ�ֽ�Ǯ��һ�ֽ�����\n";
        }
        else
                return "ȥȥȥ���������������ӣ������Ǳ����ǣ����ӽ��£�������������\n";
}

int accept_object(object who, object ob)
{
    object item;

    if( (query("money_id", ob)) && (ob->value() == 50000 )
          && (query_temp("marks/��3", who)) )
        {
        item = new("/d/city/obj/jiaohuaji");
        item->move(who);
        delete_temp("marks/��3", who);
        return 1;
    }
    else if (ob->value() < 50000)
        {
                command("say ��...��...�����Ҿ�ȴ֮�����ˡ�");
                return 1;
    }
    return 0;
}