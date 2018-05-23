// This program is a part of NT MudLIB
// moduled.c
// 修改支持同时穿多个套装 by lonely

/*
// 自造装备套装数据格式
<1>
<mod_name>$HIC$大道$NOR$</mod_name>
<bas>5</bas>
<num>12</num>
<bas_prop>
add_busy:5
add_weak:5
reduce_busy:5
avoid_weak:5
</bas_prop>
<adv_prop>
avoid_locked:5
add_damage:20
add_skill:50
avoid_busy:5
counter_damage:20
add_locked:5
reduce_damage:5
</adv_prop>
</1>

// 非自造装备套装格式...
<M3000>
<mod_name>$CYNGRN$龙之神力$NOR$</mod_name>
<mod_parts>
A3000:$CYNGRN$龙之护腕$NOR$
A3001:$CYNGRN$龙神鳞甲$NOR$
A3002:$CYNGRN$龙神披风$NOR$
A3003:$CYNGRN$龙之束带$NOR$
A3004:$CYNGRN$恶龙之触$NOR$
A3005:$CYNGRN$龙骨胫甲$NOR$
A3006:$CYNGRN$龙骨战衣$NOR$
</mod_parts>
<bas>3</bas>
<num>6</num>
<bas_prop>
avoid_locked:20
add_locked:20
add_busy:10
</bas_prop>
<adv_prop>
reduce_busy:20
avoid_busy:20
add_weak:10
avoid_weak:20
add_damage:20
reduce_damage:20
</adv_prop>
</M3000>

// 非自造套装部件格式...
<A3002>
<type>armor/surcoat</type>
<name>$CYNGRN$龙神披风$NOR$</name>
<id>dragon surcoat</id>
<value>10000</value>
<mod_level>M3000</mod_level>
<mod_name>$CYNGRN$龙之神力$NOR$</mod_name>
<require>
level:20
con:30
</require>
<quality_level>2</quality_level>
<armor_prop>
armor:10
</armor_prop>
<enchase>
apply_prop/armor1:10
apply_prop/str:2
apply_prop/dex:1
apply_prop/dodge:1
flute:2
used:2
</enchase>
<insert>
[1]
id:magic stone
name:玄石
apply_prop/armor1:10
apply_prop/str:2
[/1]
[2]
id:magic stone
name:灵石
apply_prop/dex:1
apply_prop/dodge:1
[/2]
</insert>
</A3002>
*/

#include <ansi.h>

#define EQUIP_LIST      CONFIG_DIR "equiplist/"
#define NCH_CHANNEL(x) CHANNEL_D->channel_broadcast("nch", "套装精灵："+(string)x)

class eqmodule
{
        string mod_level;       // 套装序号 作为序引读取资料
        string mod_name;        // 套装名称
        mapping mod_parts;      // 套装组件名称
        int bas;                // 套装激活基本属性数量
        int num;                // 套装组件数量
        mapping bas_prop;       // 套装组合基本属性
        mapping adv_prop;       // 套装组合高级属性
        mapping add_prop;       // 套装组合补充属性，套装属性应该是bas_prop+adv_prop+add_prop
}

class eqmodule load_module(string modlevel);
string module_stats(object obj, object owner);
int valid_module(class eqmodule mod_stats);
void equip_module(object ob, object owner);
void unequip_module(object ob, object owner);

void create()
{
        seteuid(ROOT_UID);
}

