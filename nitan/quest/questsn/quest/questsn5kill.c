#include <ansi.h>

mapping *quest = ({
        ([
                "id":          "jian seng",
                "name":        "��ɮ",
                "type":        "ɱ",
                "bonus":       72,
                "msg":        "",
                "object":      "/d/tulong/yitian/npc/18jingang-5jian.c",
        ]),
        ([
                "id":          "gongye qian",
                "name":        "��ұǬ",
                "type":        "ɱ",
                "bonus":       87,
                "msg":        "",
                "object":      "/d/yanziwu/npc/gongye.c",
        ]),
        ([
                "id":          "dao seng",
                "name":        "��ɮ",
                "type":        "ɱ",
                "bonus":       74,
                "msg":        "",
                "object":      "/d/tulong/yitian/npc/18jingang-5dao.c",
        ]),
        ([
                "id":          "yu canghai",
                "name":        "��׺�",
                "type":        "ɱ",
                "bonus":       105,
                "msg":        "",
                "object":      "/kungfu/class/qingcheng/yu.c",
        ]),
        ([
                "id":          "feng boe",
                "name":        "�粨��",
                "type":        "ɱ",
                "bonus":       73,
                "msg":        "",
                "object":      "/d/yanziwu/npc/feng.c",
        ]),
        ([
                "id":          "zhao banshan",
                "name":        "�԰�ɽ",
                "type":        "ɱ",
                "bonus":       105,
                "msg":        "",
                "object":      "/d/hangzhou/honghua/zhao.c",
        ]),
        ([
                "id":          "deng baichuan",
                "name":        "�˰ٴ�",
                "type":        "ɱ",
                "bonus":       100,
                "msg":        "",
                "object":      "/d/yanziwu/npc/deng.c",
        ]),
        ([
                "id":          "bai zhen",
                "name":        "����",
                "type":        "ɱ",
                "bonus":       70,
                "msg":        "",
                "object":      "/d/hangzhou/npc/baizhen.c",
        ]),
        ([
                "id":          "yuzhen zi",
                "name":        "������",
                "type":        "ɱ",
                "bonus":       85,
                "msg":        "",
                "object":      "/d/guanwai/npc/yuzhenzi.c",
        ]),
        ([
        "id":          "fei bin",
                "name":        "�ѱ�",
                "type":        "ɱ",
                "bonus":       85,
                "msg":        "",
                "object":      "/kungfu/class/songshan/fei.c",
        ]),
        ([
                "id":          "bao butong",
                "name":        "����ͬ",
                "type":        "ɱ",
                "bonus":       80,
                "msg":        "",
                "object":      "/d/yanziwu/npc/bao.c",
        ]),
        ([
                "id":          "mu wanqing",
                "name":        "ľ����",
                "type":        "ɱ",
                "bonus":       80,
                "msg":        "",
                "object":      "/d/wanjiegu/npc/mu.c",
        ]),
        ([
                "id":          "nv lang",
                "name":        "����Ů��",
                "type":        "ɱ",
                "bonus":       75,
                "msg":        "",
                "object":      "/d/lingjiu/npc/nvlang.c",
        ]),
        ([
                "id":          "lazhang huofo",
                "name":        "���»��",
                "type":        "ɱ",
                "bonus":       72,
                "msg":        "",
                "object":      "/kungfu/class/xueshan/lazhang.c",
        ]),
        ([
                "id":          "sheng di",
                "name":        "ʤ��",
                "type":        "ɱ",
                "bonus":       89,
                "msg":        "",
                "object":      "/kungfu/class/xuedao/shengdi.c",
        ]),
        ([
                "id":          "zhang danyue",
                "name":        "�ŵ���",
                "type":        "ɱ",
                "bonus":       82,
                "msg":        "",
                "object":      "/kungfu/class/shenlong/zhang.c",
        ]),
        ([
                "id":          "wugen daozhang",
                "name":        "�޸�����",
                "type":        "ɱ",
                "bonus":       97,
                "msg":        "",
                "object":      "/kungfu/class/shenlong/wugen.c",
        ]),
        ([
                "id":          "su quan",
                "name":        "����",
                "type":        "ɱ",
                "bonus":       87,
                "msg":        "",
                "object":      "/kungfu/class/shenlong/su.c",
        ]),
        ([
                "id":          "yu hongxing",
                "name":        "�����",
                "type":        "ɱ",
                "bonus":       80,
                "msg":        "",
                "object":      "/kungfu/class/gaibang/yu-hx.c",
        ]),
        ([
                "id":          "quan guanqing",
                "name":        "ȫ����",
                "type":        "ɱ",
                "bonus":       75,
                "msg":        "",
                "object":      "/kungfu/class/gaibang/quan-gq.c",
        ]),
        ([
                "id":          "li sheng",
                "name":        "����",
                "type":        "ɱ",
                "bonus":       73,
                "msg":        "",
                "object":      "/kungfu/class/gaibang/li-sh.c",
        ]),
});
mapping query_questsn()
{
        int i;
        mapping the_quest,random_quest;
        string *quest_key;

        random_quest = quest[random(sizeof(quest))];
        the_quest = ([]);

        quest_key = keys(random_quest);
        for (i = 0;i < sizeof(quest_key);i++)
                the_quest[quest_key[i]] = random_quest[quest_key[i]];

        return the_quest;
}
