#include <ansi.h>
inherit ROOM;
inherit __DIR__"jiguan_room.c";

void create()
{
        set("short", "石室");
        set("long", @LONG
这是一间宽敞的石室，只见四周空旷无比，不远处有一块形状奇
特的石桌（desk）。
LONG );
        set("maze", 1);
        set("no_magic", 1);
        set("virtual_room", 1);
        set("no_clean_up", 1);
        set("room_id", "number/lockroom3");
        set("item_desc", ([
                "desk" : NOR + WHT "一张形状奇特的石桌，似乎连接着什么机关！\n" NOR,
        ]));
        setup();
}