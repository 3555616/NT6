// xuan.h for fight and get letter from Xuan

#include "shaolin.h"

int accept_object(object ob, object obj)
{
        object me = this_object();

#if IS_XUAN_CI
        int r;

        if (r = ::accept_object(ob, obj))
                return r;
#endif

        if( query("id", obj) == "tuijian xin4" && 
            query_temp("have_letter", ob) )
        {
                set_temp("apprentice_ok", 1, ob);
                command("say �ã�"+query("name", ob)+
                        "����Ը�����Ϊʦ��");
                destruct(obj);
                return 1;
        }

        command("smile");
        command("say �ⶫ�����ҿ�û��ʲ���á�");
        command("give "+query("id", obj)+" to "+query("id", me));
        return 0;
}

void attempt_apprentice(object ob)
{
        object me  = this_object();
        mapping ob_fam;
        mapping my_fam=query("family", me);

        string name, new_name;

        if (! permit_recruit(ob))
                return;

        if( !(ob_fam=query("family", ob)) || 
            ob_fam["family_name"] != "������")
        {
                command("say " + RANK_D->query_respect(ob) +
                        "�뱾��������������֪�˻��Ӻ�̸��");
                return;
        }

        if( query("class", ob) != "bonze" && 
            ob_fam["family_name"] == "������") 
        {
                command("say " + RANK_D->query_respect(ob) +
                        "���׼ҵ��ӣ�����������ѧ�ա�");
                return;
        }

        if (ob_fam["generation"] <= my_fam["generation"])
        {
                command("say " + RANK_D->query_respect(ob) +
                        "��ƶɮ����ҵ� !");
                return;
        }

        if (ob_fam["generation"] == (my_fam["generation"] + 1))
        {
                command("say " + ob_fam["master_name"] +
                        "��ͽ�������ܵ���������ˣ������� !");
                command("recruit "+query("id", ob));
        }

        if (ob_fam["generation"] == (my_fam["generation"] + 2))
        {
                if( query_temp("apprentice_ok", ob) || 
                    query("luohan_winner", ob) )
                {
                        delete_temp("have_letter", ob);
                        delete_temp("apprentice_ok", ob);
        
                        command("say ��" + ob_fam["master_name"] +
                                "���������ҵİɣ���������");
                        command("say ƶɮ�ֵ�һ����֮�ţ����ǿ�ϲ�ɺأ�");

                        name=query("name", ob);
                        new_name = "��" + name[2..3];
                        set("name", new_name, ob);

                        command("say �ӽ��Ժ���ķ�������" + new_name +
                                "����ϲ������Ϊ�����ɳ��ֱ����ӣ�");
                        command("recruit "+query("id", ob));
                } else
                {
                        command("say " + RANK_D->query_respect(ob) +
                                "���㼴û���Ƽ��ţ�Ҳû�й��޺���"
                                "����Խ����ʦ��");
                        return;
                }
        }

        return;
}