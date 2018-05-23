// Updated by rama

inherit ROOM;
#include <ansi.h>

int do_open(string arg);
int do_knock(string arg);

void create() {
        set("short", "���");
        set("long", @LONG
������һ������ͨͨ����ӣ�ȫ��ֻ���ݽǰ���һ�Ŵ�(chuang)��
������ʲôҲû�С�
LONG );
        set("outdoors", "beijing");
        set("no_clean_up", 0);
        set("exits", ([
                "east" : "/d/beijing/shi_1",
        ]));
        set("item_desc", ([
                "chuang" : "ľ�����ɵ�С��������û��һ˿������\n" ,
        ]));

	set("coor/x", -2840);
	set("coor/y", 7710);
	set("coor/z", 0);
	setup();
}
void init()
{
        add_action("do_knock", "knock");
        add_action("do_open","open");
}
int do_open(string arg)
{
        if(arg=="chuang")
        return notify_fail("���������������壬���һ�㶯����û�У�\n");
        else return 0;
}

int do_knock(string arg)
{
        object me;
        me = this_player();
        if (!arg||arg=="") 
                return notify_fail("��Ҫ��ʲô��\n");
          if (arg != "chuang")
                return notify_fail("��Ҫ��ʲô��\n");
          if( arg=="chuang" ) {
                message_vision("$N���������ô��塣\n", me);
                if( query("bunch/bunch_name", me) == "������" )
                {
                        message_vision(HIB"����֨ѽһ�����ˣ�������̽����ͷ��������$N����˵������ԭ�����Լ��ֵܰ�������
˵��һ�Ѱ�$N���˽�ȥ��\n"NOR, me);
                        me->move("/d/beijing/xlm_bjfb");
                        return 1;
                }
                if( query("bunch/bunch_name", me) != "������" && query("shen", me) <= 0 )
                {
                        message_vision(HIB"����֨ѽһ�����ˣ�������̽����ͷ��������$N����˵����������Ͷ�����������ŵİɣ�����
˵��һ�Ѱ�$N���˽�ȥ��\n"NOR, me);
                        me->move("/d/beijing/xlm_bjfb");
                        return 1;
                }
                if( good_bunch(me) || query("shen", me)>0 )
                { 
                        message_vision("����֨ѽһ�����ˣ�������̽����ͷ��������$N����˵��������������Ҳ�����ˣ���Ĳ��ͷ���ô����\n�ű����صĹ����ˡ�\n",me);  
                        return 1; 
                } 
                message_vision("�Ű�֨ѽһ�����ˣ�������̽����ͷ��������$N����˵��������Ȼ�Ǳ��ŵ��ֵܣ��ͽ����ɣ�����
˵��һ�Ѱ�$N���˽�ȥ��\n",me);
                me->move("/d/beijing/xlm_bjfb"); 
                return 1; 
        }
        
        return 1;
}
  