// This program is a part of NT MudLIB
// huang.c ��ҩʦ

#include <ansi.h>
#include "taohua.h"

#define TAOHUA    "/clone/book/taohua"
#define XIAOPU    "/clone/book/xiaopu"
#define XUANFENG  "/clone/book/xuanfengtui"
//#define YUXIAO    "/clone/unique/yuxiao"
#define YUXIAO    "/clone/lonely/yuxiao"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;
inherit F_QUESTER;

void   consider();
int    ask_shagu();

mixed  ask_leave();
mixed  ask_book1();
mixed  ask_book2();
mixed  ask_book3();
mixed  ask_book4();
mixed  ask_yuxiao();

mixed  ask_skill1();
mixed  ask_skill2();
mixed  ask_skill3();
mixed  ask_skill4();
mixed  ask_skill5();
mixed  ask_skill6();
mixed  ask_skill7();
mixed  ask_skill8();
mixed  ask_skill9();
mixed  ask_skill10();
mixed  ask_skill11();

mixed  try_to_learn_bibai();
mixed  try_to_learn_count();

string* xuedao = ({
        "���Ѩ", "�縮Ѩ", "ǿ��Ѩ", "��׵Ѩ", "����Ѩ",
        "�ٻ�Ѩ", "��̨Ѩ", "̫��Ѩ", "����Ѩ", "����Ѩ",
});

void create()
{
        object ob;
        set_name("��ҩʦ", ({"huang yaoshi", "huang", "yaoshi"}));
        set("title", "�����һ�������");
        set("nickname", HIC "��а" NOR );
        set("gender", "����");
        set("age", 42);
        set("long", "�������һ����������ºö�ȫ�ɼ��ģ���˱�\n"
                    "�˳�������а����\n");
        set("attitude", "peaceful");
        set("class", "scholar");
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("qi", 7000);
        set("max_qi", 7000);
        set("jing", 5000);
        set("max_jing", 5000);
        set("neili", 7000);
        set("max_neili", 7000);
        set("jiali", 200);
        set("level", 60);
        set("combat_exp", 4000000);

        set_skill("force", 600);
        set_skill("bibo-shengong", 600);
        set_skill("hand", 620);
        set_skill("finger", 600);
        set_skill("tanzhi-shentong", 600);
        set_skill("unarmed", 600);
        set_skill("strike", 600);
        set_skill("luoying-shenzhang", 600);
        set_skill("xuanfeng-tui", 600);
        set_skill("dodge", 600);
        set_skill("luoying-shenfa", 620);
        set_skill("parry", 600);
        set_skill("sword", 600);
        set_skill("throwing", 600);
        set_skill("luoying-shenjian", 600);
        set_skill("yuxiao-jianfa", 600);
        set_skill("lanhua-shou", 600);
        set_skill("whip", 600);
        set_skill("canglang-bian", 600);
        set_skill("qimen-wuxing", 2100);
        set_skill("count", 2100);
        set_skill("mathematics", 2100);
        set_skill("literate", 2100);
        set_skill("chuixiao-jifa", 600);
        set_skill("bihai-chaosheng", 600);
        set_skill("taohua-yuan", 600);
        set_skill("calligraphy", 600);
        set_skill("medical", 600);
        set_skill("taoism", 400);
        set_skill("taohua-yaoli", 600);
        set_skill("qimen-xuanshu", 600);
        set_skill("martial-cognize", 620);

        map_skill("force", "bibo-shengong");
        map_skill("finger", "tanzhi-shentong");
        map_skill("hand", "lanhua-shou");
        map_skill("unarmed", "xuanfeng-tui");
        map_skill("whip", "canglang-bian");
        map_skill("strike", "luoying-shenzhang");
        map_skill("dodge", "luoying-shenfa");
        map_skill("parry", "tanzhi-shentong");
        map_skill("sword", "yuxiao-jianfa");
        map_skill("chuixiao-jifa", "bihai-chaosheng");
        map_skill("throwing", "tanzhi-shentong");
        map_skill("medical", "taohua-yaoli");

        prepare_skill("finger" , "tanzhi-shentong");

        set("no_teach", ([
                "count"           : (: try_to_learn_count :),
                "bihai-chaosheng" : (: try_to_learn_bibai :),
        ]));

        set("inquiry", ([
                "�뵺"       : (: ask_leave :),
                "�һ�ҩ��"   : (: ask_book1 :),
                "����"       : (: ask_book2 :),
                "����ɨҶ��" : (: ask_book3 :),
                "��ͼ"       : (: ask_book4 :),
                "����"       : (: ask_book4 :),
                "����"       : (: ask_yuxiao :),
                "������ת"   : (: ask_skill1 :),
                "������Ѩ"   : (: ask_skill2 :),
                "Ӱ��ɻ�"   : (: ask_skill3 :),
                "��������"   : (: ask_skill4 :),
                "����鳤"   : (: ask_skill5 :),
                "�̺�����"   : (: ask_skill6 :),
                "������"     : (: ask_skill7 :),
                "Х�׺�"     : (: ask_skill8 :),
                "�ƾ���"     : (: ask_skill9 :),
                "תǬ��"     : (: ask_skill10 :),
                "���컨��"     : (: ask_skill11 :),
                "ɵ��"       : (: ask_shagu :),
                "��������"   : "������ȥ�÷�Ĭ�����ɡ�",
                "���Ǵ���"   : "������ȥ��½�˷����ɡ�",
                "������"   : "������ȥ��½�˷����ɡ�",
                "�沨����"   : "������ȥ����������ɡ�",
                "����"       : "���ֱ����Ů���Ĺ�����",
                "�����澭"   : "������ܰ���ȡ���澭����һ������л�㡣",
                "������"   : "�����񹦻ֺ������˸����湦��",
                "������"     : "������Ѩ�֡�������ϧ�Ҽ������Ӷ��㲻�óɲţ�",
                "��ָ��ͨ"   : "��������һ�����վ�Ȼ���˿��Լ̳У�",
                "��������"   : "�����������ˣ�����ܹ�����⽣����",
                "�̲���"   : "���������һ������ڹ��ε���������ϧ��",
                "�Ż���¶��" : "����������Ƶý�����ú�ѧѧ�һ�ҩ�����Ժ��Լ��ưɡ�",
                "�޳���"     : "���š�����ѧͨ���һ�ҩ���İ���Լ������ưɡ�",
        ]));

        create_family("�һ���", 1, "����");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.bihai" :),
                (: perform_action, "sword.qing" :),
                (: perform_action, "sword.tian" :),
                (: perform_action, "finger.ding" :),
                (: perform_action, "finger.xiao" :),
                (: perform_action, "finger.po" :),
                (: perform_action, "finger.zhuan" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob", 5);
        setup();

        if (clonep())
        {
                ob = find_object(YUXIAO);
                if (! ob) ob = load_object(YUXIAO);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        set_temp("handing", ob);
                } else
                {
                        set_temp("handing", carry_object("/d/taohua/obj/huaban"));
                }
        }
        carry_object(__DIR__"obj/bupao")->wear();
        // carry_object("/clone/book/jiuyin2");
}