// 根据套装部件和持有部件者打印部件信息,应用于look.c调用
string module_stats(object ob, object owner)
{
        class eqmodule mod_stats;
        string modlevel, mark_level, modname, *apply, *eq_files, *key;
        mapping modparts, data;
        mapping stats;
        int i, j, n, bas, num, len = 0;
        string msg, str, eq_str;

        // 初始化资料
        msg = "";
        modlevel = query("mod_level", ob);
        modname = query("mod_name", ob);
        mod_stats = new(class eqmodule);
        // 自造套装获取mod_level
        if( ob->is_item_make() )
        {
                if( query_temp("modequip_min_level_"+modname, owner) ) // 获取套装的最低等级
                        modlevel = query_temp("modequip_min_level_"+modname, owner);

                if( query_temp("modequip_mark_level_"+modname, owner) )
                        mark_level = query_temp("modequip_mark_level_"+modname, owner);
                else
                        mark_level = modlevel;
        }
        else
                mark_level = modlevel;

        if( classp(query_temp("modequip_"+mark_level+"_"+modname+"_stats", owner)) && query_temp("modequip_"+mark_level+"_"+modname+"_name", owner) )
                mod_stats = query_temp("modequip_"+mark_level+"_"+modname+"_stats", owner); // 直接从玩家身上获取套装资料
        else
                mod_stats = load_module(modlevel); // 载入套装资料

        // 检查合法性
        if( valid_module(mod_stats) )
        {
                num = mod_stats->num;   // 套装部件数量
                // 激活套装部件或掉落的套装部件
                if( query_temp("modequip_"+mark_level+"_"+modname+"_name", owner) || !ob->is_item_make() )
                        modparts = mod_stats->mod_parts;

                // 自造未激活套装部件
                else
                        modparts = query_temp("modparts_" + mark_level+"_"+modname, owner);
                
                if( !mapp(modparts) ) modparts = ([]);
                apply = keys(modparts);
                
                msg = sprintf(HIW"  %s(%d/%d"NOR")\n",
                               modname,
                               query_temp("modamount_"+mark_level+"_"+modname, owner), num);
                msg+= sprintf(NOR "┏━━━━━━━━━━┓\n");

                data = query_temp("modparts_" + mark_level+"_"+modname, owner);
                if( !mapp(data) ) data = ([]);
                eq_files = keys(data);

                for( i=0;i<sizeof(apply);i++ )
                {
                        eq_str = "  ";

                        if( member_array(apply[i], eq_files) != -1 )
                                eq_str = WHT "√" NOR;

                        if( query("mod_mark", ob) == apply[i] )
                                if( query_temp("mod_equip", ob) )
                                        eq_str = HIR"√"NOR;
                                else
                                        eq_str = RED"×"NOR;

                        str = sprintf(NOR "┃%s%-18s"NOR"┃\n",eq_str, modparts[apply[i]]);
                        msg += str;
                }
                if( ob->is_item_make() && member_array(query("mod_mark", ob), apply) == -1 )
                {
                        eq_str = RED"×"NOR;
                        str = sprintf(NOR "┃%s%-18s"NOR"┃\n",eq_str, ob->name(1));
                        msg += str;
                }

                msg += sprintf(NOR "┗━━━━━━━━━━┛\n");
                bas = mod_stats->bas;
                if( query_temp("modamount_"+mark_level+"_"+modname, owner) >= bas )
                        eq_str = HIR;
                else
                        eq_str = HIK;
                //msg += sprintf(HIG"  装备效果"NOR")\n");
                msg += sprintf(NOR "%s┏━━━━━━━━━━┓"NOR"\n", eq_str);

                str = sprintf("%d件:", bas);
                msg += sprintf(NOR "%s┃"NOR"%-20s%s┃"NOR"\n", eq_str, str, eq_str);
                stats = copy(mod_stats->bas_prop);
                key = keys(stats);
                if( sizeof(key) > 0 )
                {
                        for( i=0;i<sizeof(key);i++ )
                        {
                                str = EQUIPMENT_D->chinese(key[i], stats[key[i]]);
                                str = HIG + str + NOR;
#ifndef LONELY_IMPROVED
                                len = color_len(str);
#endif
                                msg += sprintf(NOR "%s┃"NOR"%-" + (20 + len) + "s%s┃"NOR"\n",
                                                       eq_str, str, eq_str);
                        }
                }
                if( query_temp("modamount_"+mark_level+"_"+modname, owner) == num )
                        eq_str = HIR;
                else
                        eq_str = HIK;
                str = sprintf("%d件:", num);
                msg += sprintf(NOR "%s┃"NOR"%-20s%s┃"NOR"\n", eq_str, str, eq_str);
                stats = copy(mod_stats->adv_prop);
                key = keys(stats);
                if( sizeof(key) > 0 )
                {
                        for( i=0;i<sizeof(key);i++ )
                        {
                                str = EQUIPMENT_D->chinese(key[i], stats[key[i]]);
                                str = HIG + str + NOR;
#ifndef LONELY_IMPROVED
                                len = color_len(str);
#endif
                                msg += sprintf(NOR "%s┃"NOR"%-" + (20 + len) + "s%s┃"NOR"\n",
                                                       eq_str, str, eq_str);
                        }
                }

                if( query_temp("modamount_"+mark_level+"_"+modname, owner) >= bas )
                        eq_str = HIR;
                else
                        eq_str = HIK;
                str = sprintf("Add:");
                msg += sprintf(NOR "%s┃"NOR"%-20s%s┃"NOR"\n", eq_str, str, eq_str);
                stats = copy(mod_stats->add_prop);
                key = keys(stats);
                if( sizeof(key) > 0 )
                {
                        for( i=0;i<sizeof(key);i++ )
                        {
                                str = EQUIPMENT_D->chinese(key[i], stats[key[i]]);
                                str = HIG + str + NOR;
#ifndef LONELY_IMPROVED
                                len = color_len(str);
#endif
                                msg += sprintf(NOR "%s┃"NOR"%-" + (20 + len) + "s%s┃"NOR"\n",
                                                       eq_str, str, eq_str);
                        }
                }
                msg += sprintf(NOR "%s┗━━━━━━━━━━┛"NOR"\n", eq_str);
        }
        return msg;
}

// 根据检查一个套装是否合法，即是否存在，如果套装数据还是初始化数据，就是不存在。
int valid_module(class eqmodule mod_stats)
{
        if( mod_stats->mod_level == "" )
                return 0;

        if( mod_stats->mod_name == "" )
                return 0;
        /*
        if( !(mod_stats->mod_parts) )
                return 0;

        if( !(mod_stats->bas_prop) )
                return 0;

        if( !(mod_stats->adv_prop) )
                return 0;

        if( !(mod_stats->add_prop) )
                return 0;
        */
        return 1;
}

// 根据序号查找套装数据
class eqmodule load_module(string modlevel)
{
        string filename, this_file, temp_str;
        object ob;
        class eqmodule item;
        string *field;
        string modname, names, bas_prop, adv_prop;
        int i, bas, num;
        mapping stats;
        string key;
        mixed value;

        if( modlevel[0] == 'M' )
        {
                if ( modlevel[1] == '0' && strlen(modlevel) == 5)
                        filename = EQUIP_LIST+"basic.mod";
                else if ( modlevel[1] == '1' && strlen(modlevel) == 5)
                        filename = EQUIP_LIST+"advance.mod";
                else if ( modlevel[1] == '2' && strlen(modlevel) == 5)
                        filename = EQUIP_LIST+"expert.mod";
                else if ( modlevel[1] == '3' && strlen(modlevel) == 5)
                        filename = EQUIP_LIST+"boss.mod";
        }
        else if( modlevel == "1" || modlevel == "2" || modlevel == "3" || modlevel == "4" )
        {
                // 玩家自造装备套装化
                filename = EQUIP_LIST + "ultra.mod";
        }

        // 初始化一个空的套装文件
        item = new(class eqmodule);
        item->mod_level = "";
        item->mod_name = "";
        item->mod_parts = ([]);
        item->add_prop = ([]); // 装备部件增加的套装属性

        // 文件为空。返回空值。
        if( !stringp(filename) || file_size(filename) < 0 )
                return item;

        this_file = read_file(filename);

        // 根据套装序号查找序号所在文件表，查找匹配套装数据
        sscanf( this_file, "%*s<"+modlevel+">%s</"+modlevel+">%*s", temp_str);
        sscanf( temp_str, "%*s<mod_name>%s</mod_name>%*s", modname);
        sscanf( temp_str, "%*s<mod_parts>\n%s\n</mod_parts>%*s", names);
        sscanf( temp_str, "%*s<bas>%d</bas>%*s", bas);
        sscanf( temp_str, "%*s<num>%d</num>%*s", num);
        sscanf( temp_str, "%*s<bas_prop>\n%s\n</bas_prop>%*s", bas_prop);
        sscanf( temp_str, "%*s<adv_prop>\n%s\n</adv_prop>%*s", adv_prop);

