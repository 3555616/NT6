//1997-3-10 by qyz

inherit ROOM;
#include <room.h>

string *things = ({
        CLONE_DIR + "book/quanfa",
        CLONE_DIR + "book/jianshu",
                });



void create()
{
	set("short","十八院");
	set("long",@LONG
这里环境清幽，四处打扫得干干净净，是崆峒山弟子以及进香客歇息的地方
，由于近两年来崆峒山香火不断，进香的人越来越多，于是准备再建一处厢房供
住宿之用，这里向西走就是崆峒山的主殿－－“轩辕宫”了。
角落里是一个柜子，似乎放了什么东西。
LONG);
    set("need_clean", "崆峒派");
	set("exits",
	([
             "west" : __DIR__"xuanyuan_gong",
             "up" : __DIR__"baguatai",
          	]));
    set("sleep_room","崆峒派");
	set("objects", ([
		__DIR__"npc/kdizi4" : 1,
		]) );
    if( random(10) > 5 )
        set("search_things", ([
                "柜子" : things[random(sizeof(things))],
                    ]));

    setup();
    //place_program(ROOM);
}
