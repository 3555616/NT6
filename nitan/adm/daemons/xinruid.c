// competed.c
// writed by smallfish
// rewrited by Lonely

#include <ansi.h>

inherit F_DBASE;

#define ENTRY_ROOM      "/d/city/xinrui_dating"
#define FIGHT_ROOM      "/d/city/lunjian2"
#define XINRUI_OBJ      "/clone/misc/xinrui"
#define XINRUI_DIR      "/data/gaoshou/"
#define TEMP_OBJ        "/clone/misc/temp_xinrui"

nosave object challenger = 0;  // ��ս��
nosave object competitor = 0;  // ����ս��

// ����ֵ 1 -- ������ȥ
// ����ֵ 2 -- ���ڱ���
// ����ֵ 3 -- ��û����
nosave int state = 1;
nosave int times = 3;
nosave int top_num = 10;
nosave string top_id = "";
nosave object *total = ({ });
nosave mapping tops = ([ ]);
nosave mapping tmp_top = ([ ]);

string query_top_id() { return top_id; } 
string query_new_id()
{
        if (challenger)
                return query("id", challenger);
        else
                return "VOID";
}

mapping query_tops() { return tops; }

string *armor_type = ({ "armor", "boots", "cloth",
                        "hands", "head", "neck",
                        "shield", "surcoat","waist",
                        "wrists" });

int get_tops();
int save_tops();
protected void auto_check();
int check_out(object me);
int check_quit(object me);
protected void init_player(object me);
protected void restore_status(object me);
int join_competition(object ob);
protected int start_competition(int top_num);
protected int do_competition(object ob1, object ob2);
protected int finish_competition();
void restore_competition();
protected void message_competition(string msg);

int clean_up() { return 1; }

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "���侫��");
        CHANNEL_D->do_channel( this_object(), "sys", "��������ϵͳ�Ѿ�������");     
        get_tops();
}

void remove(string euid) 
{
        if (! this_player()) 
                return;
      
        if (state = 2 && sizeof(total) > 0) 
                error("���侫�飺Ŀǰ�������������սʮ�������㲻�ܴݻٱ��侫�顣\n"); 
}

protected void heart_beat()
{
        if (sizeof(total))
                auto_check();
}

protected void auto_check()
{
        object ob;
        string room;
        object *lost;
        int i;

        lost = ({ });
        for (i = 0; i < sizeof(total); i++)
        {
                if (! objectp(total[i]))
                {
                        total[i] = 0;
                        continue;
                }
                room = base_name(environment(total[i]));
                if (! sscanf(room, "/d/city/lunjian%*s"))
                {
                        // not in pk room
                        restore_status(total[i]);
                        // total[i]->delete("total_hatred");
                        total[i] = 0;
                        continue;
                }
                if (total[i]->is_net_dead())
                {
                        lost += ({ total[i] });
                        break;
                }

                if( query("qi", total[i])<1 || query("jing", total[i])<1 )
                {
                        lost += ({ total[i] });
                        break;
                }
        }

        // kickout the players who lost competition
        foreach (ob in lost)
                check_out(ob);

        total -= ({ 0 }); 
        
        if (sizeof(total) < 1)
        {
                finish_competition();       
                return;
        } else        
        if (sizeof(total) == 1)
        {
                if (userp(total[0]))
                {
                        top_num--;        
                        if (top_num < 0)
                        {     
                                finish_competition(); 
                                return;
                        }         
                        start_competition(top_num);
                }
                else
                        finish_competition();
        } 
}

int check_out(object me)
{
        object ob;
        mapping my;
        string msg;
        
        if (userp(me))
        {
                my = me->query_entire_dbase();
                my["eff_qi"] = my["max_qi"];
                my["eff_jing"] = my["max_jing"];
                my["jingli"] = my["max_jingli"];
                my["qi"] = 1;
                my["jing"] = 1;
                my["jingli"] = 1;

                tell_object(me, HIR "\n�������ǰһ��ģ��...�������ˣ�\n" NOR);
                if (ob = me->query_last_damage_from())
                {
                        msg = "��˵" + me->name(1) + HIY "����" + ob->name(1) + HIY "�Ķ��֣���һ��������̨��";
                } else
                        msg = "��˵" + me->name(1) + HIY "�������ѣ��������ޡ��Ѿ�������̨��";
                message_competition(msg);

                restore_status(me);
                total -= ({ me });
                me->move(ENTRY_ROOM);
                message("vision", "һ����Ӱٿ�Ĵ��˳������漴���ǡ�ž����"
                        "һ�����ͼ�" + me->name() +"ˤ���˵��ϣ�һ��������"
                        "������ӡ�\n", environment(me), ({ me }));
                tell_object(me, "�������У�����ñ���������������"
                        "���ص�ˤ���˵��ϡ�\n");
                if (! living(me))
                        me->revive();
                return 1;
        } else
        {
                message_vision(NOR "\n$Nϥ��һ������ϥ�ŵأ���ǿ����վ������������ȴ���һ��" 
                        HIR "��Ѫ" NOR "����Ȼת����ȥ��\n\n" NOR, me); 
                msg = HIY "��ϲ" + NOR + HIR + challenger->name(1) + NOR + 
                      HIY "����սʤ" + NOR + HIR + me->name(1) + NOR +  
                      HIY "����\n" NOR;
                message_competition(msg);  
               
                restore_status(me);  
                total -= ({ me });                
                destruct(me);
                return 1;
        }
}

