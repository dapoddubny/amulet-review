<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global loc_t
 * @global loc_tt
 * @global item
 * @global game
 * @global sid
 * @global PHP_SELF
 * @global char
 * @global $look
 */
if (isset($loc_i[$loc][$look])) {
    $char = explode("|", $loc_i[$loc][$look]["char"]);    // для оптимизации
    $stmp = "<p>Тип: ";
    if (substr($look, 0, 9) == 'n.a.losh.') {
        $stmp .= "лошадь, на ней можно ездить, если она принадлежит вам (выберите в меню Говорить, Сесть в седло)";
    } else {
        if (substr($look, 0, 4) == 'n.a.') {
            $stmp .= "животное";
        } else {
            if (substr($look, 0, 4) == 'n.m.') {
                $stmp .= "гном";
            } else {
                if (substr($look, 0, 4) == 'n.w.') {
                    $stmp .= "божественаая личность";
                } else {
                    if (substr($look, 0, 4) == 'n.c.') {
                        $stmp .= "монстр";
                    } else {
                        if (substr($look, 0, 4) == 'n.z.') {
                            $stmp .= "зомби, поднятый из мертвых с помощью некромантии";
                        } else {
                            if (substr($look, 0, 4) == 'n.g.') {
                                $stmp .= "городская стража";
                            } else {
                                if (substr($look, 0, 4) == 'n.s.') {
                                    $stmp .= "призван с помощью магии";
                                } else {
                                    if (substr($look, 0, 4) == 'n.h.') {
                                        $stmp .= "лекарь, может воскрешать мертвых (для этого надо поговорть с ним)";
                                    } else {
                                        $stmp .= "человек";
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (file_exists("speak/" . $look)) {
        $stmp .= "<br/>Может с вами говорить";
    }
    if (substr($look, 0, 4) == 'n.a.' && $char[8]) {
        $stmp .= "<br/><a href=\"$PHP_SELF?sid=$sid&look=char.tame\">Сложность приручения</a>: " . $char[8];
    }

    if ($loc_i[$loc][$look]["owner"]) {
        $owner = explode("|", $loc_i[$loc][$look]["owner"]);
        if (isset($loc_i[$loc][$owner[0]])) {
            $tmp = explode("|", $loc_i[$loc][$owner[0]]["char"]);
            $stmp .= "<br/>Принадлежит " . $tmp[0];
        } else {
            $stmp .= "<br/>Кому-то принадлежит, но хозяина рядом нет";
        }
    }

    // что одето
    if ($loc_i[$loc][$look]["equip"]) {
        $str   = "";
        $sto   = "";
        $equip = explode("|", $loc_i[$loc][$look]["equip"]);
        foreach ($equip as $i) {
            if ($i) {
                if (strpos($i, "_") !== false) {
                    $ti = substr($i, 0, strpos($i, "_"));
                } else {
                    $ti = $i;
                }
                if (file_exists("items/" . $ti)) {
                    $item = explode("|", (file_get_contents("items/" . $ti)));
                    if (substr($i, 0, 4) == "i.a.") {
                        if ( ! $sto) {
                            $sto = $item[0];
                        } else {
                            $sto .= ", " . $item[0];
                        }
                    } else {
                        if ( ! $str) {
                            $str = $item[0];
                        } else {
                            $str .= ", " . $item[0];
                        }
                    }
                } else {
                    die("err: no items/" . $i);
                }
            }
        }
        if ($str) {
            $stmp .= "<br/>Держит в руках: " . $str;
        }
        if ($sto) {
            $stmp .= "<br/>Одет: " . $sto;
        }
    }

    msg($stmp, $char[0]);
} else {
    addjournal($loc, $login, "Не на кого смотреть");
}