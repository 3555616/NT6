// yuanyuantai
inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "��Ϧ̨");
        set("long", @LONG
ԲԵ̨��������һ��ƽ̨������һ������������Ϧ������Ϧ̨��
�ݵ��൱����ྻ�������µ�һ������һ�ź�����ʯ���ɡ�ƾ��Զ����
�������ɣ����Ƶ�����ÿ����ҹ������Ϧ̨�۵���ţ��֯Ů�����Ƿ�
��������ǧ�ֲ��ࡢ������Ũ���ƺ��ܹ������˼䡣�ѹִ����ƣ�
����Ū�ɣ����Ǵ��ޣ������������ȡ������¶һ��꣬��ʤȴ����
��������������ˮ���������Σ��̹�ȵ�Ź�·���������Ǿó�ʱ����
���ڡ�����ĺĺ����
LONG );
        set("outdoors", "xihu");
        set("exits", ([
                "north" : "/d/hangzhou/sansheng-shi",
                "west" : "/d/hangzhou/yuanyuan-tai",
        ]));

//        set("no_clean_up", 0);
	set("coor/x", 780);
	set("coor/y", -1970);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}