inherit DEMONROOM;

void create()
{
        set("short", "九洲");
        set("long",@LONG
深切哀悼在9·18事变中牺牲的烈士，为我们的英雄报仇吧！
LONG);

        set("exits", ([
                "south"   : __DIR__"changqi2",
                "east"   : __DIR__"jiuzhou2",
                "north"  : __DIR__"jiuzhou3",
            "west"  : __DIR__"jiuzhou4",

        ]));

                set("n_time", 30); 
                set("n_npc", 5); 
                set("n_max_npc", 6);
                set("s_npc", "/clone/dream_npc/japangame/japannpc01");

        setup();
}