int check_quit(object me)
{
        message_competition("��˵" + me->name(1) +
                            "�������ӣ������ˡ�");
        restore_status(me);
        if (arrayp(total))
                total -= ({ me });
        tell_object(me, "�������Ȩ��������ȥ��\n");

        // continue run quit function
        me->move(ENTRY_ROOM);
        message("vision", "ֻ��" + me->name() + "��ɫ�ǳ��ѿ�������������\n",
                environment(me), ({ me }));
        return 1;
}

int join_competition(object ob)
{
        mixed exp;

        if (state = 2 && sizeof(total) > 0) 
                return notify_fail("������̨���ھ��б��䣬�㻹�ǵȻ�ɡ�\n");

        if (state == 3)
                return notify_fail("��̨�����Ѿ��ر��ˣ���������ʲô��\n");

        exp=query("combat_exp", ob);
        if (exp < 10000)
                return notify_fail("�㻹�����˰ɣ�����㾭��ͱ��ȥ�����ˡ�\n");

        if (ob->query_condition("killer", 1))
                return notify_fail("�����ڱ��ٸ�ͨ�������Բ��ܲμӱ��䡣\n");

        if (! get_tops())
                return notify_fail("�Բ�����̨�ϱ���������¼�д�������ϵ��ʦ��\n");

        if (ob->query_condition())
                return notify_fail("������״̬���ѣ����Ǳ��ȥ�ˡ�\n");

        if( query("id", ob) == tops[0]["id"] )
                return notify_fail("���Ѿ��ǵ�һ�����ˣ����Ǳ��ȥ�ˡ�\n");

        if (! arrayp(total))
                total = ({ ob });
        else
        if (member_array(ob, total) == -1)
                total += ({ ob });                
               
        message_competition((ultrap(ob) ? "����ʦ" : "") +
                            ob->name(1) + "����̨��սʮ�����񣬴���Ϊ�����Ͱ�����");

        init_player(ob);
        set_heart_beat(1);
        
        tmp_top["id"]=query("id", ob);
        tmp_top["title"] = ob->short(1);
        challenger = ob;
        top_num = 9;
        start_competition(top_num);
        return 1;
}

protected void init_player(object me)
{
        me->set_override("unconcious", (: call_other, __FILE__, "check_out" :));
        me->set_override("die", (: call_other, __FILE__, "check_out" :));
        me->set_override("quit", (: call_other, __FILE__, "check_quit" :));
        set_temp("backup/killer", me->query_killer(), me);
        set_temp("backup/want", me->query_want(), me);

        me->move(FIGHT_ROOM);
        if (userp(me))
                message_vision(HIW "$N����������̨����Χ����һƬ�к�����\n\n", me);
        else        
                message_vision(HIW "ֻ����һ�����죬$N�Ӻ�̨�����˳���������һ���ķ���\n\n", me); 
        set("backup/condition", me->query_condition(), me);
        me->clear_condition();
}

protected void restore_status(object me)
{
        mapping cnd;
        string *ks;
        int j, k;
        int i;
        object *inv, obj; 

        me->delete_override("unconcious");
        me->delete_override("die");
        me->delete_override("quit");
        me->remove_all_enemy(1);
        me->remove_all_killer();
        j = (int)me->query_condition("putizi_drug");
        k = (int)me->query_condition("pill_drug");
        me->clear_condition();
        me->receive_damage("qi", 0);
        me->apply_killer(query_temp("backup/killer", me));
        me->apply_want(query_temp("backup/want", me));

        cnd=query("backup/condition", me);
        delete("backup/condition", me);
        delete_temp("block_msg/all", me);
        if (j > 0)
        me->apply_condition("putizi_drug", j);
        if (k > 0)
        me->apply_condition("pill_drug", k);
        if (! mapp(cnd)) return;
        ks = keys(cnd);
        for (i = 0; i < sizeof(ks); i++)
                me->apply_condition(ks[i], cnd[ks[i]]);

        inv = deep_inventory(me); 
        if (sizeof(inv) > 0) 
        foreach( obj in inv ) { 
                if( obj && query("maze_item", obj) )
                        destruct(obj); 
        }
}