        item->mod_level = modlevel;
        item->mod_name = trans_color(modname, 3); // 转换颜色

        if( bas ) item->bas = bas;
        if( num ) item->num = num;

        // 解析属性表，填入属性关键字和套装属性。
        if (bas_prop != "")
        {
                stats = ([]);
                field = explode(bas_prop, "\n");
                for (i=0;i<sizeof(field);i++)
                {
                        //field[i] = replace_string(field[i], " ", "");
                        if( sscanf( field[i], "%s:%d", key, value ) != 2 )
                            sscanf( field[i], "%s:%s", key, value );
                        // 无需复杂的解析
                        stats[key] = value;
                }
                item->bas_prop = copy(stats);
        }

        if (adv_prop != "")
        {
                stats = ([]);
                field = explode(adv_prop, "\n");
                for (i=0;i<sizeof(field);i++)
                {
                        //field[i] = replace_string(field[i], " ", "");
                        if( sscanf( field[i], "%s:%d", key, value ) != 2 )
                            sscanf( field[i], "%s:%s", key, value );
                        // 无需复杂的解析
                        stats[key] = value;
                }
                item->adv_prop = copy(stats);
        }

        // 解析文件表，填入文件名称和套装部件中文名字。
        if( sizeof(names) )
        {
                stats = ([]);
                field = explode(names, "\n");
                for (i=0;i<sizeof(field);i++)
                {
                        //field[i] = replace_string(field[i], " ", "");
                        field[i] = trans_color(field[i], 3); // 转换颜色
                        sscanf( field[i], "%s:%s", key, value );
                        stats[key] = value;
                }
                item->mod_parts = copy(stats);
        }

        return item;
}

