<?php
/**
 * Вызывает $callback для каждого элемента(кроме списка $exclude) в $dirname
 *
 * @param $dirname string directory for scan
 * @param $callback callable callback
 * @param $exclude array list to exclude
 */
function dir_foreach($dirname, $callback, $exclude = []) {
    $dh = opendir($dirname);
    /* @var string $f_name */
    while (($f_name = readdir($dh)) !== false) {
        if(!in_array($f_name, $exclude)) {
            $callback($f_name);
        }
    }
    closedir($dh);
}