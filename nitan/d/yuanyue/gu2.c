// This program is a part of NITAN MudLIB

inherit ROOM;
#include <room.h>

void create()
{
        set("short", "����");
        set("long", @LONG
С���ϣ������ʹ��������£���Ů��Ц��СϪ������������β��
ɫ����Խˮ������
LONG );
        set("exits", ([ /* sizeof() == 4 */
                "east" : __DIR__"gu1",
                "westdown" : __DIR__"gu3",
 
        ]));
        set("outdoors","wansong");       
        set("coor/x",110);
        set("coor/y",10);
        set("coor/z",10);
        setup();
        replace_program(ROOM);
}    