#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","˯��");
  set ("long", @LONG
������ǿ�ջ�������ˡ�ֻ�������Ѿ��������˵����˼����ˡ���
������������е����ˣ�����һ����Ƿ��
LONG);

  set("exits", ([ 
  
        
          "out":__DIR__"kezhan",
         ]));
  set("sleep_room",1);
  set("valid_startroom", 1);
  setup();
 
}

int valid_leave(object me,string dir)
{
        if(dir=="out")
                delete_temp("gived_money", me);
        return ::valid_leave(me,dir);
}