protected int start_competition(int top_num)
{
        int i;
        object ob;
        
        if (top_num < 0)
        {
                finish_competition();
                return 1;
        }
        if (! challenger)
        {
                finish_competition(); 
                return 1;
        }
        
        top_id = tops[top_num]["id"];
        if( top_id == query("id", challenger) )
        {
                top_num--;
                start_competition(top_num);
                return 1;
        }
        
        ob = new(XINRUI_OBJ);
        ob->remove_all_killer();

        if (! arrayp(total))
                total = ({ ob });
        else
        if (member_array(ob, total) == -1)
                total += ({ ob });  
                        
        init_player(ob);
        
        competitor = ob;
        state = 2;
        set_heart_beat(1);
        do_competition(challenger, competitor);
        return 1;
}

protected int do_competition(object ob1, object ob2)    
{            
        object room;
               
        if (! ob1 || ! ob2)
        {
                finish_competition();
                return 1;
        }
        
        if (! room = find_object(FIGHT_ROOM))
                room = load_object(FIGHT_ROOM);
        if (present(ob1, room) && present(ob2, room))
        {
                if (! ob1->is_killing(ob2) || ! ob2->is_killing(ob1))
                {
                        if (times > 0)
                        {
                                tell_object(ob1, "\t\t" + HIR + "===" + CHINESE_D->chinese_number(times) + "===\n\n" + NOR);
                                tell_object(ob2, "\t\t" + HIR + "===" + CHINESE_D->chinese_number(times) + "===\n\n" + NOR);
                                times--;
                                call_out("do_competition", 3, ob1, ob2);
                                return 1;
                        } else
                        {
                                times = 3;
                                tell_room(room, HIY "\t-------  ��     ʼ  -------\n\n" NOR);
                                message_vision(HIW "\n$N����$n���һ������Ȼ��Ҫ�����Ǿͷ��������ɣ�\n", ob2, ob1);
                        } 
                }
                
                if (! ob2->is_killing(ob1)) 
                        ob2->kill_ob(ob1);
                if (! ob1->is_killing(ob2)) 
                        ob1->kill_ob(ob2);
        }

        return 1;
}

