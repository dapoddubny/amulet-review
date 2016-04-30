<?php
function alt($s)
{
    global $ttans, $letters;
    if ($ttans) {
        $letters = array("jo" => "ё", "je" => "э", "ju" => "ю", "ja" => "я", "zh" => "ж", "ch" => "ч", "sh" => "ш", "JO" => "Ё", "JE" => "Э", "JU" => "Ю", "JA" => "Я", "ZH" => "Ж", "CH" => "Ч", "SH" => "Ш");
        $s = strtr($s, $letters);
        $s = preg_replace("/(j|J)_(a|A|u|U|o|O|e|E)/", "\\1\\2", $s);
        $s = preg_replace("/(z|Z|c|C|s|S)_(h|H)/", "\\1\\2", $s);
        $s = strtr($s, "wxq'ertyuiopasdfghjklzcvbnmWQXERTYUIOPASDFGHJKLZCVBNM", 'щъььертыуиопасдфгхйклзцвбнмЩЬЪЕРТЫУИОПАСДФГХЙКЛЗЦВБНМ');
    }
    $ttans = !$ttans;
    return $s;
}

function trans($s)
{
    global $ttans;
    $ttans = true;
    return preg_replace("/(.*)##??/Ue", "alt('\\1')", "$s#");
}