#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "红包" NOR, ({ "hongbao"}) );
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "这一是个新年红包，上面用金色的字体写着" HIY "「猪年吉祥 万事如意」" HIR " ！\n"
                                "拆开(chai)红包可以获得新年压岁钱及小小的经验潜能奖励。\n"
                                "*请于2007年4月28日前使用红包，过期则使用无效！！！\n\n" NOR);
                set("value", 1);
                set("unit", "个"); 
        }
}

void init()
{
        //add_action("do_chai", "chai");
}

int do_chai(string arg)
{
        object me = this_player();
        string msg;
        int i, exp, pot;
        
        // 新手村的拿不到
        
        if (! objectp(me))return 0;
        
        if (! arg || arg != "hongbao")
                return notify_fail("你要拆开什么？\n");
                
        if (environment(this_object()) != me)
                return notify_fail("你身上没有这样东西呀。\n");
                
        i = 8000 + random(2000);
        exp = 80000 + random(20001);
        pot = 80000 + random(20001);

        message_vision(HIR "$N一阵兴奋，赶紧将红包拆开，用无比期待地眼神朝红包内一望，刹那间，一阵光环"
                       "将$N笼罩 ……\n" NOR, me);
        
        tell_object(me, HIG "恭喜你，获得了" HIY + chinese_number(exp) + HIG "点实战经验、" HIY + chinese_number(pot) + 
                        HIG "点潜能及" HIY + chinese_number(i) + HIG "两黄金（YSG）。\n炎黄祝您「猪年吉祥 万事如意」！\n" NOR);
        
        me->add("stocks/balance", i);
        me->add("combat_exp", exp);
        me->add("potential", pot);
        
        me->save();
        
        log_file("hongbao", me->query("id") + " 于 " + ctime(time()) + " 打开红包。(/clone/misc/hongbao) \n");

        destruct(this_object());
        return 1;
}
/*
int query_autoload()
{
        return 1;
}
*/