protected int finish_competition()
{
        int i, j;
        int mingci, old_mingci;
        string from_file, to_file, temp_file;
        string weapon_file, armor_file, *carry_ob;
        string msg;
        object weapon, armor, temp_ob;
        
        set_heart_beat(0);
        
        if (objectp(competitor))
                destruct(competitor);
        
        if (! objectp(challenger))
        {
                restore_competition();
                return 1;
        }

        mingci = top_num + 1;

        if (base_name(environment(challenger)) == FIGHT_ROOM && top_num < 0)
        {               
                restore_status(challenger);
                challenger->move(ENTRY_ROOM);
                message_vision(HIW "$N����һЦ������Ʈ������̨��\n" NOR, challenger);
                msg = HIY + challenger->name(1) + "����������񣬴�Ц�ŷ���Ʈ����̨��\n" NOR;
                message_competition(msg);    
        }
        
        /*
        if (mingci != 0)
        {
                msg = HIY + challenger->name(1) + "��������̧������̨��\n" NOR;
                message_competition(msg);    
        }
        */
                
        if (mingci > 9)
        {
                restore_competition();   
                return 1;
        }
        old_mingci = 100;
        for (i = 0;i < sizeof(tops);i++)
        {
                if( tops[i]["id"] == query("id", challenger) )
                {
                        old_mingci = i;
                        break;
                }
        }
        if (old_mingci == 100)
                old_mingci = 9;
        else 
        if (mingci >= old_mingci)
        {      
                restore_competition();
                return 1;
        }

        if (old_mingci == 9)
        {
                //ɾ�������µ�ʮ������
                temp_file = XINRUI_DIR + "npc/" + tops[9]["id"] + "_xr.o";
                if (file_size(temp_file) >= 0)
                        rm(temp_file);
                temp_file = XINRUI_DIR + "weapon/" + tops[9]["id"] + "_xr-weapon.c";
                if (file_size(temp_file) >= 0)
                        rm(temp_file);
                for (i = 0;i < sizeof(armor_type);i++)
                {
                        temp_file = XINRUI_DIR + "weapon/" + tops[9]["id"] + "_xr-" + armor_type[i] + ".c";
                        if (file_size(temp_file) >= 0)
                                rm(temp_file);
                }
        }

        carry_ob = ({});
        from_file = challenger->query_save_file() + ".o";
        to_file=XINRUI_DIR+"npc/"+query("id", challenger)+"_xr.o";
        for (i = old_mingci;i >= 0;i--)
        {
                if (i < mingci) break;
                if (i == mingci)
                {
                        tops[i] = tmp_top;
                        //������ҵ���
                        cp(from_file, to_file);

                        //�޸��µĵ�������
                        temp_ob = new(TEMP_OBJ);
                        temp_ob->delete_status();
                        //��������
                        if( objectp(weapon=query_temp("weapon", challenger)) && 
                            (! weapon->is_no_clone() ||
                             weapon->is_item_make()))
                        {
                                weapon_file = base_name(weapon);
                                from_file = weapon_file + ".c";
                                to_file = XINRUI_DIR + "weapon/" + 
                                          query("id", challenger)+
                                          "_xr-weapon.c";
                                cp(from_file,to_file);
                                if (strlen(weapon_file) > 11 && 
                                    weapon_file[0..10] == "/data/item/")
                                {
                                        set("can_summon/"+query("id", challenger)+
                                                     "_xr-weapon", to_file, temp_ob);
                                } else carry_ob += ({ to_file });
                        }
                        if( objectp(weapon=query_temp("secondary_weapon", challenger)) && 
                            (! weapon->is_no_clone() ||
                             weapon->is_item_make()))
                        {
                                weapon_file = base_name(weapon);
                                from_file = weapon_file + ".c";
                                to_file = XINRUI_DIR + "weapon/" + 
                                          query("id", challenger)+
                                          "_xr-weapon2.c";
                                cp(from_file,to_file);
                                if (strlen(weapon_file) > 11 && 
                                    weapon_file[0..10] == "/data/item/")
                                {
                                        set("can_summon/"+query("id", challenger)+
                                                     "_xr-weapon2", to_file, temp_ob);
                                } else carry_ob += ({ to_file });
                        }

                        //���Ʒ���
                        for (j = 0;j<sizeof(armor_type);j++)
                        {
                                if( objectp(armor=query_temp("armor/"+armor_type[j], challenger)) )
                                {
                                        armor_file = base_name(armor);
                                        if (strlen(armor_file) > 11 && 
                                            armor_file[0..10] == "/data/item/")
                                        {
                                                from_file = armor_file + ".c";
                                                to_file = XINRUI_DIR + "weapon/" + 
                                                          query("id", challenger)+
                                                          "_xr-" + armor_type[j] + ".c";
                                                cp(from_file,to_file);
                                                set("can_summon/"+query("id", challenger)+
                                                             "_xr-" + armor_type[j], to_file, temp_ob);
                                        } else carry_ob += ({ armor_file });
                                }
                        }
                        
                        if (sizeof(carry_ob))
                                set("carry_ob", carry_ob, temp_ob);

                        set("auto_perform", 1, temp_ob);
                        temp_ob->save();
                        destruct(temp_ob);
                        break;
                }
                tops[i] = tops[i - 1];
        }
        save_tops();
        msg = HIY "��ϲ" + challenger->name(1) +
              HIY "�ٵ�" + HIG + "��" + chinese_number(mingci + 1) +
              NOR + HIY + "����Ŀ�ϲ�ɼ���\n" NOR;
        message_competition(msg);    
        get_tops();
        restore_competition();
        return 1;
}

void restore_competition()
{
        state = 1;
        challenger = 0;
        competitor = 0;
        times = 3;
        total = ({ });
        tmp_top = ([ ]);
        top_num = 10;
        top_id = "";
        return;
}

int get_tops()
{
        int i;
        string *str, *line;
        mapping top;
        
        if (file_size(XINRUI_DIR + "xinrui_tops") < 0)
        {
                for (i = 0; i < 10; i ++)
                {
                        top = ([ ]);
                        top["id"] = "test";
                        top["title"] = "����ʦ�����������(test)";
                        tops += ([ i : top ]);       
                }
                save_tops();
                return 1;
        }                
                
        str = explode(read_file(XINRUI_DIR + "xinrui_tops"), "\n");
        // if (sizeof(str) != 10)
                // return 0;
        tops = ([ ]);        
        for (i = 0; i < sizeof(str); i ++)
        {
                top = ([ ]);
                line = explode(str[i], "|");
                if (sizeof(line) != 2) return 0;
                top["id"] = line[0];
                top["title"] = line[1];
                tops += ([ i : top ]);
        }
        return 1;
}

int save_tops()
{
        int i;
        string str;
        str = "";
        
        for (i = 0;i < sizeof(tops);i ++)
        {
                str += tops[i]["id"] + "|" + replace_string(tops[i]["title"], "|", "");
                if (i + 1 != sizeof(tops))
                        str += "\n";
        }
        write_file(XINRUI_DIR + "xinrui_tops", str, 1);
        return 1;
}

protected void message_competition(string msg)
{
        return;
        message("sys", HIY "�����������" + msg + "\n" NOR, users());
}