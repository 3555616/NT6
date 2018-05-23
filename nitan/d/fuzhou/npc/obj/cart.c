// cart.c

inherit ITEM;

void create()
{
        set_name("�ڳ�", ({ "silver cart", "cart"}) );
        set_weight(3000000);
        set("no_get", 1);
        set_max_encumbrance(80000000);
        set("unit", "��");
        set("long", "һ����������ڳ���������Ÿ����ھֵĴ��졣\n");
        set("closed", 1);
        set("value", 2000);
    
}

int is_container() {return 1;}

void init()
{
         add_action("do_open","open");
         add_action("do_close","close");
}

int do_close(string arg)
{
        object me, ob;

        me = this_player();
        ob = this_object();
        if(arg != "cart" && arg != "silver cart")
                return notify_fail("��Ҫ����ʲô��\n");
               message_vision("$N��$n�Ź����ˡ�\n", me, ob);
        set("closed", 1, ob);
        return 1;
}

int do_open(string arg)
{
        object me, ob;

        if(arg != "cart" && arg != "silver cart")
                return notify_fail("��Ҫ��ʲô��\n");
        me = this_player();
        if (objectp(ob=present("biao tou",environment())))
                return notify_fail(ob->name()+"������һ�ۣ�����Ҫ��ʲô����\n");
        set("closed", 0, this_object());
        message_vision("$N��$n�Ǵ򿪡�\n", me, this_object());
        return 1;
}

int is_closed()
{
        return (query("closed", this_object()));
}