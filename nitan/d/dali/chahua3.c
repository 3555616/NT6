//Room: /d/dali/chahua3.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","�軨԰");
        set("long", @LONG
�����軨�ھ����£����������Ĳ軨��Ȼ���Ƿ�Ʒ���������ڲ�
��԰�У�������ܵĶ������涷���Ĳ軨�����ϰ���һ������ԵĲ�
����΢���ˮ�洵����ҡҷ��涡�
LONG );
        set("objects", ([
           "/d/dali/obj/chahua8": 1,
           "/d/dali/obj/chahua9": 1,
           "/d/dali/obj/chahua10": 1,
        ]));
        set("outdoors", "daliwang");
        set("exits",([ /* sizeof() == 1 */
            "southwest"  : "/d/dali/chahua2",
            "north"      : "/d/dali/chahua6",
            "southeast"  : "/d/dali/chahua5",
        ]));
	set("coor/x", -19071);
	set("coor/y", -6851);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}