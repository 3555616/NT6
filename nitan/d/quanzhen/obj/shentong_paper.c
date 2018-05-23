// Code of ShenZhou
// shentong_paper.c
//Can't use it in no_fight rooms By Sure
//5.2001

#include <ansi.h>
inherit ITEM;

string long_desc();

mapping default_dirs = ([
                  "north":        "��",
                  "south":        "��",
                  "east":         "��",
                  "west":         "��",
                  "northup":      "����",
                  "southup":      "�ϱ�",
                  "eastup":       "����",
                  "westup":       "����",
                  "northdown":    "����",
                  "southdown":    "�ϱ�",
                  "eastdown":     "����",
                  "westdown":     "����",
                  "northeast":    "����",
                  "northwest":    "����",
                  "southeast":    "����",
                  "southwest":    "����",
                  "up":           "��",
                  "down":         "��",
                  "out":          "��",
                  "enter":        "��",
]);

void create()
{
                  set_name("������ͨ���ؾ�", ({"shentong mijue", "mijue"}));
                  set_weight(100);
                  if( clonep() )
                                         set_default_object(__FILE__);
                  else {
                                         set("unit", "��");
                                         set("long", (: long_desc :));
                                         set("value", 10000000);
                                         set("material", "paper");
                                         set("no_drop","�������������뿪�㡣\n");
                  }
}

string long_desc()
{
        string desc;

        if( random(2) )
        {
          desc ="

������ͨ���ؾ�

������ͨ��ϵ��ɽ��������á�����׳�������ڿ����ҵ����С����ս��
ɱ�������������γ�͢��������������֮ʿ�㱻ɱ�����й�֮���������š�
�������Ļ��죬���ҳ������Ѿ�������������Ϊ��Ϊ���һ���������֮��
�࿮֮̾�࣬��������ͬ��֮ʿ���޻�����Ĺ�����������Ϊ�պ�ɽ
����֮�������ִ�ȫ��̣��㴫��ͽ���ڷ���֮�������ҽ���ͽ�ܳ�Ϊ��
����֮�����������Ҵ������ˣ�ȫϵ�����ˡ���չض��꣬����ں������
��Ӣ�д��Σ���ζ������澭���մ󳹴��򣬵óɴ�������������ģ�
���߽������꣬���ܾ޴���Σ���������ŷ�����ս���Σ��������󡹦��
�������ܾ綾��Ԫ�����ˣ��ֲ��վ�Ҫ���졣ϧ��ͽ������һ�㣬������
�����湦��ʦ�ܲ�ͨ��������ѣ����ѷǴ���֮�����Ҳ�ͨ��������ȥ֮
�󣬿����������վ�Ҫ����ˣ���Ҳ�����������������ؾ������ڼ���֮
�����պ���Ե�����ܻ�ô˾��������ܵô˾������Ǽ�Ϊ��Ե�����˻��ģ�
ȫ�����꣬���겻��������������ϰ�ɴ˹����ɽ���Ϊ��ͽ���պ�������
���壬�����е���

����ɽ������
\n";
        }
        else desc="
�����ؾ�����������Ƨ��֮�����ִ��ؾ�������Ǳ������(xiulian)��
�ѻ����뵱���߻���ħ���˹��������ã��볣���͸����д�(qiecuo)��\n";


return desc;
}


void init()
{
        add_action("do_xiulian","xiulian");
        add_action("do_xiulian","xiu");
        add_action("do_qiecuo","qiecuo");
}