void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()))
        {
                if( query_temp("th_tomb_thief", ob) )
                {
                        command("say " + RANK_D->query_rude(ob) + "������˽���ҷ���Ĺ�ң���������\n");
                        start_busy(1);
                        kill_ob(ob);
                }
                if( query("th_killer", ob) || query_temp("th_killer", ob) )
                {
                        command("sneer"+query("id", ob));
                        command("say ��ͽ�ô��ӣ���Ȼͬ�ŵ���������У�");
                        message_vision(HIR "��ҩʦ˵��һ̧�֣�һָ����$N��" +
                                       xuedao[random(sizeof(xuedao))] + "�ϡ�\n" NOR, ob);
                        call_out("move_it", 1, ob);
                }

                if( query("kill_th_traitor", ob )
                 && query("help_chengfeng", ob )
                 && query("help_lingfeng", ob )
                 && query("help_mofeng", ob) )
                {
                        set_temp("huang_recr", 1, ob);
                        command("smile "+query("id", ob));
                }
        }
}

void move_it(object ob)
{
        object *inv;
        int k;

        if (ob)
        {
                set("eff_qi", 10, ob);
                set("eff_jing", 10, ob);
                set("jing", 0, ob);
                delete("th_killer", ob);
                delete_temp("th_killer", ob);

                inv = all_inventory(ob);
                for (k = 0; k < sizeof(inv); k++)
                {
                        if( (query("armor_prop", inv[k]) && query("equipped", inv[k]) )
                         || query("no_get", inv[k]) )
                                continue;
                        destruct(inv[k]);
                }
                ob->unconcious();
                ob->move("/d/taohua/maze/maze"+(random(63)+1));
        }
}

void attempt_apprentice(object ob)
{
        string master;
        string *app = ({ "½�˷�", "�����" });
        object obj;

        if (! permit_recruit(ob))
                return;

        if (ob->query_int() < 25)
        {
                command("say �Ҳ������ʲ�ĵ��ӣ�����ذɣ�");
                return;
        }

        if( query("shen", ob)<-10000
         || query("shen", ob)>10000 )
        {
                command("say �Ҳ����������򽻵�������ذɣ�");
                return;
        }
        /*
        if( query("combat_exp", ob)<400000 )
        {
                if( stringp(master=query_temp("taohua/master", ob)) )
                {
                        command("say ���������" + master + "ѧ��������ô���£�");
                        return;
                }

                if( query("family/family_name", ob) == "�һ���" && 
                    query("family/master_name", ob) != "��ҩʦ" )
                {
                        command("say��úø�"+query("family/master_name", ob)+
                                "ѧ�գ�ˮƽ�����Ϸ���Ȼ�����Ե㲦�㡣");
                        return;
                }

                master = app[random(sizeof(app))];

                command("say �š����㳤;���������ʦ���Ϸ���������һ�����");
                command("say ��������ѧ����ɾ����ޣ������ȸ��ҵ���" + master + "ѧϰ�ɡ�");
                set_temp("taohua/master", master, ob);
                set("family/family_name", "�һ���", ob);
                return;
        }
        */

        if( !query_temp("huang_recr", ob) && !query("reborn", ob) )
        {
                tell_object(ob, "��ҩʦ�����Ҳ���ǡ�\n");
                return;
        }

        command("say �ܺã��ܺá�");
        command("recruit "+query("id", ob));

        obj = new("/d/taohua/obj/bagua");
        obj->move(this_object());

        command("give "+query("id", ob)+" bagua");

        if( query("short", environment(this_object())) != "��ҩʦ�Ӵ�" )
        {
                write("˵�꣬��ҩʦƮȻ��ȥ��\n");
                destruct(this_object());
        }
}

