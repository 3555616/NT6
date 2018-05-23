//1997-3-10 by qyz
#include <room.h>

inherit ROOM;


void create()
{
	set("short","聚仙桥");
	set("long",@LONG
相传聚仙桥是八仙聚会的地方，在聚仙桥的中央，有一个二米见方的石台，
三面悬空，周围环着足有儿臂粗细的铁链，道教信士经常在这里焚表以祭奠天神
，每逢春夏之交，香客们在登峰进香后，将祭神的表撕成碎片，掷于台下，可看
山谷间千百只飞燕群相争衔，蔚为奇观。
LONG);
	set("exits",
	([
	"south" : __DIR__"shijie4",
	"east" : __DIR__"xiangtou_ya",
          "northup" : __DIR__"shanmen",
	]));
        set("outdoors","kongdong");
	set("objects", ([
		__DIR__"npc/youke" : 3,
		]) );
        setup();
        //place_program(ROOM);
}
