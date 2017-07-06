<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global loc_t
 * @global loc_tt
 * @global to
 * @global game
 * @global sid
 * @global PHP_SELF
 * @global char
 * @global id
 * @global skills
 * @global i
 */
// охрана замка
global $lcen;
if (gettype($lcen) != "array") {
    $lcen = [];
    $gate = substr($i, 0, 4) . "gate";
    loadloc($gate);
    $d = explode("|", $loc_tt[$gate]["d"]);
    if (strpos($d[0], "*") !== false) {
        $clanc = substr($d[0], strpos($d[0], "*") + 1, strrpos($d[0], "*") - strpos($d[0], "*") - 1);
        foreach ($loc_i[$i] as $k => $v) {
            if (substr($k, 0, 2) == "u." && strpos($loc_i[$i][$k]["char"], "*" . $clanc . "*") === false &&
                strpos($d[0], ":" . $k . ":") === false
            ) {
                $tct = explode("|", $loc_i[$i][$k]["char"]);
                if ( ! $tct[8]) {
                    $lcen[] = $k;
                }
            }
        }
    }
}
if (count($lcen) > 0) {
    $char[7] = $lcen[rand(0, count($lcen) - 1)];
} 