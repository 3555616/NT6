//Room: /d/dali/heilongling.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","������");
        set("long", @LONG
���������к�÷���꣬���Ѱ�ʴ�ݾ��������Ƥ�����ʰ�쵣���
���ڵأ��������죬�罾�������壬���������������Ƭ�����
���巼Ϯ�ˣ���ֲ֪�Ժδ����ഫ��Ϊ��÷���ɻ�ȻҲ���������
����̶��
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "north"      : "/d/dali/xiaodao1",
            "south"      : "/d/dali/shulinwai",
            "southwest"  : "/d/dali/xiaodao2",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19110);
	set("coor/y", -6900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}