// 装备套装部件
// ob套装部件 owner装备者
void equip_module(object ob, object owner)
{
        class eqmodule mod_stats;
        class eqmodule tmp_stats;
        mapping data, stats, prop, applied_prop;
        mapping modparts;
        string *apply;
        string modname;
        string modlevel, mark_level, file, name;
        object *inv, *obs;
        int i, j, n, flag = 0;
        int bas, num, change = 0;

        if( ob->is_item_make() )
        {
                // 自造装备非装备主人无法激活套装属性
                if( ob->item_owner() != query("id", owner) )
                        return;
        }

        modlevel = query("mod_level", ob); // 套装的序号、等级
        modname = query("mod_name", ob);   // modname 来判断是否是套装

        inv = all_inventory(owner);
        if( ob->is_item_make() )        // 检查套装部件
        {
                obs = filter_array(inv,
                        (: query("equipped", $1) && query("mod_name", $1) == $(modname) &&
                           $1->is_item_make() && $1->item_owner() == $(query("id", owner)) :));
                /*
                n = sizeof(obs);
                for( i=0; i<n; i++ ) {
                        if( to_int(query("mod_level", obs[i])) < to_int(modlevel) )
                                modlevel = query("mod_level", obs[i]); // 获取套装的最低等级
                }
                */

                // 这个等级会变化
                if( !query_temp("modequip_min_level_"+modname, owner) )
                        set_temp("modequip_min_level_"+modname, modlevel, owner); // 套装的最低等级
                if( to_int(modlevel) < to_int(query_temp("modequip_min_level_"+modname, owner)) )
                {
                        set_temp("modequip_min_level_"+modname, modlevel, owner); // 套装的最低等级
                        change = 1;
                }
                else
                        modlevel = query_temp("modequip_min_level_"+modname, owner); // 套装的最低等级

                if( !query_temp("modequip_mark_level_"+modname, owner) )    // 套装的标记等级，以装备的第一件套装等级为标记
                        set_temp("modequip_mark_level_"+modname, modlevel, owner);
        }
        else
                obs = filter_array(inv,
                        (: query("equipped", $1) && query("mod_name", $1) == $(modname) &&
                           query("mod_level", $1) == $(modlevel) && !$1->is_item_make() :));

        n = sizeof(obs); // 装备的套装件数
        mod_stats = new(class eqmodule);
        // 读取套装资料
        mod_stats = load_module(modlevel);
        // 检查合法性
        if( !valid_module(mod_stats) )
                return;

        bas = mod_stats->bas;
        num = mod_stats->num;

        // 自造的绿化的时候用base_name作为mark，掉落的用部件序号作为mark
        file = query("mod_mark", ob);
        name = query("name", ob);

        if( ob->is_item_make() )
                mark_level = query_temp("modequip_mark_level_"+modname, owner);
        else
                mark_level = modlevel;

        // 标记套装组件
        modparts=query_temp("modparts_"+mark_level+"_"+modname, owner);
        if( !mapp(modparts) || !sizeof(modparts) ) modparts = ([]);
        modparts[file] = name; 
        set_temp("modparts_"+mark_level+"_"+modname, modparts, owner);

        // 标记套装件数
        addn_temp("modamount_"+mark_level+"_"+modname, 1, owner);

        // 装备的套装设置标记
        set_temp("mod_equip", 1, ob);

        if( n < bas-1 ) return; // 小于最少激活套装数量，无法激活套装属性
        else if( n == bas-1 )
        {
                // 加上正在装备的ob，正好激活套装属性
                mod_stats->mod_name = modname;  // 自造套装名称不是一样
                if( ob->is_item_make() )        // 补充套装的部件资料
                        mod_stats->mod_parts = ([ file : name ]);

                set_temp("mod_active", 1, ob);  // look时候颜色变化
                stats = copy(query("enchase/mod_prop", ob));  // 绿化时候拥有的属性同时激活
                if( !sizeof(stats) ) stats = ([]);
                for( i=0; i<n; i++ ) {
                        if( ob->is_item_make() )
                        {
                                data = copy(mod_stats->mod_parts);
                                data[query("mod_mark", obs[i])] = obs[i]->name(1);
                                mod_stats->mod_parts = copy(data);
                        }

                        set_temp("mod_active", 1, obs[i]);  // look时候颜色变化
                        prop = copy(query("enchase/mod_prop", obs[i]));
                        if( !sizeof(prop) ) continue;
                        apply = keys(prop);
                        for( j=0; j<sizeof(apply); j++ ) {
                                if( undefinedp(stats[apply[j]]) )
                                        stats[apply[j]] = prop[apply[j]];
                                else
                                        stats[apply[j]] += prop[apply[j]];
                        }
                }
                if( sizeof(stats) )
                        mod_stats->add_prop = copy(stats); // 套装补充属性

                set_temp("modequip_"+mark_level+"_"+modname+"_stats", mod_stats, owner);  // 玩家身上标记套装属性
                set_temp("modequip_"+mark_level+"_"+modname+"_name", modname, owner);     // 玩家身上标记已经激活的套装名称

                if( sizeof(stats) ) apply = keys(stats);
                else apply = ({});
                applied_prop = query_temp("apply", owner);
                if( !mapp(applied_prop) )
                        applied_prop = ([]);
                for( i = 0; i<sizeof(apply); i++ )
                {
                        if (apply[i] == "int" || apply[i] == "str" ||
                            apply[i] == "con" || apply[i] == "add_skill" ||
                            apply[i] == "max_qi" || apply[i] == "max_jing")
                                flag = 1;

                        if( undefinedp(applied_prop[apply[i]]) )
                                applied_prop[apply[i]] = stats[apply[i]];
                        else
                                applied_prop[apply[i]] += stats[apply[i]];
                }

                stats = copy(mod_stats->bas_prop); // 套装基本属性
                apply = keys(stats);
                for( i = 0; i<sizeof(apply); i++ )
                {
                        if (apply[i] == "int" || apply[i] == "str" ||
                            apply[i] == "con" || apply[i] == "add_skill" ||
                            apply[i] == "max_qi" || apply[i] == "max_jing")
                                flag = 1;

                        if( undefinedp(applied_prop[apply[i]]) )
                                applied_prop[apply[i]] = stats[apply[i]];
                        else
                                applied_prop[apply[i]] += stats[apply[i]];
                }

                set_temp("apply", applied_prop, owner); // 套装基本属性及补充属性生效
                if( flag ) CHAR_D->setup_char(owner);
                return;
        }
        else if( n == num-1 )
        {
                if( !classp(tmp_stats = copy(query_temp("modequip_"+mark_level+"_"+modname+"_stats", owner))) ||
                    !query_temp("modequip_"+mark_level+"_"+modname+"_name", owner) )
                        error("套装属性出现混乱，请立刻提交bug给admin。\n");

                // 套装全齐了
                mod_stats->mod_name = modname;  // 自造套装名称不是一样
                if( ob->is_item_make() )
                {
                        data = copy(tmp_stats->mod_parts);
                        data[file] = name;
                        mod_stats->mod_parts = copy(data);
                }

                set_temp("mod_active", 1, ob);

                applied_prop=query_temp("apply", owner);
                if( !mapp(applied_prop) )
                        applied_prop = ([]);

                stats = copy(tmp_stats->add_prop);
                if( !sizeof(stats) ) stats = ([]);
                prop = copy(query("enchase/mod_prop", ob)); // 套装补充属性
                if( sizeof(prop) )
                {
                        apply = keys(prop);
                        for( i=0; i<sizeof(apply); i++ ) {
                                if (apply[i] == "int" || apply[i] == "str" ||
                                    apply[i] == "con" || apply[i] == "add_skill" ||
                                    apply[i] == "max_qi" || apply[i] == "max_jing")
                                        flag = 1;

                                if( undefinedp(applied_prop[apply[i]]) )
                                        applied_prop[apply[i]] = prop[apply[i]];
                                else
                                        applied_prop[apply[i]] += prop[apply[i]];

                                if( undefinedp(stats[apply[i]]) )
                                        stats[apply[i]] = prop[apply[i]];
                                else
                                        stats[apply[i]] += prop[apply[i]];
                        }
                }
                if( sizeof(stats) )
                        mod_stats->add_prop = copy(stats); // 套装补充属性

                set_temp("modequip_"+mark_level+"_"+modname+"_stats", mod_stats, owner);  // 玩家身上标记套装属性
                set_temp("modequip_"+mark_level+"_"+modname+"_name", modname, owner);     // 玩家身上标记已经激活的套装名称
                if( ob->is_item_make() )
                        set_temp("modequip_itemmake_level", to_int(modlevel), owner);     // 玩家身上标记全套的自造套装等级

                if( change )
                {
                        stats = copy(tmp_stats->bas_prop); // 由于可套装等级变化，套装基本属性会变化，先去除原有的
                        apply = keys(stats);
                        for( i=0; i<sizeof(apply); i++ ) {
                                if (apply[i] == "int" || apply[i] == "str" ||
                                    apply[i] == "con" || apply[i] == "add_skill" ||
                                    apply[i] == "max_qi" || apply[i] == "max_jing")
                                        flag = 1;

                                applied_prop[apply[i]] -= stats[apply[i]];
                        }

                        stats = copy(mod_stats->bas_prop); // 套装基本属性
                        apply = keys(stats);
                        for( i = 0; i<sizeof(apply); i++ )
                        {
                                if (apply[i] == "int" || apply[i] == "str" ||
                                    apply[i] == "con" || apply[i] == "add_skill" ||
                                    apply[i] == "max_qi" || apply[i] == "max_jing")
                                        flag = 1;

                                if( undefinedp(applied_prop[apply[i]]) )
                                        applied_prop[apply[i]] = stats[apply[i]];
                                else
                                        applied_prop[apply[i]] += stats[apply[i]];
                        }
                }
                stats = copy(mod_stats->adv_prop);      // 套装高级属性
                apply = keys(stats);
                for( i = 0; i<sizeof(apply); i++ )
                {
                        if (apply[i] == "int" || apply[i] == "str" ||
                            apply[i] == "con" || apply[i] == "add_skill" ||
                            apply[i] == "max_qi" || apply[i] == "max_jing")
                                flag = 1;

                        if( undefinedp(applied_prop[apply[i]]) )
                                applied_prop[apply[i]] = stats[apply[i]];
                        else
                                applied_prop[apply[i]] += stats[apply[i]];
                }

                set_temp("apply", applied_prop, owner);
                if( flag ) CHAR_D->setup_char(owner);
                return;
        }
        else
        {
                // 已经激活套装属性，附加新的套装单件属性
                // 首先检查已经激活的套装属性是否出了问题
                if( !classp(tmp_stats = copy(query_temp("modequip_"+mark_level+"_"+modname+"_stats", owner))) ||
                    !query_temp("modequip_"+mark_level+"_"+modname+"_name", owner) )
                        error("套装属性出现混乱，请立刻提交bug给admin。\n");

                mod_stats->mod_name = modname;  // 自造套装名称不是一样

                if( ob->is_item_make() )
                {
                        data = copy(tmp_stats->mod_parts);
                        data[file] = name;
                        mod_stats->mod_parts = copy(data);
                }

                set_temp("mod_active", 1, ob);

                applied_prop=query_temp("apply", owner);
                if( !mapp(applied_prop) )
                        applied_prop = ([]);

                stats = copy(tmp_stats->add_prop);
                if( !sizeof(stats) ) stats = ([]);
                prop = copy(query("enchase/mod_prop", ob)); // 套装补充属性
                if( sizeof(prop) )
                {
                        apply = keys(prop);
                        for( i=0; i<sizeof(apply); i++ ) {
                                if (apply[i] == "int" || apply[i] == "str" ||
                                    apply[i] == "con" || apply[i] == "add_skill" ||
                                    apply[i] == "max_qi" || apply[i] == "max_jing")
                                        flag = 1;

                                if( undefinedp(applied_prop[apply[i]]) )
                                        applied_prop[apply[i]] = prop[apply[i]];
                                else
                                        applied_prop[apply[i]] += prop[apply[i]];

                                if( undefinedp(stats[apply[i]]) )
                                        stats[apply[i]] = prop[apply[i]];
                                else
                                        stats[apply[i]] += prop[apply[i]];
                        }
                }
                if( sizeof(stats) )
                        mod_stats->add_prop = copy(stats); // 套装补充属性

                set_temp("modequip_"+mark_level+"_"+modname+"_stats", mod_stats, owner);  // 玩家身上标记套装属性
                set_temp("modequip_"+mark_level+"_"+modname+"_name", modname, owner);     // 玩家身上标记已经激活的套装名称

                if( change )
                {
                        stats = copy(tmp_stats->bas_prop); // 由于可套装等级变化，套装基本属性会变化，先去除原有的
                        apply = keys(stats);
                        for( i=0; i<sizeof(apply); i++ ) {
                                if (apply[i] == "int" || apply[i] == "str" ||
                                    apply[i] == "con" || apply[i] == "add_skill" ||
                                    apply[i] == "max_qi" || apply[i] == "max_jing")
                                        flag = 1;

                                applied_prop[apply[i]] -= stats[apply[i]];
                        }

                        stats = copy(mod_stats->bas_prop); // 套装基本属性
                        apply = keys(stats);
                        for( i = 0; i<sizeof(apply); i++ )
                        {
                                if (apply[i] == "int" || apply[i] == "str" ||
                                    apply[i] == "con" || apply[i] == "add_skill" ||
                                    apply[i] == "max_qi" || apply[i] == "max_jing")
                                        flag = 1;

                                if( undefinedp(applied_prop[apply[i]]) )
                                        applied_prop[apply[i]] = stats[apply[i]];
                                else
                                        applied_prop[apply[i]] += stats[apply[i]];
                        }
                }

                set_temp("apply", applied_prop, owner);
                if( flag ) CHAR_D->setup_char(owner);
                return;
        }
}


