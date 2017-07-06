<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global loc_t
 * @global loc_tt
 * @global locai
 * @global game
 * @global sid
 * @global PHP_SELF
 * @global char
 * @global id
 * @global tchar
 * @global i
 * @global j
 */
// обработка подчиненных npc
$owner = explode("|", $loc_i[$i][$j]["owner"]);
// хозяин крима крим
if ($char[9] && isset($loc_i[$i][$owner[0]])) {
    docrim($i, $owner[0]);
}
if ( ! isset($owner[0])) {
    $owner[0] = "";
}
if ( ! isset($owner[1])) {
    $owner[1] = "";
}
if ( ! isset($owner[2])) {
    $owner[2] = "";
}
if ( ! isset($owner[3])) {
    $owner[3] = "";
}
if ( ! isset($owner[4])) {
    $owner[4] = "";
}
if ( ! isset($owner[5])) {
    $owner[5] = time() + 60 * 60;
}

$b = 0;
// вышло время
if ($owner[3] && time() > $owner[3] || time() > $owner[5] && substr($i, 0, 2) != "c.") {
    $b = 1;
    unset($loc_i[$i][$j]["owner"]);
    addjournal($loc, $owner[0], $char[0] . " покинул вас");
    if ($owner[6]) {
        addnpc($j, $i, $owner[6]);
    } else {
        $ttw = explode("|", $loc_i[$i][$j]["war"]);
        if ($ttw[15]) {
            $ttwr = explode(":", $ttw[15]);
            addnpc($j, $i, $ttwr[0]);
        } else {
            addnpc($j, $i);
        }
    }
}
// heal
if (substr($j, 0, 5) == "n.he." && time() > $loc_i[$loc][$j]["h_t"] && isset($loc_i[$loc][$owner[0]])) {
    $tc = explode("|", $loc_i[$loc][$owner[0]]["char"]);
    if ($tc[1] < $tc[2]) {
        addjournal($loc, "all", substr($loc_i[$loc][$j]["char"], 0, strpos($loc_i[$loc][$j]["char"], "|")) . ": " .
                                $loc_i[$loc][$j]["h_s"]);
        $tc[1] += rand($loc_i[$loc][$j]["h_v1"], $loc_i[$loc][$j]["h_v2"]);
        $htmp = rand($loc_i[$loc][$j]["h_v1"], $loc_i[$loc][$j]["h_v2"]);
        addjournal($loc, $owner[0], $tchar[0] . ": жизнь +" . $htmp);
        if ($tc[1] > $tc[2]) {
            $tc[1] = $tc[2];
        }
        $loc_i[$loc][$owner[0]]["char"] = implode("|", $tc);
        $loc_i[$loc][$j]["h_t"]         = time() + $loc_i[$loc][$j]["h_p"];
    }
}
if ( ! $b) {
    // следуем
    if ($owner[1] && ! isset($loc_i[$i][$owner[1]])) {
        for ($k = 3; $k < count($locai); $k += 2) {
            if (isset($loc_i[$locai[$k]][$owner[1]])) {
                $bc = 1;
                if (substr($j, 0, 4) == "n.o.") {
                    if (substr($i, 0, 2) == "c." && substr($i, 3) != ".in") {
                        $bc = 0;
                    }
                    if ($bc && substr($k, 3) != ".in") {
                        $count = 0;
                        if ($loc_i[$locai[$k]]) {
                            foreach (array_keys($loc_i[$locai[$k]]) as $m) {
                                if (substr($m, 0, 4) == "n.o.") {
                                    $count++;
                                }
                            }
                        }
                        if ($count >= 5) {
                            $bc = 0;
                            addjournal($locai[$k], $owner[0],
                                $char[0] . " говорит: я туда не пойду, там и так полно стражников");
                        }
                    }
                }
                if ($bc && substr($owner[1], 0, 2) == "u.") {
                    $tc = explode("|", $loc_i[$locai[$k]][$owner[1]]["char"]);
                    if ($tc[8]) {
                        $bc = 0;
                    }
                }
                if ($bc && substr($j, 0, 4) != "n.o.") {
                    $count = 0;
                    foreach ($loc_i[$locai[$k]] as $jn) {
                        if (isset($jn["owner"]) && strpos($jn["owner"], $owner[1]) !== false) {
                            $count++;
                            if ($count > 3) {
                                $bc = 0;
                                break;
                            }
                        } //не следуют если больше трех
                    }
                }
                if ($bc) {
                    $char[7]               = "";
                    $loc_i[$i][$j]["char"] = implode("|", $char);
                    addnpc($j, $i, $locai[$k]);
                    $char                           = explode("|", $loc_i[$locai[$k]][$j]["char"]);
                    $char[12]                       = "";
                    $loc_i[$locai[$k]][$j]["char"]  = implode("|", $char);
                    $owner[5]                       = time() + 60 * 60;    // 1 час ждет движения
                    $loc_i[$locai[$k]][$j]["owner"] = implode("|", $owner);
                    $b                              = 1;
                    break;
                }
            }
        }
    }
    if ( ! $b) {        //$j не ушел

        // охраняем
        if (substr($j, 0, 4) != "n.o." && $owner[2] && isset($loc_i[$i][$owner[2]])) {
            $k1 = array_keys($loc_i[$i]);
            foreach ($k1 as $k) {
                if ($k != $j && $k != $owner[2] && $k != $owner[0] && $k != $owner[1]) {
                    $ch = explode("|", $loc_i[$i][$k]["char"]);
                    if ($ch[7] == $owner[2] ||
                        substr($loc_i[$loc][$ch[7]]["owner"], 0, strlen($owner[2])) == $owner[2]
                    ) {
                        if ($locai[1] == 1) {
                            $tco = explode("|", $loc_i[$loc][$owner[2]]["char"]);
                            if ($tco[9]) {
                                break;
                            }
                        }
                        $char[7] = $k;
                        break;
                    }
                }
            }
        }
    }
}