#include <ansi.h>
inherit ITEM;

void create()
{
set_name("往生石",({"wangsheng shi","sheng shi","shi","stone"}));
set("unit","块");
setup();
}

int query_autoload()
{
return 1;
}

void init()
{
add_action("do_hf","huifu");
}

int do_hf(string id)
{
string arg1,arg2;       
object me = this_player();
if ( !id || !wizardp(me) )
        return 0;
if ( file_size(sprintf("/data/login/%c/%s.o",id[0],id))>0 )
        write(id+"的上线档案已经存在，取消此步骤，继续下一步。\n");
else if ( file_size(sprintf("/backup/2013-6-24/login/%c/%s.o",id[0],id))<=0 )
        {
        write(id+"的上线档案备份目录中没有，无法恢复。\n");
        return 1;
        }
else    {
        arg1 = sprintf("/backup/2006-7-6/login/%c/%s.o",id[0],id);     
        arg2 = sprintf("/data/login/%c/%s.o",id[0],id);
        if ( !("/cmds/adm/adcp.c")->main(me,arg1+" "+arg2) )
                return notify_fail(id+"上线记录恢复失败。\n");
        write(id+"上线记录恢复完毕。\n");       
        }
        
if ( file_size(sprintf("/data/user/%c/%s.o",id[0],id))>0 )
        return notify_fail(id+"的档案已经存在，请手动恢复。\n");
if ( file_size(sprintf("/data/user/%c/%s.oo.o",id[0],id))<=0 )
        return notify_fail(id+"的档案备份目录中没有，无法恢复。\n");
arg1 = sprintf("/data/user/%c/%s.oo.o",id[0],id);
arg2 = sprintf("/data/user/%c/%s.o",id[0],id);
if ( !("/cmds/adm/adcp.c")->main(me,arg1+" "+arg2) )
        return notify_fail(id+"记录恢复失败。\n");
write(id+"记录恢复完毕。\n");
message("shout",HIR"【"BLK"系统"NOR HIR"】"BLK"数据恢复："+id+" 数据恢复完毕。\n"NOR,users());
return 1;
}
