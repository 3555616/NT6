// chaboshi.c �販ʿ�


inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("�販ʿ", ({ "cha boshi", "chaboshi", "boshi" }) );
        set("gender", "����" );
        set("age", 22);
        set("long", "��λ�販ʿһ�����Ŵ�����һ������Ĩ����Ц�����æ�š�\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("no_get", "1");
        set("vendor_goods", ({
                __DIR__"obj/dongtingchun",
                __DIR__"obj/yinzhencha",
                __DIR__"obj/xianglian",
        }));
        setup();
        carry_object(CLOTH_DIR"male-cloth")->wear();
        carry_object(CLOTH_DIR"male-shoe")->wear();
}

void init()
{
        object ob;
        mapping myfam;

        ob = this_player();

        ::init();
        if( interactive(ob) && !is_fighting() ) {
                if( (myfam=query("family", ob) )
                && myfam["family_name"] == "ؤ��"
                && ob->query_skill("begging",1) > 10 )
                {
                        remove_call_out("saying");
                        call_out("saying", 0, ob);
                }
                else
                {
                        remove_call_out("greeting");
                        call_out("greeting", 1, ob);
                }
        }

        add_action("do_buy", "buy");
        add_action("do_list", "list");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(2) ) {
                case 0:
                        say( "��С��Ц�����˵������λ" + RANK_D->query_respect(ob) + "�������ȱ��裬ЪЪ�Ȱɡ�\n");
                        break;
                case 1:
                        say( "��С���ò����ϵ�ë��Ĩ��Ĩ�֣�˵������λ" + RANK_D->query_respect(ob) + "����������\n");
                        break;
        }
}

void saying(object ob)
{
        if (!ob || environment(ob) != environment()) return;

        say("\n��С�����һ���������Ҫ���Ľ�����ʲ�᣿���ҹ���ȥ��\n\n");
        remove_call_out("kicking");
        call_out("kicking", 1, ob);

}

void kicking(object ob)
{
        if (!ob || environment(ob) != environment()) return;

        ob->move("/d/yueyang/nanjie");
        message("vision","ֻ����ƹ����һ����"+query("name", ob)+"���˴Ӷ���¥��һ�����˳������Ǳ���״���ӿ��ˡ�\n",environment(ob),ob);
}