// 卸下套装部件
// ob套装部件 owner装备者
void unequip_module(object ob, object owner)
{
        class eqmodule mod_stats;
        class eqmodule tmp_stats;
        mapping data, stats, prop, applied_prop;
        mapping modparts;
        string *apply;
        string modname;
        string modlevel, mark_level, file, name;
        object *inv, *obs;
        int i, j, n, flag = 0;
        int bas, num, change = 0;

        if( ob->is_item_make() ) {
                if( ob->item_owner() != query("id", owner) )
                        return;
        }

        modlevel = query("mod_level", ob);
        modname = query("mod_name", ob);
        mod_stats = new(class eqmodule);

        inv = all_inventory(owner);
        if( ob->is_item_make() )        // 检查套装部件
        {
                obs = filter_array(inv,
                        (: query("equipped", $1) && query("mod_name", $1) == $(modname) &&
                           $1->is_item_make() && $1->item_owner() == $(query("id", owner)) :));

                modlevel = query_temp("modequip_min_level_"+modname, owner); // 套装的最低等级
                if( query("mod_level", ob) == modlevel ) // 套装等级可能会变化
                {
                        modlevel = "4";
                        n = sizeof(obs);
                        for( i=0; i<n; i++ ) {
                                if( obs[i] == ob ) continue;
                                if( to_int(query("mod_level", obs[i])) < to_int(modlevel) )
                                        modlevel = query("mod_level", obs[i]); // 获取套装的最低等级
                        }
                        set_temp("modequip_min_level_"+modname, modlevel, owner); // 套装的最低等级
                        if( modlevel != query("mod_level", ob) )
                                change = 1;
                }
                if( !modlevel ) modlevel = query("mod_level", ob);

        }
        else
                obs = filter_array(inv,
                        (: query("equipped", $1) && query("mod_name", $1) == $(modname) &&
                           query("mod_level", $1) == $(modlevel) && !$1->is_item_make() :));

        n = sizeof(obs);
        mod_stats = new(class eqmodule);
        // 读取套装资料
        mod_stats = load_module(modlevel);
        // 检查合法性
        if( !valid_module(mod_stats) )
                return;

        // 检查套装部件ob是否是套装里的一件
        file = query("mod_mark", ob);
        name = query("name", ob);

        if( ob->is_item_make() )
                mark_level = query_temp("modequip_mark_level_"+modname, owner);
        else
                mark_level = modlevel;

        // 标记套装文件
        modparts=query_temp("modparts_"+mark_level+"_"+modname, owner);
        if( !mapp(modparts) || !sizeof(modparts) )
                modparts = ([]);
        
        map_delete(modparts, file);
        set_temp("modparts_"+mark_level+"_"+modname, modparts, owner);

        if( ob->is_item_make() && !sizeof(modparts) )
        {
                delete_temp("modequip_min_level_"+modname, owner);
                delete_temp("modequip_mark_level_"+modname, owner);
        }

        // 标记套装件数
        addn_temp("modamount_"+mark_level+"_"+modname, -1, owner);
        if( query_temp("modamount_"+mark_level+"_"+modname, owner)<0 )
                delete_temp("modamount_"+mark_level+"_"+modname, owner);

        // 删除装备套装部件标记
        delete_temp("mod_equip", ob);
        delete_temp("mod_active", ob); // look时候显示mod_prop颜色变化

        /*
        if( query_temp("modamount_"+mark_level+"_"+modname, owner) != n )
                error("套装装备件数出现混乱，请立刻提交bug给admin。\n");
        */

        bas = mod_stats->bas;
        num = mod_stats->num;

        // 如果onwer身上装备的套装件数+1未达到套装激活件数时，
        // 因为没附加过套装属性，所以不需要执行删除onwer套装属性
        if( n < bas ) return;
        else if( n == bas ) {
                if( !classp(tmp_stats = copy(query_temp("modequip_"+mark_level+"_"+modname+"_stats", owner))) ||
                    !query_temp("modequip_"+mark_level+"_"+modname+"_name", owner) )
                        error("套装属性出现混乱，请立刻提交bug给admin。\n");

                // 正好bas件，卸下套装部件，则消除套装的所有补充属性和基本属性
                for( i=0; i<sizeof(obs); i++ )
                {
                        if( obs[i] == ob ) continue;
                        delete_temp("mod_equip", obs[i]);   // 取消装备标记
                        delete_temp("mod_active", obs[i]);  // 取消激活标记
                }

                applied_prop = query_temp("apply", owner);
                stats = copy(tmp_stats->add_prop); // 补充属性
                apply = keys(stats);
                for( i=0; i<sizeof(apply); i++ ) {
                        if (apply[i] == "int" || apply[i] == "str" ||
                            apply[i] == "con" || apply[i] == "add_skill" ||
                            apply[i] == "max_qi" || apply[i] == "max_jing")
                                flag = 1;

                        applied_prop[apply[i]] -= stats[apply[i]];
                }

                stats = copy(tmp_stats->bas_prop); // 基本属性
                apply = keys(stats);
                for( i=0; i<sizeof(apply); i++ ) {
                        if (apply[i] == "int" || apply[i] == "str" ||
                            apply[i] == "con" || apply[i] == "add_skill" ||
                            apply[i] == "max_qi" || apply[i] == "max_jing")
                                flag = 1;

                        applied_prop[apply[i]] -= stats[apply[i]];
                }

                delete_temp("modequip_"+mark_level+"_"+modname+"_stats", owner);
                delete_temp("modequip_"+mark_level+"_"+modname+"_name", owner);

                set_temp("apply", applied_prop, owner);
                if (flag) CHAR_D->setup_char(owner);
                return;
        }
        else if( n == num ) {
                if( !classp(tmp_stats = copy(query_temp("modequip_"+mark_level+"_"+modname+"_stats", owner))) ||
                    !query_temp("modequip_"+mark_level+"_"+modname+"_name", owner) )
                        error("套装属性出现混乱，请立刻提交bug给admin。\n");
                
                mod_stats->mod_name = modname;  // 自造套装名称不是一样
                if( ob->is_item_make() )
                {
                        data = copy(tmp_stats->mod_parts);
                        map_delete(data, file);
                        mod_stats->mod_parts = copy(data);
                }
                // 取消套装的部件补充属性及套装高级属性
                applied_prop = query_temp("apply", owner);
                stats = copy(tmp_stats->add_prop);
                prop = copy(query("enchase/mod_prop", ob)); // 套装补充属性
                if( sizeof(prop) )
                {
                        apply = keys(prop);
                        for( i=0; i<sizeof(apply); i++ ) {
                                if (apply[i] == "int" || apply[i] == "str" ||
                                    apply[i] == "con" || apply[i] == "add_skill" ||
                                    apply[i] == "max_qi" || apply[i] == "max_jing")
                                        flag = 1;

                                applied_prop[apply[i]] -= prop[apply[i]];
                                stats[apply[i]] -= prop[apply[i]];
                        }
                        mod_stats->add_prop = copy(stats);
                }

                set_temp("modequip_"+mark_level+"_"+modname+"_stats", mod_stats, owner);
                if( ob->is_item_make() )
                        delete_temp("modequip_itemmake_level", owner); // 删除套装等级，suit special调用

                stats = copy(tmp_stats->adv_prop);      // 套装高级属性
                apply = keys(stats);
                for( i = 0; i<sizeof(apply); i++ )
                {
                        if (apply[i] == "int" || apply[i] == "str" ||
                            apply[i] == "con" || apply[i] == "add_skill" ||
                            apply[i] == "max_qi" || apply[i] == "max_jing")
                                flag = 1;

                        applied_prop[apply[i]] -= stats[apply[i]];
                }
                if( change )
                {
                        stats = copy(tmp_stats->bas_prop); // 由于可套装等级变化，套装基本属性会变化，先去除原有的
                        apply = keys(stats);
                        for( i=0; i<sizeof(apply); i++ ) {
                                if (apply[i] == "int" || apply[i] == "str" ||
                                    apply[i] == "con" || apply[i] == "add_skill" ||
                                    apply[i] == "max_qi" || apply[i] == "max_jing")
                                        flag = 1;

                                applied_prop[apply[i]] -= stats[apply[i]];
                        }

                        stats = copy(mod_stats->bas_prop); // 套装基本属性
                        apply = keys(stats);
                        for( i = 0; i<sizeof(apply); i++ )
                        {
                                if (apply[i] == "int" || apply[i] == "str" ||
                                    apply[i] == "con" || apply[i] == "add_skill" ||
                                    apply[i] == "max_qi" || apply[i] == "max_jing")
                                        flag = 1;

                                if( undefinedp(applied_prop[apply[i]]) )
                                        applied_prop[apply[i]] = stats[apply[i]];
                                else
                                        applied_prop[apply[i]] += stats[apply[i]];
                        }
                }

                set_temp("apply", applied_prop, owner);
                if( flag ) CHAR_D->setup_char(owner);
                return;
        }
        else
        {
                if( !classp(tmp_stats = copy(query_temp("modequip_"+mark_level+"_"+modname+"_stats", owner))) ||
                    !query_temp("modequip_"+mark_level+"_"+modname+"_name", owner) )
                        error("套装属性出现混乱，请立刻提交bug给admin。\n");
                
                mod_stats->mod_name = modname;  // 自造套装名称不是一样
                if( ob->is_item_make() )
                {
                        data = copy(tmp_stats->mod_parts);
                        map_delete(data, file);
                        mod_stats->mod_parts = copy(data);
                }
                // 仅仅取消套装部件的补充属性
                applied_prop = query_temp("apply", owner);
                stats = copy(tmp_stats->add_prop);
                prop = copy(query("enchase/mod_prop", ob)); // 套装补充属性
                if( sizeof(prop) )
                {
                        apply = keys(prop);
                        for( i=0; i<sizeof(apply); i++ ) {
                                if (apply[i] == "int" || apply[i] == "str" ||
                                    apply[i] == "con" || apply[i] == "add_skill" ||
                                    apply[i] == "max_qi" || apply[i] == "max_jing")
                                        flag = 1;

                                applied_prop[apply[i]] -= prop[apply[i]];
                                stats[apply[i]] -= prop[apply[i]];
                        }
                        mod_stats->add_prop = copy(stats);
                }

                set_temp("modequip_"+mark_level+"_"+modname+"_stats", mod_stats, owner);

                if( change )
                {
                        stats = copy(tmp_stats->bas_prop); // 由于可套装等级变化，套装基本属性会变化，先去除原有的
                        apply = keys(stats);
                        for( i=0; i<sizeof(apply); i++ ) {
                                if (apply[i] == "int" || apply[i] == "str" ||
                                    apply[i] == "con" || apply[i] == "add_skill" ||
                                    apply[i] == "max_qi" || apply[i] == "max_jing")
                                        flag = 1;

                                applied_prop[apply[i]] -= stats[apply[i]];
                        }

                        stats = copy(mod_stats->bas_prop); // 套装基本属性
                        apply = keys(stats);
                        for( i = 0; i<sizeof(apply); i++ )
                        {
                                if (apply[i] == "int" || apply[i] == "str" ||
                                    apply[i] == "con" || apply[i] == "add_skill" ||
                                    apply[i] == "max_qi" || apply[i] == "max_jing")
                                        flag = 1;

                                if( undefinedp(applied_prop[apply[i]]) )
                                        applied_prop[apply[i]] = stats[apply[i]];
                                else
                                        applied_prop[apply[i]] += stats[apply[i]];
                        }
                }
                set_temp("apply", applied_prop, owner);
                if (flag) CHAR_D->setup_char(owner);
                return;
        }
}

