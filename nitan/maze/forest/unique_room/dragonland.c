#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short",HIR"��Ѩ"NOR);
        set("long",@LONG
�ö�������
LONG);

        set("maze", 1);
        set("no_clean_up", 1);
        set("no_magic", 1);
        set("virtual_room",1);
        set("outdoors", "forest");
        
        set("objects",([
                "/maze/forest/npc/dragon": 1,  
                "/maze/forest/npc/dragon_baby": 5,    
                "/maze/forest/obj/box2": 1, 
        ]));        
        setup();
}
