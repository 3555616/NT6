//1997-3-10 by qyz
#include <room.h>

inherit ROOM;


void create()
{
	set("short","石阶");
	set("long",@LONG
这里石峡壁立，险峻异常，脚下有一条前人在无路可攀的陡壁上，耗尽心血
，用崖壁上坚硬无比的石头砌成的一级级石阶，石阶的两旁立着一棵棵石柱，上
面连着一条粗如儿臂的铁链，游人们就只有倚着这条铁链方敢沿着石阶上下。古
人曾有诗叹耶：“一寸进一步，天门攀铁柱。自向此间行，才得上天路。”可见
此山之险。
LONG);
	set("exits",
	([
          "southdown" : __DIR__"shijie1",
          "westup" : __DIR__"shangtian_ti",
	]));
        set("outdoors","kongdong");
        setup();
        //place_program(ROOM);
}