// 移除套装特技效果
void remove_effect(object me, string name, int level)
{
        int i;
        string *jifa_list;

        if( query_temp("suit_special", me) )
        {
                delete_temp("suit_special");
                jifa_list = query_temp("suit/jifa_list", me);
                if( sizeof(jifa_list) )
                {
                        for (i = 0; i < sizeof(jifa_list); i ++)
                        {
                                addn_temp("apply/" + jifa_list[i], -1 * level, me);
                        }
                }
                delete_temp("suit/jifa_list", me);
                tell_object(me, HIC "你的套装特技" + name + HIC "运行完毕！\n");
                return;
        }
}

void remove_effect2(object me, string name, int damage, int armor)
{
        if( query_temp("suit_defense", me) )
        {
                addn_temp("apply/damage", -1 * damage, me);
                addn_temp("apply/armor", -1 * armor, me);

                delete_temp("suit_defense", me);
                tell_object(me, HIC "你的套装特技" + name + HIC "运行完毕！\n");
                return;
        }
}

// 调用来自 /cmds/std/suit.c 使用套装特技
public int suit_special(object me, string arg)
{
        int i;
        mapping jifa_map;
        string *jifa_list;
        int slvl;

        slvl = query_temp("modequip_itemmake_level", me);

        /*
        并额外附加套装特技 星辰之力(stars)。施展(special stars <项目>)
        后可提升下列某项状态 50% ，并持续 10 分钟。
        无视攻击、无视躲闪、无视招架、无视内功、抗毒效果、毒素伤害
        虚弱对手、解封绝招、绝招伤害、绝招命中、双倍伤害、
        化解伤害、抵抗虚弱、封存绝招、绝招防御、研究效果、汲取效果
        */


        if( slvl < 2 )
        {
                return notify_fail("你目前的套装等级不够，无法使用套装特技！\n");
        }

        sscanf(arg, "special %s", arg);
        if (slvl == 2)
        {
                if( arg != "changying" )
                        return notify_fail("你目前不具备该套装特技！\n");

                if( query_temp("suit_special", me) )
                        return notify_fail("你现在正在运用此类特技中，请稍后再使用。\n");

                if( query("neili", me) < query("max_neili", me))
                        return notify_fail("你的剩余内力不足，无法施展套装绝技。\n");
                set("neili", 0, me);

                message_combatd(HIC "$N一声长吟，全身装备刹那间流光异彩，将其笼罩！\n" NOR, me);
                set_temp("suit_special", 100, me);

                jifa_list = ({});
                jifa_map = me->query_skill_map();
                if( sizeof(jifa_map) )
                {
                        jifa_list = keys(jifa_map);

                        set_temp("suit/jifa_list", jifa_list, me);
                        for (i = 0; i < sizeof(jifa_list);i ++)
                        {
                                addn_temp("apply/" + jifa_list[i], 200, me);
                        }
                }

                me->start_call_out((: call_other,  __FILE__, "remove_effect", me, HIC "长吟" NOR, 200 :), 300);
                return 1;
        }

        if( slvl == 3 )
        {
                if( arg != "zongheng" && arg != "tianzhidao" )
                        return notify_fail("你目前不具备该套装特技！\n");

                if( arg == "tianzhidao" )
                {
                        if( me->query_temp("suit_special") )
                                return notify_fail("你现在正在运用此类特技中，请稍后再使用。\n");

                        if( query("neili", me) < query("max_neili", me))
                                return notify_fail("你的剩余内力不足，无法施展套装绝技。\n");
                        set("neili", 0, me);

                        message_combatd(HIG "$N施展出套装绝技「天之道」，瞬间全身泛出金色光芒！\n" NOR, me);
                        set_temp("suit_special", 150, me);

                        jifa_list = ({});
                        jifa_map = me->query_skill_map();
                        if( sizeof(jifa_map) )
                        {
                                jifa_list = keys(jifa_map);

                                set_temp("suit/jifa_list", jifa_list, me);
                                for (i = 0; i < sizeof(jifa_list);i ++)
                                {
                                        addn_temp("apply/" + jifa_list[i], 400, me);
                                }
                        }
                        me->start_call_out((: call_other,  __FILE__, "remove_effect", me, HIG "天之道" NOR, 400:), 600);
                        return 1;
                }
                if( arg == "zongheng" )
                {
                        if( query_temp("suit_defense", me) )
                                return notify_fail("你现在正在运用此类特技中，请稍后再使用。\n");

                        if( query("neili", me) < query("max_neili", me))
                                return notify_fail("你的剩余内力不足，无法施展套装绝技。\n");
                        set("neili", 0, me);

                        message_combatd(HIG "$N施展出套装绝技「纵横」，两道金光一纵一横从天际掠过，旋转于$N四周！\n" NOR, me);
                        set_temp("suit_defense", 1, me);
                        addn_temp("apply/damage", 10000, me);
                        addn_temp("apply/armor", 5000, me);

                        me->start_call_out((: call_other,  __FILE__, "remove_effect2", me, HIG "天之道" NOR, 10000, 5000 :), 300);
                        return 1;
                }
        }

        if( slvl == 4 )
        {
                if (arg != "juedai" && arg != "tianjiao")
                        return notify_fail("你目前不具备该套装特技！\n");

                if (arg == "tianjiao")
                {
                        if( query_temp("suit_special", me) )
                                return notify_fail("你现在正在运用此类特技中，请稍后再使用。\n");

                        if( query("neili", me) < query("max_neili", me))
                                return notify_fail("你的剩余内力不足，无法施展套装绝技。\n");
                        set("neili", 0, me);

                        message_combatd(HIM "$N负手而力，衣裳无风而动，口中念念有词，「天驕之魂」已然迸发而出！\n" NOR, me);
                        set_temp("suit_special", 200, me);

                        jifa_list = ({});
                        jifa_map = me->query_skill_map();
                        if( sizeof(jifa_map) )
                        {
                                jifa_list = keys(jifa_map);

                                set_temp("suit/jifa_list", jifa_list, me);
                                for (i = 0; i < sizeof(jifa_list);i ++)
                                {
                                        addn_temp("apply/" + jifa_list[i], 600, me);
                                }
                        }

                        me->start_call_out((: call_other,  __FILE__, "remove_effect", me, HIM "天驕之魂" NOR, 600 :), 900);
                        return 1;
                }
                if( arg == "juedai" )
                {
                        if( query_temp("suit_defense", me) )
                                return notify_fail("你现在正在运用此类特技中，请稍后再使用。\n");

                        if( query("neili", me) < query("max_neili", me))
                                return notify_fail("你的剩余内力不足，无法施展套装绝技。\n");
                        set("neili", 0, me);

                        message_combatd(HIM "$N目光如炬，浑身紫光闪现，令人不寒而栗，实乃一代天驕，无与抗衡！\n" NOR, me);
                        set_temp("suit_defense", 1, me);
                        addn_temp("apply/damage", 15000, me);
                        addn_temp("apply/armor", 10000, me);

                        me->start_call_out((: call_other,  __FILE__, "remove_effect2", me, HIM "絕代天驕" NOR, 15000, 10000 :), 600);
                        return 1;
                }
        }

        if( slvl == 5 )
        {
                if( arg != "zhanws1" && arg != "zhanws2" )
                        return notify_fail("你目前不具备该套装特技！\n");

                if( arg == "zhanws2" )
                {
                        if( query_temp("suit_special", me) )
                                return notify_fail("你现在正在运用此类特技中，请稍后再使用。\n");

                        if( query("neili", me) < query("max_neili", me))
                                return notify_fail("你的剩余内力不足，无法施展套装绝技。\n");
                        set("neili", 0, me);

                        message_combatd(HIR "$N举头望天，悠然一声长叹，忽然全身被红色的光芒包裹，杀气骤现！\n" NOR, me);
                        set_temp("suit_special", 300, me);

                        jifa_list = ({});
                        jifa_map = me->query_skill_map();
                        if( sizeof(jifa_map) )
                        {
                                jifa_list = keys(jifa_map);

                                set_temp("suit/jifa_list", jifa_list, me);
                                for (i = 0; i < sizeof(jifa_list);i ++)
                                {
                                        addn_temp("apply/" + jifa_list[i], 1000, me);
                                }
                        }
                        me->start_call_out((: call_other,  __FILE__, "remove_effect", me, HIR "斬·無雙" NOR, 1000 :), 1800);
                        return 1;
                }
                if( arg == "zhanws1" )
                {
                        if( query_temp("suit_defense", me) )
                                return notify_fail("你现在正在运用此类特技中，请稍后再使用。\n");

                        if( query("neili", me) < query("max_neili", me))
                                return notify_fail("你的剩余内力不足，无法施展套装绝技。\n");
                        set("neili", 0, me);

                        message_combatd(HIR "$N长啸一声，轻抚全身装备，所过之处泛出红色血芒，令人心胆具寒。\n" NOR, me);
                        set_temp("suit_defense", 1, me);
                        addn_temp("apply/damage", 20000, me);
                        addn_temp("apply/armor", 10000, me);

                        me->start_call_out((: call_other,  __FILE__, "remove_effect2", me, HIR "戰·無雙" NOR, 20000, 10000 :), 1200);
                        return 1;
                }
        }

        return 1;
}