int recognize_apprentice(object me, string skill)
{
        if( !query("can_learn/huang/count", me) )
        {
                command("say ����˭���������ģ�Ҫ��ɶ��");
                return -1;
        }

        if (skill != "count"
            && skill != "mathematics"
            && skill != "chuixiao-jifa")
        {
                command("say �Ͻл�����ʲô��ѧʲô���㲻ѧ�����ˡ�");
                return -1;
        }

        if ((int)me->query_skill("count", 1) > 379)
        {
                command("say ����Ϊֹ����Ĺ���Ҳ�����ˣ�ʣ�µ��Լ�ȥ����");
                return -1;
        }

        return 1;
}

mixed try_to_learn_count()
{
        object ob = this_player();

        if( query("can_learn/huang/count", ob) )
                return 0;

        if (ob->query_skill("mathematics", 1) >= 200)
        {
                command("nod2");
                command("say �����������Ҳ���м��⣬�����Ϸ�ͽ�"
                        "��Щ�������Ե�֪ʶ��");
                set("can_learn/huang/count", 1, ob);
                return 0;
        }
        return "���������Ҳ����״��ڡ�";
}

mixed try_to_learn_bibai()
{
        object ob = this_player();

        if( query("can_learn/huang/bihai-chaosheng", ob) )
                return 0;

        if (ob->query_skill("bibo-shengong", 1) >= 120
        &&  ob->query_skill("chuixiao-jifa", 1) >= 120)
        {
                command("sigh");
                command("say �벻����������Ȼ�Ѵ�˾��磬�����Ϸ�"
                        "�ʹ���̺��������ɡ�");
                set("can_learn/huang/bihai-chaosheng", 1, ob);
                return 0;
        }
        return "�����������ˣ���̺������������ʺ��㡣";
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/luoying-shenzhang/zhuan", me) )
                return "��һ���Ҳ����Ѿ��̹������𣿻�����ʲô��";

        if( query("family/family_name", me) != query("family/family_name") )
                return "�㲻�������һ������ˣ������Ϸ���书�к���ͼ��";

        if (me->query_skill("luoying-shenzhang", 1) < 1)
                return "������Ӣ���ƶ�ûѧ��������ʲô�ң�";

        if( query("family/gongji", me)<350 )
                return "�������һ���������Ϊ�������Ϸ���ʱ�����ܴ��㡣";

        if (me->query_skill("force") < 180)
                return "����ڹ����������ߣ������������ɡ�";

        if (me->query_skill("qimen-wuxing", 1) < 120)
                return "����������е��о����������л�ѧ���ᡣ";

        if (me->query_skill("luoying-shenzhang", 1) < 120)
                return "�ߣ��������Ӣ�����������������ң�";

        message_sort(HIY "\n$n" HIY "������$N" HIY "һ�ۣ����ֹ���һ�ơ�$N" HIY
                     "������ƽƽ���������棬��֪�������ֵ���һ˲��ŷ���$n" HIY
                     "��������ƺӾ��̰���ӿ���룬$N" HIY "��ʱ��Ҳ�ѳֲ�ס����"
                     "���������ý�����ת����Ȧ���ò����ײ�ͣ��������\n\n" NOR,
                     me, this_object());

        command("say ���ˣ�����ȥ�ɡ�");
        tell_object(me, HIC "��ѧ���ˡ�������ת����\n" NOR);
        if (me->can_improve_skill("qimen-wuxing"))
                me->improve_skill("qimen-wuxing", 1500000);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("luoying-shenzhang"))
                me->improve_skill("luoying-shenzhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/luoying-shenzhang/zhuan", 1, me);
        addn("family/gongji", -350, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/lanhua-shou/fu", me) )
                return "�Լ���ȥ��������ʲô��";

        if( query("family/family_name", me) != query("family/family_name") )
                return "�㲻�������һ������ˣ������Ϸ���书�к���ͼ��";

        if (me->query_skill("lanhua-shou", 1) < 1)
                return "����������Ѩ�ֶ�ûѧ��������ʲô�ң�";

        if( query("family/gongji", me)<300 )
                return "�������һ���������Ϊ�������Ϸ���ʱ�����ܴ��㡣";

        if (me->query_skill("force") < 160)
                return "����ڹ����������ߣ������������ɡ�";

        if (me->query_skill("lanhua-shou", 1) < 120)
                return "�����������Ѩ���������������Ϸ�";

        message_sort(HIY "\n$n" HIY "΢΢���˵�ͷ���������������ָ����ת��һ��"
                     "ʢ������������׼$N" HIY "�ļ���Ѩ��������¡�\n\n" NOR,
                     me, this_object());

        command("say ������ô��");
        tell_object(me, HIC "��ѧ���ˡ�������Ѩ����\n" NOR);
        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("lanhua-shou"))
                me->improve_skill("lanhua-shou", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/lanhua-shou/fu", 1, me);
        addn("family/gongji", -300, me);

        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/lanhua-shou/fei", me) )
                return "�������Լ���ȥ���ɡ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return "�㲻�������һ������ˣ������Ϸ���书�к���ͼ��";

        if (me->query_skill("lanhua-shou", 1) < 1)
                return "����������Ѩ�ֶ�ûѧ��������ʲô�ң�";

        if( query("family/gongji", me)<400 )
                return "�������һ���������Ϊ�������Ϸ���ʱ�����ܴ��㡣";

        if (me->query_skill("force") < 200)
                return "����ڹ����������ߣ������������ɡ�";

        if (me->query_skill("lanhua-shou", 1) < 140)
                return "�����������Ѩ���������������Ϸ�";

        message_sort(HIY "\n$n" HIY "һ����̾�����ֽ�$N" HIY "���������ԣ�����"
                     "��$N" HIY "����ϸ˵���á�$N" HIY "һ����һ�ߵ�ͷ��������"
                     "$n" HIY "�Ľ̵���������\n\n" NOR, me, this_object());

        command("say �������Լ���ȥ���ɡ�");
        tell_object(me, HIC "��ѧ���ˡ�Ӱ��ɻ�����\n" NOR);
        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("lanhua-shou"))
                me->improve_skill("lanhua-shou", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/lanhua-shou/fei", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();

        if( query("can_perform/yuxiao-jianfa/tian", me) )
                return "��һ���Ҳ����Ѿ��̹������𣿻�����ʲô��";

        if( query("family/family_name", me) != query("family/family_name") )
                return "�㲻�������һ������ˣ������Ϸ���书�к���ͼ��";

        if (me->query_skill("yuxiao-jianfa", 1) < 1)
                return "�������｣����ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<350 )
                return "�������һ���������Ϊ�������Ϸ���ʱ�����ܴ��㡣";

        if (me->query_skill("bibo-shengong", 1) < 120)
                return "��̲��񹦵���Ϊ������ѧ������һ�С�";

        if (me->query_skill("yuxiao-jianfa", 1) < 120)
                return "������｣���������������������������ҡ�";

        message_sort(HIY "\n$n" HIY "΢΢���˵�ͷ�����ֽ�$N" HIY "�е���ǰ����"
                     "$N" HIY "���������ֹ���Щ����$N" HIY "���˰��죬ͻȻ�䲻"
                     "�ɻ��ĵ�һЦ��������������\n\n" NOR, me, this_object());

        command("nod2");
        command("say ����ȥ���ɡ�");
        tell_object(me, HIC "��ѧ���ˡ�������������\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("yuxiao-jianfa"))
                me->improve_skill("yuxiao-jianfa", 1500000);
        if (me->can_improve_skill("bibo-shengong"))
                me->improve_skill("bibo-shengong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/yuxiao-jianfa/tian", 1, me);
        addn("family/gongji", -350, me);

        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();

        if( query("can_perform/yuxiao-jianfa/qing", me) )
                return "��һ���Ҳ����Ѿ��̹������𣿻�����ʲô��";

        if( query("family/family_name", me) != query("family/family_name") )
                return "�㲻�������һ������ˣ������Ϸ���书�к���ͼ��";

        if (me->query_skill("yuxiao-jianfa", 1) < 1)
                return "�������｣����ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<400 )
                return "�������һ���������Ϊ�������Ϸ���ʱ�����ܴ��㡣";

        if (me->query_skill("force") < 200)
                return "����ڹ����������ߣ������������ɡ�";

        if (me->query_skill("yuxiao-jianfa", 1) < 150)
                return "������㱾�£���������｣���������������Ұɣ�";

        message_sort(HIY "\n$n" HIY "��ͷ���죬������˼�����ִ���$N" HIY "�ļ�"
                     "ͷ��$N" HIY "��Ȼ��������ԴԴ���ţ����ɴ󾪣�\n\n" NOR,
                     me, this_object());

        command("sigh");
        command("say �㶮��ô��");
        tell_object(me, HIC "��ѧ���ˡ�����鳤����\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("yuxiao-jianfa"))
                me->improve_skill("yuxiao-jianfa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/yuxiao-jianfa/qing", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}

mixed ask_skill6()
{
        object me;

        me = this_player();

        if( query("can_perform/yuxiao-jianfa/bihai", me) )
                return "��һ���Ҳ����Ѿ��̹������𣿻�����ʲô��";

        if( query("family/family_name", me) != query("family/family_name") )
                return "�㲻�������һ������ˣ������Ϸ���书�к���ͼ��";

        if (me->query_skill("yuxiao-jianfa", 1) < 1
        &&  me->query_skill("bibo-shengong", 1) < 1
        &&  me->query_skill("bihai-chaosheng", 1) < 1)
                return "�����｣�����̲��񹦡��̺�������һ����ûѧ����ʲô�ң�";

        if( query("family/gongji", me)<1000 )
                return "�������һ���������Ϊ�������Ϸ���ʱ�����ܴ��㡣";

        if (me->query_skill("bibo-shengong", 1) < 180)
                return "��̲��񹦵���Ϊ������ѧ������һ�С�";

        if (me->query_skill("yuxiao-jianfa", 1) < 180)
                return "������｣���������������������������ҡ�";

        if (me->query_skill("bihai-chaosheng", 1) < 180)
                return "��ı̺���������������";

        message_sort(HIY "\n$n" HIY "�����𻰣����ָ������ֻ�������������ٻ�"
                     "�񣬷��˼����������������Ʈ��������͵Ķ���������ֻ����"
                     "����������Ʈ����������ת������һŮ��һ���̾Ϣ��һ�������"
                     "������һ���ȴ�������´�������л������������������������"
                     "�������������޲���Զ����ˮ�����ƽ����������죬��������ӿ"
                     "��������ɽ������ˮ����Ծ�����������Ϸ�ХŸ�ɣ��ټ���ˮ����"
                     "�֣�ȺħŪ����������ɽƮ���������Ⱥ���У��������֮���¡�"
                     "ʱ�����ȴ��������������ϸ�������������ţ�������󺣳���"
                     "��ˮƽ�羵һ�㣬������ȴ���ǰ����ļ�����ӿ���ȡ�ֱ��$n" HIY
                     "���ױ̺����������꣬ȴ����$N" HIY "����������������֮�У���"
                     "ȫ�޷��԰Ρ�\n\n" NOR, me, this_object());

        command("nod");
        command("say ����ȥ���ɡ�");
        tell_object(me, HIC "��ѧ���ˡ��̺������������\n" NOR);

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("chuixiao-jifa"))
                me->improve_skill("chuixiao-jifa", 1500000);
        if (me->can_improve_skill("yuxiao-jianfa"))
                me->improve_skill("yuxiao-jianfa", 1500000);
        if (me->can_improve_skill("bibo-shengong"))
                me->improve_skill("bibo-shengong", 1500000);
        if (me->can_improve_skill("bihai-chaosheng"))
                me->improve_skill("bihai-chaosheng", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/yuxiao-jianfa/bihai", 1, me);
        addn("family/gongji", -1000, me);

        return 1;
}

mixed ask_skill7()
{
        object me;

        me = this_player();

        if( query("can_perform/tanzhi-shentong/ding", me) )
                return "��һ���Ҳ����Ѿ��̹������𣿻�����ʲô��";

        if( query("family/family_name", me) != query("family/family_name") )
                return "�㲻�������һ������ˣ������Ϸ���书�к���ͼ��";

        if (me->query_skill("tanzhi-shentong", 1) < 1)
                return "������ָ��ͨ��ûѧ��Ϲ����ʲô��";

        if( query("family/gongji", me)<450 )
                return "�������һ���������Ϊ�������Ϸ���ʱ�����ܴ��㡣";

        if (me->query_skill("force") < 180)
                return "����ڹ����������ߣ������������ɡ�";

        if (me->query_skill("tanzhi-shentong", 1) < 120)
                return "��ĵ�ָ��ͨ��򻹲����������������������ҡ�";

        message_sort(HIY "\n$n" HIY "ת��ͷ����$N" HIY "һ�ۣ������𻰣�ֻ����"
                     "�������ָ����ָ�ᵯ����ʱֻ����쬡���һ����һ����������"
                     "���������$n" HIY "ָ���������$N" HIY "�����ȥ��$N" HIY
                     "�پ�в��һ�飬�ѱ�$n" HIY "��ָ�����У�ȫ����������������"
                     "������\n\n" NOR, me, this_object());

        command("say ��ʽ������ˣ���վ��������ĥһ�°ɡ�");
        tell_object(me, HIC "��ѧ���ˡ������ء���\n" NOR);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("tanzhi-shentong"))
                me->improve_skill("tanzhi-shentong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/tanzhi-shentong/ding", 1, me);
        addn("family/gongji", -450, me);
        me->start_busy(15);

        return 1;
}

mixed ask_skill8()
{
        object me;

        me = this_player();

        if( query("can_perform/tanzhi-shentong/xiao", me) )
                return "��һ���Ҳ����Ѿ��̹������𣿻�����ʲô��";

        if (me->query_skill("tanzhi-shentong", 1) < 1)
                return "������ָ��ͨ��ûѧ��Ϲ����ʲô��";

        if( query("family/gongji", me)<800 )
                return "�������һ���������Ϊ�������Ϸ���ʱ�����ܴ��㡣";

        if (me->query_skill("force") < 280)
                return "����ڹ����������ߣ������������ɡ�";

        if( query("max_neili", me)<3000 )
                return "���������Ϊ̫��������ߵ������ɡ�";

        if (me->query_skill("tanzhi-shentong", 1) < 200)
                return "��ĵ�ָ��ͨ��򻹲����������������������ҡ�";

        message_sort(HIY "\n$n" HIY "һ����̾�����ֽ�$N" HIY "���������ԣ�����"
                     "��$N" HIY "����ϸ˵���á�$N" HIY "һ����һ�ߵ�ͷ��������"
                     "$n" HIY "�Ľ̵���������\n\n" NOR, me, this_object());

        command("nod2");
        command("say ���š����Լ���ȥ�ɡ�");
        tell_object(me, HIC "��ѧ���ˡ�Х�׺�����\n" NOR);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("tanzhi-shentong"))
                me->improve_skill("tanzhi-shentong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/tanzhi-shentong/xiao", 1, me);
        addn("family/gongji", -800, me);

        return 1;
}

mixed ask_skill9()
{
        object me;

        me = this_player();

        if( query("can_perform/tanzhi-shentong/po", me) )
                return "��һ���Ҳ����Ѿ��̹������𣿻�����ʲô��";

        if( query("family/family_name", me) != query("family/family_name") )
                return "�㲻�������һ������ˣ������Ϸ���书�к���ͼ��";

        if (me->query_skill("tanzhi-shentong", 1) < 1)
                return "������ָ��ͨ��ûѧ��Ϲ����ʲô��";

        if( query("family/gongji", me)<1300 )
                return "�������һ���������Ϊ�������Ϸ���ʱ�����ܴ��㡣";

        if (me->query_skill("force") < 250)
                return "����ڹ����������ߣ������������ɡ�";

        if( query("max_neili", me)<2500 )
                return "���������Ϊ̫��������ߵ������ɡ�";

        if (me->query_skill("throwing", 1) < 180)
                return "��İ������û�������죬��ȥ���������ɡ�";

        if (me->query_skill("tanzhi-shentong", 1) < 180)
                return "��ĵ�ָ��ͨ��򻹲����������������������ҡ�";

        message_sort(HIY "\n$n" HIY "΢΢һЦ������Ҳ���������ִ������һ���"
                     "������һƬ���꣬$N" HIY "�������ƣ������ƿ�����������Ƭ"
                     "��������$n" HIY "ָ�⼲����������ʱֻ������һ������û��"
                     "$N" HIY "��ǰ����ʯש�ڣ�ʯ�������һ��С�ס�\n\n" NOR,
                      me, this_object());

        command("haha");
        tell_object(me, HIC "��ѧ���ˡ��ƾ��򡹡�\n" NOR);
        if (me->can_improve_skill("throwing"))
                me->improve_skill("throwing", 1500000);
        if (me->can_improve_skill("throwing"))
                me->improve_skill("throwing", 1500000);
        if (me->can_improve_skill("tanzhi-shentong"))
                me->improve_skill("tanzhi-shentong", 1500000);
        if (me->can_improve_skill("tanzhi-shentong"))
                me->improve_skill("tanzhi-shentong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/tanzhi-shentong/po", 1, me);
        addn("family/gongji", -1300, me);

        return 1;
}

mixed ask_skill10()
{
        object me;

        me = this_player();

        if( query("can_perform/tanzhi-shentong/zhuan", me) )
                return "��һ���Ҳ����Ѿ��̹������𣿻�����ʲô��";

        if( query("family/family_name", me) != query("family/family_name") )
                return "�㲻�������һ������ˣ������Ϸ���书�к���ͼ��";

        if (me->query_skill("tanzhi-shentong", 1) < 1)
                return "������ָ��ͨ��ûѧ��Ϲ����ʲô��";

        if( query("family/gongji", me)<2200 )
                return "�������һ���������Ϊ�������Ϸ���ʱ�����ܴ��㡣";

        if (me->query_skill("force") < 300)
                return "����ڹ����������ߣ������������ɡ�";

        if( query("max_neili", me)<3500 )
                return "���������Ϊ̫��������ߵ������ɡ�";

        if (me->query_skill("qimen-wuxing", 1) < 200)
                return "����������е��о����������л�ѧ���ᡣ";

        if (me->query_skill("tanzhi-shentong", 1) < 220)
                return "��ĵ�ָ��ͨ��򻹲����������������������ҡ�";

        message_sort(HIY "\n$n" HIY "������$N" HIY "���죬���������벻�����һ�"
                     "����Ȼ����������˲ţ�����պ�̳��Ϸ��²�����Ī���ˡ���"
                     "$n" HIY "˵�����һЦ����$N" HIY "�������ԣ�����ϸ˵����"
                     "���ã�ȫ��$N" HIY "ƽ����δ����ľ��磬$N" HIY "һ����һ"
                     "�ߵ�ͷ��������$n" HIY "�Ľ̵���������\n\n" NOR,
                     me, this_object());

        command("haha");
        command("say �ܴ��ڵ��Ҷ��Ѵ����ˣ��պ���Լ�Ŭ���ɡ�");
        tell_object(me, HIC "��ѧ���ˡ�תǬ������\n" NOR);
        if (me->can_improve_skill("qimen-wuxing"))
                me->improve_skill("qimen-wuxing", 1500000);
        if (me->can_improve_skill("qimen-wuxing"))
                me->improve_skill("qimen-wuxing", 1500000);
        if (me->can_improve_skill("qimen-wuxing"))
                me->improve_skill("qimen-wuxing", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("tanzhi-shentong"))
                me->improve_skill("tanzhi-shentong", 1500000);
        if (me->can_improve_skill("tanzhi-shentong"))
                me->improve_skill("tanzhi-shentong", 1500000);
        if (me->can_improve_skill("tanzhi-shentong"))
                me->improve_skill("tanzhi-shentong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/tanzhi-shentong/zhuan", 1, me);
        addn("family/gongji", -2200, me);

        return 1;
}

//�������컨���PFM
mixed ask_skill11() 
{ 
        object me; 
        
        me = this_player(); 
        
        if( query("can_perform/tanzhi-shentong/huayu", me) )
                return "��һ���Ҳ����Ѿ��̹������𣿻�����ʲô��"; 
        
        if( query("family/family_name", me) != query("family/family_name") )
                return "�㲻�������һ������ˣ������Ϸ���书�к���ͼ��"; 
        
        if (me->query_skill("tanzhi-shentong", 1) < 1) 
                return "������ָ��ͨ��ûѧ��Ϲ����ʲô��"; 
        
        if( query("family/gongji", me)<2200 )
                return "�������һ���������Ϊ�������Ϸ���ʱ�����ܴ��㡣"; 
        
        if (me->query_skill("force") < 300) 
                return "����ڹ����������ߣ������������ɡ�"; 
        
        if( query("max_neili", me)<3500 )
                return "���������Ϊ̫��������ߵ������ɡ�"; 
        
        if (me->query_skill("qimen-wuxing", 1) < 200) 
                return "����������е��о����������л�ѧ���ᡣ"; 
        
        if (me->query_skill("tanzhi-shentong", 1) < 220) 
                return "��ĵ�ָ��ͨ��򻹲����������������������ҡ�"; 
        
        message_sort(HIY "\n$n" HIY "������$N" HIY "���죬���������벻�����һ�" 
                     "����Ȼ����������˲ţ�����պ�̳��Ϸ��²�����Ī���ˡ���" 
                     "$n" HIY "˵�����һЦ����$N" HIY "�������ԣ�����ϸ˵����" 
                     "���ã�ȫ��$N" HIY "ƽ����δ����ľ��磬$N" HIY "һ����һ" 
                     "�ߵ�ͷ��������$n" HIY "�Ľ̵���������\n\n" NOR, 
                     me, this_object());  
        
        command("haha"); 
        command("say �ܴ��ڵ��Ҷ��Ѵ����ˣ��պ���Լ�Ŭ���ɡ�"); 
        tell_object(me, HIC "��ѧ���ˡ����컨�꡹��\n" NOR); 
        if (me->can_improve_skill("qimen-wuxing")) 
                me->improve_skill("qimen-wuxing", 1500000); 
        if (me->can_improve_skill("qimen-wuxing")) 
                me->improve_skill("qimen-wuxing", 1500000); 
        if (me->can_improve_skill("qimen-wuxing")) 
                me->improve_skill("qimen-wuxing", 1500000); 
        if (me->can_improve_skill("finger")) 
                me->improve_skill("finger", 1500000); 
        if (me->can_improve_skill("finger")) 
                me->improve_skill("finger", 1500000); 
        if (me->can_improve_skill("finger")) 
                me->improve_skill("finger", 1500000); 
        if (me->can_improve_skill("tanzhi-shentong")) 
                me->improve_skill("tanzhi-shentong", 1500000); 
        if (me->can_improve_skill("tanzhi-shentong")) 
                me->improve_skill("tanzhi-shentong", 1500000); 
        if (me->can_improve_skill("tanzhi-shentong")) 
                me->improve_skill("tanzhi-shentong", 1500000); 
        me->improve_skill("martial-cognize", 1500000); 
        set("can_perform/tanzhi-shentong/huayu", 1, me);
        addn("family/gongji", -2200, me);
        
        return 1; 
} 

mixed ask_leave()
{
        object me;

        me = this_player();
        if( query("family/family_name", me) == "�һ���" )
        {
                message_vision(CYN "$N" CYN "��$n" CYN "ŭ�������Ȼ���һ���"
                               "���£��һ�������㲻�ã�Ҫ�뵺�Լ��ߵ�����ȥ"
                               "��\n" NOR, this_object(), me);
                return 1;
        }

        command("hmm");
        message_vision(HIW "\n$N" HIW "���һ�������������������ͣ���$n" HIW
                       "���˳�ȥ��\n\n" NOR, this_object(), me);
        me->move("/d/taohua/haitan");
        message_vision(HIW "\n$N" HIW "�������������˺��ߡ�\n\n" NOR, me);
        return 1;
}

mixed ask_book1()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( query("family/family_name", me) != "�һ���" )
                return "���ҹ�����";

        if( query("family/master_id", me) != query("id") )
                return "ֻ���Ϸ�ĵ��Ӳ��������顣";

        if ((int)me->query_skill("taohua-yaoli", 1) < 60)
                return "����һ�ҩ�����˽�̫ǳ�����������������˵��";

        ob = find_object(TAOHUA);
        if (! ob) ob = load_object(TAOHUA);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "�Ǳ�ҩ���������������ڿ���";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "���š��һ�ҩ�����ڲ��������";

                if( query("family/family_name", owner) == "�һ���" )
                        return "����������ʱ����ͬ��"+query("name", owner)+
                               "�ڿ�����Ҫ�þ�ȥ�����ɡ�";
                else
                return "�һ�ҩ������������"+query("name", owner)+
                       "���У���ȥ�������ذɡ�";
        }
        ob->move(this_object());
        command("say �Ȿ�һ�ҩ�������ȥ���ɣ���Ҫ�����ж���");
        command("give taohua yaoshu to "+query("id", me));
        return 1;
}