int do_xiulian(string arg)
{
        object me = this_player();
        object here=environment(me);
                object where;

                seteuid(getuid());
        where = environment(me);

        if(me->is_busy())return notify_fail("����æ���ء�\n");
                if( query("no_fight", where) )
                return notify_fail("��ֻ�����������أ��޷����������\n");
        if( query("neili", me)<1000)return notify_fail("���������㣬�޷�������\n");
        if( query("jingli", me)<1000)return notify_fail("�㾫�����㣬�޷�������\n");
        if(me->query_skill("xiantian-gong",1)<300)return notify_fail("�����칦����̫��޷�������\n");
        if(me->query_skill("force",1)<300)return notify_fail("���ڹ�����̫��޷�������\n");
        if(me->query_skill("taoism",1)<300)return notify_fail("���ѧ����̫��޷�������\n");
        if( query("shen", me)<3500000)return notify_fail("����������֮�����ò������������㣬�޷�������\n");

        if( query("quanzhen/shentong_times", me)>20 )
        {
                set("can_perform/xiantian-gong/shen", 1, me);
                return notify_fail("�������Ѿã���ȥʵսӦ��һ���ˡ�\n");
        }

        message_vision(
HIG"$N���մ�����ͨ���ؾ��������������칦�������֮���������Ϲ��������裬
͸ʮ����¥�������أ�ͨ�ζ��������⵽������������\n"NOR,me);

        me->start_busy( 1+random(5) );

        call_out("done",1+random(10) );

        return 1;
}

void done()
{
        object me = this_player();
        object here=environment(me);
        int marries=query("married/times", me);
        object where;


        if( random(marries) > 0 )
        {
                message_vision(
HIY"$Nֻ��Ԫ�����㣬��Ҫ��ͨ�Ķ���ֻ��һ˿˿������ƫƫ���ǹ���ȥ���۵ó���һ���󺹡�\n"NOR,me);
                addn("neili", -query("neili", me)/2, me);
                addn("jingli", -1000, me);
                me->improve_skill("force",100+random(400));
        }
        else
        {
                if( random(query("neili", me))>8000 )
                {
                        message_vision(
HIG"$Nֻ��������ֱͨ�ζ���Խ������Խ�ǳ��棬��̨һƬ����������ƫ���泩�ޱȡ�\n"NOR,me);
                        me->improve_skill("force",200+random(400));
                        addn("neili", -1000-random(2000), me);
                        addn("shentong", random(2), me);
                }
                else if( random(query("neili", me))>3000 )
                {
                        message_vision(
HIG"$Nֻ��������ͨ���ζ����������棬ƫ���泩�ޱȡ�\n"NOR,me);
                        if( query("potential", me) )
                        {
                                addn("potential", -1, me);
                                addn("neili", -random(50), me);
                        }
                        else addn("neili", -100-random(50), me);

                        me->improve_skill("force",100+random(100));
                }
                else
                {
                        message_vision(
HIY"$Nֻ���������㣬��Ҫ��ͨ������ֻ��һ˿˿������ƫƫ���ǹ���ȥ���۵ó���һ���󺹡�\n"NOR,me);
                        addn("neili", -100, me);
                        addn("jingli", -500, me);
                }
        }

        addn("quanzhen/shentong_times", 1, me);
}


int do_qiecuo(string arg)
{
        object me = this_player();
        object target;
        object here=environment(me);
        int skill, value;
                object where;

                seteuid(getuid());
        where = environment(me);

        if(me->is_busy())return notify_fail("����æ���ء�\n");
                if( query("no_fight", where) )
                return notify_fail("���Ե���ͷ��������һ�������ܾ�������һ��ɱ����\n");
        if(!arg)return notify_fail("�����˭�д裿\n");
        target = present(arg,here);
        if(!target)return notify_fail("�����˭�д裿\n");

        if( query("race", target) != "����")return notify_fail("��ϧ���������¡�\n");
        if( query("combat_exp", target)*3<query("combat_exp", me)*2 )
                return notify_fail("�����书̫��޷������д衣\n");

        if(!living(target)) return notify_fail("��õ��˼����˲��С�\n");
        if(target->is_busy())return notify_fail("�˼���æ���ء�\n");

        if( query("neili", me)<1000)return notify_fail("���������㣬�޷��д衣\n");
        if( query("jingli", me)<1000)return notify_fail("�㾫�����㣬�޷��д衣\n");
        if(me->query_skill("xiantian-gong",1)<300)return notify_fail("�����칦����̫��޷��д衣\n");
        if(me->query_skill("force",1)<300)return notify_fail("���ڹ�����̫��޷��д衣\n");
        if(me->query_skill("taoism",1)<300)return notify_fail("���ѧ����̫��޷��д衣\n");

        if( query("quanzhen/shentong_times", me)<1)return notify_fail("�㴿����ͨδ���Ѿã���ȥ����һ���ˡ�\n");

        message_vision(
HIG"$N���մ�����ͨ���ؾ��������������칦�������֮���������Ϲ��������裬
͸ʮ����¥�������أ�ͨ�ζ��������⵽������������\n"NOR,me);
        message_vision(
HIW"$N�����Ž�����ƫ��ȫ����ֻ������������ȫ����˫�۾������䣬��ƽʱ�������ˡ�\n" NOR, me);

        message_vision(
HIR"$N����ͻȻ���ƹ���$n��������������Ϣ��ȴѸ�����硣\n" NOR, me,target);

                  skill = me->query_skill("force");
                  addn("neili", -skill*2, me);
                  set("jiali", 0, me);
                  value=skill*(5+random(query("shentong", me)*5));
                  if( value > 90000 ) value = 90000;
                  if( value < 30000 ) value = 30000;
                  addn("jingli", value, me);
                  addn_temp("apply/attack", value/200, me);
                  COMBAT_D->do_attack(me,target,query_temp("weapon", me));
                  me->start_busy(1+random(2));
                  addn("jingli", -value, me);
                  addn_temp("apply/attack", -value/200, me);
                  me->improve_skill("force",50+random(100));

                  if( random(10)==1 ) call_out("run_away",0,target);

                  set("quanzhen/shentong_times",query("quanzhen/shentong_times",  me)-4, me);

        return 1;
}

void destroy_me(object ob)
{
        message_vision(HIR"$N��������ͨ�������������������ɵ���������˲����ڵ�������������������
˵��ת�����Ⱦ��ܣ������ӻ��죬ת�۾Ͳ����ˡ�\n"NOR,ob);
        destruct(ob);
}

void run_away(object ob)
{
        object obj;
        object here = environment(ob);
        string *dirs,dir,dest,target_dir;
        mapping exit;

        if(!ob)return;
        if(!here || !objectp(here) )return;

        if( !userp(ob) && random(100)==1 )
        {
                call_out("destroy_me",1,ob);
                return;
        }

        if(random(5) != 0) call_out("run_away",0,ob);

        message_vision(HIR"$N��������ͨ�������������ƣ����ɵ���������˲���\n"NOR,ob);

        exit=query("exits", here);
        if( !exit ) return;
        dirs = keys(exit);
        if (sizeof(dirs) > 0)
        dir = dirs[random(sizeof(dirs))];
        if(!dir)return;
        dest = exit[dir];
        if( !dest )return;

        if( !(obj = find_object(dest)) )
                call_other(dest, "???");
        if( !(obj = find_object(dest)) )
                return;
        if( !wizardp(ob) && query("short", obj) == "��ʦ��Ϣ��" )
                return;

        if( !undefinedp(default_dirs[dir]) )
                                         target_dir = default_dirs[dir];
                  else
                                         target_dir = dir;


        if( ob->move(obj) ) {
                        message_vision(HIY"ֻ��$N������Ǻ���˹�����\n" NOR, ob);
        }
}