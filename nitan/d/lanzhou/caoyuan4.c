//  Room:  /d/lanzhou/caoyuan4.c

inherit  ROOM;

void  create  ()
{
        int dir1,dir2,dir3,dir4;
        dir1=random(5)+1;
        dir2=random(5)+1;
        dir3=random(5)+1;
        dir4=random(5)+1;
        while (dir1!=5 && dir2!=5 && dir3!=5 && dir4!=5)        
        {        
                dir1=random(5)+1;
                dir2=random(5)+1;
                dir3=random(5)+1;                
                dir4=random(5)+1;                
        }
        set("short",  "���ԭ");
        set("long",  @LONG
����ƽԭ�ϵĴ��ԭ����֮�ɹŲ�ԭ����ѷɫ�������͵�����ֱ��
��ߡ������������̵أ����𶫱��ĺ�ɽ��ˮ��������һ����Ȥ��
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "south" : __DIR__"caoyuan"+dir1,
                "north" : __DIR__"caoyuan"+dir2,
                "east"  : __DIR__"caoyuan"+dir3,
                "west"  : __DIR__"caoyuan"+dir4,
        ]));
        set("objects",  ([
                "/d/xingxiu/npc/herdsman" : random(2),
        ]));
        set("outdoors", "lanzhou");
        set("no_clean_up", 0);
	set("coor/x", -15740);
	set("coor/y", 3780);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}