mixed ask_book2()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( query("family/family_name", me) != "�һ���" )
                return "���ҹ�����";

        if( query("family/master_id", me) != query("id") )
                return "ֻ���Ϸ�ĵ��Ӳ��������顣";

        if ((int)me->query_skill("chuixiao-jifa", 1) >= 150)
                return "����＼����˵ز��������׶������޶�������";

        ob = find_object(XIAOPU);
        if (! ob) ob = load_object(XIAOPU);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "�Ǳ����ײ������������ڿ���";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "�ҵ������Ѿ����ȥ�ˡ�";

                if( query("family/family_name", owner) == "�һ���" )
                        return "����������ʱ����ͬ��"+query("name", owner)+
                               "�ڿ�����Ҫ�þ�ȥ�����ɡ�";
                else
                        return "�Ϸ����������������"+query("name", owner)+
                               "���У���ȥ�������ذɡ�";
        }
        ob->move(this_object());
        command("say �Ȿ���������ȥ���ɡ�");
        command("give xiao pu to "+query("id", me));
        return 1;
}

mixed ask_book3()
{
        object me;
        object ob;

        me = this_player();

        if( query("family/family_name", me) != "�һ���" )
                return "���ҹ�����";

        command("say ����������̫���������˳˷磮����");
        command("sigh");

        if (! query("xfsy_xinfa_given") || query("xfsy_xinfa_given") < 10)
        {
                command("say �������һ���ķ����ෳ" + RANK_D->query_respect(me) +
                        "����˷磬�������⹦��ȥ�����ͳ���һ����������ȴ�ǲ��ѣ���������");
                ob = new(XUANFENG);
                ob->move(me);
                set("xfsy_xinfa_given", 1);
                message_vision("$N�ݸ�$nһ�ű�ֽ��\n", this_object(), me);
        } else
                command("say ��ȥ�ҳ˷�ɡ�");
        return 1;
}

