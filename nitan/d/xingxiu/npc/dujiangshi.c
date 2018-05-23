// dujiangsi.c 毒僵尸

inherit NPC;

void create()
{
        set_name("毒僵尸", ({ "du jiangshi", "jiangshi" }) );
        set("gender", "男性" );
        set("age", 30);
        set("long", "一个星宿派练功用的毒僵尸，经药物泡制，对练功大有好处。\n");
        set("attitude", "heroism");

        set("str", 25);
        set("con", 25);
        set("dex", 25);
        set("int", 25);

        set("no_get", "1");
        set("max_qi", 300);
        set("eff_qi", 300);
        set("qi", 300);
        set("max_jing", 100);
        set("jing", 100);
        set("neili", 300);
        set("max_neili", 300);
        set("jiali", 10);
        set("shen_type", 0);

        set("combat_exp", 50000);

        set_skill("force", 30);
        set_skill("unarmed", 30);
        set_skill("dodge", 30);
        set_skill("parry", 30);

        set("fight_times", 0);

        setup();

}

int accept_fight(object ob)
{
        object me;
        mapping hp_status, skill_status, map_status, prepare_status;
        string *sname, *mname, *pname;
        int i, temp;

        me = this_object();

        if (is_fighting()) return 0;

        if( query("damaged", me) )
                return notify_fail("这个毒僵尸已经被打坏了！\n");

        if( random(query("fight_times", me)) >= 10){
                set("damaged", 1, me);
                return notify_fail("这个毒僵尸已经被打坏了！\n");
        }

        if( query("last_fighter", me) == query("id", ob) )
                return notify_fail("你刚跟这个毒僵尸练过功！\n");

        set("last_fighter",query("id",  ob), me);
        addn("fight_times", 1, me);

        remove_call_out("renewing");
        call_out("renewing", 300 + random(300), me);
/* delete and copy skills */

        if ( mapp(skill_status = me->query_skills()) ) {
                skill_status = me->query_skills();
                sname  = keys(skill_status);

                temp = sizeof(skill_status);
                for(i=0; i<temp; i++) {
                        me->delete_skill(sname[i]);
                }
        }

        if ( mapp(skill_status = ob->query_skills()) ) {
                skill_status = ob->query_skills();
                sname  = keys(skill_status);

                for(i=0; i<sizeof(skill_status); i++) {
                        me->set_skill(sname[i], skill_status[sname[i]]);
                }
        }

/* delete and copy skill maps */
        if ( mapp(map_status = me->query_skill_map()) ) {
                mname  = keys(map_status);

                temp = sizeof(map_status);
                for(i=0; i<temp; i++) {
                        me->map_skill(mname[i]);
                }
        }

        if ( mapp(map_status = ob->query_skill_map()) ) {
                mname  = keys(map_status);

                for(i=0; i<sizeof(map_status); i++) {
                        me->map_skill(mname[i], map_status[mname[i]]);
                }
        }

/* delete and copy skill prepares */

        if ( mapp(prepare_status = me->query_skill_prepare()) ) {
                pname  = keys(prepare_status);

                temp = sizeof(prepare_status);
                for(i=0; i<temp; i++) {
                        me->prepare_skill(pname[i]);
                }
        }

        if ( mapp(prepare_status = ob->query_skill_prepare()) ) {
                pname  = keys(prepare_status);

                for(i=0; i<sizeof(prepare_status); i++) {
                        me->prepare_skill(pname[i], prepare_status[pname[i]]);
                }
        }

        hp_status = ob->query_entire_dbase();

                set("str", hp_status["str"], me);
                set("int", hp_status["int"], me);
                set("con", hp_status["con"], me);
                set("dex", hp_status["dex"], me);

                set("max_qi", hp_status["max_qi"], me);
                set("eff_qi", hp_status["eff_qi"], me);
                set("qi", hp_status["qi"], me);
                set("max_jing", hp_status["max_jing"], me);
                set("eff_jing", hp_status["eff_jing"], me);
                set("jing", hp_status["jing"], me);
                set("max_neili", hp_status["max_neili"], me);
                set("neili", hp_status["neili"], me);
                set("jiali", hp_status["jiali"], me);
                set("combat_exp", hp_status["combat_exp"], me);

        return 1;
}

void renewing(object me)
{
        delete("last_fighter", me);
}