// newbie.c

#include <ansi.h>
#include <command.h>

inherit ITEM;

int do_read(string arg);

void create()
{
        set_name(HIW"�������űض�"NOR, ({"book", "newbie book"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "�����̹Ÿ�������׼�����飬����������"
                            "��Σ����������̶��ؿ�����\n");
        }
        setup();
}

void init()
{
        add_action("do_read", "read");
}
 
int do_read(string arg)
{
        if (! arg || arg != "book")
                return notify_fail("��Ҫ��ʲô��Ҫ�����������(read book)��\n");

        return HELP_CMD->main(this_player(), "feature");
}