mixed ask_book4()
{
        object me = this_player();

        if( query("family/family_name", me) != "�һ���"
         && !query("can_learn/huang/count", me) )
                return "���ҹ�����";

        if( query("combat_exp", me)<1000000 )
                return "�����ڵľ���̫�ͣ������ȶ�������������";

        if ((int)me->query_skill("count", 1) < 100)
                return "�������Ҳ����������������ʲô��";

        set_temp("taohua/countbook", 1, me);
        command("nod");
        command("say ��ȥ�������ɣ������������ڱ��ܡ�");
        return 1;
}

mixed ask_yuxiao()
{
        object me;
        object ob;
        object owner;
int cost;

        me = this_player();

        if( query("family/family_name", me) != "�һ���" )
                return "���ҹ�����";

        if( query("family/master_id", me) != query("id") )
                return "��������Ϸ�ĵ�����˵��";

        if (me->query_skill("yuxiao-jianfa", 1) < 150)
                return "�㻹���Ƚ��������������������˵��";

        if (me->query_skill("chuixiao-jifa", 1) < 150)
                return "�ߣ������ﶼ�����ã����������к��ã�";

   if( query("family/first", me) ) cost = 250; 
             else cost = 500; 
             if( query("family/gongji", me) < cost ) 
                     return "��Ϊ���һ���Ч��������������ӵ���㹻��ʦ�Ź��������һ�����ʹ��ʱ��ɡ�";
        ob = find_object(YUXIAO);
        if (! ob) ob = load_object(YUXIAO);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "�Ϸ��ǰ��������������𣿻�����ʲô��";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "�������ڲ����Ϸ����";

                if( query("family/family_name", owner) == "�һ���" )
                        return "����������ʱ����ͬ��"+query("name", owner)+
                               "���ã���Ҫ�þ�ȥ�����ɡ�";
                else
                        return "�Ϸ����������������"+query("name", owner)+
                               "���У���ȥ�������ذɡ�";
        }
        ob->move(this_object());
        set_temp("handing", carry_object("/d/taohua/obj/huaban"));
        command("say ����̿��ù��������Ϸ�ͽ��������㡣");
        command("say ���߽������¶��С�ģ��ɲ�Ҫ�����Ϸ������");
        command("give yu xiao to "+query("id", me));
