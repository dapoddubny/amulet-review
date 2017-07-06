<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global loc_t
 * @global loc_tt
 * @global game
 * @global sid
 * @global PHP_SELF
 * @global char
 * @global cost
 * @global locai
 * @global tchar
 * @global g_list
 * @global trader
 * @global skill
 * @global min
 * @global max
 */

// магия
// проверки
if (strpos($loc_i[$loc][$login]["magic"], $skill . ":") !== false) {
    msg("<p>У вас уже есть это заклинание", $tchar[0]);
}
if ($min) {
    if ($skills[13] < $min) {
        msg("<p>У вас недостаточный навык магии (надо минимум " . $min . ")", $tchar[0]);
    }
}
if ($max) {
    if ($skills[13] > $max) {
        msg("<p>У вас слишком высокий навык магии (максимум " . $max . ")", $tchar[0]);
    }
}
if ($cost) {
    $money = intval(preg_replace('/.*i\.money:(\d+).*/', "\\1", $loc_i[$loc][$login]["items"]));
    if ($money < $cost) {
        msg("<p>У вас недостаточно денег (надо " . $cost . " монет)", $tchar[0]);
    }
    additem($loc, $login, "", "i.money", $cost, "items", "items", 1, -1, 1);
}
if ( ! $loc_i[$loc][$login]["magic"]) {
    $loc_i[$loc][$login]["magic"] = $skill . ":1";
} else {
    $loc_i[$loc][$login]["magic"] .= "|" . $skill . ":1";
}
msg("<p>Вы выучили новое заклинание!", $tchar[0]);