inherit ROOM;

void create()
{
        set("short", "���յ�");
        set("long", @LONG
վ�����մ���ϣ���ᷢ���������п�����֮�֣��ֵ�������ֲ�ɰأ�
�������ŵƽ�ʡ��������������������̡��ٽֵ����ﾭӪ�����塢��
�����մɡ��Ŷ������ơ�С�Եȣ����ַǷ���������һ��˽�ӣ��ϱ�����
�˵޽��Լ�ͽ����Լ�ĵط�����һ��ǣ��
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"eroad3",
                  "north" : __DIR__"sishu",
                  "south" : __DIR__"yuelao",
                  "west" : __DIR__"eroad1",
        ]));
        set("objects", ([
                "/d/beijing/npc/boy1" : 1,
                "/d/beijing/npc/old2" : 1,
        ]));
	set("coor/x", -6970);
	set("coor/y", 2150);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}