addn("family/gongji", -cost, me); 
        ob->start_borrowing();
        return 1;
}

int accept_object(object me, object ob)
{
        int r;
        if (r = ::accept_object(me, ob))
                return r;

        if (base_name(ob) != "/clone/book/jiuyin1")
        {
                command("say ��������ֶ�����ʲô��");
                return 0;
        }

        message_sort("��ҩʦ���˿�$N�������ؼ������˵�ͷ��˵����\n"
                     "�ѵ��㽫�澭�ͻء������ҵĶ����Ҿ������ˡ�\n"
                     "��Ϊ����, ����Դ�������ѧ�㹦��\n", me);

        command("heihei");
        command("say �ðɣ���Ȼ�������Ҿʹ����������ԣ��������ʱ�����ң�");
        destruct(ob);
        set("can_learn/huang/count", 1, me);

        return 1;
}

int ask_shagu()
{
        object me, obj;

        me = this_player();

        command("say �⺢�������ڴ����������ʱ�ҵ��ģ��ܿ��������֮Ů����ϧ��֪����ʲ�ᾪ�ţ�����������ӡ�");
        if( (present("amulet",me) || query_temp("play_with_shagu", me)>10 )
         && !query_temp("ask_huang_about_shagu", me) )
        {
                command("say �⺢���Խ̫�ã��ѵ���������ͶԵ���Ҹ�������һ�⣬��������������磬����ת����");
                obj = new("/d/taohua/obj/shouyu");
                obj->move(me);
                set_temp("ask_huang_about_shagu", 1, me);
                message_vision("$N�ݸ�$nһ�����š�\n", this_object(), me);
        }

        command("sigh");
        return 1;
}

/*
void unconcious()
{
        die();
}
*/